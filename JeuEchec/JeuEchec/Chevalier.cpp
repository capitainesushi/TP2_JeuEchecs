#include "Chevalier.h"

Chevalier::Chevalier(const Enums::EPieceColor a_PieceColor)
	: Piece(a_PieceColor == Enums::EPieceColor::Blanche ? "images/WKnight" : "images/BKnight")
{
	m_PieceType = Enums::EPieceType::Chevalier;
	m_PieceColor = a_PieceColor;
	
	m_AvailableMoves[Enums::EDirection::South_West].push_back(std::tuple<int, int>(-1, -2));
	m_AvailableMoves[Enums::EDirection::North_West].push_back(std::tuple<int, int>(1, -2));
	m_AvailableMoves[Enums::EDirection::South_East].push_back(std::tuple<int, int>(-1, 2));
	m_AvailableMoves[Enums::EDirection::North_East].push_back(std::tuple<int, int>(1, 2));

	m_AvailableMoves[Enums::EDirection::South_West].push_back(std::tuple<int, int>(-1, -2));
	m_AvailableMoves[Enums::EDirection::North_West].push_back(std::tuple<int, int>(1, -2));
	m_AvailableMoves[Enums::EDirection::South_East].push_back(std::tuple<int, int>(-1, 2));
	m_AvailableMoves[Enums::EDirection::North_East].push_back(std::tuple<int, int>(1, 2));

	m_AvailableMoves[Enums::EDirection::South_West].push_back(std::tuple<int, int>(-2, -1));
	m_AvailableMoves[Enums::EDirection::North_West].push_back(std::tuple<int, int>(2, -1));
	m_AvailableMoves[Enums::EDirection::South_East].push_back(std::tuple<int, int>(-2, 1));
	m_AvailableMoves[Enums::EDirection::North_East].push_back(std::tuple<int, int>(2, 1));
}

Chevalier::~Chevalier()
{
}