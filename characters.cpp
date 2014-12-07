/*
 * characters.cpp - character data structures
 */

#include <string>
#include <ctime>
#include <cstdlib>

#include "characters.h"
#include "utils.h"
#include "weapons.h"

/** constructors */
Character::Character() : hp(0), str(0), state(INIT)
{
	std::srand(std::time(NULL));
}
Character::Character(std::string n, Weapon& w, int hp, int str)
	: name(n), weap(w), hp(hp), str(str), state(INIT)
{
	Character();
}

void Character::addhp(int amt)
{
	hp += amt;
}
void Character::setflags(unsigned f)
{
	state |= f;
}
void Character::clearflags(unsigned f)
{
	state &= ~f;
}
int Character::gethp() const
{
	return hp;
}
unsigned Character::getflags() const
{
	return state;
}
bool Character::is_dead() const
{
	return hp <= 0;
}
void Character::attack(Character* ch)
{
	unsigned roll = rand_range(1u, 100u);
	unsigned critchance = 15u;
	int dmg = 0;

	if (roll <= weap.hitrate()) {
		ch->setflags(Character::HIT);
		dmg = str + weap.getdmg();
		if (roll <= critchance) {
			ch->setflags(Character::CRIT);
			dmg += weap.getdmg() / 2;
		}
		ch->addhp(-dmg);
	}
}


/** Output stream behavior for our Character objects */
std::ostream& operator<< (std::ostream& o, Character const& ch)
{
	return o << ch.name;
}
