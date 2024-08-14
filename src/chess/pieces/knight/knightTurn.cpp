#include <tartan/chess.hpp>
#include <tartan/board/exceptions.hpp>

namespace tt::chess {
using Turn = Knight::Turn;

bool Turn::isEqual(const Piece::Turn& rhs) const {
	const Knight::Turn* crhs = dynamic_cast<const Knight::Turn*>(&rhs);
	if (!crhs)
		return false;

	return Piece::Turn::isEqual(rhs);
}


}
