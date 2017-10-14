#include "map.hpp"

#include <fstream>
#include <sstream>

#include "curses_include.h"
#include "spdlog/spdlog.h"

using kb::rogue::Map;

Map::Map(int x0, int y0) : x0(x0), y0(y0)
{}

void Map::initialize(const std::string& filePath)
{
	std::ifstream file(filePath);
	file.exceptions(std::ifstream::badbit);
	try
	{
		std::string tmp;
		while (std::getline(file, tmp))
		{
			data.push_back(tmp);
		}

		std::ifstream collisionFile(filePath + ".collision");
		collisionFile.exceptions(std::ifstream::badbit);

		while (std::getline(collisionFile, tmp))
		{
			std::stringstream ss(tmp);
			collisionData.push_back(std::vector<int>());
			while (std::getline(ss, tmp, ','))
			{
				collisionData.back().push_back(std::stoi(tmp));
			}
		}
	}
	catch (const std::ifstream::failure& e)
	{
		spdlog::get("logger")->error("Can't open the file({0} or {1}): {2}",
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
}

void Map::render()
{
	for (int y = 0; y < height; ++y)
	{
		mvaddstr(y + y0, x0, data.at(y).c_str());
	}
}
