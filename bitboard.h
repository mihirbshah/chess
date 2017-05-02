#pragma once

#include "chess_types.h"
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>
#include <cassert>

// macro to generate unsigned long long constants
#define C64(constantU64) constantU64##ULL

// 64 bit
typedef unsigned long long Bitboard;
typedef std::vector<short> BitPos;

void disp_bb(Bitboard b, const std::string& header = std::string())
{
	std::cout << header << ":\n\n";
	// mask to extract MSB
	Bitboard mask = C64(0x8000000000000000);
	std::string s;
	for (int i = 0; i < 65; ++i) //Run the loop til 65 to print the last batch
	{
		if (i % 8 == 0)
		{
			if (s.length())
			{
				// derive rank number
				s = std::to_string(9 - int(i/8)) + " | " + s;
				std::cout << s << "\n";
				s.clear();
			}
		}
		// prepend new bits since LSB <-> a1 and MSB <-> h8
		if (b & mask) // check if MSB is set
			s = "X  " + s;
		else
			s = "-  " + s;
		b = b << 1; // drop MSB
	}
	// unicode for continuous horizontal dash
	//const char* hdash  = "\u2500\u2500\u2500\u2500\u2500\u2500\u2500";
	//std::cout << hdash << hdash << hdash << hdash << std::endl;
	std::cout << "---------------------------\n";
	std::cout << "  | a  b  c  d  e  f  g  h  \n\n";
}


/*
 * 3 ways to shift -
 * 1. Using individual shift functions
 * 2. Using shift_one()
 * 3. Using rotate_one()
 */

/* Bitboard shifts
  northwest    north   northeast
  noWe         nort         noEa
          +7    +8    +9
              \  |  /
  west    -1 <-  0 -> +1    east
              /  |  \
          -9    -8    -7
  soWe         sout         soEa
  southwest    south   southeast
*/
Bitboard south_one(Bitboard b)
{
	return b >> 8;
}

Bitboard north_one(Bitboard b)
{
	return b << 8;
}

namespace
{
	const Bitboard not_a_file = C64(0xfefefefefefefefe); // ~0x0101010101010101
	const Bitboard not_h_file = C64(0x7f7f7f7f7f7f7f7f); // ~0x8080808080808080
	const Bitboard not_g_h_file = C64(0x3f3f3f3f3f3f3f3f);
	const Bitboard not_a_b_file = C64(0xfcfcfcfcfcfcfcfc);
};

Bitboard east_one(Bitboard b)
{
	return (b << 1) & not_a_file;
}

Bitboard west_one(Bitboard b)
{
	return (b >> 1) & not_h_file;
}

Bitboard ne_one(Bitboard b)
{
	return (b << 9) & not_a_file;
}

Bitboard nw_one(Bitboard b)
{
	return (b << 7) & not_h_file;
}

Bitboard se_one(Bitboard b)
{
	return (b >> 7) & not_a_file;
}

Bitboard sw_one(Bitboard b)
{
	return (b >> 9) & not_h_file;
}


enum ray_dir {ne, east, se, south, sw, west, nw, north};

namespace
{
//                ne e  se  s   sw  w   nw n
short shift[8] = {9, 1, -7, -8, -9, -1, 7, 8};

Bitboard shift_mask[8] =
{
	C64(0xfefefefefefefefe), // ne
	C64(0xfefefefefefefefe), // e
	C64(0xfefefefefefefefe), // se
	C64(0xffffffffffffffff), // s
	C64(0x7f7f7f7f7f7f7f7f), // sw
	C64(0x7f7f7f7f7f7f7f7f), // w
	C64(0x7f7f7f7f7f7f7f7f), // nw
	C64(0xffffffffffffffff)  // n
};

Bitboard rotate_mask[8] =
{
	C64(0xfefefefefefefe00), // ne
	C64(0xfefefefefefefefe), // e
	C64(0x00fefefefefefefe), // se
	C64(0x00ffffffffffffff), // s
	C64(0x007f7f7f7f7f7f7f), // sw
	C64(0x7f7f7f7f7f7f7f7f), // w
	C64(0x7f7f7f7f7f7f7f00), // nw
	C64(0xffffffffffffff00)  // n
};

};

Bitboard shift_one(Bitboard b, ray_dir dir)
{
	if (shift[dir] > 0)
		return (b << shift[dir]) & shift_mask[dir]; // n, e, ne, nw
	else
		return (b >> abs(shift[dir])) & shift_mask[dir]; // s, w, se, sw
}

/* Bitboard rotation */
Bitboard rotl64(Bitboard b, short pos)
{
	return (b << pos) | (b >> (64 - pos));
}

Bitboard rotr64(Bitboard b, short pos)
{
	return (b >> pos) | (b << (64 - pos));
}

Bitboard rotate_one(Bitboard b, ray_dir dir)
{
	return rotl64(b, shift[dir]) & rotate_mask[dir];
}


Bitboard lookup[64];
//TODO: Check if we can do this compile time  by template metaprogramming
void setup_lookup_table()
{
	for (int i = 0; i < 64; ++i)
		lookup[i] = C64(1) << i;
}

bool test(Bitboard x, Position pos)
{
	return x & lookup[pos];
}

Bitboard set(Bitboard x, Position pos)
{
	return x | lookup[pos];
}

Bitboard toggle(Bitboard x, Position pos)
{
	return x ^ lookup[pos];
}

Bitboard reset(Bitboard x, Position pos)
{
	//slower way
	//return x & ~lookup[pos];
	//faster way
	return toggle(set(x, pos), pos);
}

// http://stackoverflow.com/questions/14086854/get-an-array-of-the-bit-positions-within-a-64-bit-integer
// Time Complexity O(set bits)
BitPos get_set_bits(Bitboard b)
{
	BitPos res;
	res.reserve(64);
	for (int n = 0; b; ++n, b &= (b - 1))
	{
		res.push_back(log2(b & ~(b - 1)));
	}
	return res;
}

Bitboard upper_bits(Position pos)
{
	return C64(~1) << pos;
}

Bitboard lower_bits(Position pos)
{
	return (C64(1) << pos) - 1;
}

// http://chessprogramming.wikispaces.com/General+Setwise+Operations#Shifting Bitboards-Swapping Bits
/**
 * swap n non-overlapping bits from index "from" to index "to"
 * @param b any bitboard
 * @param from,to positions on bitboard
 * @param n number of consecutive bits to swap
 * @return bitboard with swapped bit-sequences
 */
Bitboard swap_n_bits(Bitboard b, Position from, Position to, int n)
{
	Bitboard m = (1 << n) - 1;
	Bitboard x = ((b >> from) ^ (b >> to)) & m;
	return ((x << from) ^ (x << to)) ^ b;
}

/**
 * swap any non-overlapping pairs of bits that are delta places apart
 * @param b any bitboard
 * @param mask has a 1 on the least significant position
 *        for each pair supposed to be swapped
 * @param delta of pairwise swapped bits
 * @return bitboard b with bits swapped
 */

Bitboard delta_swap(Bitboard b, Bitboard mask, int delta)
{
	Bitboard x = (b ^ (b >> delta)) & mask;
	return (x ^ (x << delta)) ^ b;
}

// Get LS1B
Bitboard ls1b_of_x(Bitboard b)
{
	return b & (-b);
}

// Reset LS1B
Bitboard reset_ls1b_of_x(Bitboard b)
{
	return b & (b - 1);
}

// Get mask of all bits above LS1B set
Bitboard above_ls1b_mask(Bitboard b)
{
	return b ^ (-b);
}

// Get mask of all bits below (including) LS1B
Bitboard below_ls1b_mask_including(Bitboard b)
{
	return b ^ (b - 1);
}

// Get mask of all bits below LS1B
Bitboard below_ls1b_mask(Bitboard b)
{
	return (~b) & (b - 1);
}

// Paint all bits above LS1B with 1b
Bitboard smear_ls1b_up(Bitboard b)
{
	return b | (-b);
}

// Paint all bits below LS1B with 1b
Bitboard smear_ls1b_down(Bitboard b)
{
	return b | (b - 1);
}

// Get LS0B
Bitboard ls0b_of_x(Bitboard b)
{
	return b | ~(b + 1);
}

// Set LS0B
Bitboard set_ls0b_of_x(Bitboard b)
{
	return b | (b + 1);
}

// Get mask of all bits below (including) LS0B
Bitboard below_ls0b_mask_including(Bitboard b)
{
	return b ^ (b + 1);
}

// Get mask of all bits below LS0B
Bitboard below_ls0b_mask(Bitboard b)
{
	return b & ~(b + 1);
}

// Get mask of all bits above LS0B set
Bitboard above_ls0b_mask(Bitboard b)
{
	return ~below_ls0b_mask_including(b);
}

// Paint all bits above LS0B with 0b
Bitboard smear_ls0b_up(Bitboard b)
{
	return below_ls0b_mask(b);
}

// Paint all bits below LS0B with 0b
Bitboard smear_ls0b_down(Bitboard b)
{
	return b & (b + 1);
}

bool empty(Bitboard b) { return !b; }

// Bitboard is power of 2
bool popcnt_eq_1(Bitboard b)
{
	return (!empty(b) && !reset_ls1b_of_x(b));
}

// popcnt = 0 or 1
bool popcnt_le_1(Bitboard b)
{
	return !reset_ls1b_of_x(b);
}

// popcnt > 1
bool popcnt_gt_1(Bitboard b)
{
	return reset_ls1b_of_x(b);
}

// x % 2^n == x & (2^n - 1)
Bitboard mod(Bitboard x, Bitboard y)
{
	if (popcnt_eq_1(y)) return x & (y - 1);
	return x % y;
}

int pop_cnt_0(Bitboard b)
{
	int cnt = 0;
	for (int i = 0; i < 64; ++i, b >>= 1)
		cnt += (int)(b & 1);
	return cnt;
}

// population count - Kernighan way
int pop_cnt_1(Bitboard b)
{
	int cnt = 0;
	while (b)
	{
		++cnt;
		b = reset_ls1b_of_x(b);
	}
	return cnt;
}

// population count - lookup table
unsigned char pop_cnt_of_byte[256];
void init_pop_cnt_of_byte()
{
	pop_cnt_of_byte[0] = 0;
	for (int i = 1; i < 256; ++i)
		pop_cnt_of_byte[i] = pop_cnt_of_byte[i/2] + mod(i,2);
}

int pop_cnt_2(Bitboard b)
{
	return pop_cnt_of_byte[b         & 0xff] +
		   pop_cnt_of_byte[(b >> 8)  & 0xff] +
		   pop_cnt_of_byte[(b >> 16) & 0xff] +
		   pop_cnt_of_byte[(b >> 24) & 0xff] +
		   pop_cnt_of_byte[(b >> 32) & 0xff] +
		   pop_cnt_of_byte[(b >> 40) & 0xff] +
		   pop_cnt_of_byte[(b >> 48) & 0xff] +
		   pop_cnt_of_byte[(b >> 56) & 0xff];
}

// Return bit index of LS1B
int bit_scan_forward(Bitboard b)
{
	assert(b);
	// slow
	//return log2(ls1b_of_x(b));

	// fast (because it avoids negation)
	// return log2(below_ls1b_mask_including(b));

	// faster avoids log2
	return pop_cnt_1(below_ls1b_mask_including(b)) - 1;
}

int bit_scan_reverse(Bitboard b)
{
	return floor(log2(b));
}

int trailing_zero_cnt(Bitboard b)
{
	if (b) return bit_scan_forward(b);
	return 64;
}

int leading_zero_cnt(Bitboard b)
{
	if (b) return bit_scan_reverse(b) ^ 63; // xor with 63 because 63 is the largest value return by bit_scan_reverse
	return 64;
}

Bitboard sum(Bitboard a, Bitboard b)
{
	return (a ^ b) + 2 * (a & b);
}

Bitboard flip_vertical(Bitboard b)
{
  Bitboard sel_mask_1 = C64(0xff000000000000ff);
  Bitboard sel_mask_2 = C64(0x00ff00000000ff00);
  Bitboard sel_mask_3 = C64(0x0000ff0000ff0000);
  Bitboard sel_mask_4 = C64(0x000000ffff000000);
  Bitboard and_mask_1 = C64(0x00000000000000ff);
  Bitboard and_mask_2 = C64(0x000000000000ff00);
  Bitboard and_mask_3 = C64(0x0000000000ff0000);
  Bitboard and_mask_4 = C64(0x00000000ff000000);
  return delta_swap(b & sel_mask_1, and_mask_1, (a8 - a1)) |
         delta_swap(b & sel_mask_2, and_mask_2, (a7 - a2)) |
         delta_swap(b & sel_mask_3, and_mask_3, (a6 - a3)) |
         delta_swap(b & sel_mask_4, and_mask_4, (a5 - a4));
}

Bitboard mirror_horizontal(Bitboard b)
{
  Bitboard sel_mask_1 = C64(0x8181818181818181);
  Bitboard sel_mask_2 = C64(0x4242424242424242);
  Bitboard sel_mask_3 = C64(0x2424242424242424);
  Bitboard sel_mask_4 = C64(0x1818181818181818);
  Bitboard and_mask_1 = C64(0x0101010101010101);
  Bitboard and_mask_2 = C64(0x0202020202020202);
  Bitboard and_mask_3 = C64(0x0404040404040404);
  Bitboard and_mask_4 = C64(0x0808080808080808);
  return delta_swap(b & sel_mask_1, and_mask_1, (h1 - a1)) |
         delta_swap(b & sel_mask_2, and_mask_2, (g1 - b1)) |
         delta_swap(b & sel_mask_3, and_mask_3, (f1 - c1)) |
         delta_swap(b & sel_mask_4, and_mask_4, (e1 - d1));
}

Bitboard flip_diag_a1h8(Bitboard b) {
  Bitboard t;
  const Bitboard k1 = C64(0x5500550055005500);
  const Bitboard k2 = C64(0x3333000033330000);
  const Bitboard k4 = C64(0x0f0f0f0f00000000);
  t  = k4 & (b ^ (b << 28));
  b ^=       t ^ (t >> 28) ;
  t  = k2 & (b ^ (b << 14));
  b ^=       t ^ (t >> 14) ;
  t  = k1 & (b ^ (b <<  7));
  b ^=       t ^ (t >>  7) ;
  return b;
}

Bitboard flip_diag_a8h1(Bitboard b) {
  Bitboard t;
  const Bitboard k1 = C64(0xaa00aa00aa00aa00);
  const Bitboard k2 = C64(0xcccc0000cccc0000);
  const Bitboard k4 = C64(0xf0f0f0f00f0f0f0f);
  t  =       b ^ (b << 36) ;
  b ^= k4 & (t ^ (b >> 36));
  t  = k2 & (b ^ (b << 18));
  b ^=       t ^ (t >> 18) ;
  t  = k1 & (b ^ (b <<  9));
  b ^=       t ^ (t >>  9) ;
  return b;
}

Bitboard rotate180(Bitboard b)
{
	return flip_vertical(mirror_horizontal(b));
}

Bitboard rotate90_clockwise(Bitboard b)
{
	return flip_vertical(flip_diag_a1h8(b));
}

Bitboard rotate90_anticlockwise(Bitboard b)
{
	return flip_vertical(flip_diag_a8h1(b));
}

