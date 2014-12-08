/*
 * npc.cpp - non-player character class declarations
 */

#include <string>

#include "characters.h"

NPCharacter::NPCharacter() : Character() {}
NPCharacter::NPCharacter(std::string n, Weapon w, int hp, int str)
	: Character(n, w, hp, str) {}
