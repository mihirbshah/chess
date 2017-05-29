#pragma once

#include "bitboard.h"
#include "chess_types.h"

Bitboard south_attacks(Bitboard piece_bb, Bitboard empty)
{
	Bitboard flood = piece_bb;
	flood |= piece_bb = (piece_bb >> 8) & empty;
	flood |= piece_bb = (piece_bb >> 8) & empty;
	flood |= piece_bb = (piece_bb >> 8) & empty;
	flood |= piece_bb = (piece_bb >> 8) & empty;
	flood |= piece_bb = (piece_bb >> 8) & empty;
	flood |= piece_bb = (piece_bb >> 8) & empty;
	flood |=            (piece_bb >> 8) & empty;
	return south_one(flood);
}

Bitboard north_attacks(Bitboard piece_bb, Bitboard empty)
{
	Bitboard flood = piece_bb;
	flood |= piece_bb = (piece_bb << 8) & empty;
	flood |= piece_bb = (piece_bb << 8) & empty;
	flood |= piece_bb = (piece_bb << 8) & empty;
	flood |= piece_bb = (piece_bb << 8) & empty;
	flood |= piece_bb = (piece_bb << 8) & empty;
	flood |= piece_bb = (piece_bb << 8) & empty;
	flood |=            (piece_bb << 8) & empty;
	return north_one(flood);
}

Bitboard east_attacks(Bitboard piece_bb, Bitboard empty)
{
	Bitboard flood = piece_bb;
	empty &= not_a_file;
	flood |= piece_bb = (piece_bb << 1) & empty;
	flood |= piece_bb = (piece_bb << 1) & empty;
	flood |= piece_bb = (piece_bb << 1) & empty;
	flood |= piece_bb = (piece_bb << 1) & empty;
	flood |= piece_bb = (piece_bb << 1) & empty;
	flood |= piece_bb = (piece_bb << 1) & empty;
	flood |=            (piece_bb << 1) & empty;
	return east_one(flood);
}

Bitboard west_attacks(Bitboard piece_bb, Bitboard empty)
{
	Bitboard flood = piece_bb;
	empty &= not_h_file;
	flood |= piece_bb = (piece_bb >> 1) & empty;
	flood |= piece_bb = (piece_bb >> 1) & empty;
	flood |= piece_bb = (piece_bb >> 1) & empty;
	flood |= piece_bb = (piece_bb >> 1) & empty;
	flood |= piece_bb = (piece_bb >> 1) & empty;
	flood |= piece_bb = (piece_bb >> 1) & empty;
	flood |=            (piece_bb >> 1) & empty;
	return west_one(flood);
}

Bitboard ne_attacks(Bitboard piece_bb, Bitboard empty)
{
	Bitboard flood = piece_bb;
	empty &= not_a_file;
	flood |= piece_bb = (piece_bb << 9) & empty;
	flood |= piece_bb = (piece_bb << 9) & empty;
	flood |= piece_bb = (piece_bb << 9) & empty;
	flood |= piece_bb = (piece_bb << 9) & empty;
	flood |= piece_bb = (piece_bb << 9) & empty;
	flood |= piece_bb = (piece_bb << 9) & empty;
	flood |=            (piece_bb << 9) & empty;
	return ne_one(flood);
}

Bitboard nw_attacks(Bitboard piece_bb, Bitboard empty)
{
	Bitboard flood = piece_bb;
	empty &= not_h_file;
	flood |= piece_bb = (piece_bb << 7) & empty;
	flood |= piece_bb = (piece_bb << 7) & empty;
	flood |= piece_bb = (piece_bb << 7) & empty;
	flood |= piece_bb = (piece_bb << 7) & empty;
	flood |= piece_bb = (piece_bb << 7) & empty;
	flood |= piece_bb = (piece_bb << 7) & empty;
	flood |=            (piece_bb << 7) & empty;
	return nw_one(flood);
}

Bitboard se_attacks(Bitboard piece_bb, Bitboard empty)
{
	Bitboard flood = piece_bb;
	empty &= not_a_file;
	flood |= piece_bb = (piece_bb >> 7) & empty;
	flood |= piece_bb = (piece_bb >> 7) & empty;
	flood |= piece_bb = (piece_bb >> 7) & empty;
	flood |= piece_bb = (piece_bb >> 7) & empty;
	flood |= piece_bb = (piece_bb >> 7) & empty;
	flood |= piece_bb = (piece_bb >> 7) & empty;
	flood |=            (piece_bb >> 7) & empty;
	return se_one(flood);
}

Bitboard sw_attacks(Bitboard piece_bb, Bitboard empty)
{
	Bitboard flood = piece_bb;
	empty &= not_h_file;
	flood |= piece_bb = (piece_bb >> 9) & empty;
	flood |= piece_bb = (piece_bb >> 9) & empty;
	flood |= piece_bb = (piece_bb >> 9) & empty;
	flood |= piece_bb = (piece_bb >> 9) & empty;
	flood |= piece_bb = (piece_bb >> 9) & empty;
	flood |= piece_bb = (piece_bb >> 9) & empty;
	flood |=            (piece_bb >> 9) & empty;
	return sw_one(flood);
}

Bitboard rook_attacks(Position sq, Bitboard empty)
{
	Bitboard b = board(sq);
	return north_attacks(b, empty) |
		   south_attacks(b, empty) |
		   east_attacks(b, empty)  |
		   west_attacks(b, empty);
}

Bitboard bishop_attacks(Position sq, Bitboard empty)
{
	Bitboard b = board(sq);
	return ne_attacks(b, empty) |
		   nw_attacks(b, empty) |
		   se_attacks(b, empty)  |
		   sw_attacks(b, empty);
}

Bitboard queen_attacks(Position sq, Bitboard empty)
{
	return rook_attacks(sq, empty) | bishop_attacks(sq, empty);
}

// TODO Implement Kogge-Stone algorithm for occluded fill & compare with Dumb7 fill above
// TODO Implement Rotated/Magic bitboards based sliding piece attacks [http://chessprogramming.wikispaces.com/Sliding+Piece+Attacks]
