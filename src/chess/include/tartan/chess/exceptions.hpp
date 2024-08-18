#ifndef _TARTAN_CHESS_EXCEPTIONS_HPP_
#define _TARTAN_CHESS_EXCEPTIONS_HPP_

#include <tartan/chess.hpp>
#include <tartan/board/exceptions.hpp>

#include <string>

//! Chess related exceptions namespace
namespace tt::chess::ex {

/**
 * @brief Thrown when inserted King is already provided
 */
class duplicate_king : public tt::ex::bad_piece {
public:
	duplicate_king(
		const Piece* p, 
		const std::string& what_arg = "Board already has a king"
	) : bad_piece(p, what_arg) {};
};

/**
 * @brief Thrown when tt::chess::Chessboard has 
 * no King object of certain tt::Piece::Color
 */
class no_king : public tt::ex::tartan {
public:
	/**
	 * @param c color of King object that is 
	 * not present
	 * @param what_arg message string
	 */
	no_king(
		Piece::Color c,
		const std::string& what_arg = "Board does not have a king"
	) : tartan(what_arg) { e_color = c; };
	Piece::Color e_color;
	/**
	 * @brief Get the King color
	 *
	 * @return Non-existent King object color
	 */
	Piece::Color color() const { return e_color; };
};

/**
 * @brief Thrown when turn cannot be perfomred 
 * because of King beeing in check
 * @sa tt::chess::King::check()
 */
class check : public tt::ex::illegal_move {
public:
	/**
	 * @param k pointer to endangered
	 * King object
	 * @copydetails tt::ex::illegal_move()
	 */
	check(
		const Piece* p,
		const Piece::Position& to, 
		const Piece* k,
		const std::string& what_arg = "King is under check after move") 
	:	illegal_move(p, to, what_arg) { e_king = k; };
	//! @brief Get the King object
	const Piece* king() const { return e_king; };
private:
	const Piece* e_king;
};

/**
 * @brief Thrown when turn cannot be perfomred 
 * because of King is under checkmate
 * @sa tt::chess::King::checkmate()
 */
class checkmate : public check {
public:
	/**
	 * @copydetails check::check() 
	*/
	checkmate(
		const Piece* p,
		const Piece::Position& to, 
		const Piece* k,
		const std::string& what_arg = "King is under checkmate") 
	:	check(p, to, k, what_arg) {};
};

}

#endif // !_TARTAN_CHESS_EXCEPTIONS_HPP_
