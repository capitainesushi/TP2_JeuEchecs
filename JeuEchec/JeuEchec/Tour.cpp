#include "Tour.h"

Tour::Tour(const Enums::EPieceColor a_PieceColor)
	: Piece(a_PieceColor == Enums::EPieceColor::Blanche ? "images/WTower" : "images/BTower")
{
	m_PieceType = Enums::EPieceType::Tour;
	m_PieceColor = a_PieceColor;

	for (int i = 1, j = 1; i < 8; i++, j++)
	{
		m_AvailableMoves[Enums::EDirection::North].push_back(std::tuple<int, int>(i, 0));
		m_AvailableMoves[Enums::EDirection::East].push_back(std::tuple<int, int>(0, j));
		m_AvailableMoves[Enums::EDirection::South].push_back(std::tuple<int, int>(-i, 0));
		m_AvailableMoves[Enums::EDirection::West].push_back(std::tuple<int, int>(0, -j));
	}
}

Tour::~Tour()
{
}