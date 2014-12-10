/*
 * commands.cpp - implementation for various commands
 */

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
	Help(std::string n, bool argv, bool reqd) : Command(n, argv, reqd) {};

	void dispatch(Character* c, Level* lvl, const std::vector<std::string>& args)
	{
		std::cout << lvl->getmessage("help") << '\n';
	};

};

/*
 * player character attack command
 */
struct Attack : public Command {
	Attack() : Command() {};
	Attack(std::string n, bool argv, bool reqd) : Command(n, argv, reqd) {};

	void dispatch(Character* c, Level* lvl, const std::vector<std::string>& args)
	{
		if (!args.empty()) {
			Character *npc = lvl->getchar(args[0]);
			c->attack(npc);
		}
	};
};

/*
 * look command - gives player information about the level
 */
struct Look : public Command {
	Look() : Command() {};
	Look(std::string n, bool argv, bool reqd) : Command(n, argv, reqd) {};

	void dispatch(Character* c, Level* lvl, const std::vector<std::string>& args)
	{
		std::string look = lvl->getmessage(args.empty() ? "default" : args[0]);

		if (!look.empty()) {
			std::cout << look;
			Character *enemy;
			while ((enemy = lvl->nextchar()) != NULL) {
				if (enemy->gettype() == NPC)
					printf(lvl->getmessage("enemy_item").c_str(), enemy->getname().c_str());
			}
		}
		else
			errormsg("msg_not_found");
	};
};

/*
 * exit command
 */
struct Exit : public Command {
	Exit() : Command() {};
	Exit(std::string n) : Command(n) {};

	void dispatch(Character* c, Level* lvl, const std::vector<std::string>& args)
	{
		clean_up();
	};
};
