/*
 * weapons.h - weapon data structure
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

#ifndef WEAPONS_H_
#define WEAPONS_H_

#include <string>

class Weapon {
	std::string name;
	unsigned hit;

	int dmg;

public:
	Weapon() : hit(0u), dmg(0) {};
	Weapon(std::string n, unsigned h, int d) : name(n), hit(h), dmg(d) {};

	int getdmg() const { return dmg; };
	std::string getname() const { return name; };
	unsigned hitrate() const { return hit; };

	void setname(std::string& n) { name = n; };
	void setdmg(int d) { dmg = d; };
};
#endif
