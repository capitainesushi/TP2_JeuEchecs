#include "Case.h"
#include "Board.h"
#include "Pion.h"
#include "Tour.h"
#include "Chevalier.h"
#include "Fou.h"
#include "Reine.h"
#include "Roi.h"
#include <tuple>

Case::Case(const int a_X, const int a_Y)
	: m_OriginalX(a_X)
	, m_OriginalY(a_Y)
{
	Init();
}

Case::Case(const int a_X, const int a_Y, const Enums::EPieceType a_PieceType, const Enums::EPieceColor a_Color)
	: Case(a_X, a_Y)
{
	switch (a_PieceType)
	{
	case Enums::EPieceType::Pion:
		m_Piece = new Pion(a_Color);
		break;
	case Enums::EPieceType::Tour:
		m_Piece = new Tour(a_Color);
		break;
	case Enums::EPieceType::Chevalier:
		m_Piece = new Chevalier(a_Color);
		break;
	case Enums::EPieceType::Fou:
		m_Piece = new Fou(a_Color);
		break;
	case Enums::EPieceType::Reine:
		m_Piece = new Reine(a_Color);
		break;
	case Enums::EPieceType::Roi:
		m_Piece = new Roi(a_Color);
		break;
	default:
		break;
	}
}

Case::~Case()
{
	if (m_Piece != nullptr)
	{
		delete m_Piece;
	}
}

void Case::Init()
{
	m_Rect = { m_OriginalX, m_OriginalY, Board::CASE_WIDTH, Board::CASE_HEIGHT };
}

void Case::Draw(SDL_Surface* a_Parent)
{
	if (m_Piece != nullptr) 
	{
		m_Piece->Draw(a_Parent, &m_Rect);
	}
}

void Case::Update()
{

}

void Case::Move(int a_X, int a_Y)
{
	m_Rect.x = a_X - static_cast<int>(Board::CASE_WIDTH * 0.5f);
	m_Rect.y = a_Y - static_cast<int>(Board::CASE_HEIGHT * 0.5f);
}

void Case::SwapPieceWith(Case* a_OtherCase)
{
	Piece* tempPiece = m_Piece;
	m_Piece = a_OtherCase->m_Piece;
	a_OtherCase->m_Piece = tempPiece;
}

std::vector<std::tuple<int, int>> Case::GetAvailableMoves(const std::vector<std::vector<Case*>> a_Cases)
{
	if (m_Piece == nullptr)
	{
		return std::vector<std::tuple<int, int>>();
	}

	std::vector<std::tuple<int, int>> availableMoves = std::vector<std::tuple<int, int>>();

	// Look for availablesMoves
	std::vector<std::vector<std::tuple<int, int>>> possibleMoves = m_Piece->GetPossibleMoves();

	// Go trought all directions availables for the piece
	for (std::vector<std::vector<std::tuple<int, int>>>::iterator iter2 = possibleMoves.begin(); iter2 != possibleMoves.end(); iter2++)
	{
		// Check all available cases
		for (std::vector<std::tuple<int, int>>::iterator iter = (*iter2).begin(); iter != (*iter2).end(); iter++)
		{
			// Update the index of the move with the I and J of this case.
			(*iter) = std::tuple<int, int>(std::get<0>(*iter) + GetI(), std::get<1>(*iter) + GetJ());

			int i = std::get<0>(*iter);
			int j = std::get<1>(*iter);
			if (i > -1 && i < Board::CASE_NUMBER && j > -1 && j < Board::CASE_NUMBER)
			{
				if (a_Cases[i][j]->IsEmpty())
				{
					// handle the special start move of pawn
					if (m_Piece->GetType() == Enums::EPieceType::Pion)
					{
						if (GetI() == (m_Piece->GetColor() == Enums::EPieceColor::Blanche ? 6 : 1))
						{
							std::tuple<int, int> possibleCase = std::tuple<int, int>(i + (m_Piece->GetColor() == Enums::EPieceColor::Blanche ? -1 : 1), j);
							if (a_Cases[std::get<0>(possibleCase)][std::get<1>(possibleCase)]->IsEmpty())
							{
								availableMoves.push_back(possibleCase);
							}
						}
					}
					availableMoves.push_back(*iter);
				}
				else if (m_Piece->GetType() != Enums::EPieceType::Chevalier) // the only piece to jump over other pieces is the knight.
				{
					break;
				}
			}
		}
	}
	
	// Look for availableAttacks
	possibleMoves = m_Piece->GetPossibleAttack();

	// Go trought all directions availables for the piece
	for (std::vector<std::vector<std::tuple<int, int>>>::iterator iter2 = possibleMoves.begin(); iter2 != possibleMoves.end(); iter2++)
	{
		// Check all available cases
		for (std::vector<std::tuple<int, int>>::iterator iter = (*iter2).begin(); iter != (*iter2).end(); iter++)
		{
			// Update the index of the move with the I and J of this case.
			(*iter) = std::tuple<int, int>(std::get<0>(*iter) + GetI(), std::get<1>(*iter) + GetJ());

			int i = std::get<0>(*iter);
			int j = std::get<1>(*iter);
			if (i > -1 && i < Board::CASE_NUMBER && j > -1 && j < Board::CASE_NUMBER)
			{
				// If a piece of the opposite color is found, add the targeted indexes, and look for another direction.
				if (a_Cases[i][j]->IsNotEmpty() && a_Cases[i][j]->IsPieceIsNotThisColor(m_Piece->GetColor()))
				{
					availableMoves.push_back(*iter);
					break;
				}
			}
		}
	}

	return availableMoves;
}

void Case::BackToOriginalPosition() 
{
	m_Rect.x = m_OriginalX;
	m_Rect.y = m_OriginalY;
}