#include "item.hpp"

using kb::rogue::Item;

Item::Item(char mark, const std::string& name) : mark(mark), name(name), amount(1)
{
}

bool operator==(const Item& r, const Item& l)
{
	return (r.getMark() == l.getMark()) && (r.getName() == l.getName());
}

bool operator!=(const Item& r, const Item& l)
{
	return !(r == l);
}
