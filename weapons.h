/*
 * weapons.h - weapon data structure
 */

#ifndef WEAPONS_H_
#define WEAPONS_H_

#include <string>

class Weapon {
	std::string name;
	unsigned hit;

	int dmg;

public:
	Weapon() : hit(0u), dmg(0) {};
	Weapon(std::string n, unsigned h, int d) : name(n), hit(h), dmg(d) {};

	int getdmg() const { return dmg; };
	std::string getname() const { return name; };
	unsigned hitrate() const { return hit; };

	void setname(std::string& n) { name = n; };
	void setdmg(int d) { dmg = d; };
};
#endif
