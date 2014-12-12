/*
 * parser.cpp - parse data for commands
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
