#pragma once

#include "bitboard.h"
#include "chess_types.h"
#include <iostream>
#include <string>
#include <algorithm>


struct Move;

class ChessBoard
{
 public:
	enum Piece
	{
		nWhite,  // all white pieces
		nBlack,  // all black pieces
		nPawn,   // all pawns
		nKnight, // all knights
		nBishop, // all bishops
		nRook,   // all rooks
		nQueen,  // all queens
		nKing,   // all kings
		InvalidPiece
	};

	ChessBoard();

	void disp_cboard(const std::string& header = "Board");

	void quite_move(Move m);
	void capture_move(Move m);

 private:
	Bitboard pieceBB[8];
	Bitboard occupied_sq;
	Bitboard empty_sq;
};

typedef ChessBoard::Piece Piece;

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
		piece = color = c_piece = c_color = ChessBoard::InvalidPiece;
	}

	Move(Position from_, Position to_, Piece piece_, Piece color_, Piece c_piece_ = ChessBoard::InvalidPiece, Piece c_color_ = ChessBoard::InvalidPiece)
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
 	Bitboard fromBB = lookup[m.from];
	Bitboard toBB = lookup[m.to];
	Bitboard fromtoBB = fromBB ^ toBB;
	pieceBB[m.piece] ^= fromtoBB;
	pieceBB[m.color] ^= fromtoBB;
	occupied_sq ^= fromtoBB;
	empty_sq ^= fromtoBB;
}

void ChessBoard::capture_move(Move m)
{
 	Bitboard fromBB = lookup[m.from];
	Bitboard toBB = lookup[m.to];
	Bitboard fromtoBB = fromBB ^ toBB;
	pieceBB[m.piece] ^= fromtoBB;
	pieceBB[m.color] ^= fromtoBB;
	pieceBB[m.c_piece] ^= toBB;
	pieceBB[m.c_color] ^= toBB;
	occupied_sq ^= fromBB;
	empty_sq ^= fromBB;
}
