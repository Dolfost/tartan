#include "include/dchess.hpp"
#include "include/dchess/exceptions.hpp"

namespace dchess {
	using Turn = Piece::Turn;

	Turn::Turn(const Piece* p, const Position& t, const Piece* c) {
		if (p == nullptr)
			throw illegal_turn("Turn piece cannot be nullptr.");
		m_piece = p;
		m_to = t;
		m_from = p->position();
		m_capture = c;
	}

	bool operator==(const Turn& lhs, const Turn& rhs) {
		return (
				(lhs.m_to == rhs.m_to) and 
				(lhs.m_piece == rhs.m_piece) and 
				(lhs.m_capture == rhs.m_capture));
	}

	std::ostream& operator<<(std::ostream& os, const Turn& t) {
		os << '[' << t.m_piece->position() << "->" << t.m_to;
		if (t.m_capture)
			os << ' ' << t.m_capture->position();
		os << ']';

		return os;
	}

}
