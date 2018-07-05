#ifndef __ROI__
#define __ROI__

#include "Piece.h"
class Roi :
	public Piece
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="Roi"/> class.
	/// </summary>
	/// <param name="a_PieceColor">Color of a piece.</param>
	Roi(const Enums::EPieceColor a_PieceColor);
	
	/// <summary>
	/// Finalizes an instance of the <see cref="Roi"/> class.
	/// </summary>
	virtual ~Roi();
};

#endif // __ROI__