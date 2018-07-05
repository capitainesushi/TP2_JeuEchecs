#ifndef __FOU__
#define __FOU__

#include "Piece.h"
class Fou :
	public Piece
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="Fou"/> class.
	/// </summary>
	/// <param name="a_PieceColor">Color of a piece.</param>
	Fou(const Enums::EPieceColor a_PieceColor);
	
	/// <summary>
	/// Finalizes an instance of the <see cref="Fou"/> class.
	/// </summary>
	virtual ~Fou();
};

#endif // __FOU__
