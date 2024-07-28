#include "../include/dchess.hpp"

#include<iostream>

namespace dchess {
	using Position = Piece::Position;
	using MoveMapT = Piece::MoveMapT;

	MoveMapT Pawn::moveMap() const {
		MoveMapT map;
		Position npos;
		Pawn* enemy_pawn;
		Piece* enemy;

		npos = p_position(0, 1);
		// front piece
		if (!p_chessboard[npos]) {
			map.push_front(npos);
			// two cell turn
			if (movesMade() == 0) {
				npos = npos(0, 1);
				if (!p_chessboard[npos]) {
					map.push_front(npos); 
				}
			}
		}

		// en passant left enemy
		if (p_position.x() > 1) {
			npos = p_position(-1, 0);
			enemy_pawn = 
				dynamic_cast<Pawn*>(p_chessboard[npos]);
			if (enemy_pawn and 
					enemy->movesMade() == 1 and 
					enemy->position().y() ==  5)
				map.push_front(npos(0, 1));
		}

		// en passant right enemy
		if (p_position.x() < 8) {
			npos = p_position(1, 0);
			enemy_pawn = 
				dynamic_cast<Pawn*>(p_chessboard[npos]);
			if (enemy_pawn and 
					enemy->movesMade() == 1 and 
					enemy->position().y() ==  5)
				map.push_front(npos(0, 1));
		}

		// defeat left/right pawn
		if (p_position.x() > 1) {
			npos = p_position(-1, 1);
			if ((enemy = p_chessboard[npos]))
				map.push_front(npos);
		}
		if (p_position.x() < 8) {
			npos = p_position(1, 1);
			if (p_chessboard[npos]) {
				map.push_front(npos);
			}
		}
		
		return map;
	}
	
}
