/*
 * castlecurses.cpp - main entrypoint for program
 */

#include <iostream>
#include <string>

#include "level0.h"
#include "errmessages.h"
#include "characters.h"
#include "weapons.h"

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
				Weapon sword("Vorpal Sword", 90, 30);
				Player p(name, sword, 220, 25);
				p.setweapon(sword);

				run_level0(&p);

				if (p.is_dead()) {
					std::cout << "\nGame Over, man! GAME OVER!\n";
				}
				else {
					std::cout << "\nCONGLATURATION !!! YOU HAVE COMPLETED GREAT GAME.\n";
				}
			}
			else {
				errormsg("input_error");
			}
		}
	}
	else {
		errormsg("input_error");
	}

	return 0;
}
