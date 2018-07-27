#include "Player.h"
#include <iostream>
#include "Board.h"

Player::Player()
{
	m_Mana = 0;
}


Player::~Player()
{
}

void Player::CastSpell1(Piece* targetedPiece, int damage)
{	
	targetedPiece->AddDamage(damage);	
}

void Player::CastSpell2(Piece* targetedPiece)
{
	targetedPiece->Invincibility();
}

void Player::CastSpell3(Piece* targetedPiece)
{
	targetedPiece->RestoreSpell();
}

void Player::CastSpell4(Piece* targetedPiece)
{
	targetedPiece->DamageArmorBoost();
}

void Player::CastSpell5(Piece* targetedPiece)
{
}





