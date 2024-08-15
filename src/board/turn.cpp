#include <tartan/board.hpp>
#include <tartan/board/exceptions.hpp>

namespace tt {
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

void Turn::apply(bool) {
	Board& cb = *t_piece->p_board;
	cb.b_turnIndex++;
	
	if (t_capture)
		cb[t_capture->position()] = nullptr;

	t_piece->move(t_to);
}

void Turn::undo() {
	Board& cb = *t_piece->p_board;
	cb.b_turnIndex--;

	t_piece->move(t_from);

	if (t_capture)
		cb[t_capture->position()] = t_capture;

	t_piece->p_movesMade -= 2;
}

bool Turn::isEqual(const Turn& rhs) const {
	return (
	(t_to == rhs.t_to) and 
	(t_piece == rhs.t_piece) and 
	(t_capture == rhs.t_capture) and
	(t_possible == rhs.t_possible));
}

std::string Turn::str() const {
	std::string str; 
	if (!t_possible)
		str.append("X ");

	str.append(t_from.str() + "->" + t_to.str());

	if (t_capture)
		str.append(" " + t_capture->position().str());
	return str;
}

bool operator==(const Turn& lhs, const Turn& rhs) {
	return lhs.isEqual(rhs);
}

bool operator!=(const Turn& lhs, const Turn& rhs) {
	return !lhs.isEqual(rhs);
}


std::ostream& operator<<(std::ostream& os, const Turn& t) {
	return os << '[' << t.str() << ']';
}

auto Turn::clone() const -> std::decay<decltype(*this)>::type * {
	return new std::decay<decltype(*this)>::type(*this);
}

}
