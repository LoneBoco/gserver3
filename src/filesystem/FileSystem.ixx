export module graal.filesystem;

import graal.filesystem.watch;
import graal.file;

import "common.h";

import <filesystem>;
import <list>;
import <mutex>;
import <condition_variable>;
import <future>;
import <fstream>;
import <atomic>;


export namespace graal::fs
{

struct FileData
{
	std::filesystem::path File;
	uint32_t CRC32 = 0;
	intmax_t TimeSinceEpoch = 0;
	uintmax_t FileSize = 0;
};

//class File;
class FileSystem
{
private:
	struct FileEntry
	{
		FileEntry(const std::filesystem::path& file) : File(file) {}

		std::filesystem::path File;		// Full path + filename
		std::filesystem::file_time_type ModifiedTime;
		uint32_t CRC32 = 0;
		size_t FileSize = 0;
	};

	using FileEntryPtr = std::unique_ptr<FileEntry, std::default_delete<FileEntry>>;

	struct DirectoryGroup
	{
		std::filesystem::path Directory;
		std::list<std::filesystem::path> ExcludedDirectories;
		std::map<const std::filesystem::path, FileEntryPtr> Files;
	};

#pragma region Headers
public:
	FileSystem() = default;
	~FileSystem() = default;

	FileSystem(const FileSystem& other) = delete;
	FileSystem(FileSystem&& other) = delete;
	FileSystem& operator=(const FileSystem& other) = delete;
	FileSystem& operator=(FileSystem&& other) = delete;
#pragma endregion

	//! Binds to a directory.
	//! \param directory The directory to bind to.
	//! \param exclude_dirs A list of directories to exclude.  Will be pattern matched like *exclude_dir*
	template <typename... Args>
	void Bind(const std::filesystem::path& directory, Args... exclude_dirs)
	{
		std::list<std::filesystem::path> exclude_list;
		buildExclusionList(exclude_list, exclude_dirs...);
		bind(directory, std::move(exclude_list));
	}

	//! Binds to a directory.
	//! \param directory The directory to bind to.
	//! \param exclude_dirs A list of directories to exclude.  Will be pattern matched like *exclude_dir*
	template <typename... Args>
	void BindFront(const std::filesystem::path& directory, Args... exclude_dirs)
	{
		std::list<std::filesystem::path> exclude_list;
		buildExclusionList(exclude_list, exclude_dirs...);
		bind(directory, std::move(exclude_list), true);
	}

	//! Checks if the file exists in the filesystem.
	//! \return Successful if the file exists.
	bool HasFile(const std::filesystem::path& file) const;

	//! Checks if the file exists in the filesystem.
	//! \return Successful if the file exists.
	bool HasFile(const std::filesystem::path& root_dir, const std::filesystem::path& file) const;

	//! Returns information about the file.
	//! \return Information about the file.
	FileData GetFileData(const std::filesystem::path& file) const;

	//! Returns information about the file.
	//! \return Information about the file.
	FileData GetFileData(const std::filesystem::path& root_dir, const std::filesystem::path& file) const;

	//! Gets a file by name.
	//! \return A shared pointer to the file.
	std::shared_ptr<File> GetFile(const std::filesystem::path& file) const;

	//! Gets a file by name.
	//! \return A shared pointer to the file.
	std::shared_ptr<File> GetFile(const std::filesystem::path& root_dir, const std::filesystem::path& file) const;

	//! Gets the full path to a file by name.
	//! \return The full path to a file.
	std::filesystem::path GetFilePath(const std::filesystem::path& file) const;

	//! Gets the full path to a file by name.
	//! \return The full path to a file.
	std::filesystem::path GetFilePath(const std::filesystem::path& root_dir, const std::filesystem::path& file) const;

	//! Gets the first iterator for the directory we are watching.  Does not honor exclusion list.
	// filesystem::directory_iterator GetFirstDirectoryIterator() const;

	//! Gets an iterator for the directory we are watching.  Does not honor exclusion list.
	// std::list<std::filesystem::directory_iterator> GetDirectoryIterators() const;

	//! Returns true if we are searching the filesystem.
	bool IsSearchingForFiles() const
	{
		return m_searching_files;
	}

	//! Blocks the thread until files have been fully searched.
	void WaitUntilFilesSearched()
	{
		if (!m_searching_files)
			return;

		std::unique_lock guard(m_file_mutex);
		m_searching_files_condition.wait(guard);
	}

	//! Checks for changes to the underlying OS filesystem.  Call this every so often.
	void Update()
	{
		m_watcher.Update();
	}

private:
	void bind(const std::filesystem::path& directory, std::list<std::filesystem::path>&& exclude_list, bool at_front = false);
	bool isExcluded(const std::list<std::filesystem::path>& exclude_list, const std::filesystem::path& directory);

private:
	void buildExclusionList(std::list<std::filesystem::path>& exclude_list) {}

	template <typename T, typename... Args>
	void buildExclusionList(std::list<std::filesystem::path>& exclude_list, T dir, Args... args)
	{
		exclude_list.push_back(dir);
		buildExclusionList(exclude_list, args...);
	}

private:
	watch::FileWatch m_watcher;
	std::atomic<bool> m_searching_files;
	std::condition_variable m_searching_files_condition;

	// Using list instead of vector as some compilers don't noexcept certain STL container member functions and can, down the line, cause issues with unique_ptr.
	std::list<DirectoryGroup> m_directories;

	mutable std::mutex m_file_mutex;
};

} // end namespace graal::fs

namespace graal::fs
{

void FileSystem::bind(const std::filesystem::path& directory, std::list<std::filesystem::path>&& exclude_list, bool at_front)
{
	std::scoped_lock guard(m_file_mutex);

	// Make sure we aren't already listening to this directory.
	auto existingGroup = std::find_if(std::begin(m_directories), std::end(m_directories), [&directory](decltype(m_directories)::value_type const& entry) { return entry.Directory == directory; });
	if (existingGroup != std::end(m_directories))
	{
		// We are going to abort, but first lets merge our exclude directory list as we may have wanted to update it.
		if (!exclude_list.empty())
		{
			existingGroup->ExcludedDirectories.splice(std::end(existingGroup->ExcludedDirectories), exclude_list);
			existingGroup->ExcludedDirectories.unique();
		}
		return;
	}

	// Insert our directory to the list.
	auto directoryGroup = m_directories.emplace(at_front ? m_directories.begin() : m_directories.end());
	directoryGroup->Directory = directory;
	directoryGroup->ExcludedDirectories = std::move(exclude_list);

	// We are starting our file search.
	m_searching_files = true;

	// Create directories that don't exist.
	std::filesystem::create_directories(directory);

	// Fill our filesystem with file information.
	for (const auto& file : std::filesystem::recursive_directory_iterator(directory))
	{
		// If it is not a regular file, abort.
		if (!std::filesystem::is_regular_file(file.status()))
			continue;

		const auto& path = file.path();

		// Check if the directory is in the exclusion list.
		if (isExcluded(directoryGroup->ExcludedDirectories, path))
			continue;

		auto entry = std::make_unique<FileEntry>(path);
		directoryGroup->Files.insert(std::make_pair(path.filename(), std::move(entry)));
	}

	// We are done searching our file system.
	m_searching_files = false;
	m_searching_files_condition.notify_all();

	//m_directory_include.push_back(directory);
	m_watcher.Add(directory,
		[this](uint32_t watch_id, const std::filesystem::path& dir, const std::filesystem::path& file, watch::Event e)
		{
			if (e == watch::Event::Invalid || e == watch::Event::Modified)
				return;

			// Get our directory group.
			auto directoryGroup = std::find_if(m_directories.begin(), m_directories.end(), [&](const auto& group) { return group.Directory == dir; });
			if (directoryGroup == std::end(m_directories))
				return;

			// Check if the directory is in the exclusion list.
			if (isExcluded(directoryGroup->ExcludedDirectories, dir))
				return;

			std::scoped_lock guard(m_file_mutex);
			auto iter = directoryGroup->Files.find(file);

			if (iter != directoryGroup->Files.end())
			{
				if (e == watch::Event::Add)
				{
					iter->second->File = dir / file;
				}
				else if (e == watch::Event::Delete)
				{
					directoryGroup->Files.erase(iter);
				}
				else if (e == watch::Event::Modified)
				{
					// TODO: Send out a modification event?
				}
			}
			else
			{
				if (e == watch::Event::Add)
				{
					auto entry = std::make_unique<FileEntry>(dir / file);
					directoryGroup->Files.insert(std::make_pair(file, std::move(entry)));
				}
			}
		}
	);
}

bool FileSystem::isExcluded(const std::list<std::filesystem::path>& exclude_list, const std::filesystem::path& directory)
{
	// Check if this directory has been excluded.
	auto exclude = std::find_if(exclude_list.begin(), exclude_list.end(), [&](const auto& excluded) -> bool
		{
			if (directory.parent_path().string().find(excluded.string()) != std::string::npos)
				return true;
			return false;
		});
	if (exclude == exclude_list.end())
		return false;
	return true;
}

bool FileSystem::HasFile(const std::filesystem::path& file) const
{
	if (std::filesystem::exists(file))
		return true;

	// Check if our file is saved in the file system list.
	{
		std::scoped_lock guard(m_file_mutex);

		for (const auto& group : m_directories)
		{
			auto iter = group.Files.find(file);
			if (iter != group.Files.end())
				return true;
		}
	}

	return false;
}

bool FileSystem::HasFile(const std::filesystem::path& root_dir, const std::filesystem::path& file) const
{
	if (std::filesystem::exists(root_dir / file))
		return true;

	// Check if our file is saved in the file system list.
	{
		std::scoped_lock guard(m_file_mutex);

		auto group = std::find_if(std::begin(m_directories), std::end(m_directories), [&](decltype(m_directories)::value_type const& entry) { return entry.Directory == root_dir; });
		if (group == std::end(m_directories))
			return false;

		auto iter = group->Files.find(file);
		if (iter != group->Files.end())
			return true;
	}

	return false;
}

FileData FileSystem::GetFileData(const std::filesystem::path& file) const
{
	FileData data;

	auto f = GetFile(file);
	if (f)
	{
		data.CRC32 = f->Crc32();
		data.FileSize = f->Size();
		data.TimeSinceEpoch = f->ModifiedTime();
	}

	return data;
}

FileData FileSystem::GetFileData(const std::filesystem::path& root_dir, const std::filesystem::path& file) const
{
	FileData data;

	auto f = GetFile(root_dir, file);
	if (f)
	{
		data.CRC32 = f->Crc32();
		data.FileSize = f->Size();
		data.TimeSinceEpoch = f->ModifiedTime();
	}

	return data;
}

std::shared_ptr<File> FileSystem::GetFile(const std::filesystem::path& file) const
{
	// Check if the file exists in the native file system and file is a direct path.
	if (std::filesystem::exists(file))
	{
		auto f = std::make_shared<File>(file);
		return f;
	}

	// Check if the file exists in the native file system and file is a filename we want to find.
	{
		std::scoped_lock guard(m_file_mutex);
		for (const auto& group : m_directories)
		{
			auto iter = group.Files.find(file);
			if (iter != group.Files.end())
				return std::make_shared<File>(iter->second->File);
		}
	}

	return nullptr;
}

std::shared_ptr<File> FileSystem::GetFile(const std::filesystem::path& root_dir, const std::filesystem::path& file) const
{
	// Check if the file exists in the native file system and file is a direct path.
	if (std::filesystem::exists(root_dir / file))
	{
		auto f = std::make_shared<File>(root_dir / file);
		return f;
	}

	// Check if the file exists in the native file system and file is a filename we want to find.
	{
		std::scoped_lock guard(m_file_mutex);

		auto group = std::find_if(std::begin(m_directories), std::end(m_directories), [&](decltype(m_directories)::value_type const& entry) { return entry.Directory == root_dir; });
		if (group == std::end(m_directories))
			return nullptr;

		auto iter = group->Files.find(file);
		if (iter != group->Files.end())
			return std::make_shared<File>(iter->second->File);
	}

	return nullptr;
}

std::filesystem::path FileSystem::GetFilePath(const std::filesystem::path& file) const
{
	if (std::filesystem::exists(file))
		return file;

	// Check if the file exists in the native file system and file is a filename we want to find.
	{
		std::scoped_lock guard(m_file_mutex);
		for (const auto& group : m_directories)
		{
			auto iter = group.Files.find(file);
			if (iter != group.Files.end())
				return iter->second->File;
		}
	}

	return {};
}

std::filesystem::path FileSystem::GetFilePath(const std::filesystem::path& root_dir, const std::filesystem::path& file) const
{
	if (std::filesystem::exists(root_dir / file))
		return root_dir / file;

	// Check if the file exists in the native file system and file is a filename we want to find.
	{
		std::scoped_lock guard(m_file_mutex);

		auto group = std::find_if(std::begin(m_directories), std::end(m_directories), [&](decltype(m_directories)::value_type const& entry) { return entry.Directory == root_dir; });
		if (group == std::end(m_directories))
			return {};

		auto iter = group->Files.find(file);
		if (iter != group->Files.end())
			return iter->second->File;
	}

	return {};
}

/*
std::filesystem::directory_iterator FileSystem::GetFirstDirectoryIterator() const
{
	if (m_directory_include.empty())
		return std::filesystem::directory_iterator{};
	return std::filesystem::directory_iterator{ m_directory_include.front() };
}

std::list<std::filesystem::directory_iterator> FileSystem::GetDirectoryIterators() const
{
	std::list<std::filesystem::directory_iterator> directories;
	std::for_each(m_directory_include.begin(), m_directory_include.end(), [&directories](const decltype(m_directory_include)::value_type& p)
	{
		directories.push_back(std::filesystem::directory_iterator{ p });
	});
	return directories;
}
*/

} // end namespace graal::fs
