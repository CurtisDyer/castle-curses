/*
 * player.cpp - player class declarations
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

#include "characters.h"
#include "weapons.h"

Player::Player() : Character()
{
	settype(PLAYER);

	// basic default attack range
	min = 15;
	max = 25;
}
Player::Player(std::string n)
	: Character(n)
{
	settype(PLAYER);

	min = 15;
	max = 25;
}
Player::Player(std::string n, int hp, int str)
	: Character(n, hp, str)
{
	settype(PLAYER);

	// basic default attack range
	min = 15;
	max = 25;
}
