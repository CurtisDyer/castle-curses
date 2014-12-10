/*
 * errmessages.cpp - error messages
 */

#include <cstdio>
#include <string>
#include <cstdarg>

#include "messages.h"
#include "errmessages.h"

static StringTable tbl;

static void init_errors()
{
	if (tbl.empty()) {
		tbl["msg_not_found"] = "Unable to load message from language table.\n";
	}
}

void errormsg(std::string key, ...)
{
	init_errors();

	if (tbl.count(key)) {
		va_list args;
		va_start(args, key);

		std::string msg = "castle-curses:error:" + tbl[key];
		vfprintf(stderr, msg.c_str(), args);

		va_end(args);
	}
	else
		fputs("Error key not found\n", stderr);
}
