/*
 * characters.cpp - character data structures
 *
 * This is a minimal text-based game whose purpose is to demonstrate
 * modular programming.
 *
 * Copyright (C) 2014  Curtis Dyer
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
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

Character::Character() : hp(0), str(0), min(0), max(0), state(INIT)
{
	init();
	maxhp = hp;
}
Character::Character(std::string n)
	: name(n), hp(0), str(0), min(0), max(0), state(INIT)
{
	init();
	maxhp = hp;
}

Character::Character(std::string n, int hp, int str)
	: name(n), hp(hp), str(str), min(0), max(0), state(INIT)
{
	init();
	maxhp = hp;
}
Character::~Character() {}

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

void Character::sethp(int amt)
{
	hp = amt;
}
void Character::addhp(int amt)
{
	hp += amt;
}
void Character::setstr(int amt)
{
	str = amt;
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
	state = f;
}
void Character::clearflags(unsigned f)
{
	state &= ~f;
}
void Character::setname(std::string& n)
{
	name = n;
}
void Character::settype(CharType t)
{
	type = t;
}


int Character::attack(Character* ch)
{
	unsigned critchance = 10u;
	int dmg = rand_range(min, max);

	if (rand_range(1u, 100u) <= weap.hitrate()) {
		ch->setflags(Character::HIT);
		dmg += str + weap.getdmg();
		if (rand_range(1u, 100u) <= critchance) {
			ch->setflags(Character::CRIT);
			dmg += weap.getdmg() / 2;
		}
		ch->addhp(-dmg);
	}
	else {
		dmg = 0;
	}

	return dmg;
}


std::ostream& operator<< (std::ostream& o, Character const& ch)
{
	return o << ch.name;
}
