#include "Reine.h"

Reine::Reine(const Enums::EPieceColor a_PieceColor)
	: Piece(a_PieceColor == Enums::EPieceColor::Blanche ? "images/WQueen" : "images/BQueen")
{
	m_PieceType = Enums::EPieceType::Reine;
	m_PieceColor = a_PieceColor;

	for (int i = 1, j = 1; i < 8; i++, j++)
	{
		m_AvailableMoves[Enums::EDirection::North_East].push_back(std::tuple<int, int>(i, j));
		m_AvailableMoves[Enums::EDirection::North_West].push_back(std::tuple<int, int>(i, -j));
		m_AvailableMoves[Enums::EDirection::South_East].push_back(std::tuple<int, int>(-i, j));
		m_AvailableMoves[Enums::EDirection::South_West].push_back(std::tuple<int, int>(-i, -j));

		m_AvailableMoves[Enums::EDirection::North].push_back(std::tuple<int, int>(i, 0));
		m_AvailableMoves[Enums::EDirection::East].push_back(std::tuple<int, int>(0, j));
		m_AvailableMoves[Enums::EDirection::South].push_back(std::tuple<int, int>(-i, 0));
		m_AvailableMoves[Enums::EDirection::West].push_back(std::tuple<int, int>(0, -j));
	}
}

Reine::~Reine()
{
}