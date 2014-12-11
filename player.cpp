/*
 * player.cpp - player class declarations
 */

#include <string>

#include "characters.h"
#include "weapons.h"

Player::Player() : Character()
{
	type = PLAYER;

	// basic default attack range
	min = 10;
	max = 20;
}
Player::Player(std::string n, Weapon w, int hp, int str)
	: Character(n, w, hp, str)
{
	type = PLAYER;
}
Player::~Player() {}
