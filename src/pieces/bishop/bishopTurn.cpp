#include <dchess.hpp>
#include <dchess/exceptions.hpp>

namespace dchess {
using Turn = Bishop::Turn;

bool Turn::isEqual(const Piece::Turn& rhs) const {
	const Bishop::Turn* crhs = dynamic_cast<const Bishop::Turn*>(&rhs);
	if (!crhs)
		return false;

	return Piece::Turn::isEqual(rhs);
}


}
