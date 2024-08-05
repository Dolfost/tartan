#include <dchess.hpp>

namespace dchess {
using Position = Piece::Position;
using TurnMap = Piece::TurnMap;

TurnMap Rook::moveMap() const {
	return Piece::straightMoves(this);
}

}
