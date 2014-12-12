/*
 * characters.cpp - character data structures
 *
 * This is a minimal text-based game whose purpose is to demonstrate
 * modular programming.
 *
 * Copyright (C) 2014  Curtis Dyer
 *
 * This program is free software: you can redistribute it and/or
 * modify
 * it under the terms of the GNU General Public License as published
 * by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include <string>
#include <ctime>
#include <cstdlib>

#include "characters.h"
#include "utils.h"
#include "weapons.h"


void Character::init()
{
	srand(time(NULL));
}

/** constructors */
Character::Character() : hp(0), str(0), min(0), max(0), state(INIT)
{
	init();
	maxhp = hp;
}
Character::Character(std::string n, Weapon w, int hp, int str)
	: name(n), weap(w), hp(hp), str(str), min(0), max(0), state(INIT)
{
	init();
	maxhp = hp;
}
Character::~Character() {}

/* accessors */
int Character::gethp() const
{
	return hp;
}
int Character::getmaxhp() const
{
	return maxhp;
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
void Character::setmaxhp(int hp)
{
	maxhp = hp;
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
int Character::attack(Character* ch)
{
	unsigned roll = rand_range(1u, 100u);
	unsigned critchance = 15u;
	int dmg = rand_range(min, max);

	if (roll <= weap.hitrate()) {
		ch->setflags(Character::HIT);
		dmg += str + weap.getdmg();
		if (roll <= critchance) {
			ch->setflags(Character::CRIT);
			dmg += weap.getdmg() / 2;
		}
		ch->addhp(-dmg);
	}

	return dmg;
}


/** Output stream behavior for our Character objects */
std::ostream& operator<< (std::ostream& o, Character const& ch)
{
	return o << ch.name;
}
