#pragma once

#include <vector>

// macro to generate unsigned long long constants
#define C64(constantU64) constantU64##ULL

// 64 bit
typedef unsigned long long Bitboard;
typedef std::vector<short> BitPos;

typedef enum
{
	a1,b1,c1,d1,e1,f1,g1,h1,
	a2,b2,c2,d2,e2,f2,g2,h2,
	a3,b3,c3,d3,e3,f3,g3,h3,
	a4,b4,c4,d4,e4,f4,g4,h4,
	a5,b5,c5,d5,e5,f5,g5,h5,
	a6,b6,c6,d6,e6,f6,g6,h6,
	a7,b7,c7,d7,e7,f7,g7,h7,
	a8,b8,c8,d8,e8,f8,g8,h8,
	InvalidPos
} Position;

const Bitboard rank1 = C64(0x00000000000000ff);
const Bitboard rank2 = C64(0x000000000000ff00);
const Bitboard rank3 = C64(0x0000000000ff0000);
const Bitboard rank4 = C64(0x00000000ff000000);
const Bitboard rank5 = C64(0x000000ff00000000);
const Bitboard rank6 = C64(0x0000ff0000000000);
const Bitboard rank7 = C64(0x00ff000000000000);
const Bitboard rank8 = C64(0xff00000000000000);

const Bitboard fileA = C64(0x0101010101010101);
const Bitboard fileB = C64(0x0202020202020202);
const Bitboard fileC = C64(0x0404040404040404);
const Bitboard fileD = C64(0x0808080808080808);
const Bitboard fileE = C64(0x1010101010101010);
const Bitboard fileF = C64(0x2020202020202020);
const Bitboard fileG = C64(0x4040404040404040);
const Bitboard fileH = C64(0x8080808080808080);
