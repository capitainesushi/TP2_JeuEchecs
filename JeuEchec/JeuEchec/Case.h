#ifndef __CASE__
#define __CASE__

#include <SDL.h>
#include "EPieceType.h"
#include "EPieceColor.h"

#include "Piece.h"
#include "Board.h"

class Case
{
public:
	
	/// <summary>
	/// Initializes a new instance of the <see cref="Case"/> class.
	/// </summary>
	/// <param name="a_X">The X position of the case</param>
	/// <param name="a_Y">The Y position of the case</param>
	Case(const int a_X, const int a_Y);
	
	/// <summary>
	/// Initializes a new instance of the <see cref="Case"/> class.
	/// </summary>
	/// <param name="a_X">The X position of the case</param>
	/// <param name="a_Y">Teh Y position of the case</param>
	/// <param name="a_PieceType">Type of the piece to instantiate</param>
	/// <param name="a_Color">Color of the piece to instantiate</param>
	Case(const int a_X, const int a_Y, Enums::EPieceType a_PieceType, Enums::EPieceColor a_Color);
	
	/// <summary>
	/// Finalizes an instance of the <see cref="Case"/> class.
	/// </summary>
	~Case();
	
	/// <summary>
	/// Perform a draw on the piece, if exists.
	/// </summary>
	/// <param name="a_Parent">The parent where to draw the piece</param>
	void Draw(SDL_Surface* a_Parent);
	
	/// <summary>
	/// Updates this instance.
	/// </summary>
	void Update();
	
	/// <summary>
	/// Moves the case to a specified position.
	/// </summary>
	/// <param name="a_X">The targeted X</param>
	/// <param name="a_Y">The targeted Y</param>
	void Move(int a_X, int a_Y);
	
	/// <summary>
	/// Backs the case to the original position.
	/// </summary>
	void BackToOriginalPosition();
	
	/// <summary>
	/// Swaps the piece with the piece from another case.
	/// </summary>
	/// <param name="a_OtherCase">The other case to switch with</param>
	void SwapPieceWith(Case* a_OtherCase);
	
	/// <summary>
	/// Removes the piece from the case.
	/// </summary>
	void RemovePiece() { m_Piece = nullptr; }
	
	/// <summary>
	/// Gets the available moves for the piece on this case.
	/// </summary>
	/// <param name="a_Cases">All cases of the board</param>
	/// <returns>The list of available moves for the piece on the case</returns>
	std::vector<std::tuple<int, int>> GetAvailableMoves(const std::vector<std::vector<Case*>>  a_Cases);
	
	/// <summary>
	/// Gets the I of the case.
	/// </summary>
	/// <returns>The index I of the case</returns>
	const int GetI() { return (m_OriginalY - Board::Y_OFFSET) / Board::CASE_WIDTH; }
	
	/// <summary>
	/// Gets the J of the case.
	/// </summary>
	/// <returns>The index J of the case</returns>
	const int GetJ() { return (m_OriginalX - Board::X_OFFSET) / Board::CASE_HEIGHT; }
	
	/// <summary>
	/// Determines whether this case is empty.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this case is empty; otherwise, <c>false</c>.
	/// </returns>
	bool IsEmpty() { return m_Piece == nullptr; }
	
	/// <summary>
	/// Determines whether this case is not empty.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this case is not empty; otherwise, <c>false</c>.
	/// </returns>
	bool IsNotEmpty() { return !IsEmpty(); }
	
	/// <summary>
	/// Determines whether the color of the piece is the same as the parameter.
	/// </summary>
	/// <param name="a_Color">To color to test against</param>
	/// <returns>
	///   <c>true</c> if the color is the same as the piece; otherwise, <c>false</c>.
	/// </returns>
	bool IsPieceIsThisColor(Enums::EPieceColor a_Color) { return m_Piece->IsThisColor(a_Color); }
	
	/// <summary>
	/// Determines whether the color of the piece is not the same as the parameter.
	/// </summary>
	/// <param name="a_Color">a color.</param>
	/// <returns>
	///   <c>true</c> if the color is not the same as the piece; otherwise, <c>false</c>.
	/// </returns>
	bool IsPieceIsNotThisColor(Enums::EPieceColor a_Color) { return m_Piece->IsNotThisColor(a_Color); }


	// Va chercher la pièce sélectionnée
	Piece* GetPiece() { return m_Piece; }

private:
	
	/// <summary>
	/// Initializes this instance.
	/// </summary>
	void Init();

	SDL_Rect m_Rect;  // The rect where the content of the case will be draw
	Piece* m_Piece;   // The piece on this case (can be nullptr)

	int m_OriginalX;  // The original X position (at the instantiation)
	int m_OriginalY;  // The original Y position (at the instantiation)
};

#endif // __CASE__
