#pragma once

#include "bitboard.h"
#include "chess_types.h"
#include "pawn.h"
#include "knight.h"
#include "king.h"
#include "sliding_pieces.h"
#include <iostream>
#include <string>
#include <algorithm>


struct Move;

class ChessBoard
{
 public:
	ChessBoard();

	void disp_cboard(const std::string& header = "Board");

	void quite_move(Move m);
	void capture_move(Move m);

	Bitboard all_pawns() { return pieceBB[nPawn]; }
	Bitboard all_knights() { return pieceBB[nKnight]; }
	Bitboard all_bishops() { return pieceBB[nBishop]; }
	Bitboard all_rooks() { return pieceBB[nRook]; }
	Bitboard all_queens() { return pieceBB[nQueen]; }
	Bitboard all_kings() { return pieceBB[nKing]; }
	Bitboard pawns(Piece side) { return pieceBB[nPawn] & pieceBB[nWhite + side]; }
	Bitboard knights(Piece side) { return pieceBB[nKnight] & pieceBB[nWhite + side]; }
	Bitboard bishops(Piece side) { return pieceBB[nBishop] & pieceBB[nWhite + side]; }
	Bitboard rooks(Piece side) { return pieceBB[nRook] & pieceBB[nWhite + side]; }
	Bitboard queens(Piece side) { return pieceBB[nQueen] & pieceBB[nWhite + side]; }
	Bitboard kings(Piece side) { return pieceBB[nKing] & pieceBB[nWhite + side]; }
	Bitboard empty() { return empty_sq; }
	Bitboard occupied() { return occupied_sq; }

	Bitboard attacks_to(Position sq);
	bool is_attacked(Position sq, Piece side);

 private:
	Bitboard pieceBB[8];
	Bitboard occupied_sq;
	Bitboard empty_sq;
};

//typedef ChessBoard::Piece Piece;

ChessBoard::ChessBoard()
{
	pieceBB[nWhite]  = C64(0x000000000000ffff);
	pieceBB[nBlack]  = C64(0xffff000000000000);
	pieceBB[nPawn]   = C64(0x00ff00000000ff00);
	pieceBB[nKnight] = C64(0x4200000000000042);
	pieceBB[nBishop] = C64(0x2400000000000024);
	pieceBB[nRook]   = C64(0x8100000000000081);
	pieceBB[nQueen]  = C64(0x0800000000000008);
	pieceBB[nKing]   = C64(0x1000000000000010);

	occupied_sq = pieceBB[nWhite] | pieceBB[nBlack];
	empty_sq = ~occupied_sq;
}

void ChessBoard::disp_cboard(const std::string& header)
{
	std::cout << header << ": \n\n";
	char board_str[65];
	BitPos onebits, zerobits;
	onebits = get_set_bits(pieceBB[nPawn] & pieceBB[nWhite]); for (short i : onebits) board_str[i] = 'P';
	onebits = get_set_bits(pieceBB[nKnight] & pieceBB[nWhite]); for (short i : onebits) board_str[i] = 'N';
	onebits = get_set_bits(pieceBB[nBishop] & pieceBB[nWhite]); for (short i : onebits) board_str[i] = 'B';
	onebits = get_set_bits(pieceBB[nRook] & pieceBB[nWhite]); for (short i : onebits) board_str[i] = 'R';
	onebits = get_set_bits(pieceBB[nQueen] & pieceBB[nWhite]); for (short i : onebits) board_str[i] = 'Q';
	onebits = get_set_bits(pieceBB[nKing] & pieceBB[nWhite]); for (short i : onebits) board_str[i] = 'K';
	onebits = get_set_bits(pieceBB[nPawn] & pieceBB[nBlack]); for (short i : onebits) board_str[i] = 'p';
	onebits = get_set_bits(pieceBB[nKnight] & pieceBB[nBlack]); for (short i : onebits) board_str[i] = 'n';
	onebits = get_set_bits(pieceBB[nBishop] & pieceBB[nBlack]); for (short i : onebits) board_str[i] = 'b';
	onebits = get_set_bits(pieceBB[nRook] & pieceBB[nBlack]); for (short i : onebits) board_str[i] = 'r';
	onebits = get_set_bits(pieceBB[nQueen] & pieceBB[nBlack]); for (short i : onebits) board_str[i] = 'q';
	onebits = get_set_bits(pieceBB[nKing] & pieceBB[nBlack]); for (short i : onebits) board_str[i] = 'k';
	zerobits = get_set_bits(empty_sq); for (short i : zerobits) board_str[i] = '-';
	board_str[64] = '\0'; //needed just incase you want to print board_str

	std::string s;
	for (int i = 63; i >= 0; --i)
	{
		if (((i + 1) % 8))
		{
			s += ' '; s += ' ';
		}
		s += board_str[i];
		if (i % 8 == 0)
		{
			if (s.length())
			{
				// derive rank number
				std::reverse(s.begin(), s.end());
				s = std::to_string(1 + int(i/8)) + " | " + s;
				std::cout << s << "\n";
				s.clear();
			}
		}
	}
	std::cout << "---------------------------\n";
	std::cout << "  | a  b  c  d  e  f  g  h  \n\n";
}

struct Move
{
	Position from, to;
	Piece piece, color, c_piece, c_color;

	Move()
	{
		to = InvalidPos;
		from = InvalidPos;
		piece = color = c_piece = c_color = InvalidPiece;
	}

	Move(Position from_, Position to_, Piece piece_, Piece color_, Piece c_piece_ = InvalidPiece, Piece c_color_ = InvalidPiece)
	{
		from = from_;
		to = to_;
		piece = piece_;
		color = color_;
		c_piece = c_piece_;
		c_color = c_color_;
	}
};

void ChessBoard::quite_move(Move m)
{
 	Bitboard fromBB = board(m.from);
	Bitboard toBB = board(m.to);
	Bitboard fromtoBB = fromBB ^ toBB;
	pieceBB[m.piece] ^= fromtoBB;
	pieceBB[m.color] ^= fromtoBB;
	occupied_sq ^= fromtoBB;
	empty_sq ^= fromtoBB;
}

void ChessBoard::capture_move(Move m)
{
 	Bitboard fromBB = board(m.from);
	Bitboard toBB = board(m.to);
	Bitboard fromtoBB = fromBB ^ toBB;
	pieceBB[m.piece] ^= fromtoBB;
	pieceBB[m.color] ^= fromtoBB;
	pieceBB[m.c_piece] ^= toBB;
	pieceBB[m.c_color] ^= toBB;
	occupied_sq ^= fromBB;
	empty_sq ^= fromBB;
}

Bitboard ChessBoard::attacks_to(Position sq)
{
	Bitboard bishop_queens, rook_queens;
	bishop_queens = rook_queens = all_queens();
	bishop_queens |= all_bishops();
	rook_queens |= all_rooks();

	return (pawn_attacks(sq, nWhite) & pawns(nBlack)) |
		   (pawn_attacks(sq, nBlack) & pawns(nWhite)) |
		   (knight_attacks(sq) & all_knights()) |
		   (king_attacks(sq) & all_kings()) |
		   (bishop_attacks(sq, empty_sq) & bishop_queens) |
		   (rook_attacks(sq, empty_sq) & rook_queens);
}

bool ChessBoard::is_attacked(Position sq, Piece side)
{
	if (pawn_attacks(sq, Piece(side^1)) & pawns(side)) return true;
	if (knight_attacks(sq) & knights(side))  return true;
	if (king_attacks(sq) & kings(side)) return true;
	if (bishop_attacks(sq, empty_sq) & (bishops(side) | queens(side))) return true;
	if (rook_attacks(sq, empty_sq) & (rooks(side) | queens(side))) return true;
	return false;
}
