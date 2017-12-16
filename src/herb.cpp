#include "herb.hpp"

#include "mob.hpp"

using kb::rogue::Herb;

Herb::Herb(int recoveryAmount) : Item('!', "herb"), recoveryAmount(recoveryAmount)
{}

void Herb::use(std::vector<std::shared_ptr<Mob>> targets)
{
	targets[0]->setHp(targets[0]->getHp() + recoveryAmount);
}
