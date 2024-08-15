#ifndef _TARTAN_BOARD_EXCEPTIONS_HPP_
#define _TARTAN_BOARD_EXCEPTIONS_HPP_

#include <tartan/board.hpp>
#include <stdexcept>
#include <string>

namespace tt {
using std::string;
using std::logic_error;
using std::bad_typeid;
using std::runtime_error;

class board_error : public logic_error {
public:
	using logic_error::logic_error;
};

class can_not_produce_set : public board_error {
public:
	can_not_produce_set(
		const string& what_arg = "Can not produce piece set"
	) : board_error(what_arg) {};
};

class invalid_piece : public board_error {
public:
	invalid_piece(
		const Piece* p, 
		const string& what_arg = "Invalid piece"
	) : board_error(what_arg) { e_piece = p; }
	const Piece* piece() const { return e_piece; };
private:
	const Piece* e_piece;
};

class invalid_piece_spec : public invalid_piece {
public:
	invalid_piece_spec(
		const string& spec,
		const string what_arg = "Invalid piece specification"
	) : invalid_piece(nullptr, what_arg) { e_spec = spec; };  
	const string& spec() const { return e_spec; };
private:
	string e_spec;
};

class piece_belongs_to_board_already : public invalid_piece {
public:
	piece_belongs_to_board_already(
		const Piece* p, 
		const string& what_arg = "Piece belongs to board already"
	) : invalid_piece(p, what_arg) {};
};

class position_is_taken : public invalid_piece {
public:
	position_is_taken(
		const Piece* p, 
		const string& what_arg = "Piece insertion position is taken"
	) : invalid_piece(p, what_arg) {};
};
	
class illegal_move : public board_error {
public:
	illegal_move(const Piece* p, const Piece::Position& to, 
							const string& what_arg = "Illegal move") : 
		board_error(what_arg), e_piece(p), e_to(to) {
	};
	const Piece* piece() const { return e_piece; };
	const Piece::Position& to() const { return e_to; };
private:
	const Piece* e_piece;
	const Piece::Position& e_to;
};


class tile_is_empty : public illegal_move {
public:
	tile_is_empty(
		const Piece::Position& from, 
		const Piece::Position& to, 
		const string& what_arg = "Selected tile is empty") 
	:	illegal_move(nullptr, to, what_arg), e_from(from) {};
	const Piece* piece() = delete;
	const Piece::Position& from() const { return e_from; };
private:
	const Piece::Position& e_from;
};

class piece_in_wrong_color : public illegal_move {
public:
	piece_in_wrong_color(
		const Piece* from, 
		const Piece::Position& to, 
		const string& what_arg = "Moved piece is in wrong color") 
	:	illegal_move(from, to, what_arg) {};
};

class can_not_move : public illegal_move {
public:
	can_not_move(
		const Piece* p,
		const Piece::Position& to, 
		const string& what_arg = "Selected piece can't move") 
	:	illegal_move(p, to, what_arg) {};
};

class no_such_move : public illegal_move {
public:
	no_such_move(
		const Piece* p,
		const Piece::Position& to, 
		const string& what_arg = "Selected piece can't perform such move") 
	:	illegal_move(p, to, what_arg) {};
};

class illegal_turn : public runtime_error {
public:
	using runtime_error::what;
	illegal_turn(const string& what_arg) :
		runtime_error(what_arg) {};
	illegal_turn(const char* what_arg) :
		runtime_error(what_arg) {};
};

class illegal_getter_type : public bad_typeid {
public:
	illegal_getter_type() :
		bad_typeid() {};
};

}

#endif // !_TARTAN_BOARD_EXCEPTIONS_HPP_