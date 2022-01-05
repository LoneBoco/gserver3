module;

export module graal.level;
export import graal.level.parts;

import graal.core;

import "common.h";


export namespace graal::level
{

class Level
{
public:
	Level();
	~Level();

	Level(const Level& other) = delete;
	Level(Level&& other) = delete;
	Level& operator=(const Level& other) = delete;
	Level& operator=(Level&& other) = delete;
	bool operator==(const Level& other) = delete;

public:
	bool reload();

protected:
	chrono::time_point m_last_updated;
	bool m_sparringzone;
	bool m_singleplayer;
	uint16_t m_tiles[4096];
	std::string m_filename;
	std::string m_fileversion;
	std::string m_levelname;
	std::string m_actual_levelname;
	std::vector<Chest> m_chests;
	std::vector<Item> m_items;
	std::vector<Link> m_links;
	std::vector<Sign> m_signs;
	std::vector<Baddy> m_baddies;
	std::vector<BoardChange> m_board_changes;
	std::vector<Horse> m_horses;
	// NPC
	// Player
};

} // end namespace graal::level
