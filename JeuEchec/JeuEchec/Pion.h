#ifndef __PION__
#define __PION__

#include "Piece.h"

class Pion :
	public Piece
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="Pion"/> class.
	/// </summary>
	/// <param name="a_PieceColor">Color of a piece.</param>
	Pion(const Enums::EPieceColor a_PieceColor);
	
	/// <summary>
	/// Finalizes an instance of the <see cref="Pion"/> class.
	/// </summary>
	virtual ~Pion();
	
	/// <summary>
	/// Gets the possible attacks.
	/// </summary>
	/// <returns>All possibles attack for the pawn</returns>
	virtual std::vector<std::vector<std::tuple<int, int>>> GetPossibleAttack() { return m_PossibleAttacks; } // Return the same as availableMoves. Only pawns have different move for attack.
	
	virtual void SetHP(int HP);

	virtual void CastSpell();

	virtual int GetHP() { return m_Hp; }

protected:
	
private:
	std::vector<std::vector<std::tuple<int, int>>> m_PossibleAttacks;   // Contains possible attacks for a pawn.
};

#endif // __PION__