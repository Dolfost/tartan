#include <tartan/chess.hpp>

namespace tt::chess {
using Position = Piece::Position;
using TurnMap = Piece::TurnMap;

TurnMap Pawn::moveMap(int) const {
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
	if (!p_board->at(tpos)) {
		map.push_front(new Turn{this, tpos});
		// two cell turn
		if (movesMade() == 0) {
			tpos = tpos(0, 1);
			if (!p_board->at(tpos)) {
				map.push_front(new Turn{this, tpos}); 
			}
		}
	}

	// en passant left enemy
	if (!pos.atLeft()) {
		tpos = pos(-1, 0);
		enemy_pawn = 
			dynamic_cast<Pawn*>(p_board->at(tpos));
		if (enemy_pawn and 
			enemy_pawn->p_color != p_color and
			enemy_pawn->movesMade() == 1 and
			enemy_pawn->turnIndex() == p_board->turnIndex())
			map.push_front(new Turn{this, tpos(0, 1), enemy_pawn});
	}

	// en passant right enemy
	if (!pos.atRight()) {
		tpos = pos(1, 0);
		enemy_pawn = 
			dynamic_cast<Pawn*>(p_board->at(tpos));
		if (enemy_pawn and 
			enemy_pawn->p_color != p_color and
			enemy_pawn->movesMade() == 1 and
			enemy_pawn->turnIndex() == p_board->turnIndex())
			map.push_front(new Turn{this, tpos(0, 1), enemy_pawn});
	}

	// defeat left/right pawn
	if (!pos.atLeft()) {
		tpos = pos(-1, 1);
		if ((enemy = p_board->at(tpos)) and enemy->color() != p_color)
			map.push_front(new Turn{this, tpos, enemy});
	}
	if (!pos.atRight()) {
		tpos = pos(1, 1);
		if ((enemy = p_board->at(tpos)) and enemy->color() != p_color) {
			map.push_front(new Turn{this, tpos, enemy});
		}
	}

	return map;
}

}
