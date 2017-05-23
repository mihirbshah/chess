#pragma once

#include "bitboard.h"
#include "chess_types.h"

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
	return wpawns_single_push_targets(wpawns_single_push_targets(wpawns, empty), empty) & rank4;
}

Bitboard bpawns_single_push_targets(Bitboard bpawns, Bitboard empty)
{
	return south_one(bpawns) & empty;
}

Bitboard bpawns_double_push_targets(Bitboard bpawns, Bitboard empty)
{
	return bpawns_single_push_targets(bpawns_single_push_targets(bpawns, empty), empty) & rank5;
}

// pawn able to push
Bitboard wpawns_able_to_push(Bitboard wpawns, Bitboard empty)
{
	return south_one(empty) & wpawns;
}

Bitboard wpawns_able_to_dbl_push(Bitboard wpawns, Bitboard empty)
{
	Bitboard empty_rank3_for_rank4 = south_one(empty & rank4) & empty;
	return wpawns_able_to_push(wpawns, empty_rank3_for_rank4);
}

Bitboard bpawns_able_to_push(Bitboard bpawns, Bitboard empty)
{
	return north_one(empty) & bpawns;
}

Bitboard bpawns_able_to_dbl_push(Bitboard bpawns, Bitboard empty)
{
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


// pawn levers
Bitboard wpawn_east_lever(Bitboard wpawns, Bitboard bpawns)
{
	return wpawns & bpawns_west_attacks(bpawns);
}

Bitboard wpawn_west_lever(Bitboard wpawns, Bitboard bpawns)
{
	return wpawns & bpawns_east_attacks(bpawns);
}

Bitboard wpawn_any_lever(Bitboard wpawns, Bitboard bpawns)
{
	return wpawn_east_lever(wpawns, bpawns) | wpawn_west_lever(wpawns, bpawns);
}

Bitboard bpawn_east_lever(Bitboard wpawns, Bitboard bpawns)
{
	return bpawns & wpawns_west_attacks(wpawns);
}

Bitboard bpawn_west_lever(Bitboard wpawns, Bitboard bpawns)
{
	return bpawns & wpawns_east_attacks(wpawns);
}

Bitboard bpawn_any_lever(Bitboard wpawns, Bitboard bpawns)
{
	return bpawn_east_lever(wpawns, bpawns) | bpawn_west_lever(wpawns, bpawns);
}

Bitboard wpawn_inner_lever(Bitboard wpawns, Bitboard bpawns)
{
	const Bitboard abc_files = C64(0x0707070707070707);
	const Bitboard fgh_files = C64(0xE0E0E0E0E0E0E0E0);
	return (wpawn_east_lever(wpawns, bpawns) & abc_files) |
		   (wpawn_west_lever(wpawns, bpawns) & fgh_files);
}

Bitboard wpawn_outer_lever(Bitboard wpawns, Bitboard bpawns)
{
	const Bitboard bcd_files = C64(0x0E0E0E0E0E0E0E0E);
	const Bitboard efg_files = C64(0x7070707070707070);
	return (wpawn_east_lever(wpawns, bpawns) & efg_files) |
		   (wpawn_west_lever(wpawns, bpawns) & bcd_files);
}

Bitboard wpawn_center_lever(Bitboard wpawns, Bitboard bpawns)
{
	return (wpawn_east_lever(wpawns, bpawns) & fileD) |
		   (wpawn_west_lever(wpawns, bpawns) & fileE);
}

Bitboard bpawn_inner_lever(Bitboard wpawns, Bitboard bpawns)
{
	const Bitboard abc_files = C64(0x0707070707070707);
	const Bitboard fgh_files = C64(0xE0E0E0E0E0E0E0E0);
	return (bpawn_east_lever(wpawns, bpawns) & abc_files) |
		   (bpawn_west_lever(wpawns, bpawns) & fgh_files);
}

Bitboard bpawn_outer_lever(Bitboard wpawns, Bitboard bpawns)
{
	const Bitboard bcd_files = C64(0x0E0E0E0E0E0E0E0E);
	const Bitboard efg_files = C64(0x7070707070707070);
	return (bpawn_east_lever(wpawns, bpawns) & efg_files) |
		   (bpawn_west_lever(wpawns, bpawns) & bcd_files);
}

Bitboard bpawn_center_lever(Bitboard wpawns, Bitboard bpawns)
{
	return (bpawn_east_lever(wpawns, bpawns) & fileD) |
		   (bpawn_west_lever(wpawns, bpawns) & fileE);
}


// defended/defender pawns
Bitboard wpawn_defended_from_west(Bitboard wpawns)
{
	return wpawns & wpawns_east_attacks(wpawns);
}

Bitboard wpawn_defended_from_east(Bitboard wpawns)
{
	return wpawns & wpawns_west_attacks(wpawns);
}

Bitboard bpawn_defended_from_west(Bitboard bpawns)
{
	return bpawns & bpawns_east_attacks(bpawns);
}

Bitboard bpawn_defended_from_east(Bitboard bpawns)
{
	return bpawns & bpawns_west_attacks(bpawns);
}


Bitboard wpawn_defenders_from_west(Bitboard wpawns)
{
	return wpawns & bpawns_west_attacks(wpawns);
}

Bitboard wpawn_defenders_from_east(Bitboard wpawns)
{
	return wpawns & bpawns_east_attacks(wpawns);
}

Bitboard bpawn_defenders_from_west(Bitboard bpawns)
{
	return bpawns & wpawns_west_attacks(bpawns);
}

Bitboard bpawn_defenders_from_east(Bitboard bpawns)
{
	return bpawns & wpawns_east_attacks(bpawns);
}


// neighbours
Bitboard pawns_with_east_neighbours(Bitboard pawns)
{
	return pawns & west_one(pawns);
}

Bitboard pawns_with_west_neighbours(Bitboard pawns)
{
	return pawns & east_one(pawns);
}

Bitboard pawn_duo(Bitboard pawns)
{
	Bitboard with_east_neighbours = pawns_with_east_neighbours(pawns);
	Bitboard with_west_neighbours = pawns_with_west_neighbours(pawns);
	Bitboard with_one_exclusive_neighbour = with_east_neighbours ^ with_west_neighbours;
	Bitboard with_exclusive_east_neighbour = with_one_exclusive_neighbour & with_east_neighbours;
	Bitboard with_exclusive_west_neighbour = with_one_exclusive_neighbour & with_west_neighbours;
	Bitboard duo_west_one = with_exclusive_east_neighbour & (with_exclusive_west_neighbour >> 1);
	Bitboard duo_east_one = duo_west_one << 1;
	return duo_west_one | duo_east_one;
}

// TODO Implement pawn_trio, pawn_quart


// open, closed, half-open, semi-closed files
Bitboard pawn_closed_files(Bitboard wpawns, Bitboard bpawns)
{
	return pawn_file_fill(wpawns) & pawn_file_fill(bpawns);
}

Bitboard pawn_open_files(Bitboard wpawns, Bitboard bpawns)
{
	return ~(pawn_file_fill(wpawns) | pawn_file_fill(bpawns));
}

Bitboard pawn_half_open_or_open_files(Bitboard pawns)
{
	return ~pawn_file_fill(pawns);
}

Bitboard wpawn_half_open_file(Bitboard wpawns, Bitboard bpawns)
{
	return pawn_half_open_or_open_files(wpawns) ^ pawn_open_files(wpawns, bpawns);
}

// TODO Implement semi-closed files
// TODO Implement http://chessprogramming.wikispaces.com/Pawn+Pattern+and+Properties#Properties-Based on Spans




