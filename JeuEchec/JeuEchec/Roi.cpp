#include "Roi.h"

Roi::Roi(const Enums::EPieceColor a_PieceColor)
	: Piece(a_PieceColor == Enums::EPieceColor::Blanche ? "images/WKing" : "images/BKing")
{
	m_PieceType = Enums::EPieceType::Roi;
	m_PieceColor = a_PieceColor;

	m_Hp = 12;
	m_AttackDamage = 2;
	m_Armor = 2;

	m_SpellAvailable = true;

	m_AvailableMoves[Enums::EDirection::East].push_back(std::tuple<int, int>(0, 1));
	m_AvailableMoves[Enums::EDirection::North_East].push_back(std::tuple<int, int>(1, 1));
	m_AvailableMoves[Enums::EDirection::North].push_back(std::tuple<int, int>(1, 0));
	m_AvailableMoves[Enums::EDirection::North_West].push_back(std::tuple<int, int>(1, -1));
	m_AvailableMoves[Enums::EDirection::West].push_back(std::tuple<int, int>(0, -1));
	m_AvailableMoves[Enums::EDirection::South_West].push_back(std::tuple<int, int>(-1, -1));
	m_AvailableMoves[Enums::EDirection::South].push_back(std::tuple<int, int>(-1, 0));
}

Roi::~Roi()
{
}