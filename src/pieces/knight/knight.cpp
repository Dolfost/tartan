#include <dchess.hpp>

namespace dchess {
using Position = Piece::Position;
using TurnMap = Piece::TurnMap;

TurnMap Knight::moveMap(bool) const {
	TurnMap map;
	Position tpos, pos = p_position;
	Piece* enemy;

	if (p_color == Piece::Color::Black) {
		pos.setOffsetMode(Position::Mode::Reverse);
		tpos.setOffsetMode(Position::Mode::Reverse);
	}

	std::pair<int, int> ofs[8] = {
		{-2,  1}, {-1,  2}, {1,  2}, {2,  1},
		{-2, -1}, {-1, -2}, {1, -2}, {2, -1},
	};

	for (auto& of : ofs) {
		try {
			tpos = pos.offset(of.first, of.second);
		} catch (std::out_of_range& ex) {
			continue;
		}
		enemy = p_chessboard->at(tpos);
		map.push_front(new Turn(this, tpos, enemy));
	}

	return map;
}

}
