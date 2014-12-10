/*
 * characters.h - character data declarations
 */

#ifndef CHARACTERS_H_
#define CHARACTERS_H_

#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "weapons.h"

enum CharType { PLAYER, NPC };


class Character {
	void init();

protected:
	std::string name;
	Weapon weap;

	// more stats in the future?
	int hp;
	int str;

	CharType type;
	unsigned state;		// bit set

public:
	// option flags
	static const unsigned INIT	= 0u;
	static const unsigned HIT	= 1 << 0u;
	static const unsigned CRIT	= 1 << 1u;
	static const unsigned MISS	= 1 << 2u;

	Character();
	Character(std::string n, Weapon w, int hp, int str);

	friend std::ostream& operator<< (std::ostream& o, Character const& ch);

	int gethp() const;
	unsigned getflags() const;
	Weapon getweapon() const;
	bool is_dead() const;
	std::string getname() const;
	CharType gettype() const;

	void addhp(int amt);
	void setname(std::string& n);
	void setweapon(Weapon w);
	void setflags(unsigned f);
	void clearflags(unsigned f);
	void settype(const CharType& t);

	// moves
	virtual void attack(Character* ch, bool retaliate = true);
};


// The player character
struct Player : public Character {
	Player();
	Player(std::string n, Weapon w, int hp, int str);

	void attack(Character* ch, bool retaliate = true);
};


/*
 * NPCs - for now, the main difference is that their attacks don't
 * crit
 */
struct NPCharacter : public Character {
	NPCharacter();
	NPCharacter(std::string n, Weapon w, int hp, int str);

	void attack(Character* ch, bool retaliate = true);
};
#endif
