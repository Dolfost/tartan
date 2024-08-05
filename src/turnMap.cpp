#include "include/dchess.hpp"

namespace dchess {
using Turn = Piece::Turn;
using TurnMap = Piece::TurnMap;

TurnMap::~TurnMap() {
	std::for_each(begin(), end(), [](Turn* t) {
		delete t;
	});
}

TurnMap::TurnMap(const TurnMap& t) : forward_list(t) {
}

TurnMap::TurnMap(const TurnMap&& t) : forward_list(std::move(t)) {
}

TurnMap& TurnMap::operator=(const TurnMap& t) {
	static_cast<forward_list<Turn*>&>(*this) = 
		forward_list<Turn*>(t);
	return *this;
}

TurnMap& TurnMap::operator=(TurnMap&& t) {
	static_cast<forward_list<Turn*>&>(*this) = std::move(t);
	return *this;
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
