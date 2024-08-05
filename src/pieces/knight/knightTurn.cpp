#include <dchess.hpp>
#include <dchess/exceptions.hpp>

namespace dchess {
using Turn = Knight::Turn;

bool Turn::isEqual(const Piece::Turn& rhs) const {
	const Knight::Turn* crhs = dynamic_cast<const Knight::Turn*>(&rhs);
	if (!crhs)
		return false;

	return Piece::Turn::isEqual(rhs);
}


}
