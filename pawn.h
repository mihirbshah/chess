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



// pawn push
Bitboard wpawns_single_push_targets(Bitboard wpawns, Bitboard empty)
{
	return north_one(wpawns) & empty;
}

Bitboard wpawns_double_push_targets(Bitboard wpawns, Bitboard empty)
{
	const Bitboard rank4 = C64(0x00000000FF000000);
	return wpawns_single_push_targets(wpawns_single_push_targets(wpawns, empty), empty) & rank4;
}

Bitboard bpawns_single_push_targets(Bitboard bpawns, Bitboard empty)
{
	return south_one(bpawns) & empty;
}

Bitboard bpawns_double_push_targets(Bitboard bpawns, Bitboard empty)
{
	const Bitboard rank5 = C64(0x000000FF00000000);
	return bpawns_single_push_targets(bpawns_single_push_targets(bpawns, empty), empty) & rank5;
}

// pawn able to push
Bitboard wpawns_able_to_push(Bitboard wpawns, Bitboard empty)
{
	return south_one(empty) & wpawns;
}

Bitboard wpawns_able_to_dbl_push(Bitboard wpawns, Bitboard empty)
{
	const Bitboard rank4 = C64(0x00000000FF000000);
	Bitboard empty_rank3_for_rank4 = south_one(empty & rank4) & empty;
	return wpawns_able_to_push(wpawns, empty_rank3_for_rank4);
}

Bitboard bpawns_able_to_push(Bitboard bpawns, Bitboard empty)
{
	return north_one(empty) & bpawns;
}

Bitboard bpawns_able_to_dbl_push(Bitboard bpawns, Bitboard empty)
{
	const Bitboard rank5 = C64(0x000000FF00000000);
	Bitboard empty_rank6_for_rank5 = north_one(empty & rank5) & empty;
	return bpawns_able_to_push(bpawns, empty_rank6_for_rank5);
}

// pawn attacks
Bitboard wpawns_east_attacks(Bitboard wpawns)
{
	return ne_one(wpawns);
}

Bitboard wpawns_west_attacks(Bitboard wpawns)
{
	return nw_one(wpawns);
}

Bitboard bpawns_east_attacks(Bitboard bpawns)
{
	return se_one(bpawns);
}

Bitboard bpawns_west_attacks(Bitboard bpawns)
{
	return sw_one(bpawns);
}

Bitboard wpawns_any_attacks(Bitboard wpawns)
{
	return wpawns_east_attacks(wpawns) | wpawns_west_attacks(wpawns);
}

Bitboard wpawns_dbl_attacks(Bitboard wpawns)
{
	return wpawns_east_attacks(wpawns) & wpawns_west_attacks(wpawns);
}

Bitboard wpawns_single_attacks(Bitboard wpawns)
{
	return wpawns_east_attacks(wpawns) ^ wpawns_west_attacks(wpawns);
}

Bitboard bpawns_any_attacks(Bitboard bpawns)
{
	return bpawns_east_attacks(bpawns) | bpawns_west_attacks(bpawns);
}

Bitboard bpawns_dbl_attacks(Bitboard bpawns)
{
	return bpawns_east_attacks(bpawns) & bpawns_west_attacks(bpawns);
}

Bitboard bpawns_single_attacks(Bitboard bpawns)
{
	return bpawns_east_attacks(bpawns) ^ bpawns_west_attacks(bpawns);
}

// pawn sets which can capture
// TODO check how this would work
Bitboard wpawns_able_to_capture_east(Bitboard wpawns, Bitboard bpieces)
{
	return wpawns & bpawns_west_attacks(bpieces);
}

Bitboard wpawns_able_to_capture_west(Bitboard wpawns, Bitboard bpieces)
{
	return wpawns & bpawns_east_attacks(bpieces);
}

Bitboard wpawns_able_to_capture_any(Bitboard wpawns, Bitboard bpieces)
{
	return wpawns & bpawns_any_attacks(bpieces);
}

Bitboard bpawns_able_to_capture_east(Bitboard bpawns, Bitboard wpieces)
{
	return bpawns & wpawns_west_attacks(wpieces);
}

Bitboard bpawns_able_to_capture_west(Bitboard bpawns, Bitboard wpieces)
{
	return bpawns & wpawns_east_attacks(wpieces);
}

Bitboard bpawns_able_to_capture_any(Bitboard bpawns, Bitboard wpieces)
{
	return bpawns & wpawns_any_attacks(wpieces);
}


// pawn rams
Bitboard wpawn_rams(Bitboard wpawns, Bitboard bpawns)
{
	return south_one(bpawns) & wpawns;
}

Bitboard bpawn_rams(Bitboard wpawns, Bitboard bpawns)
{
	return north_one(wpawns) & bpawns;
}
