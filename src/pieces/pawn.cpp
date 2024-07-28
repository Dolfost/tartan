#include "../include/dchess.hpp"
#include <iostream>

namespace dchess {
	using Position = Piece::Position;
	using MoveMapT = Piece::MoveMapT;

	MoveMapT Pawn::moveMap() const {
		MoveMapT map;
		Position npos;
		Pawn* enemy;

		npos = p_position + Position(0, 1);
		std::cout << std::endl << "DADA" <<std::endl;
		// front piece
		if (!p_chessboard[npos]) {
			map.push_front(npos);
			// two cell turn
			if (movesMade() == 0) {
				npos += {0, 1};
				if (!p_chessboard[npos])
					map.push_front(npos); 
			}
		}

		// en passant left enemy
		if (p_position.x() > 1) {
			npos = p_position + Position(-1, 0);
			enemy = dynamic_cast<Pawn*>(p_chessboard[npos]);
			if (enemy and 
					enemy->movesMade() == 1 and 
					enemy->position().y() ==  5)
				map.push_front(npos + Position(0, 1));
		}

		// en passant right enemy
		if (p_position.x() < 8) {
			npos = p_position + Position(1, 0);
			enemy = dynamic_cast<Pawn*>(p_chessboard[npos]);
			if (enemy and 
					enemy->movesMade() == 1 and 
					enemy->position().y() ==  5)
				map.push_front(npos + Position(0, 1));
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
