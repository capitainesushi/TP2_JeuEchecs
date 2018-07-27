#include "Fou.h"

Fou::Fou(const Enums::EPieceColor a_PieceColor)
	: Piece(a_PieceColor == Enums::EPieceColor::Blanche ? "images/WBishop" : "images/BBishop")
{
	m_PieceType = Enums::EPieceType::Fou;
	m_PieceColor = a_PieceColor;

	m_Hp = 6;
	m_AttackDamage = 2;
	m_Armor = 1;

	m_SpellAvailable = false;

	for (int i = 1, j = 1; i < 8; i++, j++)
	{
		m_AvailableMoves[Enums::EDirection::North_East].push_back(std::tuple<int, int>(i, j));
		m_AvailableMoves[Enums::EDirection::North_West].push_back(std::tuple<int, int>(i, -j));
		m_AvailableMoves[Enums::EDirection::South_East].push_back(std::tuple<int, int>(-i, j));
		m_AvailableMoves[Enums::EDirection::South_West].push_back(std::tuple<int, int>(-i, -j));
	}
}

Fou::~Fou()
{
}