/*
 * level.h - declarations for level class
 */

#ifndef LEVEL_H_
#define LEVEL_H_

#include <string>
#include <vector>

#include "messages.h"
#include "characters.h"


class Level {
	std::string name;
	std::string desc;
	unsigned id_;

	std::vector<Character*> chars;
	std::vector<Weapon*> weaps;

	std::vector<Character*>::iterator char_iter;
	std::vector<Weapon*>::iterator weap_iter;

	StringTable tbl;

public:
	Level() : id_(0)
	{
		char_iter = chars.begin();
		weap_iter = weaps.begin();
	};
	Level(std::string n, std::string d, unsigned id)
		: name(n), desc(d), id_(id)
	{
		char_iter = chars.begin();
		weap_iter = weaps.begin();
	};

	std::string getname() const { return name; };
	void setname(std::string n) { name = n; };

	std::string getmessage(std::string k)
	{
		std::string ret;
		if (tbl.count(k))
			ret = tbl[k];
		return ret;
	};

	std::string getdesc() const { return desc; };
	void setdesc(std::string d) { desc = d; };

	unsigned id() const { return id_; };
	unsigned id(unsigned newid) { return id_ = newid; };

	void initmessages(StringTable& t) { tbl = t; };

	Weapon* nextweap()
	{
		Weapon *w = NULL;
		if (++weap_iter != weaps.end())
			w = *weap_iter;
		return w;
	};
	Character* nextchar()
	{
		Character *c = NULL;
		if (++char_iter != chars.end())
			c = *char_iter;
		return c;
	}
	Character* getchar(std::string mob)
	{
		Character *m = NULL;
		for (size_t i = 0; m == NULL && i < chars.size(); ++i) {
			if (mob == chars[i]->getname())
				m = chars[i];
		}
		return m;
	}
	void resetweap() { weap_iter = weaps.begin(); };
	void resetchar() { char_iter = chars.begin(); };

	void addweap(Weapon *w) { weaps.push_back(w); };
	void addchar(Character *c) { chars.push_back(c); };
};
#endif
