export module graal.core:log;

// Don't change this order.  For some reason the compile will fail.
import <fstream>;
import <sstream>;
import <iostream>;
import <filesystem>;
//

export namespace graal::core
{

class Log
{
public:
	Log() = delete;
	~Log() = delete;

	Log(const Log& other) = delete;
	Log(Log&& other) = delete;
	Log& operator=(const Log& other) = delete;
	Log& operator=(Log&& other) = delete;
	bool operator==(const Log& other) = delete;

public:
	template <typename ...Args>
	static void Print(std::string_view fmt, Args&... args)
	{
		auto localtime = std::chrono::zoned_time{ std::chrono::current_zone(), std::chrono::system_clock::now() }.get_local_time();

		std::ostringstream text;
		text
			<< std::format("[{:%F %H:%M:%S}] ", std::chrono::floor<std::chrono::seconds>(localtime))
			<< std::vformat(fmt, std::make_format_args(args...))
			<< std::endl;

		if (Log::m_file.is_open())
			Log::m_file << text.str();

		std::cout << text.str();
	}

public:
	static void SetLogFile(const std::filesystem::path& p)
	{
		if (Log::m_file && Log::m_file.is_open())
		{
			Log::m_file.flush();
			Log::m_file.close();
		}
		Log::m_file.open(p, std::ios::binary | std::ios::out | std::ios::app);
	}

private:
	static std::ofstream m_file;
};

} // end namespace graal::core

namespace graal::core
{

std::ofstream Log::m_file;

}
