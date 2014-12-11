/*
 * commands.cpp - implementation for various commands
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

	void dispatch(Character* c, Level* lvl)
	{
		if (!args.empty()) {
			Character *npc = lvl->getchar(args[0]);
			int dmg = c->attack(npc, false);

			const char *pname = c->getname().c_str();
			const char *npcname = npc->getname().c_str();
			const char *stats = lvl->getmessage("stats").c_str();

			printf(stats, pname, c->gethp(), c->getmaxhp());
			printf(stats, npcname, npc->gethp(), npc->getmaxhp());
			std::cout << '\n';

			std::string k = (npc->getflags() & Character::CRIT) ? "crit_target" : "attack_target";
			printf(lvl->getmessage(k).c_str(), args[0].c_str(), dmg);

			// retaliatory attack
			if (!npc->is_dead()) {
				printf(lvl->getmessage("retaliate").c_str(), npcname);
				dmg = npc->attack(c, false);
				printf(lvl->getmessage("attack_target").c_str(), pname);
			}
			std::cout << '\n';

			printf(stats, pname, c->gethp(), c->getmaxhp());
			printf(stats, npcname, npc->gethp(), npc->getmaxhp());
			std::cout << '\n';

			if (npc->is_dead() || c->is_dead()) {
				const char *who;
				const char *tar;
				if (npc->is_dead()) {
					who = lvl->getmessage("target_dead").c_str();
					tar = npcname;
				}
				else {
					who = lvl->getmessage("player_dead").c_str();
					tar = pname;
				}
				printf(who, tar);
			}
		}
	};
};

/*
 * look command - gives player information about the level
 * FIXME
 */
struct Look : public Command {
	Look() : Command() {};
	Look(std::string n, bool argv = true, bool reqd = false) : Command(n, argv, reqd) {};

	void dispatch(Character* c, Level* lvl)
	{
		if (args.empty()) {
			std::cout << lvl->getmessage("default");
		}
		else {
			Character *enemy;
			lvl->resetchar();
			while ((enemy = lvl->nextchar()) != NULL) {
				if (enemy->gettype() == NPC)
					printf(lvl->getmessage("enemy_item").c_str(), enemy->getname().c_str());
			}
		}
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
