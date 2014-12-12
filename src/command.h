/*
 * command.h - command data structure
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

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <string>
#include <map>
#include <vector>

#include "characters.h"
#include "level.h"

class Command {
protected:
	std::vector<std::string> args;
	std::string name;
	bool args_ok;
	bool reqd;

public:
	Command() : args_ok(false), reqd(false) {};
	Command(std::string n, bool argv = false, bool r = false)
		: name(n), args_ok(argv), reqd(r) {};

	bool accept_args() const { return args_ok; };
	bool requires_args() const { return reqd; };

	std::vector<std::string> getargs() const { return args; };
	void setargs(std::vector<std::string> a) { args = a; };

	virtual void dispatch(Character* c, Level* lvl) =0;
};

typedef std::map<std::string,Command*> CmdTable;

/*
 * command parsing functions
 */
Command* parsecmd(std::string src, CmdTable& cmds);

#endif
