#include <tartan/chess.hpp>
#include <tartan/board/exceptions.hpp>

namespace tt::chess {
using Turn = King::Turn;

bool Turn::isEqual(const Piece::Turn& rhs) const {
	const King::Turn* crhs = dynamic_cast<const King::Turn*>(&rhs);
	if (!crhs)
		return false;

	bool castling;
	if (k_castlingTurn == crhs->k_castlingTurn)
		castling = true;
	else if (k_castlingTurn and crhs->k_castlingTurn) 
		castling = *k_castlingTurn == *(crhs->k_castlingTurn);
	else
		castling = false;

	return Piece::Turn::isEqual(rhs) and castling;
}

void Turn::apply(bool) {
	Piece::Turn::apply();

	if (k_castlingTurn) {
		k_castlingTurn->apply();
		dynamic_cast<King*>(t_piece)->k_castled = true;
	}
}

void Turn::undo() {
	Piece::Turn::undo();

	if (k_castlingTurn) {
		k_castlingTurn->undo();
		dynamic_cast<King*>(t_piece)->k_castled = false;
	}
}

std::string Turn::str() const {
	std::string s = Piece::Turn::str();

	if (k_castlingTurn)
		s.append(" {" + k_castlingTurn->str() + "}");

	return s;
}

}
