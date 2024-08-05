#include <dchess.hpp>

namespace dchess {
using Position = Piece::Position;
using TurnMap = Piece::TurnMap;

TurnMap Bishop::moveMap() const {
	return Piece::diagonalMoves(this);
}

}
