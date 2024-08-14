#ifndef _TARTAN_CHESS_EXCEPTIONS_HPP_
#define _TARTAN_CHESS_EXCEPTIONS_HPP_

#include <tartan/chess.hpp>
#include <tartan/board/exceptions.hpp>

#include <string>

namespace tt::chess {
using std::string;

class duplicate_king : public invalid_piece {
public:
	duplicate_king(
		const Piece* p, 
		const string& what_arg = "Board already has a king"
	) : invalid_piece(p, what_arg) {};
};

class no_king : public board_error {
public:
	no_king(
		Piece::Color c,
		const string& what_arg = "Board does not have a king"
	) : board_error(what_arg) { e_color = c; };
	Piece::Color e_color;
};

class king_is_under_check : public illegal_move {
public:
	king_is_under_check(
		const Piece* p,
		const Piece::Position& to, 
		const Piece* k,
		const string& what_arg = "King is under check after move") 
	:	illegal_move(p, to, what_arg) { e_king = k; };
	const Piece* king() const { return e_king; };
private:
	const Piece* e_king;
};

class king_is_under_checkmate : public king_is_under_check {
public:
	king_is_under_checkmate(
		const Piece* p,
		const Piece::Position& to, 
		const Piece* k,
		const string& what_arg = "King is under checkmate") 
	:	king_is_under_check(p, to, k, what_arg) {};
private:
};

}

#endif // !_TARTAN_CHESS_EXCEPTIONS_HPP_
