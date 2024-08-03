#include "include/dchess.hpp"
#include <iostream>

namespace dchess {
using Turn = Piece::Turn;
using TurnMap = Piece::TurnMap;

TurnMap::~TurnMap() {
	std::for_each(begin(), end(), [](Turn* t) {
		delete t;
	});
}

TurnMap::TurnMap(std::initializer_list<Turn> turns) {
	for (auto& turn : turns) {
		push_front(new Turn(turn));
	}
}

bool operator==(const TurnMap& lhs, const TurnMap& rhs) {
	auto lit = lhs.begin();
	auto rit = rhs.begin();

	while (lit != lhs.end() and rit != rhs.end()) {
		if (!(*lit)->isEqual(**rit))
			return false;
		lit++, rit++;
	}

	if (lit != lhs.end() or rit != rhs.end())
		return false;

	return true;
}

}
