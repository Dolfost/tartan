#include <tartan/chess.hpp>

namespace tt::chess {
using Position = Piece::Position;
using TurnMap = Piece::TurnMap;

TurnMap Queen::moveMap(bool) const {
	TurnMap map, m;

	map = Piece::diagonalMoves(this);
	m = Piece::straightMoves(this); 
	map.insert(
		map.begin(), m.begin(), m.end()
	);
	m.clear();

	return map;
}

}
