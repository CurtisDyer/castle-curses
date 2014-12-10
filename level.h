/*
 * level.h - declarations for level class
 */

#ifndef LEVEL_H_
#define LEVEL_H_

#include <string>
#include <vector>

class Level {
	std::string name;
	std::string desc;
	unsigned id_;

	std::vector<Character*> chars;
	std::vector<Weapon*> weaps;

public:
	Level() : id_(0) {};
	Level(std::string n, std::string d, unsigned id)
		: name(n), desc(d), id_(id) {};

	std::string getname() const { return name; };
	void setname(std::string n) { name = n; };

	std::string getdesc() const { return desc; };
	void setdesc(std::string d) { desc = d; };

	unsigned id() const { return id_; };
	unsigned id(unsigned newid) { return id_ = newid; };

	void addweap(const Weapon *w) { weaps.push_back(w); };
	void addchar(const Character *c) { chars.push_back(c); };
};
