#include "include/dchess.hpp"

#include<stdexcept>
using std::out_of_range;

#include<string>
using std::string;
using std::to_string;

namespace dchess {
	using Position = Piece::Position;

	Position::Position(int x, int y) {
		setX(x);
		setY(y);
	}

	Position::Position(char l, int d) {
		setLetter(l);
		setDigit(d);
	}

	int Position::setX(int x) {
		if (x < 1 or x >  8) {
			throw out_of_range(
					string("Chess piece x position can't be ") + 
					to_string(x) + ".");
		}

		short ret = p_x;
		p_x = x;

		return ret;
	}

	int Position::setY(int y) {
		if (y < 1 or y >  8) {
			throw out_of_range(
					string("Chess piece y position can't be ") + 
					to_string(y) + ".");
		}

		short ret = p_y;
		p_y = y;

		return ret;
	}

	Position Position::offset(int ox, int oy) const {
		return {p_x + ox, p_y + oy};
	}

	inline Position Position::offset(char ol, int od) const {
		return offset(ol - 'a' + 1, od);
	}

	Position Position::operator+(const Position& p) const {
		return Position(p_x + p.p_x, p_y + p.p_y);
	}

	Position Position::operator-(const Position& p) const {
		return Position(p_x - p.p_x, p_y - p.p_y);
	}

	Position Position::operator+=(const Position& p) {
		return *this + p;
	}

	Position Position::operator-=(const Position& p) {
		return *this - p;
	}

	Position Position::operator()(int x, int y) const {
		return offset(x, y);
	}

	inline Position Position::operator()(char l, int d) const {
		return offset(l, d);
	}

	bool Position::operator==(const Position& p) const {
		return !(p.p_x == p_x and p.p_y == p_y);
	}

	std::ostream& operator<<(std::ostream& os, const Position& p) {
		os << p.letter() << p.digit();
		return os;
	}

}
