#include <dchess.hpp>

namespace dchess {
using Position = Piece::Position;
using TurnMap = Piece::TurnMap;

TurnMap Rook::moveMap() const {
	TurnMap map;
	Position tpos, pos = p_position;
	Piece* enemy;

	if (p_color == Piece::Color::Black) {
		pos.setOffsetMode(Position::Mode::Reverse);
		tpos.setOffsetMode(Position::Mode::Reverse);
	}

	using func = bool (Position::*)(void) const;
	std::tuple<func, std::pair<int, int>> conds[4] = {
		{&Position::atBottom, {0, -1}},
		{&Position::atTop, {0, 1}},
		{&Position::atLeft, {-1, 0}},
		{&Position::atRight, {1, 0}},
	};

	for (auto& v: conds) {
		tpos = pos;
		while (!(tpos.*std::get<0>(v))()) {
			std::pair<int, int> of = std::get<1>(v);
			tpos = tpos.offset(of.first, of.second);
			enemy = p_chessboard->at(tpos);
			if (enemy) {
				map.push_front(new Turn(this, tpos, enemy));
				break;
			}
			map.push_front(new Turn(this, tpos));
		}
	}
	
	return map;
}

}
