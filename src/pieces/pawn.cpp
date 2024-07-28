#include "../include/dchess.hpp"

namespace dchess {
	using Position = Piece::Position;
	using MoveMapT = Piece::MoveMapT;

	MoveMapT Pawn::moveMap() const {
		MoveMapT map;
		Position npos = p_position;
		Pawn* enemy;

		// front piece
		npos += {0, 1};
		if (!p_chessboard[npos])
			map.push_front(npos);

		// start
		if (movesMade() == 0) {
			npos += {0, 1};
			if (!p_chessboard[npos])
				map.push_front(npos); 
			return map;
		}

		// en passant left enemy
		if (p_position.x() > 1) {
			npos += {-1, -1};
			enemy = dynamic_cast<Pawn*>(p_chessboard[npos]);
			if (enemy and 
					enemy->movesMade() == 1 and 
					enemy->position().y() ==  5)
				map.push_front(npos + Position(0, 1));
			return map;
		}

		npos = p_position;

		// en passant right enemy
		if (p_position.x() < 8) {
			npos += {1, 0};
			enemy = dynamic_cast<Pawn*>(p_chessboard[npos]);
			if (enemy and 
					enemy->movesMade() == 1 and 
					enemy->position().y() ==  5)
				map.push_front(npos + Position(0, 1));
			return map;
		}

		// defeat left/right pawn
		if (p_position.x() > 1) {
			npos = p_position + Position(-1, 1);
			if ((enemy = dynamic_cast<Pawn*>(p_chessboard[npos])))
				map.push_front(npos);
		}
		if (p_position.x() < 8) {
			npos = p_position + Position(1, 1);
			if ((enemy = dynamic_cast<Pawn*>(p_chessboard[npos])))
				map.push_front(npos);
		}
		
		return map;
	}
	
}
