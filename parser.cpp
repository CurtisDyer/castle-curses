/*
 * parser.cpp - parse data for commands
 */

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

#include "command.h"

// delimiter separating commands and arguments
#define DELIM ' '

/**
 * parse a line, lookup command, and store arguments, if appropriate
 *
 * @param src the source, or line of input
 * @param cmds the lookup table of commands
 * @return whether or not the parsing succeeds
 */
Command* parsecmd(std::string src, CmdTable& cmds)
{
	Command *result = NULL;

	std::stringstream ss(src);
	std::string name;
	if (std::getline(ss, name, DELIM)) {
		CmdTable::iterator it = cmds.find(name);
		if (it != cmds.end())
			result = it->second;

		if (result != NULL && result->accept_args()) {
			std::vector<std::string> args;
			std::string arg;
			while (std::getline(ss, arg, DELIM))
				args.push_back(arg);

			if (!args.empty())
				result->setargs(args);
			else if (result->requires_args() && args.empty())
				result = NULL;
		}
	}

	return result;
}
