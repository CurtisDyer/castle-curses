/*
 * characters.h - character data declarations
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

#ifndef CHARACTERS_H_
#define CHARACTERS_H_

#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "weapons.h"

enum CharType {
	PLAYER,
	NPC
};

class Character {
	void init();

protected:
	std::string name;
	Weapon weap;
	CharType type;

	// more stats in the future?
	int hp;
	int str;
	int maxhp;

	// damage range
	int min;
	int max;

	unsigned state;		// bit set

public:
	/** initial state */
	static const unsigned INIT	= 0u;
	/** character was hit */
	static const unsigned HIT	= 1 << 0u;
	/** character was critically hit */
	static const unsigned CRIT	= 1 << 1u;
	/** character missed */
	static const unsigned MISS	= 1 << 2u;

	Character();

	/**
	 * create character with name, weapon, HP, and strength
	 * @param name
	 * @param health points
	 * @param strength
	 */
	Character(std::string n, int hp, int str);

	/**
	 * Create character with just a name
	 * @param name character name
	 */
	Character(std::string n);

	virtual ~Character();

	/**
	 * Output stream behavior for our Character objects
	 * @param output stream
	 * @param a Character object (automatically string-ifies to name)
	 * @return the output stream passed
	 */
	friend std::ostream& operator<< (std::ostream& o, Character const& ch);

	int gethp() const;
	int getmaxhp() const;
	unsigned getflags() const;
	bool is_dead() const;
	Weapon getweapon() const;
	std::string getname() const;
	CharType gettype() const;

	void sethp(int amt);
	void addhp(int amt);
	void setstr(int amt);
	void setmaxhp(int hp);
	void setname(std::string& n);
	void setweapon(Weapon w);
	void setflags(unsigned f);
	void clearflags(unsigned f);
	void settype(CharType t);

	/**
	 * attack a target character
	 * @param the target character
	 * @return the amount of damage dealt
	 */
	virtual int attack(Character* ch);
};


// The player character
struct Player : public Character {
	Player();
	Player(std::string n);
	Player(std::string n, int hp, int str);
};


/*
 * NPCs - for now, the main difference is that their attacks don't
 * crit
 */
struct NPCharacter : public Character {
	NPCharacter();
	NPCharacter(std::string n);
	NPCharacter(std::string n, int hp, int str);

	int attack(Character* ch);
};

std::ostream& operator<< (std::ostream& o, Character const& ch);
#endif
