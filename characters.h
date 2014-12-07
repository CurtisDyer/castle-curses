/*
 * characters.h - character data declarations
 */

#ifndef CHARACTERS_H_
#define CHARACTERS_H_

#include <string>
#include <iostream>

#include "weapons.h"

/** for now, a very limited character class */
class Character {
protected:
	std::string name;
	Weapon weap;

	// more stats in the future?
	int hp;
	int str;

	unsigned state;		// bit set

public:
	// state modifier flags
	static const unsigned INIT	= 0u;
	static const unsigned HIT	= 1 << 0u;
	static const unsigned CRIT	= 1 << 1u;
	static const unsigned MISS	= 1 << 2u;

	// constructors
	Character();
	Character(std::string n, Weapon& w, int hp, int str);

	friend std::ostream& operator<< (std::ostream& o, Character const& ch);

	// stat behaviors
	int gethp() const;
	unsigned getflags() const;
	bool is_dead() const;

	virtual void addhp(int amt);
	void setflags(unsigned f);
	void clearflags(unsigned f);

	// moves
	virtual void attack(Character* ch);
};


/**
 * The player character
 */
struct Player : public Character {
	Player();
	Player(std::string n, Weapon w, int hp);

	void attack(Character* ch);
};


/**
 * NPCs - for now, the main difference is that their attacks don't
 * crit
 */
struct NPCharacter : public Character {
	NPCharacter();
	NPCharacter(std::string n, Weapon w, int hp);

	void attack(Character* ch);
};
#endif
