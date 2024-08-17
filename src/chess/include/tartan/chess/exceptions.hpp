#ifndef _TARTAN_CHESS_EXCEPTIONS_HPP_
#define _TARTAN_CHESS_EXCEPTIONS_HPP_

#include <tartan/chess.hpp>
#include <tartan/board/exceptions.hpp>

#include <string>

//! Chess related exceptions namespace
namespace tt::chess::ex {
using std::string;

class duplicate_king : public tt::ex::bad_piece {
public:
	duplicate_king(
		const Piece* p, 
		const string& what_arg = "Board already has a king"
	) : bad_piece(p, what_arg) {};
};

class no_king : public tt::ex::tartan {
public:
	no_king(
		Piece::Color c,
		const string& what_arg = "Board does not have a king"
	) : tartan(what_arg) { e_color = c; };
	Piece::Color e_color;
};

class check : public tt::ex::illegal_move {
public:
	check(
		const Piece* p,
		const Piece::Position& to, 
		const Piece* k,
		const string& what_arg = "King is under check after move") 
	:	illegal_move(p, to, what_arg) { e_king = k; };
	const Piece* king() const { return e_king; };
private:
	const Piece* e_king;
};

class checkmate : public check {
public:
	checkmate(
		const Piece* p,
		const Piece::Position& to, 
		const Piece* k,
		const string& what_arg = "King is under checkmate") 
	:	check(p, to, k, what_arg) {};
private:
};

}

#endif // !_TARTAN_CHESS_EXCEPTIONS_HPP_
