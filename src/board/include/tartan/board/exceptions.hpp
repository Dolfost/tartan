#ifndef _TARTAN_BOARD_EXCEPTIONS_HPP_
#define _TARTAN_BOARD_EXCEPTIONS_HPP_

#include <tartan/board.hpp>
#include <stdexcept>
#include <string>

namespace {
using std::string;
using std::logic_error;
using std::bad_typeid;
using std::runtime_error;
}

//! Tartan tt::Board exceptions set
namespace tt::ex {

/**
 * @brief Base class for all tartan exceptions
 *
 * Every exception that is related to gameplay
 * thrown by this library
 * is derived from this class.
 */
class tartan : public logic_error {
public:
	using logic_error::logic_error;
	virtual ~tartan() = default;
};

/**
 * @brief Exception when Board::set() functions fail
 *
 * This exception is rethrown in 
 * Board::set() functions with std::throw_with_nested.
 */
class bad_set : public tartan {
public:
	bad_set(
		const string& what_arg = "Can not produce piece set"
	) : tartan(what_arg) {};
};

//! Base class for exceptions about pieces
class bad_piece : public tartan {
public:
	/**
	 * @param p Piece object report is based on
	 * @param what_arg message string
	 */
	bad_piece(
		const Piece* p, 
		const string& what_arg = "Invalid piece"
	) : tartan(what_arg) { e_piece = p; }
	/**
	 * @brief Get the reported tt::Piece object
	 *
	 * @return Piece object
	 */
	const Piece* piece() const { return e_piece; };
private:
	const Piece* e_piece;
};

/** 
	* @brief Thrown when Piece pointer 
	* is `nullptr` when it should not be
	*/
class null_piece : public bad_piece {
public:
	/**
	 * @param what_arg message string
	 */
	null_piece(
		const string what_arg = "Piece does not exists"
	) : bad_piece(nullptr, what_arg) {};
	const Piece* piece() const = delete;
};

/**
 * @brief Thrown when piece does not belong to Board
 * object in which it is being processed
 */
class foreign_piece : public bad_piece {
public:
	/**
	 * @param p Piece that is foreign
	 * @param b Board which were trying to do 
	 * something with `p` (`p` does not belong to `b` Board)
	 * @param what_arg message string
	 */
	foreign_piece(
		const Piece* p, 
		const Board* b, 
		const string& what_arg = "Piece does not belong to this board"
	) : bad_piece(p, what_arg) { e_board = b; };
	/**
	 * @brief Get the Board object
	 *
	 * @return Board object that tried to process 
	 * foreign Piece object
	 */
	const Board* board() const { return e_board; };
private:
	const Board* e_board;
};

/**
 * @brief Thrown when Board::piece() can not 
 * recognize Piece specification
 */
class bad_piece_spec : public bad_piece {
public:
	/**
	 * @param spec the spec that is malformed
	 * @param what_arg message string
	 */
	bad_piece_spec(
		const string& spec,
		const string what_arg = "Invalid piece specification"
	) : bad_piece(nullptr, what_arg) { e_spec = spec; };  
	/**
	 * @brief Get the malformed spec string
	 *
	 * @return the bad spec string
	 */
	const string& spec() const { return e_spec; };
private:
	string e_spec;
};

/**
 * @brief Thrown when Piece Position on Board is 
 * occupied when it should not to
 */
class position_is_taken : public bad_piece {
public:
	position_is_taken(
		const Piece* p, 
		const string& what_arg = "Piece position is taken"
	) : bad_piece(p, what_arg) {};
};
	
/**
 * @brief Base class for Board::makeMove()
 * function errors
 */
class illegal_move : public tartan {
public:
	/**
	 * @param p Piece object that tries 
	 * to make illegal move
	 * @param to location to which `p` tried to move
	 * @param what_arg message string
	 */
	illegal_move(const Piece* p, const Piece::Position& to, 
							const string& what_arg = "Illegal move") : 
		tartan(what_arg), e_piece(p), e_to(to) {
	};
	/**
	 * @brief Get Piece object
	 *
	 * @return Piece object that tried 
	 * to perform illegal move
	 */
	const Piece* piece() const { return e_piece; };
	/**
	 * @brief Get move target location
	 *
	 * @return Position to which Piece 
	 * object tried to move
	 */
	const Piece::Position& to() const { return e_to; };
	virtual ~illegal_move() = default;
private:
	const Piece* e_piece;
	const Piece::Position& e_to;
};

/**
 * @brief Thrown when selected Piece location
 * is empty of the Board
 */
class tile_is_empty : public illegal_move {
public:
	/**
	 * @param from Position turn were performed from
	 * @param to Position turn were performed to 
	 * @param what_arg message string
	 */
	tile_is_empty(
		const Piece::Position& from, 
		const Piece::Position& to, 
		const string& what_arg = "Selected tile is empty") 
	:	illegal_move(nullptr, to, what_arg), e_from(from) {};
	const Piece* piece() = delete;
	/**
	 * @brief Get empli tile Position
	 *
	 * @return empty tile Position
	 */
	const Piece::Position& from() const { return e_from; };
private:
	const Piece::Position& e_from;
};

/**
 * @brief Thrown when trying to Board::makeMove()
 * on Piece that has wrong Piece::Color.
 */
class piece_in_wrong_color : public illegal_move {
public:
	/**
	 * @param p Piece object that is in wrong color
	 * @param to target Position of move
	 * @param what_arg message string
	 */
	piece_in_wrong_color(
		const Piece* p, 
		const Piece::Position& to, 
		const string& what_arg = "Moved piece is in wrong color") 
	:	illegal_move(p, to, what_arg) {};
};

/**
 * @brief Thrown when Board::makeMove() is performed 
 * on Piece that can not make any moves
 */
class can_not_move : public illegal_move {
public:
	/**
	 * @param p Piece object that can not move
	 * @param to target Position of such move
	 * @param what_arg message string
	 */
	can_not_move(
		const Piece* p,
		const Piece::Position& to, 
		const string& what_arg = "Selected piece can't move") 
	:	illegal_move(p, to, what_arg) {};
};

/**
 * @brief Thrown when piece moved with Board::makeMove() 
 * can not have such move.
 */
class no_such_move : public illegal_move {
public:
	/**
	 * @param p Piece object that does not have
	 * such move
	 * @param to target Position of such move
	 * @param what_arg message string
	 */
	no_such_move(
		const Piece* p,
		const Piece::Position& to, 
		const string& what_arg = "Selected piece can't perform such move") 
	:	illegal_move(p, to, what_arg) {};
};

/**
 * @brief Thrown when constructed Piece::Turn object 
 * is malformed
 */
class illegal_turn : public tartan {
public:
	/**
	 * @param what_arg message string
	 */
	illegal_turn(const string& what_arg) :
		tartan(what_arg) {};
	illegal_turn(const char* what_arg) :
		tartan(what_arg) {};
};

/**
 * @brief Thrown when tt::Board::getPieceType() returns std::type_info
 * that is not mentioned in its argument.
 */
class bad_piece_type : public tartan {
public:
	bad_piece_type(const string what_arg = "Piece type is illegal") :
		tartan(what_arg) {};
};

}

#endif // !_TARTAN_BOARD_EXCEPTIONS_HPP_
