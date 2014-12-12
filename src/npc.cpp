/*
 * npc.cpp - non-player character class declarations
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

#include "characters.h"
#include "utils.h"

NPCharacter::NPCharacter() : Character()
{
	type = NPC;
	min = 5;
	max = 10;
}
NPCharacter::NPCharacter(std::string n, Weapon w, int hp, int str)
	: Character(n, w, hp, str)
{
	type = NPC;
}

int NPCharacter::attack(Character* ch)
{
	unsigned roll = rand_range(1u, 100u);
	int dmg = rand_range(min, max);

	if (roll <= weap.hitrate()) {
		ch->setflags(Character::HIT);
		dmg = str + weap.getdmg();
		ch->addhp(-dmg);
	}

	return dmg;
}
