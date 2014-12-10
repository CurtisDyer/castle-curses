/*
 * commands.cpp - implementation for various commands
 */

#include <iostream>
#include <string>

#include "messages.h"
#include "command.h"
#include "level.h"

/*
 * help command output
 */
struct Help : public Command {
	Help() : name("help"), Command() {};
	Help(bool argv, bool reqd) : Command(argv, reqd) {};

	void dispatch(Character* c, const std::vector<std::string>& args)
	{
		cmd_message(HelpMessages::table["help"]);
	};

protected:
	std::string name;
};

/*
 * player character attack command
 */
struct Attack : public Command {
	Help() : name("attack"), Command() {};
	Help(bool argv, bool reqd) : Command(argv, reqd) {};

	void dispatch(Character* c, Level* lvl, const std::vector<std::string>& args)
	{
		if (!args.empty()) {
			NPCharacter npc = lvl->getmob(args[0]);
			c->attack(&npc);
		}
	};
};

/*
 * look command - gives player information about the level
 */
struct Look : public Command {
	Help() : name("look"), Command() {};
	Help(bool argv, bool reqd) : Command(argv, reqd) {};

	void dispatch(Character* c, Level* lvl, const std::vector<std::string>& args)
	{
		std::string lvlname = lvl->getname();
		std::string k = lvlname + (args.empty() ? "_default" : args[0]);

		if (LookMessages::table.count(k))
			cmd_message(LookMessages::table[k]);
		else
			cmd_message(ErrorMessages::table["msg_not_found"]);
	};
};
