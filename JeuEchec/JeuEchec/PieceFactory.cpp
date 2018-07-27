#include "PieceFactory.h"
#include "Pion.h"
#include "Tour.h"
#include "Chevalier.h"
#include "Fou.h"
#include "Reine.h"
#include "Roi.h"


PieceFactory::PieceFactory()
{
}


PieceFactory::~PieceFactory()
{
}

Piece * PieceFactory::CreatePiece(const Enums::EPieceType a_PieceType, const Enums::EPieceColor a_Color)
{
	switch (a_PieceType)
	{
	case Enums::EPieceType::Pion:
		return new Pion(a_Color);
		break;
	case Enums::EPieceType::Tour:
		return new Tour(a_Color);
		break;
	case Enums::EPieceType::Chevalier:
		return new Chevalier(a_Color);
		break;
	case Enums::EPieceType::Fou:
		return new Fou(a_Color);
		break;
	case Enums::EPieceType::Reine:
		return new Reine(a_Color);
		break;
	case Enums::EPieceType::Roi:
		return new Roi(a_Color);
		break;
	default:
		break;
	}
}

