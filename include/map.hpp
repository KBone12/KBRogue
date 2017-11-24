#ifndef _MAP_HEADER_PP_KBROGUE_
#define _MAP_HEADER_PP_KBROGUE_

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "spdlog/spdlog.h"

namespace kb
{
	namespace rogue
	{
		class Entity;
		class Enemy;
		class Player;

		class Map : public std::enable_shared_from_this<Map>
		{
			public:
				Map(const std::string& filePath, int floorNumber, int x0, int y0);

				/**
				 * Throws a spdlog::spdlog_ex when spdlog can't initialize
				 */
				void initialize();
				void update(int delta);
				void render();
				void active();
				std::shared_ptr<Entity> getEntity(int x, int y);
				std::shared_ptr<Enemy> getEnemy(int x, int y);

				std::shared_ptr<Map> sharedThis()
				{
					return shared_from_this();
				}

				const std::vector<std::vector<int>>& getCollisionData() const
				{
					return collisionData;
				}

				int getFloorNumber() const
				{
					return floorNumber;
				}

				int getX0() const
				{
					return x0;
				}

				int getY0() const
				{
					return y0;
				}

				enum MapValue
				{
					WALL = -1,
					FLOOR,
					H_DOOR,		// horizontal door
					V_DOOR,		// vertical door
				};

			private:
				const std::string filePath;
				std::shared_ptr<spdlog::logger> logger;
				int floorNumber;
				std::vector<std::shared_ptr<Entity>> entities;
				std::vector<std::shared_ptr<Enemy>> enemies;
				std::vector<std::string> data;
				std::vector<std::vector<int>> collisionData;
				int x0, y0;		// origin
				int height;
		};

		class MapManager
		{
			public:
				MapManager();
				~MapManager() noexcept;

				void initialize();
				void keyInput(int key);
				void update(int delta);
				void render();

				void addMap(const std::shared_ptr<Map>& map);
				void changeCurrentMap(const std::shared_ptr<Map>& map);
				void changeCurrentMap(int floor);

				std::shared_ptr<Map> getCurrentMap() const
				{
					return currentMap;
				}

			private:
				const std::shared_ptr<Map> EMPTY_MAP;
				std::shared_ptr<Player> player;
				/**
				 * key: this map's floor number
				 * value: this map's shared pointer
				 */
				std::unordered_map<int, std::shared_ptr<Map>> maps;
				std::shared_ptr<Map> currentMap;
		};
	}
}

#endif /* _MAP_HEADER_PP_KBROGUE_ */
