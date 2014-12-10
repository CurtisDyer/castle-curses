/*
 * utils.h - various useful macros or inline functions
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <cstdlib>
#include <climits>

// ensure the distribution is more evenly spread
inline unsigned rand_range(unsigned min, unsigned max)
{
	return min + std::rand() / (RAND_MAX / (max - min + 1) + 1);
}

inline void clean_up(bool err = false)
{
	std::exit(err ? EXIT_FAILURE : EXIT_SUCCESS);
}
#endif
