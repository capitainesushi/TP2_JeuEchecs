#include "Game.h"
#include "Board.h"
#include "Player.h"
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include "PieceFactory.h"

Enums::EPieceColor Game::m_ColorTurn = Enums::EPieceColor::Blanche;

const int Game::SCREEN_WIDTH = 1600;
const int Game::SCREEN_HEIGHT = 1000;


const std::string Game::ASK_FOR_SPELL = "Would you like to Move or Cast a Spell?";

const std::string Game::LIMITATION1 = "_________________________________________________";

const std::string Game::PLAYERSPELL1 = "Spell #1: Deal 3 points of Damage to an enemy Piece";
const std::string Game::PLAYERSPELL2 = "Spell #2: Make a Piece invincible for a turn";
const std::string Game::PLAYERSPELL3 = "Spell #3: Restore an ally Piece's spell";
const std::string Game::PLAYERSPELL4 = "Spell #4: Add 3 points of Damage and Armor to an ally Piece, permanently";
const std::string Game::PLAYERSPELL5_1 = "Spell #5: Drop a bomb that explodes in a cross and deals 6 points of";
const std::string Game::PLAYERSPELL5_2 = "Damage to every single Piece it hits";

const std::string Game::ENEMYSTATS = "Enemy piece's stats:";


std::string Game::m_Player1HPStats = "";
std::string Game::m_Player1AttackDmgStats = "";
std::string Game::m_Player1ArmorStats = "";

std::string Game::m_Player2HPStats = "";
std::string Game::m_Player2AttackDmgStats = "";
std::string Game::m_Player2ArmorStats = "";

std::string Game::m_Player1PieceSpell = "";
std::string Game::m_Player2PieceSpell = "";

std::string Game::m_Player1Mana = "Player 1 Mana: ";
std::string Game::m_Player2Mana = "Player 2 Mana: ";

std::string Game::m_Player1PieceSpellDescription = "";
std::string Game::m_Player2PieceSpellDescription = "";

std::string Game::m_EnemyHPText = "";
std::string Game::m_EnemyAttackDamageText = "";
std::string Game::m_EnemyArmorText = "";

Game::Game()
{
	Init();
}


Game::~Game()
{
	if (m_BackgroundSurface != nullptr)
	{
		SDL_FreeSurface(m_BackgroundSurface);
		m_BackgroundSurface = nullptr;
	}

	if (m_WindowSurface != nullptr)
	{
		SDL_FreeSurface(m_WindowSurface);
		m_WindowSurface = nullptr;
	}

	if (m_Window != nullptr)
	{
		SDL_DestroyWindow(m_Window);
		m_Window = nullptr;
	}

	TTF_CloseFont(m_Font);
	TTF_Quit();
}

void Game::Init()
{
	// Init the SDL Window
	m_Window = SDL_CreateWindow("Once upon a chess", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	m_WindowSurface = SDL_GetWindowSurface(m_Window);

	m_BackgroundSurface = IMG_Load("./images/Background.png");

	//Init TTF things
	TTF_Init();

	m_Renderer = SDL_CreateRenderer(m_Window, 0, SDL_RendererFlags::SDL_RENDERER_ACCELERATED);
	m_Font = TTF_OpenFont("./times.ttf", 20);
	m_TextColor = { 255, 255, 255 };


	m_PlayerSpellRect1 = { 925, 25, 100, 100 };
	m_PlayerSpellRect2 = { 925, 75, 100, 100 };
	m_PlayerSpellRect3 = { 925, 125, 100, 100 };
	m_PlayerSpellRect4 = { 925, 175, 100, 100 };
	m_PlayerSpellRect5_1 = { 925, 225, 100, 100 };
	m_PlayerSpellRect5_2 = { 1003, 250, 100, 100 };

	m_Limitation1Rect = { 925, 300, 100, 100 };

	m_Player1ManaRect = { 925, 350, 100, 100 };
	m_Player2ManaRect = { 925, 375, 100, 100 };

	m_EnemyStatsRect = { 925, 425, 100, 100 };
	m_EnemyHPRect = { 925, 450, 100, 100 };
	m_EnemyAttackDamageRect = { 925, 475, 100, 100 };
	m_EnemyArmorRect = { 925, 500, 100, 100 };

	m_Player1HP = { 250, 900, 100, 100 };
	m_Player1AttackDmg = { 250, 930, 100, 100 };
	m_Player1Armor = { 250, 960, 100, 100 };

	m_Player2HP = { 250, 10, 100, 100 };
	m_Player2AttackDmg = { 250, 40, 100, 100 };
	m_Player2Armor = { 250, 70, 100, 100 };


	m_Player1PieceSpellAvailable = { 350, 920, 200, 100 };
	m_Player1PieceSpellDesc = { 350, 940, 200, 100 };

	m_Player2PieceSpellAvailable = { 350, 20, 200, 100 };
	m_Player2PieceSpellDesc = { 350, 40, 200, 100 };


	m_Player1Name = { 125, 940, 100, 100 };
	m_Player2Name = { 125, 40, 100, 100 };

	m_Board = new Board();
}

void Game::Run()
{
	bool quit = false;
	while (!quit) {
		quit = Inputs();
		Draw();
		Update();
	}

}

bool Game::Inputs()
{
	SDL_Event e;
	//Handle events on queue
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_1:

				m_Board->OnKey1Press();
				break;

			case SDLK_2:

				m_Board->OnKey2Press();
				break;

			case SDLK_3:

				m_Board->OnKey3Press();
				break;

			case SDLK_4:

				m_Board->OnKey4Press();
				break;
			}			
		}		
		else
		{
			switch (e.type)
			{
				case SDL_QUIT:
				{
					return true;
				}
				case SDL_MOUSEBUTTONDOWN:
				{
					int x = 0;
					int y = 0;
					SDL_GetMouseState(&x, &y);
					m_Board->MouseButtonDown(x, y);
					break;
				}
				case SDL_MOUSEMOTION:
				{
					int x = 0;
					int y = 0;
					SDL_GetMouseState(&x, &y);
					m_Board->MouseMotion(x, y);
					break;
				}
				case SDL_MOUSEBUTTONUP:
				{
					int x = 0;
					int y = 0;
					SDL_GetMouseState(&x, &y);
					m_Board->MouseButtonUp(x, y);
					break;
				}
				default:
					break;
			}
		}
	}

	return false;
}

	

void Game::Draw()
{
	Piece* piece = PieceFactory::CreatePiece(Enums::EPieceType::Pion, Enums::EPieceColor::Blanche);
	SDL_UpdateWindowSurface(m_Window);

	SDL_BlitSurface(m_BackgroundSurface, NULL, m_WindowSurface, NULL);

	m_Board->Draw(m_WindowSurface);

	SDL_Surface* player1Text = TTF_RenderText_Solid(m_Font, "Player1: ", m_TextColor);
	SDL_Surface* player2Text = TTF_RenderText_Solid(m_Font, "Player2: ", m_TextColor);

	SDL_BlitSurface(player1Text, NULL, m_WindowSurface, &m_Player1Name);
	SDL_BlitSurface(player2Text, NULL, m_WindowSurface, &m_Player2Name);

	SDL_Surface* player1PieceSpellText = TTF_RenderText_Solid(m_Font, m_Player1PieceSpell.c_str(), m_TextColor);
	SDL_Surface* player2PieceSpellText = TTF_RenderText_Solid(m_Font, m_Player2PieceSpell.c_str(), m_TextColor);

	SDL_Surface* player1PieceSpellDesc = TTF_RenderText_Solid(m_Font, m_Player1PieceSpellDescription.c_str(), m_TextColor);
	SDL_Surface* player2PieceSpellDesc = TTF_RenderText_Solid(m_Font, m_Player2PieceSpellDescription.c_str(), m_TextColor);

	SDL_Surface* player1HPText = TTF_RenderText_Solid(m_Font, m_Player1HPStats.c_str(), m_TextColor);
	SDL_Surface* player1AttackDmgText = TTF_RenderText_Solid(m_Font, m_Player1AttackDmgStats.c_str(), m_TextColor);
	SDL_Surface* player1ArmorText = TTF_RenderText_Solid(m_Font, m_Player1ArmorStats.c_str(), m_TextColor);

	SDL_Surface* player2HPText = TTF_RenderText_Solid(m_Font, m_Player2HPStats.c_str(), m_TextColor);
	SDL_Surface* player2AttackDmgText = TTF_RenderText_Solid(m_Font, m_Player2AttackDmgStats.c_str(), m_TextColor);
	SDL_Surface* player2ArmorText = TTF_RenderText_Solid(m_Font, m_Player2ArmorStats.c_str(), m_TextColor);

	SDL_BlitSurface(player1PieceSpellDesc, NULL, m_WindowSurface, &m_Player1PieceSpellDesc);
	SDL_BlitSurface(player2PieceSpellDesc, NULL, m_WindowSurface, &m_Player2PieceSpellDesc);

	SDL_BlitSurface(player1PieceSpellText, NULL, m_WindowSurface, &m_Player1PieceSpellAvailable);
	SDL_BlitSurface(player2PieceSpellText, NULL, m_WindowSurface, &m_Player2PieceSpellAvailable);

	SDL_BlitSurface(player1HPText, NULL, m_WindowSurface, &m_Player1HP);
	SDL_BlitSurface(player1AttackDmgText, NULL, m_WindowSurface, &m_Player1AttackDmg);
	SDL_BlitSurface(player1ArmorText, NULL, m_WindowSurface, &m_Player1Armor);

	SDL_BlitSurface(player2HPText, NULL, m_WindowSurface, &m_Player2HP);
	SDL_BlitSurface(player2AttackDmgText, NULL, m_WindowSurface, &m_Player2AttackDmg);
	SDL_BlitSurface(player2ArmorText, NULL, m_WindowSurface, &m_Player2Armor);

	SDL_Surface* playerSpell1 = TTF_RenderText_Solid(m_Font, PLAYERSPELL1.c_str(), m_TextColor);
	SDL_Surface* playerSpell2 = TTF_RenderText_Solid(m_Font, PLAYERSPELL2.c_str(), m_TextColor);
	SDL_Surface* playerSpell3 = TTF_RenderText_Solid(m_Font, PLAYERSPELL3.c_str(), m_TextColor);
	SDL_Surface* playerSpell4 = TTF_RenderText_Solid(m_Font, PLAYERSPELL4.c_str(), m_TextColor);
	SDL_Surface* playerSpell5_1 = TTF_RenderText_Solid(m_Font, PLAYERSPELL5_1.c_str(), m_TextColor);
	SDL_Surface* playerSpell5_2 = TTF_RenderText_Solid(m_Font, PLAYERSPELL5_2.c_str(), m_TextColor);

	SDL_Surface* limitation = TTF_RenderText_Solid(m_Font, LIMITATION1.c_str(), m_TextColor);

	SDL_Surface* player1Mana = TTF_RenderText_Solid(m_Font, m_Player1Mana.c_str(), m_TextColor);
	SDL_Surface* player2Mana = TTF_RenderText_Solid(m_Font, m_Player2Mana.c_str(), m_TextColor);

	SDL_Surface* enemyStats = TTF_RenderText_Solid(m_Font, ENEMYSTATS.c_str(), m_TextColor);
	SDL_Surface* enemyHPStats = TTF_RenderText_Solid(m_Font, m_EnemyHPText.c_str(), m_TextColor);
	SDL_Surface* enemyAttackDamageStats = TTF_RenderText_Solid(m_Font, m_EnemyAttackDamageText.c_str(), m_TextColor);
	SDL_Surface* enemyArmorStats = TTF_RenderText_Solid(m_Font, m_EnemyArmorText.c_str(), m_TextColor);


	SDL_BlitSurface(playerSpell1, NULL, m_WindowSurface, &m_PlayerSpellRect1);
	SDL_BlitSurface(playerSpell2, NULL, m_WindowSurface, &m_PlayerSpellRect2);
	SDL_BlitSurface(playerSpell3, NULL, m_WindowSurface, &m_PlayerSpellRect3);
	SDL_BlitSurface(playerSpell4, NULL, m_WindowSurface, &m_PlayerSpellRect4);
	SDL_BlitSurface(playerSpell5_1, NULL, m_WindowSurface, &m_PlayerSpellRect5_1);
	SDL_BlitSurface(playerSpell5_2, NULL, m_WindowSurface, &m_PlayerSpellRect5_2);

	SDL_BlitSurface(limitation, NULL, m_WindowSurface, &m_Limitation1Rect);

	SDL_BlitSurface(player1Mana, NULL, m_WindowSurface, &m_Player1ManaRect);
	SDL_BlitSurface(player2Mana, NULL, m_WindowSurface, &m_Player2ManaRect);

	SDL_BlitSurface(enemyStats, NULL, m_WindowSurface, &m_EnemyStatsRect);

	SDL_BlitSurface(enemyHPStats, NULL, m_WindowSurface, &m_EnemyHPRect);
	SDL_BlitSurface(enemyAttackDamageStats, NULL, m_WindowSurface, &m_EnemyAttackDamageRect);
	SDL_BlitSurface(enemyArmorStats, NULL, m_WindowSurface, &m_EnemyArmorRect);

	SDL_FreeSurface(player1Text);
	SDL_FreeSurface(player2Text);

	SDL_FreeSurface(player1HPText);
	SDL_FreeSurface(player1AttackDmgText);
	SDL_FreeSurface(player1ArmorText);

	SDL_FreeSurface(player2HPText);
	SDL_FreeSurface(player2AttackDmgText);
	SDL_FreeSurface(player2ArmorText);

	SDL_FreeSurface(player1PieceSpellText);
	SDL_FreeSurface(player2PieceSpellText);

	SDL_FreeSurface(limitation);

	SDL_FreeSurface(player1Mana);
	SDL_FreeSurface(player2Mana);

	SDL_FreeSurface(enemyStats);
	SDL_FreeSurface(enemyHPStats);
	SDL_FreeSurface(enemyAttackDamageStats);
	SDL_FreeSurface(enemyArmorStats);

	SDL_FreeSurface(playerSpell1);
	SDL_FreeSurface(playerSpell2);
	SDL_FreeSurface(playerSpell3);
	SDL_FreeSurface(playerSpell4);
	SDL_FreeSurface(playerSpell5_1);
	SDL_FreeSurface(playerSpell5_2);
}

void Game::Update()
{
	m_Board->Update();
}
