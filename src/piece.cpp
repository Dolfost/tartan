#include "include/dchess.hpp"

namespace dchess {
using Position = Piece::Position;

Piece::Piece(const Position&  p, const Color& c, Chessboard* cb) { 
	p_position = p; 
	p_color = c; 
	p_chessboard = cb;

	if (p_chessboard)
		p_chessboard->insertPiece(this);
};

Chessboard* Piece::setChessboard(Chessboard* cb) {
	Chessboard* ret = p_chessboard;
	p_chessboard = cb;
	return ret;
}

Position Piece::move(const Position& p) {
	Position ret = p_position;
	p_position = p;
	p_moveHistory.push_back(p);
	return ret;
}

}
