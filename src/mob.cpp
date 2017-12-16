#include "mob.hpp"

#include <algorithm>

#include "item.hpp"
#include "map.hpp"

using kb::rogue::Item;
using kb::rogue::Mob;

Mob::Mob(const std::shared_ptr<Map>& map, char mark, int x0, int y0, int hp)
	: map(map), items(), mark(mark),
	mapX0(map->getX0()), mapY0(map->getY0()), x(x0), y(y0), hp(hp)
{}

void Mob::addItem(const std::shared_ptr<Item>& item, int amount)
{
	if (amount > 0)
	{
		auto it = std::find(items.begin(), items.end(), item);
		if (it != items.end())
		{
			(*it)->setAmount((*it)->getAmount() + amount);
		}
		else
		{
			items.push_back(item);
		}
	}
	else if (amount < 0)
	{
		removeItem(item, amount);
	}
}

void Mob::removeItem(const std::shared_ptr<Item>& item, int amount)
{
	if (amount < 0)
	{
		auto it = std::find(items.begin(), items.end(), item);
		if (it != items.end())
		{
			(*it)->setAmount((*it)->getAmount() + amount);
			if ((*it)->getAmount() == 0)
			{
				items.erase(it);
			}
		}
	}
	else if (amount > 0)
	{
		addItem(item, amount);
	}
}

std::shared_ptr<Item> Mob::getItem(const std::shared_ptr<Item>& item)
{
	auto it = std::find(items.begin(), items.end(), item);
	if (it != items.end())		return *it;
	else						return nullptr;
}
