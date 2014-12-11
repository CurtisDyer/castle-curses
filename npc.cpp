/*
 * npc.cpp - non-player character class declarations
 */

#include <string>

#include "characters.h"
#include "utils.h"

NPCharacter::NPCharacter() : Character()
{
	type = NPC;
	min = 5;
	max = 10;
}
NPCharacter::NPCharacter(std::string n, Weapon w, int hp, int str)
	: Character(n, w, hp, str)
{
	type = NPC;
}
NPCharacter::~NPCharacter() {}

int NPCharacter::attack(Character* ch)
{
	unsigned roll = rand_range(1u, 100u);
	int dmg = rand_range(min, max);

	if (roll <= weap.hitrate()) {
		ch->setflags(Character::HIT);
		dmg = str + weap.getdmg();
		ch->addhp(-dmg);
	}

	return dmg;
}
