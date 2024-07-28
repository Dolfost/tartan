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

	bool Position::operator==(const Position& p) const {
		return (p.p_x == p_x and p.p_y == p_y);
	}

	bool operator<(const Position& l, const Position& r) {
		return std::hypot(l.p_x - 1, l.p_y - 1) < 
			std::hypot(r.p_x - 1, r.p_y - 1);
	}

	std::ostream& operator<<(std::ostream& os, const Position& p) {
		os << string(p.letter(), 1) + to_string(p.digit());
		return os;
	}

}
