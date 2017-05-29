#include "bitboard.h"
#include "chess_types.h"
#include "chess_board.h"
#include "pawn.h"
#include "sliding_pieces.h"
#include "knight.h"
#include "king.h"
#include <iostream>

int main()
{
    /*Bitboard a_file = C64(0x0101010101010101);
    disp_bb(a_file, "a-file");
    Bitboard h_file = C64(0x8080808080808080);
    disp_bb(h_file, "h-file");
    Bitboard rank_8 = C64(0xFF00000000000000);
    disp_bb(rank_8, "rank 8");
    Bitboard rank_1 = C64(0x00000000000000FF);
    disp_bb(rank_1, "rank 1");
    Bitboard a1h8_diag = C64(0x8040201008040201);
    disp_bb(a1h8_diag, "a1h8 diagonal");
    Bitboard light_sq = C64(0x55AA55AA55AA55AA);
    disp_bb(light_sq, "light squares");*/

	/*Bitboard b1 = C64(0x0100000000000000);
	disp_bb(b1, "Input");
	disp_bb(east_one(b1), "Shift east");
	disp_bb(west_one(b1), "Shift west");
	disp_bb(north_one(b1), "Shift north");
	disp_bb(south_one(b1), "Shift south");
	disp_bb(ne_one(b1), "Shift north-east");
	disp_bb(nw_one(b1), "Shift north-west");
	disp_bb(se_one(b1), "Shift south-east");
	disp_bb(sw_one(b1), "Shift south-west");*/

	//std::cout << "res: " << (rotate_one(b1, west) == shift_one(b1, west));
	//disp_bb(rotate_one(b1, se), "Rotate south-east");
	//disp_bb(shift_one(b1, se), "Shift south-east");
	//disp_bb(se_one(b1), "Shift south-east");

	/*setup_lookup_table();
	Bitboard b1 = C64(0x14220022140000);
	disp_bb(b1, "Input");
	Position pos = a8;
	std::cout << "test bit: " << pos << ". Result: " << test(b1, pos) << "\n";
	std::cout << "set bit: " << pos << ". Result: " << "\n";
	disp_bb(set(b1, pos), "After bit set");
	std::cout << "toggle bit: " << pos << ". Result: " << "\n";
	disp_bb(toggle(b1, pos), "After bit toggle");
	std::cout << "reset bit: " << pos << ". Result: " << "\n";
	disp_bb(reset(b1, pos), "After bit reset");*/

	/*BitPos onebits = get_set_bits(b1);
	for (short n : onebits)
		std::cout << n << ", ";*/

	/*setup_lookup_table();
	ChessBoard board;
	board.disp_cboard();
	Move m1(e2, e4, ChessBoard::nPawn, ChessBoard::nWhite);
	board.quite_move(m1);
	board.disp_cboard("After move e2-e4");
	m1 = Move(d7, d5, ChessBoard::nPawn, ChessBoard::nBlack);
	board.quite_move(m1);
	board.disp_cboard("After move d7-d5");
	m1 = Move(e4, d5, ChessBoard::nPawn, ChessBoard::nWhite, ChessBoard::nPawn, ChessBoard::nBlack);
	board.capture_move(m1);
	board.disp_cboard("After move e4-d5");*/

	//disp_bb(upper_bits(c3), "upper bits for c3");
	//disp_bb(lower_bits(e5), "lower bits for e5");

	/*Bitboard b1 = C64(0x00005c00002a0000);
	disp_bb(b1, "Input");
	disp_bb(swap_n_bits(b1, b3, c6, 5), "swap_5_bits between b3 and c6");
	disp_bb(delta_swap(b1, C64(0x3e0000), (c6 - b3)), "delta_swap with delta=c6-b3");*/

	/*Bitboard b1 = C64(0x14220022140000);
	disp_bb(b1, "Input");
	disp_bb(ls1b_of_x(b1), "ls1b_of_x");
	disp_bb(reset_ls1b_of_x(b1), "reset_ls1b_of_x");
	disp_bb(above_ls1b_mask(b1), "above_ls1b_mask");
	disp_bb(below_ls1b_mask_including(b1), "below_ls1b_mask_including");
	disp_bb(below_ls1b_mask(b1), "below_ls1b_mask");
	disp_bb(smear_ls1b_up(b1), "smear_ls1b_up");
	disp_bb(smear_ls1b_down(b1), "smear_ls1b_down");*/

	/*Bitboard b1 = C64(0x80c0e0f0f8fcfeff);
	disp_bb(b1, "Input");
	disp_bb(ls0b_of_x(b1), "ls0b_of_x");
	disp_bb(set_ls0b_of_x(b1), "set_ls0b_of_x");
	disp_bb(below_ls0b_mask_including(b1), "below_ls0b_mask_including");
	disp_bb(below_ls0b_mask(b1), "below_ls0b_mask");
	disp_bb(above_ls0b_mask(b1), "above_ls0b_mask");
	disp_bb(smear_ls0b_up(b1), "smear_ls0b_up");
	disp_bb(smear_ls0b_down(b1), "smear_ls0b_down");*/

	/*Bitboard b1 = C64(0x80c0e0f0f8fcfeff);
	disp_bb(b1, "Input");
	std::cout << "Population count(1) for b1: " << pop_cnt_1(b1) << "\n";
	init_pop_cnt_of_byte();
	std::cout << "Population count(2) for b1: " << pop_cnt_2(b1) << "\n";*/

	/*Bitboard b1 = C64(0x00c0e0f0f8fcfe00);
	disp_bb(b1, "Input");
	std::cout << "bit scan forward: " << bit_scan_forward(b1) << "\n";
	std::cout << "bit scan reverse: " << bit_scan_reverse(b1) << "\n";
	std::cout << "trailing zero count: " << trailing_zero_cnt(b1) << "\n";
	std::cout << "leading zero count: " << leading_zero_cnt(b1) << "\n";*/

	/*Bitboard b1 = C64(0x1e2222120e0a1222);
	disp_bb(b1, "Input");
	disp_bb(flip_vertical(b1), "Vertical flip");
	disp_bb(mirror_horizontal(b1), "Horizontal mirror");
	disp_bb(flip_diag_a1h8(b1), "Flip diagonal a1h8");
	disp_bb(flip_diag_a8h1(b1), "Flip diagonal a8h1");
	disp_bb(rotate180(b1), "rotate180");
	disp_bb(rotate90_clockwise(b1), "rotate90 clockwise");
	disp_bb(rotate90_anticlockwise(b1), "rotate90 anticlockwise");*/

	/*Bitboard wpawn = C64(0x481620400);
	Bitboard bpawn = C64(0x43048008000000);
	disp_bb(wpawn, "white pawn");
	disp_bb(wpawn_front_fill(wpawn), "white pawn front fill");
	disp_bb(wpawn_rear_fill(wpawn), "white pawn rear fill");
	disp_bb(bpawn, "black pawn");
	disp_bb(bpawn_front_fill(bpawn), "black pawn front fill");
	disp_bb(bpawn_rear_fill(bpawn), "black pawn rear fill");

	disp_bb(wpawn, "white pawn");
	disp_bb(wpawn_front_span(wpawn), "white pawn front span");
	disp_bb(wpawn_rear_span(wpawn), "white pawn rear span");
	disp_bb(wpawn_stop(wpawn), "white pawn stop squares");
	disp_bb(wpawn_telestops(wpawn), "white pawn telestop squares");

	disp_bb(bpawn, "black pawn");
	disp_bb(bpawn_front_span(bpawn), "black pawn front span");
	disp_bb(bpawn_rear_span(bpawn), "black pawn rear span");
	disp_bb(bpawn_stop(bpawn), "black pawn stop squares");
	disp_bb(bpawn_telestops(bpawn), "black pawn telestop squares");*/


	/*Bitboard pawn = C64(0x8000000);
	disp_bb(pawn, "pawn");
	disp_bb(wpawn_east_attack_front_spans(pawn), "white pawn east attacks front spans");
	disp_bb(wpawn_west_attack_front_spans(pawn), "white pawn west attacks front spans");
	disp_bb(bpawn_east_attack_front_spans(pawn), "black pawn east attacks front spans");
	disp_bb(bpawn_west_attack_front_spans(pawn), "black pawn west attacks front spans");
	disp_bb(wpawn_east_attack_rear_spans(pawn), "white pawn east attacks rear spans");
	disp_bb(wpawn_west_attack_rear_spans(pawn), "white pawn west attacks rear spans");
	disp_bb(bpawn_east_attack_rear_spans(pawn), "black pawn east attacks rear spans");
	disp_bb(bpawn_west_attack_rear_spans(pawn), "black pawn west attacks rear spans");
	disp_bb(pawn_east_attacks_file_fill(pawn), "pawn east attacks file fill");
	disp_bb(pawn_west_attacks_file_fill(pawn), "pawn west attacks file fill");*/

	/*Bitboard queen_n_rook = C64(0x108000020000000);
	Bitboard empty = C64(0xbe53bdfbd77b98b6);
	disp_bb(queen_n_rook, "Queen & Rook");
	disp_bb(empty, "Empty Squares");
	disp_bb(south_attacks(queen_n_rook, empty), "South Attacks for Queen & Rook");
	disp_bb(north_attacks(queen_n_rook, empty), "North Attacks for Queen & Rook");
	disp_bb(east_attacks(queen_n_rook, empty), "East Attacks for Queen & Rook");*/

	/*Bitboard knight = C64(0x2000000);
	disp_bb(knight, "Knight");
	disp_bb(knight_attacks(knight), "Knight attacks");
    std::cout << "Knight Distance between a1 and h8: " << knight_distance(a1, h8) << "\n";*/

	/*Bitboard pawns = C64(0x7006000);
	disp_bb(pawns, "Pawns");
	disp_bb(pawn_duo(pawns), "Duo");*/

	/*Bitboard knights = C64(0x8000000);
	disp_bb(knights, "Knights");
	disp_bb(calc_knight_attacks(knights), "knight_attacks");
	disp_bb(fork_target_squares(C64(0x28000000)), "Knight fork location given target squares");*/

	/*setup_king_attacks_bb();
	disp_bb(king_attacks(Position::a8), "Attack bb for King at a4");*/

	/*setup_pawn_attacks_bb();
	disp_bb(pawn_attacks(Position::c7, Piece::nWhite), "Pawn attacks for wpawn on c7");
	disp_bb(pawn_attacks(Position::c3, Piece::nBlack), "Pawn attacks for bpawn on c3");*/

	/*setup_knight_attacks_bb();
	disp_bb(knight_attacks(Position::d4), "Attack bb for Knight at d4");*/

	/*Bitboard empty = C64(0xbe53bdfbd77b98b6);
	disp_bb(empty, "Empty Squares");
	setup_lookup_table();
	disp_bb(rook_attacks(Position::f5, empty), "Rook attacks for rook at f5");
	disp_bb(bishop_attacks(Position::f5, empty), "Bishop attacks for bishop at f5");
	disp_bb(queen_attacks(Position::f5, empty), "Queen attacks for queen at f5");*/

	setup_lookup_table();
	setup_pawn_attacks_bb();
	setup_knight_attacks_bb();
	setup_king_attacks_bb();
	ChessBoard board;
	board.disp_cboard();
	Move m1(e2, e4, nPawn, nWhite);
	board.quite_move(m1);
	board.disp_cboard("After move e2-e4");
	m1 = Move(d7, d5, nPawn, nBlack);
	board.quite_move(m1);
	board.disp_cboard("After move d7-d5");
	m1 = Move(e4, d5, nPawn, nWhite, nPawn, nBlack);
	board.capture_move(m1);
	board.disp_cboard("After move e4-d5");
	m1 = Move(c7, c6, nPawn, nBlack);
	board.quite_move(m1);
	board.disp_cboard("After move c7-c6");
	m1 = Move(d1, f3, nQueen, nWhite);
	board.quite_move(m1);
	board.disp_cboard("After move d1-f3");
	m1 = Move(c8, e6, nBishop, nBlack);
	board.quite_move(m1);
	board.disp_cboard("After move c8-e6");
	m1 = Move(f1, c4, nBishop, nWhite);
	board.quite_move(m1);
	board.disp_cboard("After move f1-c4");
	m1 = Move(g8, f6, nKnight, nBlack);
	board.quite_move(m1);
	board.disp_cboard("After move g8-f6");
	disp_bb(board.attacks_to(Position::d5), "Attacks on d5");



	return 0;
}
