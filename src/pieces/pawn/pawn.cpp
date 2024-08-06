#include <dchess.hpp>
#include <iostream>

namespace dchess {
using Position = Piece::Position;
using TurnMap = Piece::TurnMap;

TurnMap Pawn::moveMap() const {
	TurnMap map;
	Position tpos, pos = p_position;
	Pawn* enemy_pawn;
	Piece* enemy;

	if (p_color == Piece::Color::Black) {
		pos.setOffsetMode(Position::Mode::Reverse);
		tpos.setOffsetMode(Position::Mode::Reverse);
	}

	tpos = pos(0, 1);
	// front piece
	if (!p_chessboard->at(tpos)) {
		map.push_front(new Turn{this, tpos});
		// two cell turn
		if (movesMade() == 0) {
			tpos = tpos(0, 1);
			if (!p_chessboard->at(tpos)) {
				map.push_front(new Turn{this, tpos}); 
			}
		}
	}

	// en passant left enemy
	if (!pos.atLeft()) {
		tpos = pos(-1, 0);
		enemy_pawn = 
			dynamic_cast<Pawn*>(p_chessboard->at(tpos));
		if (enemy_pawn and 
			enemy_pawn->enPassant())
			map.push_front(new Turn{this, tpos(0, 1), enemy_pawn});
	}

	// en passant right enemy
	if (!pos.atRight()) {
		tpos = pos(1, 0);
		enemy_pawn = 
			dynamic_cast<Pawn*>(p_chessboard->at(tpos));
		if (enemy_pawn and 
			enemy_pawn->enPassant())
			map.push_front(new Turn{this, tpos(0, 1), enemy_pawn});
	}

	// defeat left/right pawn
	if (!pos.atLeft()) {
		tpos = pos(-1, 1);
		if ((enemy = p_chessboard->at(tpos)))
			map.push_front(new Turn{this, tpos, enemy});
	}
	if (!pos.atRight()) {
		tpos = pos(1, 1);
		if ((enemy = p_chessboard->at(tpos))) {
			map.push_front(new Turn{this, tpos, enemy});
		}
	}

	return map;
}

Position Pawn::move(const Position& p) {
	if (movesMade() == 0 and std::abs(p.y()-p_position.y()) == 2)
		p_enPassant = true;
	else
		p_enPassant = false;
	return Piece::move(p);
}

}
