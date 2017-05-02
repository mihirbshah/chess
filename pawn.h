#pragma once

#include "bitboard.h"


Bitboard pawn_north_fill(Bitboard b)
{
	b |= (b << 8);
	b |= (b << 16);
	b |= (b << 32);
	return b;
}

Bitboard pawn_south_fill(Bitboard b)
{
	b |= (b >> 8);
	b |= (b >> 16);
	b |= (b >> 32);
	return b;
}

Bitboard pawn_file_fill(Bitboard b)
{
	return pawn_north_fill(b) | pawn_south_fill(b);
}

Bitboard wpawn_front_fill(Bitboard b)
{
	return pawn_north_fill(b);
}

Bitboard wpawn_rear_fill(Bitboard b)
{
	return pawn_south_fill(b);
}

Bitboard bpawn_front_fill(Bitboard b)
{
	return pawn_south_fill(b);
}

Bitboard bpawn_rear_fill(Bitboard b)
{
	return pawn_north_fill(b);
}

Bitboard wpawn_front_span(Bitboard b)
{
	return north_one(pawn_north_fill(b));
}

Bitboard wpawn_rear_span(Bitboard b)
{
	return south_one(pawn_south_fill(b));
}

Bitboard bpawn_front_span(Bitboard b)
{
	return south_one(pawn_south_fill(b));
}

Bitboard bpawn_rear_span(Bitboard b)
{
	return north_one(pawn_north_fill(b));
}

Bitboard pawn_interspans(Bitboard wpawn, Bitboard bpawn)
{
	return wpawn_front_span(wpawn) & bpawn_front_span(bpawn);
}

Bitboard wpawn_stop(Bitboard b)
{
	return north_one(b);
}

Bitboard bpawn_stop(Bitboard b)
{
	return south_one(b);
}

Bitboard wpawn_telestops(Bitboard b)
{
	return wpawn_front_span(b) ^ wpawn_stop(b);
}

Bitboard bpawn_telestops(Bitboard b)
{
	return bpawn_front_span(b) ^ bpawn_stop(b);
}

Bitboard wpawn_east_attack_front_spans(Bitboard b)
{
	return east_one(wpawn_front_span(b));
}

Bitboard wpawn_west_attack_front_spans(Bitboard b)
{
	return west_one(wpawn_front_span(b));
}

Bitboard bpawn_east_attack_front_spans(Bitboard b)
{
	return east_one(bpawn_front_span(b));
}

Bitboard bpawn_west_attack_front_spans(Bitboard b)
{
	return west_one(bpawn_front_span(b));
}

Bitboard wpawn_east_attack_rear_spans(Bitboard b)
{
	return east_one(wpawn_rear_fill(b));
}

Bitboard wpawn_west_attack_rear_spans(Bitboard b)
{
	return west_one(wpawn_rear_fill(b));
}

Bitboard bpawn_east_attack_rear_spans(Bitboard b)
{
	return east_one(bpawn_rear_fill(b));
}

Bitboard bpawn_west_attack_rear_spans(Bitboard b)
{
	return west_one(bpawn_rear_fill(b));
}

Bitboard pawn_east_attacks_file_fill(Bitboard b)
{
	return east_one(pawn_file_fill(b));
}

Bitboard pawn_west_attacks_file_fill(Bitboard b)
{
	return west_one(pawn_file_fill(b));
}


