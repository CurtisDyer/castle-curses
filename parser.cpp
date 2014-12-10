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
 * fetch a token from string `s', delimited by `delim', store result in `t'
 *
 * @scope visible within this translation unit only
 * @return the current position in input sequence or `-1' upon failure
 */
static std::streampos gettoken(const std::string& s, std::string& t, char delim)
{
	std::stringstream ss(s);
	std::string tok;
	std::getline(ss, tok, delim);
	t = tok;

	return ss.tellg();
}

/**
 * parse a line, lookup command, and store arguments, if appropriate
 *
 * @param src the source, or line of input
 * @param cmds the lookup table of commands
 * @return whether or not the parsing succeeds
 */
bool parsecmd(std::string src, CmdTable& cmds)
{
	bool result = true;
	std::streampos p;
	std::string n;
	if ((p = gettoken(src, n, DELIM)) > -1) {
		CmdTable::iterator it = cmds.find(n);
		if (it == cmds.end())
			result = false;

		if (result && it->second->accept_args()) {
			std::string arg;
			std::vector<std::string> args;
			src = src.substr(p);
			while ((p = gettoken(src, arg, DELIM)) > -1) {
				src = src.substr(p);
				args.push_back(arg);
			}

			if (!src.empty())
				args.push_back(src);

			it->second->setargs(args);
			if (it->second->requires_args() && args.empty())
				result = false;
		}
	}
	else {
		result = false;
	}

	return result;
}
