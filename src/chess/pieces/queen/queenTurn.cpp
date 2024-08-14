#include <tartan/chess.hpp>
#include <tartan/board/exceptions.hpp>

namespace tt::chess {
using Turn = Queen::Turn;

bool Turn::isEqual(const Piece::Turn& rhs) const {
	const Queen::Turn* crhs = dynamic_cast<const Queen::Turn*>(&rhs);
	if (!crhs)
		return false;

	return Piece::Turn::isEqual(rhs);
}


}
