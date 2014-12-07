/*
 * utils.h - various useful macros or inline functions
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <cstdlib>
#include <climits>

// ensure the distribution is more evenly spread
// NB: this function assumes you've seeded the PRNG
inline unsigned rand_range(unsigned min, unsigned max)
{
	return min + std::rand() / (RAND_MAX / (max - min + 1) + 1);
}
#endif
