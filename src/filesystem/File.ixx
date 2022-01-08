export module graal.file;

import "common.h";

import <cassert>;
import <filesystem>;
import <fstream>;
import <sstream>;
import <boost/crc.hpp>;


// Not exported.
namespace graal::fs
{

uint32_t calculateCRC32(std::istream& stream);
uint32_t calculateCRC32(const std::filesystem::path& file);

}


export namespace graal::fs
{

class File
{
#pragma region Headers
public:
	File() = delete;
	File(const std::filesystem::path& file, std::unique_ptr<std::ifstream>&& stream) : m_file(file), m_stream(std::move(stream)) {}

	File(const std::filesystem::path& file) : m_file(file)
	{
		Open();
	}

	~File()
	{
		Close();
	}

	File(const File& other) = delete;
	File& operator=(const File& other) = delete;

	File(File&& other) noexcept : m_file(std::move(other.m_file))
	{
		m_stream.swap(other.m_stream);
	}

	File& operator=(File&& other) noexcept
	{
		std::swap(m_file, other.m_file);
		std::swap(m_stream, other.m_stream);
		return *this;
	}

	bool operator==(const File& other) = delete;
#pragma endregion

public:
	//! Converts directly into an istream.
	operator std::istream& () const
	{
		return *(m_stream.get());
	}

	//! Converts directly into a shared pointer to the istream.
	operator std::istream* () const
	{
		return m_stream.get();
	}

	//! Returns if this is a valid file.
	operator bool() const
	{
		return Opened();
	}

	//! Opens the file.
	//! \return If the file was successfully opened.
	bool Open() const
	{
		if (m_stream)
			dynamic_cast<std::ifstream&>(*m_stream).close();

		m_stream = std::make_unique<std::ifstream>(m_file, std::ios::binary);
		return true;
	}

	//! Closes the file.
	void Close() const
	{
		dynamic_cast<std::ifstream&>(*m_stream).close();
	}

#pragma region Read
	//! Reads the full file.
	//! \return The file contents.
	std::vector<char> Read() const
	{
		if (!Opened() || Finished())
			return std::vector<char>();

		// Seek to the end and get the file size.
		m_stream->seekg(0, std::ios::end);
		auto size = m_stream->tellg();

		// Seek to the start and read into the vector.
		std::vector<char> result(static_cast<size_t>(size));
		m_stream->seekg(0);
		m_stream->read(result.data(), size);
		return result;
	}

	//! Reads part of a file.
	//! \param count How many bytes to read.
	//! \return The file contents.
	std::vector<char> Read(std::size_t count) const
	{
		if (!Opened() || Finished())
			return std::vector<char>();

		std::vector<char> result(count);
		auto read = m_stream->readsome(result.data(), count);
		result.resize(static_cast<size_t>(read));
		return result;

	}

	//! Reads from the file until it encounters the token.
	std::vector<char> ReadUntil(const std::string& token) const
	{
		// Not implemented.
		assert(false);
		return std::vector<char>();
	}
	std::vector<char> ReadUntil(const std::vector<char>& token) const
	{
		// Not implemented.
		assert(false);
		return std::vector<char>();
	}

	//! Reads the file into a string.
	//! \return The file contents.
	std::string ReadAsString() const
	{
		if (!Opened() || Finished())
			return std::string();

		std::stringstream s;
		s << m_stream->rdbuf();
		return s.str();
	}

	//! Reads a line from the file.
	//! \return A string containing a single line, excluding the line ending.
	std::string ReadLine() const
	{
		if (!Opened() || Finished())
			return std::string();

		std::string result;
		std::getline(*m_stream, result);
		if (result.empty())
			return result;

		if (*result.crbegin() == '\r')
			result.pop_back();

		return result;
	}

	//! Reads the position indicator of the file.
	//! \return The position indicator.
	std::streampos GetReadPosition() const
	{
		return m_stream->tellg();
	}

	//! Sets the position indicator of the file.
	//! \param position The position in the file.
	void SetReadPosition(const std::streampos& position)
	{
		if (Opened())
			m_stream->seekg(position);
	}
#pragma endregion

	//! Tells us if the file is opened.
	//! \return If the file is opened or not.
	bool Opened() const
	{
		return dynamic_cast<std::ifstream&>(*m_stream).is_open();
	}

	//! Tells us if we finished reading the file.
	//! \return If we finished reading the file or not.
	bool Finished() const
	{
		if (m_stream == nullptr || !Opened())
			return true;
		return m_stream->eof();
	}

	//! Gets the file size.
	//! \return The file size.
	uintmax_t Size() const
	{
		return std::filesystem::file_size(m_file);
	}

	/// <summary>
	/// Gets the path to the file.
	/// </summary>
	/// <returns>The path to the file.</returns>
	std::filesystem::path FilePath() const
	{
		return m_file;
	}

	//! Gets the file modified time.
	//! \return The file modified time.
	intmax_t ModifiedTime() const
	{
		return std::filesystem::last_write_time(m_file).time_since_epoch().count();
	}

	//! Gets the CRC32 of the file.
	//! \return The CRC32 of the file.
	uint32_t Crc32() const
	{
		std::ifstream stream{ m_file, std::ios::binary };
		return calculateCRC32(stream);
	}

protected:
	std::filesystem::path m_file;
	mutable std::unique_ptr<std::istream> m_stream;
};

} // end namespace graal::fs


module :private;


uint32_t graal::fs::calculateCRC32(std::istream& stream)
{
	// Calculate CRC32 if we can.
	boost::crc_32_type crc32;
	if (stream)
	{
		do
		{
			constexpr size_t READBUFFER_SIZE = 1024 * 8;

			char buffer[READBUFFER_SIZE];
			stream.read(buffer, READBUFFER_SIZE);

			crc32.process_bytes(buffer, stream.gcount());
		} while (stream);
	}
	else return 0;

	return crc32.checksum();
}

uint32_t graal::fs::calculateCRC32(const std::filesystem::path& file)
{
	std::ifstream ifs{ file, std::ios::binary };
	return calculateCRC32(ifs);
}
