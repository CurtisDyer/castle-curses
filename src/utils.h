/*
 * utils.h - various useful macros or inline functions
 *
 * This is a minimal text-based game whose purpose is to demonstrate
 * modular programming.
 *
 * Copyright (C) 2014  Curtis Dyer
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <iostream>
#include <cstdlib>
#include <climits>

// ensure the distribution is more evenly spread
inline unsigned rand_range(unsigned min, unsigned max)
{
	return min + std::rand() / (RAND_MAX / (max - min + 1) + 1);
}

inline void clean_up(bool err = false)
{
	std::cout << "\nThanks for playing!\n";
	std::exit(err ? EXIT_FAILURE : EXIT_SUCCESS);
}
#endif
