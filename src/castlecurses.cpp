/*
 * castlecurses.cpp - main entrypoint for program
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

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

#include "level0.h"
#include "errmessages.h"
#include "characters.h"
#include "weapons.h"
#include "utils.h"

static void welcome()
{
	std::cout <<
		"Welcome to CASTLE CURSES!!\n\n"

		"This is a barely complete text-based \"RPG\" *cough* game. The thrust\n"
		"of the project is to demonstrate modularity through object-oriented\n"
		"design. Starting from an organized base, even throwaway software like\n"
		"this can be built upon without needing to rewrite everything.\n\n"

		"Would you like to play? "
		<< std::flush;
}

int main()
{
	welcome();

	std::string line;
	if (std::getline(std::cin, line)) {
		if (line.find('y') != std::string::npos || line.find('Y') != std::string::npos) {
			std::string name;
			std::cout << "Name your character: " << std::flush;
			if (std::getline(std::cin, name)) {
				std::cout << "\n========================\n\n";
				Weapon sword("Vorpal Sword", 90, 30);
				Player p(name, sword, 220, 25);
				p.setweapon(sword);

				run_level0(&p);
			}
			else {
				errormsg("input_error");
			}
		}
	}
	else {
		errormsg("input_error");
	}

	clean_up();

	return 0;
}
