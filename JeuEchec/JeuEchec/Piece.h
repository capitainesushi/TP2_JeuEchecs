#ifndef __PIECE__
#define __PIECE__

#include "EPieceColor.h"
#include "EPieceType.h"
#include "EDirection.h"
#include <SDL.h>
#include <string>
#include <vector>
#include <tuple>


class Case;
class Board;

class Piece
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="Piece"/> class.
	/// </summary>
	/// <param name="a_PieceTexturePath">a piece texture path.</param>
	Piece(const std::string a_PieceTexturePath);
	
	/// <summary>
	/// Finalizes an instance of the <see cref="Piece"/> class.
	/// </summary>
	~Piece();
	
	/// <summary>
	/// Draws the piece's texture
	/// </summary>
	/// <param name="a_Parent">The parent to draw in</param>
	/// <param name="a_TargetedRect">The rectangle used to draw</param>
	void Draw(SDL_Surface* a_Parent, SDL_Rect* a_TargetedRect);
	
	/// <summary>
	/// Updates this instance.
	/// </summary>
	void Update();
	
	/// <summary>
	/// Gets the possible moves.
	/// </summary>
	/// <returns>All possible moves for the piece</returns>
	std::vector<std::vector<std::tuple<int, int>>> GetPossibleMoves() { return m_AvailableMoves; }
	
	/// <summary>
	/// Gets the possible attack.
	/// </summary>
	/// <returns>All possible attack moves for the piece</returns>
	virtual std::vector<std::vector<std::tuple<int, int>>> GetPossibleAttack() { return m_AvailableMoves; } // Return the same as availableMoves. Only pawns have different move for attack.
	
	/// <summary>
	/// Gets the color.
	/// </summary>
	/// <returns>The piece color</returns>
	const Enums::EPieceColor GetColor() { return m_PieceColor; }
	
	/// <summary>
	/// Gets the type.
	/// </summary>
	/// <returns>The piece type</returns>
	const Enums::EPieceType GetType() { return m_PieceType; }
	
	/// <summary>
	/// Determines whether the color of the piece is the same as the parameter.
	/// </summary>
	/// <param name="a_Color">The color to verify against</param>
	/// <returns>
	///   <c>true</c> if the color is the same as the parameter; otherwise, <c>false</c>.
	/// </returns>
	bool IsThisColor(Enums::EPieceColor a_Color) { return m_PieceColor == a_Color; }
	
	/// <summary>
	/// Determines whether the color of the piece is not the same as the parameter.
	/// </summary>
	/// <param name="a_Color">The color to verify against</param>
	/// <returns>
	///   <c>true</c> if the color is not the same as the parameter; otherwise, <c>false</c>.
	/// </returns>
	bool IsNotThisColor(Enums::EPieceColor a_Color) { return !IsThisColor(a_Color); }


		
	
	//Fonction appelée lorsqu'une pièce attaque un ennemi. Prend  la pièce ennemie en paramètre pour avoir accès à sa position et ses stats
	void Attack(Piece* targetedPiece);
	
	// Getters afin d'avoir accès aux différentes stats de mes pièces
	int GetHP() { return m_Hp; }	
	int GetAttackDamage() { return m_AttackDamage; }
	int GetArmor() { return m_Armor; }
	bool IsSpellAvailable() { return m_SpellAvailable; }

	// Enlève des points de vie à la pièce selon les dommages encaissés
	void AddDamage(int Damage);	

	// Rend la pièce invincible
	void Invincibility();

	// Restaure le Spell d'une pièce
	void RestoreSpell();

	// Donne un boost permanent de Damage et d'armure à une pièce
	void DamageArmorBoost();
	

	

	
protected:
	
	/// <summary>
	/// Initializes this instance.
	/// </summary>
	virtual void Init();

	SDL_Surface* m_PieceTexture;  // The SDL Surface that contain the piece's texture

	Enums::EPieceType m_PieceType;  // The piece type
	Enums::EPieceColor m_PieceColor;  // The piece color

	std::vector<std::vector<std::tuple<int, int>>> m_AvailableMoves;  // Available moves for the piece	

	// Stats de mes pièces
	int m_Hp;
	int m_AttackDamage;
	int m_Armor;
	bool m_SpellAvailable;	
	
	

private:
	
	Board* m_Board;
};

#endif //__PIECE__
