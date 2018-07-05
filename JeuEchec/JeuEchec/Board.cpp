#include "Board.h"
#include "Case.h"
#include "Game.h"
#include <SDL_image.h>

const int Board::CASE_NUMBER = 8;
const int Board::CASE_WIDTH = 100;
const int Board::CASE_HEIGHT = 100;

Board::Board()
	: m_CurrentCase(nullptr)
{
	Init();
}

Board::~Board()
{
	if (m_CurrentCase != nullptr)
	{
		m_CurrentCase = nullptr;
	}

	for (std::vector<std::vector<Case*>>::iterator iter = m_Cases.begin(); iter != m_Cases.end(); iter++)
	{
		for (std::vector<Case*>::iterator iter2 = (*iter).begin(); iter2 != (*iter).end(); iter2++)
		{
			delete (*iter2);
			(*iter2) = nullptr;
		}
		(*iter).clear();
	}
	m_Cases.clear();

	if (m_BoardTexture != nullptr)
	{
		SDL_FreeSurface(m_BoardTexture);
		m_BoardTexture = nullptr;
	}
}

void Board::Init()
{
	m_BoardTexture = IMG_Load(BOARD_TEXTURE_PATH.c_str());

	// Create all cases
	m_Cases = std::vector<std::vector<Case*>>();
	for (int i = 0; i < CASE_NUMBER; i++)
	{
		m_Cases.push_back(std::vector<Case*>());

		for (int j = 0; j < CASE_NUMBER; j++)
		{
			if (i < 2 || i > 5)
			{
				Enums::EPieceColor pieceColor = i < 2 ? Enums::EPieceColor::Noire : Enums::EPieceColor::Blanche;
				if (i == 1 || i == 6)
				{
					m_Cases[i].push_back(new Case(j * Board::CASE_WIDTH, i * Board::CASE_HEIGHT, Enums::EPieceType::Pion, pieceColor));
				}
				else if (i == 0 || i == 7)
				{
					switch (j) 
					{
					case 0:
					case 7:
						m_Cases[i].push_back(new Case(j * Board::CASE_WIDTH, i * Board::CASE_HEIGHT, Enums::EPieceType::Tour, pieceColor));
						break;
					case 1:
					case 6:
						m_Cases[i].push_back(new Case(j * Board::CASE_WIDTH, i * Board::CASE_HEIGHT, Enums::EPieceType::Chevalier, pieceColor));
						break;
					case 2:
					case 5:
						m_Cases[i].push_back(new Case(j * Board::CASE_WIDTH, i * Board::CASE_HEIGHT, Enums::EPieceType::Fou, pieceColor));
						break;
					case 3:
						m_Cases[i].push_back(new Case(j * Board::CASE_WIDTH, i * Board::CASE_HEIGHT, Enums::EPieceType::Roi, pieceColor));
						break;
					case 4:
						m_Cases[i].push_back(new Case(j * Board::CASE_WIDTH, i * Board::CASE_HEIGHT, Enums::EPieceType::Reine, pieceColor));
						break;
					}
				}
			}
			else 
			{
				m_Cases[i].push_back(new Case(j * Board::CASE_WIDTH, i * Board::CASE_HEIGHT));
			}
		}
	}
}

void Board::Draw(SDL_Surface* a_Parent)
{
	SDL_BlitSurface(m_BoardTexture, NULL, a_Parent, NULL);

	for (std::vector<std::vector<Case*>>::const_iterator iter = m_Cases.begin(); iter != m_Cases.end(); iter++)
	{
		for (std::vector<Case*>::const_iterator iter2 = (*iter).begin(); iter2 != (*iter).end(); iter2++)
		{
			if (m_CurrentCase == nullptr || (*iter2) != m_CurrentCase)
			{
				(*iter2)->Draw(a_Parent);
			}			
		}
	}

	if (m_CurrentCase != nullptr) 
	{
		m_CurrentCase->Draw(a_Parent);
	}
}

void Board::Update()
{

}

void Board::MouseButtonDown(const int a_X, const int a_Y)
{
	int i = a_Y / Board::CASE_WIDTH;
	int j = a_X / Board::CASE_HEIGHT;

	Case* caseTargeted = m_Cases[i][j];
	if (caseTargeted->IsNotEmpty() && caseTargeted->IsPieceIsThisColor(Game::GetColorTurn()))
	{
		m_CurrentCase = m_Cases[i][j];
		m_AvailableMoveForCurrentPiece = m_CurrentCase->GetAvailableMoves(m_Cases);
		m_CurrentCase->Move(a_X, a_Y);
	}
}

void Board::MouseMotion(const int a_X, const int a_Y)
{
	if (m_CurrentCase != nullptr) 
	{
		m_CurrentCase->Move(a_X, a_Y);
	}
}

void Board::MouseButtonUp(const int a_X, const int a_Y)
{
	if (m_CurrentCase != nullptr)
	{
		int i = a_Y / Board::CASE_WIDTH;
		int j = a_X / Board::CASE_HEIGHT;

		Case* caseTargeted = m_Cases[i][j];
		if (std::find(m_AvailableMoveForCurrentPiece.begin(), m_AvailableMoveForCurrentPiece.end(), std::tuple<int, int>(i, j)) != m_AvailableMoveForCurrentPiece.end())
		{
			// The targeted case is empty
			if (caseTargeted->IsEmpty())
			{
				caseTargeted->SwapPieceWith(m_CurrentCase);
				Game::ChangeColorTurn();
			}
			else if (caseTargeted->IsPieceIsNotThisColor(Game::GetColorTurn()))
			{
				caseTargeted->SwapPieceWith(m_CurrentCase);
				m_CurrentCase->RemovePiece();
				Game::ChangeColorTurn();
			}
		}


		m_CurrentCase->BackToOriginalPosition();
		m_CurrentCase = nullptr;
	}
}