/*
 * npc.cpp - non-player character class declarations
 */

#include <string>

#include "characters.h"
#include "utils.h"

NPCharacter::NPCharacter() : Character()
{
	type = NPC;
}

NPCharacter::NPCharacter(std::string n, Weapon w, int hp, int str)
	: Character(n, w, hp, str)
{
	type = NPC;
}

void NPCharacter::attack(Character* ch, bool retaliate)
{
	unsigned roll = rand_range(1u, 100u);
	int dmg = 0;

	if (roll <= weap.hitrate()) {
		ch->setflags(Character::HIT);
		dmg = str + weap.getdmg();
		ch->addhp(-dmg);
	}

	if (retaliate)
		ch->attack(this, false);
}
