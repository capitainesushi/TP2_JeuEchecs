#include "Board.h"
#include "Case.h"
#include "Game.h"
#include <SDL_image.h>
#include <iostream>

const int Board::CASE_NUMBER = 8;
const int Board::CASE_WIDTH = 100;
const int Board::CASE_HEIGHT = 100;
const int Board::X_OFFSET = 100;
const int Board::Y_OFFSET = 100;

Board::Board()
	: m_CurrentCase(nullptr)
{
	m_Player1 = new Player();
	m_Player2 = new Player();

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

	if (m_Player1 != nullptr)
	{
		delete (m_Player1);
	}

	if (m_Player2 != nullptr)
	{
		delete (m_Player2);
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
	SDL_Rect r = { X_OFFSET, Y_OFFSET, CASE_WIDTH * CASE_NUMBER, CASE_HEIGHT * CASE_NUMBER };
	SDL_BlitSurface(m_BoardTexture, NULL, a_Parent, &r);

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
	int i = (a_Y - Y_OFFSET) / Board::CASE_WIDTH;
	int j = (a_X - X_OFFSET) / Board::CASE_HEIGHT;

	Case* caseTargeted = m_Cases[i][j];
	Piece* piece = caseTargeted->GetPiece();

	if (m_PlayerSpell1 && caseTargeted->IsNotEmpty() && !caseTargeted->IsPieceIsThisColor(Game::GetColorTurn()))
	{
		m_PlayerSpell2 = false;
		m_PlayerSpell3 = false;
		m_PlayerSpell4 = false;
		m_PlayerSpell5 = false;
		int damage = 3;			

		if (caseTargeted->GetPiece()->GetColor() == Enums::EPieceColor::Blanche && m_Player1->GetMana() >= 1)
		{
			m_Player1->DecreaseMana(1);
			m_Player1->CastSpell1(caseTargeted->GetPiece(), damage);	
		}
		if (caseTargeted->GetPiece()->GetColor() == Enums::EPieceColor::Noire && m_Player2->GetMana() >= 1)
		{
			m_Player2->DecreaseMana(1);
			m_Player2->CastSpell1(caseTargeted->GetPiece(), damage);
		}				

		if (caseTargeted->GetPiece()->GetHP() <= 0)
		{
			caseTargeted->RemovePiece();
		}

		m_PlayerSpell1 = false;
		Game::ChangeColorTurn();		
	}


	if (m_PlayerSpell2 && caseTargeted->IsNotEmpty() && caseTargeted->IsPieceIsThisColor(Game::GetColorTurn()))
	{
		m_PlayerSpell1 = false;
		m_PlayerSpell3 = false;
		m_PlayerSpell4 = false;
		m_PlayerSpell5 = false;

		if (caseTargeted->GetPiece()->GetColor() == Enums::EPieceColor::Blanche && m_Player1->GetMana() >= 2)
		{
			m_Player1->DecreaseMana(2);
			m_Player1->CastSpell2(caseTargeted->GetPiece());
		}
		if (caseTargeted->GetPiece()->GetColor() == Enums::EPieceColor::Noire && m_Player2->GetMana() >= 2)
		{
			m_Player2->DecreaseMana(2);
			m_Player2->CastSpell2(caseTargeted->GetPiece());
		}

		m_PlayerSpell2 = false;
		Game::ChangeColorTurn();
	}

	if (m_PlayerSpell3 && caseTargeted->IsNotEmpty() && caseTargeted->IsPieceIsThisColor(Game::GetColorTurn()))
	{
		m_PlayerSpell1 = false;
		m_PlayerSpell2 = false;
		m_PlayerSpell4 = false;
		m_PlayerSpell5 = false;

		if (caseTargeted->GetPiece()->GetColor() == Enums::EPieceColor::Blanche && m_Player1->GetMana() >= 3)
		{
			m_Player1->DecreaseMana(3);
			m_Player1->CastSpell3(caseTargeted->GetPiece());
		}
		if (caseTargeted->GetPiece()->GetColor() == Enums::EPieceColor::Noire && m_Player2->GetMana() >= 3)
		{
			m_Player2->DecreaseMana(3);
			m_Player2->CastSpell3(caseTargeted->GetPiece());
		}

		m_PlayerSpell3 = false;
		Game::ChangeColorTurn();
	}

	if (m_PlayerSpell4 && caseTargeted->IsNotEmpty() && caseTargeted->IsPieceIsThisColor(Game::GetColorTurn()))
	{
		m_PlayerSpell1 = false;
		m_PlayerSpell2 = false;
		m_PlayerSpell3 = false;
		m_PlayerSpell5 = false;

		if (caseTargeted->GetPiece()->GetColor() == Enums::EPieceColor::Blanche && m_Player1->GetMana() >= 4)
		{
			m_Player1->DecreaseMana(4);
			m_Player1->CastSpell4(caseTargeted->GetPiece());
		}
		if (caseTargeted->GetPiece()->GetColor() == Enums::EPieceColor::Noire && m_Player2->GetMana() >= 4)
		{
			m_Player2->DecreaseMana(4);
			m_Player2->CastSpell4(caseTargeted->GetPiece());
		}

		m_PlayerSpell4 = false;
		Game::ChangeColorTurn();
	}
	

	//Sélectionne la pièce seulement si la case n'est pas vide, et que la pièce est de la bonne couleur
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

	int i = (a_Y - Y_OFFSET) / Board::CASE_WIDTH;
	int j = (a_X - X_OFFSET) / Board::CASE_HEIGHT;
	
	if (i < 8 && i >= 0 && j < 8 && j >= 0)
	{
		Case* caseTargeted = m_Cases[i][j];
		Piece* piece = caseTargeted->GetPiece();

		if (caseTargeted->IsNotEmpty() && caseTargeted->GetPiece()->IsThisColor(Game::GetColorTurn()))
		{
			if (piece->GetColor() == Enums::EPieceColor::Blanche)
			{
				Game::m_Player1HPStats = "HP: " + std::to_string(caseTargeted->GetPiece()->GetHP());
				Game::m_Player1AttackDmgStats = "Attack: " + std::to_string(caseTargeted->GetPiece()->GetAttackDamage());
				Game::m_Player1ArmorStats = "Armor: " + std::to_string(caseTargeted->GetPiece()->GetArmor());

				Game::m_Player2HPStats = "";
				Game::m_Player2AttackDmgStats = "";
				Game::m_Player2ArmorStats = "";

				Game::m_Player1PieceSpell = piece->IsSpellAvailable() ? "Piece's spell is available, press F to cast:" : "Piece's spell is not available:";
				Game::m_Player2PieceSpell = "";


				if (caseTargeted->GetPiece()->GetType() == Enums::EPieceType::Pion)
				{
					Game::m_Player1PieceSpellDescription = "Grabs an enemy Piece next to him and goes back one case with it";
					Game::m_Player2PieceSpellDescription = "";
				}
				else if (caseTargeted->GetPiece()->GetType() == Enums::EPieceType::Tour)
				{
					Game::m_Player1PieceSpellDescription = "Neutralizes an enemy Piece from anywhere for a turn";
					Game::m_Player2PieceSpellDescription = "";
				}
				else if (caseTargeted->GetPiece()->GetType() == Enums::EPieceType::Chevalier)
				{
					Game::m_Player1PieceSpellDescription = "Can play twice during it's turn";
					Game::m_Player2PieceSpellDescription = "";
				}
				else if (caseTargeted->GetPiece()->GetType() == Enums::EPieceType::Fou)
				{
					Game::m_Player1PieceSpellDescription = "Swaps it's position with any Piece in range";
					Game::m_Player2PieceSpellDescription = "";
				}
				else if (caseTargeted->GetPiece()->GetType() == Enums::EPieceType::Reine)
				{
					Game::m_Player1PieceSpellDescription = "Completely heals an ally Piece";
					Game::m_Player2PieceSpellDescription = "";
				}
				else if (caseTargeted->GetPiece()->GetType() == Enums::EPieceType::Roi)
				{
					Game::m_Player1PieceSpellDescription = "Executes any enemy Piece on the board that has 2 HP or under";
					Game::m_Player2PieceSpellDescription = "";
				}

			}
			else if (piece->GetColor() == Enums::EPieceColor::Noire)
			{
				Game::m_Player2HPStats = "HP: " + std::to_string(caseTargeted->GetPiece()->GetHP());
				Game::m_Player2AttackDmgStats = "Attack: " + std::to_string(caseTargeted->GetPiece()->GetAttackDamage());
				Game::m_Player2ArmorStats = "Armor: " + std::to_string(caseTargeted->GetPiece()->GetArmor());

				Game::m_Player1HPStats = "";
				Game::m_Player1AttackDmgStats = "";
				Game::m_Player1ArmorStats = "";

				Game::m_Player2PieceSpell = piece->IsSpellAvailable() ? "Piece's spell is available, press F to cast:" : "Piece's spell is not available:";
				Game::m_Player1PieceSpell = "";

				if (caseTargeted->GetPiece()->GetType() == Enums::EPieceType::Pion)
				{
					Game::m_Player2PieceSpellDescription = "Grabs an enemy Piece next to him and goes back from 1 case with it";
					Game::m_Player1PieceSpellDescription = "";
				}
				else if (caseTargeted->GetPiece()->GetType() == Enums::EPieceType::Tour)
				{
					Game::m_Player2PieceSpellDescription = "Neutralizes an enemy Piece from anywhere for a turn";
					Game::m_Player1PieceSpellDescription = "";

				}
				else if (caseTargeted->GetPiece()->GetType() == Enums::EPieceType::Chevalier)
				{
					Game::m_Player2PieceSpellDescription = "Can play twice during it's turn";
					Game::m_Player1PieceSpellDescription = "";
				}
				else if (caseTargeted->GetPiece()->GetType() == Enums::EPieceType::Fou)
				{
					Game::m_Player2PieceSpellDescription = "Swaps it's position with any Piece in range";
					Game::m_Player1PieceSpellDescription = "";
				}
				else if (caseTargeted->GetPiece()->GetType() == Enums::EPieceType::Reine)
				{
					Game::m_Player2PieceSpellDescription = "Completely heals an ally Piece";
					Game::m_Player1PieceSpellDescription = "";
				}
				else if (caseTargeted->GetPiece()->GetType() == Enums::EPieceType::Roi)
				{
					Game::m_Player2PieceSpellDescription = "Executes any enemy Piece on the board that has 2 HP or under";
					Game::m_Player1PieceSpellDescription = "";
				}
			}
		}

		if (caseTargeted->IsNotEmpty() && caseTargeted->GetPiece()->IsNotThisColor(Game::GetColorTurn()))
		{			
			Game::m_EnemyHPText = "HP: " + std::to_string(caseTargeted->GetPiece()->GetHP());
			Game::m_EnemyAttackDamageText = "Attack: " + std::to_string(caseTargeted->GetPiece()->GetAttackDamage());
			Game::m_EnemyArmorText = "Armor: " + std::to_string(caseTargeted->GetPiece()->GetArmor());		
		}
	}
}

void Board::MouseButtonUp(const int a_X, const int a_Y)
{
	if (m_CurrentCase != nullptr)
	{
		int i = (a_Y - Y_OFFSET) / Board::CASE_WIDTH;
		int j = (a_X - X_OFFSET) / Board::CASE_HEIGHT;

		Case* caseTargeted = m_Cases[i][j];		
		Game* stats;
		
		

		if (std::find(m_AvailableMoveForCurrentPiece.begin(), m_AvailableMoveForCurrentPiece.end(), std::tuple<int, int>(i, j)) != m_AvailableMoveForCurrentPiece.end())
		{
			// The targeted case is empty
			if (caseTargeted->IsEmpty())
			{
				caseTargeted->SwapPieceWith(m_CurrentCase);

				if (Game::GetColorTurn() == Enums::EPieceColor::Blanche)
				{
					m_Player1->IncreaseMana();
				}
				else if (Game::GetColorTurn() == Enums::EPieceColor::Noire)
				{
					m_Player2->IncreaseMana();
				}

				Game::ChangeColorTurn();		

				Game::m_Player1Mana = "Player 1 mana: " + std::to_string(m_Player1->GetMana());
				Game::m_Player2Mana = "Player 2 mana: " + std::to_string(m_Player2->GetMana());

			}
			else if (caseTargeted->IsPieceIsNotThisColor(Game::GetColorTurn()))
			{				
				// Pièce sélectionnée attaque la pièce targeté
				m_CurrentCase->GetPiece()->Attack(caseTargeted->GetPiece());
				

				// Pièce sélectionnée mange la pièce si l'attaque la tue
				if(caseTargeted->GetPiece()->GetHP() <= 0)
				{
					caseTargeted->SwapPieceWith(m_CurrentCase);
					//Retire la pièce morte du jeu
					m_CurrentCase->RemovePiece();
				}

				if (Game::GetColorTurn() == Enums::EPieceColor::Blanche)
				{
					m_Player1->IncreaseMana();
				}
				else if (Game::GetColorTurn() == Enums::EPieceColor::Noire)
				{
					m_Player2->IncreaseMana();
				}
				
				//Change de tour
				Game::ChangeColorTurn();
			}		
		}
		m_CurrentCase->BackToOriginalPosition();
		m_CurrentCase = nullptr;
	}
}

void Board::OnKey1Press()
{
	m_PlayerSpell1 = true;	
	Game::m_Player1Mana = "Please choose an enemy piece to attack";
}

void Board::OnKey2Press()
{
	m_PlayerSpell2 = true;
	Game::m_Player1Mana = "Please choose an ally piece to protect";
}

void Board::OnKey3Press()
{
	m_PlayerSpell3 = true;
	Game::m_Player1Mana = "Please choose an ally piece to restore it's spell";
}

void Board::OnKey4Press()
{
	m_PlayerSpell4 = true;
	Game::m_Player1Mana = "Please choose an ally piece to boost it's armor and damage";
}

void Board::OnKey5Press()
{
}
