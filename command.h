/*
 * command.h - command data structure
 */

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <string>
#include <map>
#include <vector>

#include "characters.h"
#include "level.h"

// FIXME: adding args data member was mistake, return to
// Character::dispatch() as parameter.
//
// FIXME: Look::dispatch is behaving strangely
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
