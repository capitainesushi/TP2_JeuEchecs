#ifndef __GAME__
#define __GAME__

#include "EPieceColor.h"
#include <SDL.h>

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

	Board* m_Board;  // The instance of the board.
};

#endif // __GAME__
