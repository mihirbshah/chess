#pragma once

#include "bitboard.h"
#include "chess_types.h"

namespace
{
	Bitboard king_attacks_bb[64];
};

Bitboard calc_king_attacks(Bitboard king)
{
	Bitboard attacks = east_one(king) | west_one(king);
	king |= attacks;
	attacks |= north_one(king) | south_one(king);
	return attacks;
}

void setup_king_attacks_bb()
{
	Bitboard b = C64(0x1);
	for (int sq = 0; sq < 64; ++sq, b<<=1)
		king_attacks_bb[sq] = calc_king_attacks(b);
}

Bitboard king_attacks(Position sq)
{
	return king_attacks_bb[sq];
}

//TODO Implement http://chessprogramming.wikispaces.com/King+Pattern#King Safety
