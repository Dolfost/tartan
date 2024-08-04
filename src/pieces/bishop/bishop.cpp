#include <dchess.hpp>
#include <iostream>

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


	tpos = pos;
	while (!tpos.atRight() and !tpos.atBottom()) {
		tpos = tpos.offset(1, -1);
		enemy = p_chessboard->at(tpos);
		if (enemy) {
			map.push_front(new Turn(this, tpos, enemy));
			break;
		}
		map.push_front(new Turn(this, tpos));
	}

	tpos = pos;
	while (!tpos.atRight() and !tpos.atTop()) {
		tpos = tpos.offset(1, 1);
		enemy = p_chessboard->at(tpos);
		if (enemy) {
			map.push_front(new Turn(this, tpos, enemy));
			break;
		}
		map.push_front(new Turn(this, tpos));
	}

	tpos = pos;
	while (!tpos.atLeft() and !tpos.atBottom()) {
		tpos = tpos.offset(-1, -1);
		enemy = p_chessboard->at(tpos);
		if (enemy) {
			map.push_front(new Turn(this, tpos, enemy));
			break;
		}
		map.push_front(new Turn(this, tpos));
	}

	tpos = pos;
	while (!tpos.atLeft() and !tpos.atTop()) {
		tpos = tpos.offset(-1, 1);
		enemy = p_chessboard->at(tpos);
		if (enemy) {
			map.push_front(new Turn(this, tpos, enemy));
			break;
		}
		map.push_front(new Turn(this, tpos));
	}
	

	return map;
}

}
