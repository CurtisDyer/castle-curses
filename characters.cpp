/*
 * characters.cpp - character data structures
 */

#include <string>
#include <ctime>
#include <cstdlib>

#include "characters.h"
#include "utils.h"
#include "weapons.h"


void Character::init()
{
	std::srand(std::time(NULL));
}

/** constructors */
Character::Character() : hp(0), str(0), state(INIT)
{
	init();
}
Character::Character(std::string n, Weapon w, int hp, int str)
	: name(n), weap(w), hp(hp), str(str), state(INIT)
{
	init();
}

/* accessors */
int Character::gethp() const
{
	return hp;
}
std::string Character::getname() const
{
	return name;
}
unsigned Character::getflags() const
{
	return state;
}
Weapon Character::getweapon() const
{
	return weap;
}
bool Character::is_dead() const
{
	return hp <= 0;
}
CharType Character::gettype() const
{
	return type;
}

/* mutators */
void Character::addhp(int amt)
{
	hp += amt;
}
void Character::setweapon(Weapon w)
{
	weap = w;
}
void Character::setflags(unsigned f)
{
	state |= f;
}
void Character::clearflags(unsigned f)
{
	state &= ~f;
}
void Character::setname(std::string& n)
{
	name = n;
}
void Character::settype(const CharType& t)
{
	type = t;
}


/**
 * attack a target character
 *
 * @param the target
 * @param we need to avoid a recursive chain of calls, so we pass a
 * parameter to determine when an attack sequence should end
 */
void Character::attack(Character* ch, bool retaliate)
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

	if (retaliate)
		ch->attack(this, false);
}


/** Output stream behavior for our Character objects */
std::ostream& operator<< (std::ostream& o, Character const& ch)
{
	return o << ch.name;
}
