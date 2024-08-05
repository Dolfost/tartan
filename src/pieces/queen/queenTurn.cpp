#include <dchess.hpp>
#include <dchess/exceptions.hpp>

namespace dchess {
using Turn = Queen::Turn;

bool Turn::isEqual(const Piece::Turn& rhs) const {
	const Queen::Turn* crhs = dynamic_cast<const Queen::Turn*>(&rhs);
	if (!crhs)
		return false;

	return Piece::Turn::isEqual(rhs);
}


}
