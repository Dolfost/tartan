#include "include/dchess.hpp"
#include "include/dchess/exceptions.hpp"

namespace dchess {
using Turn = Piece::Turn;

Turn::Turn(const Piece* p, const Position& t, const Piece* c, bool u) {
	if (p == nullptr)
		throw illegal_turn("Turn piece cannot be nullptr.");
	t_piece = const_cast<Piece*>(p);
	t_to = t;
	t_from = p->position();
	t_capture = const_cast<Piece*>(c);
	t_possible = u;
}

void Turn::apply() {
	Chessboard& cb = *t_piece->p_chessboard;
	if (t_capture)
		cb[t_capture->position()] = nullptr;

	cb[t_from] = nullptr;
	cb[t_to] = t_piece;
	t_piece->move(t_to);
}

void Turn::undo() {
	Chessboard& cb = *t_piece->p_chessboard;

	t_piece->move(t_from);
	cb[t_to] = nullptr;
	cb[t_from] = t_piece;

	if (t_capture)
		cb[t_capture->position()] = t_capture;

	Piece::MoveHistoryT& hist = t_piece->p_moveHistory;
	hist.pop_back();
	hist.pop_back();
}

bool Turn::isEqual(const Turn& rhs) const {
	return (
	(t_to == rhs.t_to) and 
	(t_piece == rhs.t_piece) and 
	(t_capture == rhs.t_capture) and
	(t_possible == rhs.t_possible));
}

bool operator==(const Turn& lhs, const Turn& rhs) {
	return lhs.isEqual(rhs);
}

bool operator!=(const Turn& lhs, const Turn& rhs) {
	return !lhs.isEqual(rhs);
}

std::ostream& operator<<(std::ostream& os, const Turn& t) {
	os << '['; 
	if (!t.t_possible)
		os << "X ";
	os << t.from() << "->" << t.t_to;
	if (t.t_capture)
		os << ' ' << t.t_capture->position();
	os << ']';

	return os;
}

auto Turn::clone() const -> std::decay<decltype(*this)>::type * {
    return new std::decay<decltype(*this)>::type(*this);
}

}
