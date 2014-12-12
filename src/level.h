/*
 * level.h - declarations for level class
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

#ifndef LEVEL_H_
#define LEVEL_H_

#include <string>
#include <vector>
#include <utility>

#include "messages.h"
#include "characters.h"


class Level {
	std::string name;
	std::string desc;

	std::vector<Character*> chars;
	std::vector<Weapon*> weaps;

	std::vector<Character*>::iterator char_iter;
	std::vector<Weapon*>::iterator weap_iter;

	StringTable tbl;

	std::pair<bool,bool> gameover;

	unsigned id_;

public:
	Level() : id_(0)
	{
		char_iter = chars.begin();
		weap_iter = weaps.begin();
		gameover = std::make_pair(false, false);
	};
	Level(std::string n, std::string d, unsigned id)
		: name(n), desc(d), id_(id)
	{
		char_iter = chars.begin();
		weap_iter = weaps.begin();
		gameover = std::make_pair(false, false);
	};

	std::string getname() const { return name; };
	void setname(std::string n) { name = n; };

	bool is_gameover() const { return gameover.first; };
	bool player_wins() const { return gameover.first && gameover.second; };

	void endgame(bool win = true) {
		gameover = std::make_pair(true, win);
	};

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
