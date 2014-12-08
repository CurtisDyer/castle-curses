/*
 * command.h - command data structure
 */

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <string>
#include <map>
#include <vector>

struct Command {
	Command(dispatch d, bool argv = false, bool r = false)
		: dispatch(d), (args_ok(argv), reqd(r) {};

	bool accept_args() const { return args_ok; };
	bool requires_args() const { return reqd; };

	std::vector<std::string> getargs() const { return args; };
	void setargs(const std::vector<std::string>& a) { args = a; };

	virtual void dispatch(const std::vector<std::string>&) =0;

private:
	std::vector<std::string> args;
	bool args_ok;
	bool reqd;
};

typedef std::map<std::string,Command*> CmdTable;

#endif
