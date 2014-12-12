/*
 * errmessages.cpp - error messages
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
		tbl["input_error"] = "Error reading input.\n";
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
