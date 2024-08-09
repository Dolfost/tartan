#ifndef _DCHESS_TEST_UTILS_HPP_
#define _DCHESS_TEST_UTILS_HPP_

#include "dchess.hpp"
#include <exception>
using namespace dchess;

Chessboard::PieceTypesRetT getPiece(Chessboard::PieceTypesArgT);

Chessboard::PieceTypesRetT getQueen(Chessboard::PieceTypesArgT);

void move(Chessboard& cb,
								 Piece::Position from,
								 Piece::Position to,
								 bool rethrow = false);

void play(Chessboard& cb, 
					Chessboard::TurnsT t, 
					bool rethrow = false);

void interactive_play(Chessboard& cb, bool rethrow = false);

void placeKings(Chessboard& cb);

void print_exception(const std::exception&, int = 0);

#endif // !_DCHESS_TEST_UTILS_HPP_
