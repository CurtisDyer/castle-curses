/*
 * commands.cpp - implementation for various commands
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

#ifndef SUBCOMMANDS_CPP_
#define SUBCOMMANDS_CPP_

#include <iostream>
#include <string>
#include <cstdio>

#include "messages.h"
#include "errmessages.h"
#include "command.h"
#include "level.h"
#include "utils.h"
#include "characters.h"

/*
 * help command output
 */
struct Help : public Command {
	Help() : Command() {};
	Help(std::string n, bool argv = false, bool reqd = false) : Command(n, argv, reqd) {};

	void dispatch(Character* c, Level* lvl)
	{
		std::cout << lvl->getmessage("help") << '\n';
	};

};

/*
 * player character attack command
 */
struct Attack : public Command {
	Attack() : Command() {};
	Attack(std::string n, bool argv = true, bool reqd = true) : Command(n, argv, reqd) {};

	void dispatch(Character* c, Level* lvl) {
		if (!args.empty()) {
			Character *npc = lvl->getchar(args[0]);

			c->clearflags(c->getflags());
			npc->clearflags(npc->getflags());

			const char *pname = c->getname().c_str();
			const char *npcname = npc->getname().c_str();
			const char *stats = lvl->getmessage("stats").c_str();

			int dmg = c->attack(npc);
			std::string k = (npc->getflags() & Character::CRIT) ? "crit_target" : "attack_target";
			std::printf(lvl->getmessage(k).c_str(), npcname, dmg);

			// retaliatory attack
			if (!npc->is_dead()) {
				dmg = npc->attack(c);
				std::printf(lvl->getmessage("retaliate").c_str(), npcname, dmg);
				std::printf(lvl->getmessage("keep_attacking").c_str(), npcname);
			}
			std::cout << '\n';

			std::printf(stats, pname, c->gethp(), c->getmaxhp());
			std::printf(stats, npcname, npc->gethp(), npc->getmaxhp());
			std::cout << '\n';

			if (npc->is_dead() || c->is_dead()) {
				const char *who;
				const char *tar;
				if (npc->is_dead()) {
					lvl->endgame(true);
					who = lvl->getmessage("target_dead").c_str();
					tar = npcname;
				}
				else {
					lvl->endgame(false);
					who = lvl->getmessage("player_dead").c_str();
					tar = pname;
				}
				std::printf(who, tar);
			}
			args.clear();
		}
	};
};

/*
 * look command - gives player information about the level
 */
struct Look : public Command {
	Look() : Command() {};
	Look(std::string n, bool argv = true, bool reqd = false) : Command(n, argv, reqd) {};

	void dispatch(Character* c, Level* lvl) {
		std::cout << lvl->getmessage(args.empty() ? "default" : args[0]);

		std::cout << lvl->getmessage("attackable");

		Character *enemy;
		lvl->resetchar();
		while ((enemy = lvl->nextchar()) != NULL) {
			if (enemy->gettype() == NPC)
				std::printf(lvl->getmessage("enemy_item").c_str(), enemy->getname().c_str());
		}
		args.clear();
	};
};

/*
 * exit command
 */
struct Exit : public Command {
	Exit() : Command() {};
	Exit(std::string n) : Command(n) {};

	void dispatch(Character* c, Level* lvl)
	{
		clean_up();
	};
};
#endif
