module;

#include "common.h"

#include <filesystem>

export module graal.filesystem.watch;

/*
import std.core;
import std.memory;
import std.filesystem;
*/


export namespace graal::fs::watch
{

enum class Event
{
	Invalid = 0,
	Add = 0b1,
	Delete = 0b10,
	Modified = 0b100,
};

typedef std::function<void(uint32_t, const std::filesystem::path&, const std::filesystem::path&, Event)> watch_cb;

struct Watch;
struct WatchOS;
class FileWatch
{
public:
	FileWatch();
	~FileWatch();

	FileWatch(const FileWatch& other) = delete;
	FileWatch(FileWatch&& other) = delete;
	FileWatch& operator=(const FileWatch& other) = delete;
	FileWatch& operator=(FileWatch&& other) = delete;

	uint32_t Add(const std::filesystem::path& directory, watch_cb callback, bool recursive = true);
	void Remove(const std::filesystem::path& directory);
	void Remove(uint32_t watch_id);
	void RemoveAll();

	void Update();

private:
	std::map<uint32_t, Watch*> m_watchers;
	uint32_t m_last_id;
	std::unique_ptr<WatchOS> m_watch_os;
};

} // end namespace graal::fs::watch
