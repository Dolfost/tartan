#include "include/dchess.hpp"
#include "include/dchess/exceptions.hpp"

namespace dchess {
using Turn = Piece::Turn;

Turn::Turn(const Piece* p, const Position& t, const Piece* c) {
	if (p == nullptr)
		throw illegal_turn("Turn piece cannot be nullptr.");
	t_piece = const_cast<Piece*>(p);
	t_to = t;
	t_from = p->position();
	t_capture = const_cast<Piece*>(c);
}

void Turn::apply() {
	Chessboard& cb = t_piece->p_chessboard;
	if (t_capture) {
		cb[t_capture->position()] = nullptr;
	}

	cb[t_from] = nullptr;
	cb[t_to] = t_piece;
	t_piece->move(t_to);
}

bool Turn::isEqual(const Turn& rhs) const {
	return (
	(t_to == rhs.t_to) and 
	(t_piece == rhs.t_piece) and 
	(t_capture == rhs.t_capture));
}

bool operator==(const Turn& lhs, const Turn& rhs) {
	return lhs.isEqual(rhs);
}

bool operator!=(const Turn& lhs, const Turn& rhs) {
	return !lhs.isEqual(rhs);
}

std::ostream& operator<<(std::ostream& os, const Turn& t) {
	os << '[' << t.t_piece->position() << "->" << t.t_to;
	if (t.t_capture)
		os << ' ' << t.t_capture->position();
	os << ']';

	return os;
}


}
