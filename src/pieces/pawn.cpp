#include "../include/dchess.hpp"

namespace dchess {
using Position = Piece::Position;
using MoveMapT = Piece::MoveMapT;

MoveMapT Pawn::moveMap() const {
	MoveMapT map;
	Position tpos, pos = p_position;
	Pawn* enemy_pawn;
	Piece* enemy;

	if (p_color == Piece::Color::Black) {
		pos.setOffsetMode(Position::Mode::Reverse);
		tpos.setOffsetMode(Position::Mode::Reverse);
	}

	tpos = pos(0, 1);
	// front piece
	if (!p_chessboard[tpos]) {
		map.push_front({this, tpos});
		// two cell turn
		if (movesMade() == 0) {
			tpos = tpos(0, 1);
			if (!p_chessboard[tpos]) {
				map.push_front({this, tpos}); 
			}
		}
	}

	// en passant left enemy
	if (p_position.x() > 1) {
		tpos = pos(-1, 0);
		enemy_pawn = 
			dynamic_cast<Pawn*>(p_chessboard[tpos]);
		if (enemy_pawn and 
			p_chessboard.history().back().piece() == enemy_pawn)
			map.push_front({this, tpos(0, 1), enemy_pawn});
	}

	// en passant right enemy
	if (p_position.x() < 8) {
		tpos = pos(1, 0);
		enemy_pawn = 
			dynamic_cast<Pawn*>(p_chessboard[tpos]);
		if (enemy_pawn and 
			p_chessboard.history().back().piece() == enemy_pawn)
			map.push_front({this, tpos(0, 1), enemy_pawn});
	}

	// defeat left/right pawn
	if (p_position.x() > 1) {
		tpos = pos(-1, 1);
		if ((enemy = p_chessboard[tpos]))
			map.push_front({this, tpos, enemy});
	}
	if (p_position.x() < 8) {
		tpos = pos(1, 1);
		if ((enemy = p_chessboard[tpos])) {
			map.push_front({this, tpos, enemy});
		}
	}

	return map;
}

}
