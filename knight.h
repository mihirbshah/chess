#pragma once

#include "bitboard.h"
#include "chess_types.h"
#include <cassert>

Bitboard knight_attacks(Bitboard b)
{
	Bitboard l1 = (b >> 1) & not_h_file;
	Bitboard l2 = (b >> 2) & not_g_h_file;
	Bitboard r1 = (b << 1) & not_a_file;
	Bitboard r2 = (b << 2) & not_a_b_file;
	Bitboard h1 = l1 | r1;
	Bitboard h2 = l2 | r2;
	return (h1 << 16) | (h1 >> 16) | (h2 << 8) | (h2 >> 8);
}

int calc_knight_distance(Bitboard b1, Bitboard b2)
{
	assert(b1 && b2);
	int d = 0;
	while ((b1 & b2) == 0)
	{
		b1 = knight_attacks(b1); ++d;
	}
	return d;
}

int knight_distance(Position source, Position target)
{
	return calc_knight_distance(C64(1) << source, C64(1) << target);
}
