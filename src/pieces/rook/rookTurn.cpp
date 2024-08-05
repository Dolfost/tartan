#include <dchess.hpp>
#include <dchess/exceptions.hpp>

namespace dchess {
using Turn = Rook::Turn;

bool Turn::isEqual(const Piece::Turn& rhs) const {
	const Rook::Turn* crhs = dynamic_cast<const Rook::Turn*>(&rhs);
	if (!crhs)
		return false;

	return Piece::Turn::isEqual(rhs);
}


}
