#include "include/dchess.hpp"
#include <algorithm>

namespace dchess {
	using BoardT = Chessboard::BoardT;
	using MoveMapT = Piece::MoveMapT;
	using Position = Piece::Position;

	Chessboard::Chessboard() {
		std::for_each(b_board.begin(), b_board.end(), 
				[](BoardT& a){ a.fill(nullptr); });
	}

	bool Chessboard::placePiece(Piece* p) {
		b_board[p->position().x()-1][p->position().y()-1] = p;
		return true;
	}

	inline MoveMapT Chessboard::possibleMoves(const Piece::Position& p) const {
		return possibleMoves(operator[](p));
	};
	
	const Piece* Chessboard::operator[](const Position& p) const { 
		return b_board[p.x()-1][p.y()-1]; 
	}

	Piece* Chessboard::operator[](const Position& p) { 
		return b_board[p.x()-1][p.y()-1]; 
	}

	Chessboard::~Chessboard() {
		for (auto & p : b_board) {
			std::for_each(p.begin(), p.end(), [](Piece* p){ delete p; });
		}
	}

}
