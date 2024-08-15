#include <tartan/chess.hpp>

namespace tt::chess {
using Position = Piece::Position;
using TurnMap = Piece::TurnMap;

TurnMap Rook::moveMap(int) const {
	return Piece::straightMoves(this);
}

}
