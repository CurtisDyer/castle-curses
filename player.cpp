/*
 * player.cpp - player class declarations
 */

#include <string>

#include "characters.h"

Player::Player() : Character() {}
Player::Player(std::string n, Weapon w, int hp, int str)
	: Character(n, w, hp, str) {}