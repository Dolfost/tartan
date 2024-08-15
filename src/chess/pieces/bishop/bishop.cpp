#include <tartan/chess.hpp>

namespace tt::chess {
using Position = Piece::Position;
using TurnMap = Piece::TurnMap;

TurnMap Bishop::moveMap(int) const {
	return Piece::diagonalMoves(this);
}

}
