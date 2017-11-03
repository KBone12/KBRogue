#include "map.hpp"

#include <algorithm>
#include <fstream>
#include <sstream>

#include "curses_include.h"

#include "entity.hpp"
#include "door.hpp"
#include "player.hpp"

using kb::rogue::Door;
using kb::rogue::Entity;
using kb::rogue::Map;
using kb::rogue::MapManager;

Map::Map(const std::string& filePath, int floorNumber, int x0, int y0)
	: filePath(filePath), logger(spdlog::get("logger")),
	floorNumber(floorNumber), x0(x0), y0(y0)
{}

void Map::initialize()
{
	std::ifstream file(filePath);
	file.exceptions(std::ifstream::badbit);
	try
	{
		SPDLOG_DEBUG(logger, "the file({0}) opened.", filePath);

		std::string tmp;
		while (std::getline(file, tmp))
		{
			data.push_back(tmp);
		}

		std::ifstream collisionFile(filePath + ".collision");
		collisionFile.exceptions(std::ifstream::badbit);
		SPDLOG_DEBUG(logger, "the file({0}) opened.",
				filePath + ".collision");

		for (int y = -1; std::getline(collisionFile, tmp); ++y)
		{
			std::stringstream ss(tmp);
			collisionData.push_back(std::vector<int>());
			for (int x = -1; std::getline(ss, tmp, ','); ++x)
			{
				int mapValue = std::stoi(tmp);
				collisionData.back().push_back(mapValue);

				switch (mapValue)
				{
					case Map::H_DOOR:
						entities.push_back(std::make_shared<Door>(sharedThis(), x, y, false, true));
						break;
					case Map::V_DOOR:
						entities.push_back(std::make_shared<Door>(sharedThis(), x, y, false, false));
						break;
					default:
						break;
				}
			}
		}

		SPDLOG_DEBUG(logger, "Completed loading the map from the files({0} and {0}.collision", filePath);
	}
	catch (const std::ifstream::failure& e)
	{
		logger->error("Can't open the file({0} or {1}): {2}",
				filePath, filePath + ".collision", e.what());

		data = {
			"-----",
			"|...|",
			"|...|",
			"|...|",
			"-----",
		};

		collisionData = {
			{ -1, -1, -1, -1, -1, -1, -1 },
			{ -1, -1, -1, -1, -1, -1, -1 },
			{ -1, -1,  0,  0,  0, -1, -1 },
			{ -1, -1,  0,  0,  0, -1, -1 },
			{ -1, -1,  0,  0,  0, -1, -1 },
			{ -1, -1, -1, -1, -1, -1, -1 },
			{ -1, -1, -1, -1, -1, -1, -1 },
		};
	}

	height = data.size();

	for (const auto& e : entities)
	{
		e->initialize();
	}
}

void Map::update(int delta)
{
	for (const auto& e : entities)
	{
		e->update(delta);
	}
}

void Map::render()
{
	for (int y = 0; y < height; ++y)
	{
		mvaddstr(y + y0, x0, data.at(y).c_str());
	}

	for (const auto& e : entities)
	{
		e->render();
	}
}

std::shared_ptr<Entity> Map::getEntity(int x, int y)
{
	auto target = std::find_if(entities.begin(), entities.end(),
					[&](std::shared_ptr<Entity> entity)
					{
						return (x == entity->getX())
						&& (y == entity->getY());
					});
	if (target != entities.end())
	{
		return *target;
	}
	return nullptr;
}

MapManager::MapManager()
	: EMPTY_MAP(std::make_shared<Map>("resouce/map/test", 0, 1, 1)),
	player(std::make_shared<Player>(EMPTY_MAP, '@', 1, 1))
{
	maps[0] = EMPTY_MAP;
}

MapManager::~MapManager() noexcept
{
	player.reset();

	for (auto& elem : maps)
	{
		elem.second.reset();
	}
}

void MapManager::initialize()
{
	for (auto& map : maps)
	{
		map.second->initialize();
	}

	player->initialize();

	SPDLOG_DEBUG(spdlog::get("logger"), "MapManager initialized.");
}

void MapManager::keyInput(int key)
{
	player->keyInput(key);
}

void MapManager::update(int delta)
{
	if (currentMap)		currentMap->update(delta);
	player->update(delta);
}

void MapManager::render()
{
	if (currentMap)		currentMap->render();
	player->render();
}

void MapManager::addMap(const std::shared_ptr<Map>& map)
{
	maps[map->getFloorNumber()] = map;
	map->initialize();
}

void MapManager::changeCurrentMap(const std::shared_ptr<Map>& map)
{
	if (maps.find(map->getFloorNumber()) == maps.end())
	{
		addMap(map);
	}
	changeCurrentMap(map->getFloorNumber());
}

void MapManager::changeCurrentMap(int floor)
{
	currentMap = maps[floor];
	player->changeCurrentMap(currentMap);

	SPDLOG_DEBUG(spdlog::get("logger"), "Current map was changed.");
}
