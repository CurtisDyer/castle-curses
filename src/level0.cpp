/*
 * level0.cpp - the first (and only) level!
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
#include <cstdio>
#include <string>

#include "level0.h"

#include "messages.h"
#include "errmessages.h"
#include "level.h"
#include "characters.h"

#include "command.h"
#include "commands.cpp" // TODO: separate sub-command declarations and definitions

static void setup_lang(Level& lvl)
{
	static StringTable tbl;
	tbl["help"] =
		"Here are the available commands. Arguments with <angle> brackets are\n"
		"mandatory, while arguments with [square] brackets are optional.\n\n"

		" - help             print this message.\n"
		" - attack <target>  attack the target named \"target\".\n"
		" - look [target]    without a [target], look around. Otherwise examine\n"
		"                    the [target] more closely.\n"
		" - exit             exit the game.\n";

	tbl["welcome"] = "Welcome to: ``%s!'' The level begins now!\n";

	tbl["default"] =
		"After forcing the rotted, once-elaborate door ajar, you step through\n"
		"the darkness beyond the yawning portcullis. Time has claimed this\n"
		"once-great castle. All that now reigns is vegetation and animal waste.\n"
		"You decide to push the large door further from the inside to let in\n"
		"more light. Your heart skips a beat. A gaunt figure slowly raises\n"
		"from a kneeling position and shuffles toward you.\n\n"

		"\"Was it...feeding?\" you absently think out loud.\n\n";

	tbl["stats"] = "%s: (%d / %d)\n";

	tbl["ghoul"] =
		"Your steady, well-trained hand reaches toward your blade. You realize\n"
		"now the rumors you heard aren't merely the ravings of the\n"
		"superstitious drunkards back in town. Unfortunately, this thing is\n"
		"standing between you and a nice payday. Beyond the dilapidated\n"
		"antechamber, you spot the fabled MacGuffin Crystal. It looks like this\n"
		"ghoul is going to have to die.\n\n";

	tbl["retaliate"] = "%s ATTACKS you for %d damage!\n";

	tbl["attack_target"] = "You ATTACK %s for %d damage!\n";
	tbl["crit_target"] = "You CRIT %s for %d damage!! (Note the extra exclamation mark.)\n";
	tbl["keep_attacking"] = "%s is still alive! Keep using `attack' until it's dead!\n";

	tbl["target_dead"] = "You killed %s.\n";
	tbl["player_dead"] = "You were slain by %s.\n";

	tbl["attackable"] = "Attackable Enemies:\n";
	tbl["enemy_item"] = "  - %s\n";

	tbl["win"] = "You won!\n";
	tbl["lose"] = "You lost!\n";

	tbl["prompt"] = "%s> ";

	lvl.initmessages(tbl);
}

static void print_intro()
{
	std::cout << "\n\n"
		"|| After your travels through the vageuly ominous Forest of Tolkien, you\n"
		"|| seek rest at the nearest town. While there, you hear rumors of townsfolk\n"
		"|| going missing near a ruined and, allegedly, cursed castle. More\n"
		"|| importantly, however, the lost relic you've been hunting is also\n"
		"|| reported to be in the area (at least according to the poor sap you\n"
		"|| left hanging from a tree in the forest).\n\n";
}

void run_level0(Character *player)
{
	Level intro(
			"Castle Curses",
			"Rumors of townsfolk going missing near a cursed castle have spread.",
			1);
	setup_lang(intro);

	std::printf(intro.getmessage("welcome").c_str(), intro.getname().c_str());
	print_intro();

	// make a ghoul
	Weapon claws("Claws", 50, 15);
	NPCharacter ghoul("ghoul", claws, 165, 10);
	ghoul.setweapon(claws);

	intro.addchar(player);
	intro.addchar(&ghoul);

	// commands
	Help help("help");
	Attack atk("attack");
	Look look("look");
	Exit exit("exit");

	CmdTable ctable;
	ctable["help"] = &help;
	ctable["attack"] = &atk;
	ctable["look"] = &look;
	ctable["exit"] = &exit;
	ctable["quit"] = &exit; // alias for exit

	help.dispatch(player, &intro);
	do {
		std::printf(intro.getmessage("prompt").c_str(), "Introduction");
		std::cout << std::flush;

		std::string line;
		if (std::getline(std::cin, line)) {
			Command *c;
			if ((c = parsecmd(line, ctable)) != NULL) {
				c->dispatch(player, &intro);
			}
		}
	} while (std::cin.good() && !intro.is_gameover());
}
