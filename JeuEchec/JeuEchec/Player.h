#pragma once
#include "Game.h"

class Board;

class Player
{
public:
	Player();
	~Player();

	// Pour aller chercher la mana du joueur 1 ou 2
	int GetMana() { return m_Mana; }
	
	// Se fait appeller après chaque tour
	void IncreaseMana() { m_Mana++; }

	//Quand je cast un player spell
	void DecreaseMana(int mana) { m_Mana -= mana; }

	// Mana du joueur
	int m_Mana;


	// Fonctions liés à chaque player spell;
	void CastSpell1(Piece* targetedPiece, int damage);
	void CastSpell2(Piece* targetedPiece);
	void CastSpell3(Piece* targetedPiece);
	void CastSpell4(Piece* targetedPiece);
	void CastSpell5(Piece* targetedPiece);

private:
	
	Board* m_Board;

};

