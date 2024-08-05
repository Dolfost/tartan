#include <dchess.hpp>

namespace dchess {
using Position = Piece::Position;
using TurnMap = Piece::TurnMap;

TurnMap Queen::moveMap() const {
	TurnMap map, m;

	map = Piece::diagonalMoves(this);
	m = Piece::straightMoves(this); 
	map.insert_after(map.begin(), m.begin(), m.end());
	m.clear();

	return map;
}

}
