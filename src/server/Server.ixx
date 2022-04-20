module;

#include "common.h"

#include <limits>
#include <set>

export module graal.server;

import graal.core;
import graal.network;
import graal.programsettings;
import graal.filesystem;
import graal.packet;
import graal.player;
import graal.level;

//import std.core;
//import std.memory;


using string_list = std::vector<std::string>;

export namespace graal::server
{

class Server
{
public:
	Server() = default;
	~Server() = default;

	Server(const Server& other) noexcept = delete;
	Server(Server&& other) noexcept = delete;
	Server& operator=(const Server& other) noexcept = delete;
	Server& operator=(Server&& other) noexcept = delete;
	bool operator==(const Server& other) const noexcept = delete;

public:
	void LoadConfiguration()
	{
		Log::PrintLine(":: Loading server configuration.");

		load_settings();
		load_admin_settings();
		load_allowed_versions();
		load_filesystem();
		load_serverflags();
		load_servermessage();
		load_ipbans();
		load_classes();
		load_maps();
		load_translations();
		load_word_filter();
	}

public:
	void Run()
	{
		// Update our network.
		m_network.Run();

		// Do timed events.

		assert(false);
	}

public:
	uint32_t Send(const packet::Packet& packet, player::PlayerPtr target) const
	{
		assert(false);
		return 0;
	}

	uint32_t Broadcast(const packet::Packet& packet, player::PlayerPtr origin, bool sendToOrigin = false) const
	{
		assert(false);
		return 0;
	}

	// TODO: OnlyGmap
	uint32_t SendToLevel(const packet::Packet& packet, level::LevelPtr target, player::PlayerPtr origin = nullptr, bool sendToOrigin = false) const
	{
		assert(false);
		return 0;
	}

public:
	fs::FileSystem FileSystem;
	network::Network Network;

protected:
	void load_settings()
	{
		Log::PrintLine("{}Loading settings.", Log::Indent<1>());

		auto settings = BabyDI::Get<settings::ProgramSettings>();
		if (fs::File options{ "config/serveroptions.txt" }; options)
		{
			settings->EraseCategory("server");
			settings->LoadFromFile(options, "server");
		}
		else Log::PrintLine("** [Error] Could not open config/serveroptions.txt.  Will use default config.");

		// Load status list.
		m_status_list = settings->Get("server.playerlisticons", "Online,Away,DND,Eating,Hiding,No PMs,RPing,Sparring,PKing") | graal::split<string_list>(',');

		// Load staff list.
		m_staff_list = settings->Get("server.staff") | graal::split<string_list>(',');

		// Send our ServerHQ info in case we changed the staffonly setting.
	}

	void load_admin_settings()
	{
		Log::PrintLine("{}Loading admin settings.", Log::Indent<1>());
		assert(false);
	}

	void load_allowed_versions()
	{
		Log::PrintLine("{}Loading allowed client versions.", Log::Indent<1>());
		assert(false);
	}

	void load_filesystem()
	{
		auto settings = BabyDI::Get<settings::ProgramSettings>();

		Log::Print("{}Folder config: ", Log::Indent<1>());
		if (settings->GetAs<bool>("server.nofoldersconfig") == true)
			Log::PrintLine("Enabled.");
		else Log::PrintLine("DISABLED.");

		Log::PrintLine("{}Loading file system.", Log::Indent<1>());
		assert(false);
	}

	void load_serverflags()
	{
		Log::PrintLine("{}Loading serverflags.txt.", Log::Indent<1>());
		assert(false);
	}

	void load_servermessage()
	{
		Log::PrintLine("{}Loading config/servermessage.html.", Log::Indent<1>());
		assert(false);
	}

	void load_ipbans()
	{
		Log::PrintLine("{}Loading config/ipbans.txt.", Log::Indent<1>());
		assert(false);
	}

	void load_weapons()
	{
		Log::PrintLine("{}Loading weapons.", Log::Indent<1>());
		assert(false);
	}

	void load_classes()
	{
		Log::PrintLine("{}Loading classes.", Log::Indent<1>());
		assert(false);
	}

	void load_maps()
	{
		Log::PrintLine("{}Loading maps.", Log::Indent<1>());
		assert(false);
	}

	void load_translations()
	{
		Log::PrintLine("{}Loading translations.", Log::Indent<1>());
		assert(false);
	}

	void load_word_filter()
	{
		Log::PrintLine("{}Loading word filter.", Log::Indent<1>());
		assert(false);
	}

protected:
	uint16_t get_next_player_id()
	{
		if (auto b = std::begin(m_players_free_ids); !m_players_free_ids.empty() && *b < m_players_max_id)
		{
			auto result = *b;
			m_players_free_ids.erase(b);
			return result;
		}

		if (m_players_max_id == std::numeric_limits<uint16_t>::max())
		{
			throw "Ran out of player ids";
		}

		return ++m_players_max_id;
	}

protected:
	void on_player_connect(network::NetworkEndpointPtr&& endpoint)
	{
		auto id = get_next_player_id();

		// Make player.
		auto player = std::make_shared<player::Player>(id, std::forward<network::NetworkEndpointPtr>(endpoint));

		// Add player to server.
		m_players.insert(std::make_pair(id, player));
	}

protected:
	network::Network m_network;

	std::unordered_map<uint16_t, player::PlayerPtr> m_players;
	std::set<uint16_t> m_players_to_delete;
	std::set<uint16_t> m_players_free_ids;
	uint16_t m_players_max_id = 2;

	// std::unordered_map<uint16_t, npc::NpcPtr> m_npcs;

	std::vector<std::string> m_status_list;
	std::vector<std::string> m_staff_list;
};

} // end namespace graal::server
