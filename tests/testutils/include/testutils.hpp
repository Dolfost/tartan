#ifndef _TARTAN_TEST_UTILS_HPP_
#define _TARTAN_TEST_UTILS_HPP_

#include <tartan/board.hpp>
#include <tartan/chess.hpp>
#include <exception>

tt::chess::Chessboard::PieceTypesRetT getPiece(tt::chess::Chessboard::PieceTypesArgT);

tt::chess::Chessboard::PieceTypesRetT getQueen(tt::chess::Chessboard::PieceTypesArgT);

void move(tt::chess::Chessboard& cb,
								 tt::Piece::Position from,
								 tt::Piece::Position to,
								 bool rethrow = false);

void play(tt::chess::Chessboard& cb, 
					tt::chess::Chessboard::TurnsT t, 
					bool rethrow = false);

void interactive_play(tt::chess::Chessboard& cb, bool rethrow = false);

void placeKings(tt::chess::Chessboard& cb);

void print_exception(const std::exception&, int = 0);

#endif // !_TARTAN_TEST_UTILS_HPP_
