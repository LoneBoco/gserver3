module;

#include "common.h"

#include <filesystem>
#include <locale>
#include <sstream>

#include <boost/program_options.hpp>

export module graal.programsettings;

import graal.file;

/*
import std.core;
import std.memory;
import std.filesystem;

import <boost/algorithm/string.hpp>;
*/


export namespace graal::settings
{

class ProgramSettings
{
#pragma region Headers
public:
	ProgramSettings() = default;
	~ProgramSettings() = default;

	ProgramSettings(const ProgramSettings& other) = delete;
	ProgramSettings(ProgramSettings&& other) = delete;
	ProgramSettings& operator=(const ProgramSettings& other) = delete;
	ProgramSettings& operator=(ProgramSettings&& other) = delete;
#pragma endregion

public:

#pragma region Load and Save
	bool LoadFromFile(const char* file, const std::string_view& default_category = "Global")
	{
		return LoadFromFile(std::string_view{ file }, default_category);
	}

	bool LoadFromFile(const std::string_view& file, const std::string_view& default_category = "Global")
	{
		fs::File f{ file };
		return LoadFromFile(f, default_category);
	}

	bool LoadFromFile(const fs::File& file, const std::string_view& default_category = "Global")
	{
		std::string category{ default_category };

		while (!file.Finished())
		{
			std::string line = file.ReadLine();

			// Erase any carriage returns.
			line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());

			// Trim.
			boost::trim(line);

			if (!line.empty())
			{
				// Check if this is a category.
				if (line[0] == '[' && *(line.rbegin()) == ']')
				{
					// Register the new category.
					category = line.substr(1, line.size() - 2);
				}
				else
				{
					// Parse our string.
					std::size_t sep = line.find('=');
					std::string setting = line.substr(0, sep);
					std::string value;
					if (sep != std::string::npos)
						value = line.substr(sep + 1, line.size() - sep - 1);
					boost::trim_right(setting);
					boost::trim_left(value);

					// Save it.
					Set(category + "." + setting, value);
				}
			}
		}

		return true;
	}

	bool LoadFromCommandLine(int argc, char** argv)
	{
		namespace po = boost::program_options;
		po::options_description desc;
		desc.add_options()
			("server", po::value<std::string>()->implicit_value("default"), "server folder to use")
			("host", po::value<std::string>()->implicit_value("localhost"), "hostname or IP address to bind to")
			("port", po::value<uint16_t>()->implicit_value(13131), "port to listen on")
			("broadcasthost", po::value<std::string>(), "public IP to broadcast to the list server")
			;

		po::variables_map vm;
		po::store(po::command_line_parser(argc, argv).options(desc).allow_unregistered().run(), vm);
		po::notify(vm);

		if (vm.count("server"))
			Set("global.server", vm["server"].as<std::string>());

		if (vm.count("host"))
			Set("global.host", vm["host"].as<std::string>());

		if (vm.count("port"))
			Set("global.port", vm["host"].as<uint16_t>());

		if (vm.count("broadcasthost"))
			Set("global.broadcasthost", vm["broadcasthost"].as<std::string>());

		return true;
	}
	
	/*
	bool WriteToFile(const io::path& filename, io::IFileSystem* FileSystem)
	{
		if (FileSystem == 0)
			return false;

		// Assemble the file.
		std::string filedata;
		for (auto i = category_order.begin(); i != category_order.end(); ++i)
		{
			ProgramSettingsCategory* category = *i;
			if (category == nullptr) continue;

			filedata += '[';
			filedata += category->get_category_name();
			filedata += "]\r\n";

			auto settings_map = category->get_settings();
			auto settings_vector = category->get_settings_order();
			for (auto j = settings_vector.begin(); j != settings_vector.end(); ++j)
			{
				auto s = settings_map.find(*j);
				if (s == settings_map.end())
					continue;

				filedata += s->first;
				filedata += " = ";
				filedata += s->second;
				filedata += "\r\n";
			}

			filedata += "\r\n";
		}
		if (filedata.empty()) return true;

		// Save the file.
		core::array<uchar8_t> utf8 = filedata.toUTF8(true);
		rha::fs::file f((const char*)utf8.pointer(), (const char*)utf8.pointer() + utf8.size() - 1);
		f.set_filename(filename);
		f.save(FileSystem);
		return true;
	}
	*/
#pragma endregion

#pragma region Get
	bool Exists(const std::string& setting) const
	{
		std::string lower{ setting };
		std::transform(lower.begin(), lower.end(), lower.begin(), [](auto ch) { return std::tolower(ch, std::locale("")); });

		auto i = m_settings.find(lower);
		if (i == m_settings.end()) return false;
		return true;
	}

	std::string Get(const std::string& setting, const std::string& def = "") const
	{
		return GetAs<std::string>(setting, def);
	}

	template <typename T>
	T GetAs(const std::string& setting, const T def = T{}) const
	{
		std::string lower{ setting };
		std::transform(lower.begin(), lower.end(), lower.begin(), [](auto ch) { return std::tolower(ch, std::locale("")); });

		auto i = m_settings.find(lower);
		if (i == m_settings.end()) return def;

		std::istringstream str(i->second);
		T v;
		str >> v;
		return v;
	}

	template <>
	bool GetAs<bool>(const std::string& setting, const bool def) const
	{
		std::string lower{ setting };
		std::transform(lower.begin(), lower.end(), lower.begin(), [](auto ch) { return std::tolower(ch, std::locale("")); });

		auto i = m_settings.find(lower);
		if (i == m_settings.end()) return def;

		std::string lowervalue{ i->second };
		std::transform(lowervalue.begin(), lowervalue.end(), lowervalue.begin(), [](auto ch) { return std::tolower(ch, std::locale("")); });

		if (lowervalue == "on")
			return true;
		if (lowervalue == "true")
			return true;
		if (lowervalue == "yes")
			return true;

		return false;
	}
#pragma endregion
	
#pragma region Set
	void Set(const std::string& setting, const std::string& value)
	{
		std::string lower{ setting };
		std::transform(lower.begin(), lower.end(), lower.begin(), [](auto ch) { return std::tolower(ch, std::locale("")); });

		auto i = m_settings.find(lower);
		if (i == m_settings.end())
		{
			m_settings[lower] = value;
			m_settings_order.push_back(setting);
		}
		else i->second = value;
	}

	void Set(const std::string& setting, const int32_t value)
	{
		std::stringstream str;
		str << value;
		Set(setting, str.str());
	}

	void Set(const std::string& setting, const float value)
	{
		std::stringstream str;
		str << value;
		Set(setting, str.str());
	}

	void Set(const std::string& setting, const bool value)
	{
		Set(setting, value ? std::string("true") : std::string("false"));
	}
#pragma endregion

#pragma region Delete
	void EraseCategory(const std::string_view& category)
	{
		std::erase_if(m_settings,
			[category](const auto& p) -> bool
			{
				const auto& [k, v] = p;
				return boost::istarts_with(k, category);
			}
		);
	}
#pragma endregion

private:
	std::map<std::string, std::string> m_settings;
	std::vector<std::string> m_settings_order;
};

} // end namespace graal::settings
