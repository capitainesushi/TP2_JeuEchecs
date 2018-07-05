#include "Pion.h"
#include "Case.h"

Pion::Pion(const Enums::EPieceColor a_PieceColor)
	: Piece(a_PieceColor == Enums::EPieceColor::Blanche ? "images/WPawn" : "images/BPawn")
{
	m_PieceType = Enums::EPieceType::Pion;
	m_PieceColor = a_PieceColor;

	for (int i = 0; i < Enums::EDirection::Direction_Count; i++)
	{
		m_PossibleAttacks.push_back(std::vector<std::tuple<int, int>>());
	}

	m_AvailableMoves[m_PieceColor == Enums::EPieceColor::Blanche ? Enums::EDirection::South : Enums::EDirection::North].push_back(std::tuple<int, int>(m_PieceColor == Enums::EPieceColor::Blanche ? -1 : 1, 0));
}

Pion::~Pion()
{
}