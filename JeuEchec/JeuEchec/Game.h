#ifndef __GAME__
#define __GAME__

#include "EPieceColor.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "Piece.h"
#include <string>

class Board;

class Game
{
public:
	
	/// <summary>
	/// Initializes a new instance of the <see cref="Game"/> class.
	/// </summary>
	Game();
	
	/// <summary>
	/// Finalizes an instance of the <see cref="Game"/> class.
	/// </summary>
	~Game();
	
	/// <summary>
	/// Runs this instance. This is the game loop.
	/// </summary>
	void Run();
	
	/// <summary>
	/// Changes the color turn. 
	/// </summary>
	static void ChangeColorTurn() { m_ColorTurn = static_cast<Enums::EPieceColor>(!static_cast<bool>(m_ColorTurn)); }
	
	/// <summary>
	/// Gets the color turn.
	/// </summary>
	/// <returns></returns>
	static Enums::EPieceColor GetColorTurn() { return m_ColorTurn; }



	
	// Stats de pièce du Player1
	static std::string m_Player1HPStats;
	static std::string m_Player1AttackDmgStats;
	static std::string m_Player1ArmorStats;

	//Stats de pièce du Player2
	static std::string m_Player2HPStats;
	static std::string m_Player2AttackDmgStats;
	static std::string m_Player2ArmorStats;

	// Spells des pièces
	static std::string m_Player1PieceSpell;
	static std::string m_Player2PieceSpell;

	// Description des spells de pièces
	static std::string m_Player1PieceSpellDescription;
	static std::string m_Player2PieceSpellDescription;


	// Description des 5 spells du joueur
	static const std::string PLAYERSPELL1;
	static const std::string PLAYERSPELL2;
	static const std::string PLAYERSPELL3;
	static const std::string PLAYERSPELL4;
	static const std::string PLAYERSPELL5_1;
	static const std::string PLAYERSPELL5_2;

	// Donne la Mana des joueurs
	static std::string m_Player1Mana;
	static std::string m_Player2Mana;

	// Donne les stats de la pièce ciblée
	static const std::string ENEMYSTATS;
	static std::string m_EnemyHPText;
	static std::string m_EnemyAttackDamageText;
	static std::string m_EnemyArmorText;	
	

private:
	
	static const int SCREEN_WIDTH;  // Define the width of the screen
	static const int SCREEN_HEIGHT; // Define the height of the screen

	static Enums::EPieceColor m_ColorTurn; // The color to play
	
	/// <summary>
	/// Initializes this instance.
	/// </summary>
	void Init();
	
	/// <summary>
	/// Handle all the inputs from the SDL pollEvent function.
	/// </summary>
	/// <returns>True if the user want to quit.</returns>
	bool Inputs();
	
	/// <summary>
	/// Call the draw on every cases
	/// </summary>
	void Draw();
	
	/// <summary>
	/// Call the update on every cases.
	/// </summary>
	void Update();

	SDL_Window* m_Window;	// The SDL window itself
	SDL_Surface* m_WindowSurface;  // The surface of the SDL window
	SDL_Surface* m_BackgroundSurface;

	Board* m_Board;  // The instance of the board.

	SDL_Renderer* m_Renderer;
	TTF_Font* m_Font;
	SDL_Color m_TextColor;
		
	SDL_Rect m_Player1HP;
	SDL_Rect m_Player1AttackDmg;	
	SDL_Rect m_Player1Armor;

	SDL_Rect m_Player2HP;	
	SDL_Rect m_Player2AttackDmg;
	SDL_Rect m_Player2Armor;

	SDL_Rect m_Player1PieceSpellAvailable;
	SDL_Rect m_Player2PieceSpellAvailable;
	
	SDL_Rect m_Player1PieceSpellDesc;
	SDL_Rect m_Player2PieceSpellDesc;


	// Demande au joueur s'il veut Caster ou Move
	static const std::string ASK_FOR_SPELL;
	SDL_Rect m_AskForSpell;

	// Mes numéros de players affichés
	SDL_Rect m_Player1Name;
	SDL_Rect m_Player2Name;

	//Limitation au milieu entre Les infos du player 1 et 2
	static const std::string LIMITATION1;	
	SDL_Rect m_Limitation1Rect;

	// Description des 5 spells du joueur
	SDL_Rect m_PlayerSpellRect1;
	SDL_Rect m_PlayerSpellRect2;
	SDL_Rect m_PlayerSpellRect3;
	SDL_Rect m_PlayerSpellRect4;
	SDL_Rect m_PlayerSpellRect5_1;
	SDL_Rect m_PlayerSpellRect5_2;

	//Donne la mana des 2 joueurs
	SDL_Rect m_Player1ManaRect;
	SDL_Rect m_Player2ManaRect;

	//Donne les statistiques de la pièce ciblée
	SDL_Rect m_EnemyStatsRect;
	SDL_Rect m_EnemyHPRect;
	SDL_Rect m_EnemyAttackDamageRect;
	SDL_Rect m_EnemyArmorRect;


};

#endif // __GAME__
