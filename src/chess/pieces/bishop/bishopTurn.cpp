#include <tartan/chess.hpp>
#include <tartan/board/exceptions.hpp>

namespace tt::chess {
using Turn = Bishop::Turn;

bool Turn::isEqual(const Piece::Turn& rhs) const {
	const Bishop::Turn* crhs = dynamic_cast<const Bishop::Turn*>(&rhs);
	if (!crhs)
		return false;

	return Piece::Turn::isEqual(rhs);
}


}
