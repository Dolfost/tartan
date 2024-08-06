#include <dchess.hpp>
#include <dchess/exceptions.hpp>

namespace dchess {
using Turn = King::Turn;

bool Turn::isEqual(const Piece::Turn& rhs) const {
	const King::Turn* crhs = dynamic_cast<const King::Turn*>(&rhs);
	if (!crhs)
		return false;

	return Piece::Turn::isEqual(rhs);
}


}
