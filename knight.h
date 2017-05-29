#pragma once

#include "bitboard.h"
#include "chess_types.h"
#include <cassert>

namespace
{
	const Bitboard not_ab_file = ~(fileA | fileB);
	const Bitboard not_gh_file = ~(fileG | fileH);
};

// Single Knight attack
Bitboard no_no_ea(Bitboard b) { return (b << 17) & not_a_file; }
Bitboard no_ea_ea(Bitboard b) { return (b << 10) & not_ab_file; }
Bitboard so_ea_ea(Bitboard b) { return (b >> 6) & not_ab_file; }
Bitboard so_so_ea(Bitboard b) { return (b >> 15) & not_a_file; }
Bitboard no_no_we(Bitboard b) { return (b << 15) & not_h_file; }
Bitboard no_we_we(Bitboard b) { return (b << 6) & not_gh_file; }
Bitboard so_we_we(Bitboard b) { return (b >> 10) & not_gh_file; }
Bitboard so_so_we(Bitboard b) { return (b >> 17) & not_h_file; }

// Multiple Knight attacks
Bitboard calc_knight_attacks(Bitboard b)
{
	Bitboard l1 = (b >> 1) & not_h_file;
	Bitboard l2 = (b >> 2) & not_g_h_file;
	Bitboard r1 = (b << 1) & not_a_file;
	Bitboard r2 = (b << 2) & not_a_b_file;
	Bitboard h1 = l1 | r1;
	Bitboard h2 = l2 | r2;
	return (h1 << 16) | (h1 >> 16) | (h2 << 8) | (h2 >> 8);
}

namespace{
	Bitboard knight_attacks_bb[64];
};

void setup_knight_attacks_bb()
{
	Bitboard b = C64(0x1);
	for (int sq = 0; sq < 64; ++sq, b<<=1)
		knight_attacks_bb[sq] = calc_knight_attacks(b);
}

Bitboard knight_attacks(Position sq)
{
	return knight_attacks_bb[sq];
}


// Knight fill
Bitboard knight_fill(Bitboard knights) { return calc_knight_attacks(knights) | knights; }

// Knight Fork
Bitboard fork_target_squares(Bitboard targets)
{
	Bitboard east, west, attacks, forks;

	east = east_one(targets);
	west = west_one(targets);
	attacks = east << 16;
	disp_bb(attacks, "attacks");
	forks = (west << 16) & attacks;
	disp_bb(forks, "forks");
	attacks |= (west << 16);
	disp_bb(attacks, "attacks");
	forks |= (east >> 16) & attacks;
	disp_bb(forks, "forks");
	attacks |= (east >> 16);
	disp_bb(attacks, "attacks");
	forks |= (west >> 16) & attacks;
	disp_bb(forks, "forks");
	attacks |= (west >> 16);
	disp_bb(attacks, "attacks");

	east = east_one(east);
	west = west_one(west);
	forks |= (east << 8) & attacks;
	disp_bb(forks, "forks");
	attacks |= east << 8;
	disp_bb(attacks, "attacks");
	forks |= (west << 8) & attacks;
	disp_bb(forks, "forks");
	attacks |= (west << 8);
	disp_bb(attacks, "attacks");
	forks |= (east >> 8) & attacks;
	disp_bb(forks, "forks");
	attacks |= (east >> 8);
	disp_bb(attacks, "attacks");
	forks |= (west >> 8) & attacks;
	disp_bb(forks, "forks");

	return forks;
}

// Knight distance
int calc_knight_distance(Bitboard b1, Bitboard b2)
{
	assert(b1 && b2);
	int d = 0;
	while ((b1 & b2) == 0)
	{
		b1 = calc_knight_attacks(b1); ++d;
	}
	return d;
}

int knight_distance(Position source, Position target)
{
	return calc_knight_distance(C64(1) << source, C64(1) << target);
}

