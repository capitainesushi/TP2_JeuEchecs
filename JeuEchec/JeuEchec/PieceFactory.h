#pragma once
#include "Piece.h"
#include "EPieceType.h"

static class PieceFactory
{
public:
	PieceFactory();
	~PieceFactory();

	static Piece* CreatePiece(const Enums::EPieceType a_PieceType, const Enums::EPieceColor a_Color);

};

