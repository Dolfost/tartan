#include <dchess.hpp>

namespace dchess {
using Position = Piece::Position;
using TurnMap = Piece::TurnMap;

TurnMap Bishop::moveMap() const {
	TurnMap map;
	Position tpos, pos = p_position;
	Pawn* enemy_pawn;
	Piece* enemy;

	if (p_color == Piece::Color::Black) {
		pos.setOffsetMode(Position::Mode::Reverse);
		tpos.setOffsetMode(Position::Mode::Reverse);
	}

	using func = bool (Position::*)(void) const;
	std::tuple<func, func, std::pair<int, int>> conds[4] = {
		{&Position::atRight, &Position::atBottom, {1, -1}},
		{&Position::atRight, &Position::atTop, {1, 1}},
		{&Position::atLeft, &Position::atBottom, {-1, -1}},
		{&Position::atLeft, &Position::atTop, {-1, 1}},
	};

	for (auto& v: conds) {
		tpos = pos;
		while (!(tpos.*std::get<0>(v))() and !(tpos.*std::get<1>(v))()) {
			std::pair<int, int> of = std::get<2>(v);
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
