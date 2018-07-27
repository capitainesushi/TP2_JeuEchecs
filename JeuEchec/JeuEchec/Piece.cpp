#include "Piece.h"

#include <SDL_image.h>
#include "Board.h"

Piece::Piece(const std::string a_PieceTexturePath)
{
	m_PieceTexture = IMG_Load((a_PieceTexturePath + ".png").c_str());

	m_AvailableMoves = std::vector<std::vector<std::tuple<int, int>>>();

	for (int i = 0; i < Enums::EDirection::Direction_Count; i++)
	{
		m_AvailableMoves.push_back(std::vector<std::tuple<int, int>>());
	}

	Init();
}

Piece::~Piece()
{
	if (m_PieceTexture != nullptr) 
	{
		SDL_FreeSurface(m_PieceTexture);
		m_PieceTexture = nullptr;
	}
}

void Piece::Init()
{

}

void Piece::Draw(SDL_Surface* a_Parent, SDL_Rect* a_TargetedRect)
{
	SDL_BlitSurface(m_PieceTexture, NULL, a_Parent, a_TargetedRect);
}

void Piece::Update()
{

}


void Piece::Attack(Piece* targetedPiece)
{
	targetedPiece->AddDamage(m_AttackDamage);
}

void Piece::AddDamage(int Damage)
{	
	if (Damage > m_Armor)
	{
		m_Hp -= Damage - m_Armor;
	}	
}

void Piece::Invincibility()
{
	m_Armor += 20;
}

void Piece::RestoreSpell()
{
	m_SpellAvailable = true;
}

void Piece::DamageArmorBoost()
{
	m_AttackDamage += 3;
	m_Armor += 3;
}






