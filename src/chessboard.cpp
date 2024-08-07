#include "dchess.hpp"
#include "dchess/exceptions.hpp"

#include <algorithm>
#include <ostream>
#include <iostream>
#include <sys/wait.h>

namespace dchess {
using BoardT = Chessboard::BoardT;
using TurnMap = Piece::TurnMap;
using Position = Piece::Position;
using Turn = Piece::Turn;
using Color = Piece::Color;

Chessboard::Chessboard() {
	std::for_each(b_board.begin(), b_board.end(), 
							 [](BoardT& row){ row.fill(nullptr); });
}

Piece* Chessboard::insertPiece(Piece* p) {
	if (p->chessboard())
		throw piece_belongs_to_board_already(p);

	King* king = dynamic_cast<King*>(p);
	if (king) {
		if (king->color() == Piece::Color::White) {
			if (!b_whiteKing) {
				b_whiteKing = king;
				b_currentKing = king;
			} else
				throw duplicate_king(p);
		} else if (king->color() == Piece::Color::Black) {
			if (!b_blackKing) {
				b_blackKing = king;
				b_currentEnemyKing = king;
			} else
				throw duplicate_king(p);
		}
	}
		
	Piece*& dest = 
		b_board[p->position().x()-1][p->position().y()-1];
	if (dest)
		throw position_is_taken(p);
	dest = p;

	p->setChessboard(this);
	return p;
}

inline TurnMap Chessboard::possibleMoves(const Position& p) const {
	return possibleMoves(operator[](p));
};

inline TurnMap Chessboard::possibleMoves(const Piece* p) const {
	Piece::TurnMap map = p->moveMap();
	markChecks(map);
	return map;
};

const Turn* Chessboard::makeTurn(const Position& from, const Position& to) {
	Piece* turnpiece = operator[](from);
	if (!turnpiece) 
		throw tile_is_empty(from, to);

	if (turnpiece->color() != b_currentTurnColor)
		throw piece_in_wrong_color(turnpiece, to);

	TurnMap possible = possibleMoves(from);

	if (possible.empty())
		throw can_not_move(turnpiece, to);

	TurnMap::iterator turn = find_if(
		possible.begin(), 
		possible.end(), 
		[&](Turn*& v) { 
			return (v->from() == from and v->to() == to);
		}
	);

	if (turn == possible.end())
		throw no_such_move(turnpiece, to);

	Turn* t = *turn; 

	if (!t->possible())
		throw king_is_under_check(t->piece(), t->to(), b_currentKing);

	b_history.push_back(t->clone());
	if (t->capture())
		b_capturedPieces.push_front(t->capture());

	t->apply();

	if (b_currentTurnColor == Color::White) {
		b_currentTurnColor = Color::Black;
	} else {
		b_currentTurnColor = Color::White;
	}

	std::swap(b_currentKing, b_currentEnemyKing);

	return b_history.back();
}

void Chessboard::markChecks(TurnMap& tm) const {
	if (!b_currentKing)
		throw no_king(b_currentTurnColor);

	for (auto& t : tm) {
		(*t).apply(true);
		(*t).setPossible(!b_currentKing->check());
		(*t).undo();
	}
}

Color Chessboard::setCurrentTurn(Color c) {
	Color ret = b_currentTurnColor;

	b_currentTurnColor = c;

	if (b_currentTurnColor == Color::White) {
		b_currentKing = b_whiteKing;
		b_currentEnemyKing = b_blackKing;
	} else { 
		b_currentKing = b_blackKing;
		b_currentEnemyKing = b_whiteKing;
	}

	return ret;
}

Chessboard::PieceTypesRetT Chessboard::getPieceType(
	Chessboard::PieceTypesArgT types) {
	if (!b_pieceGetter)
		throw std::runtime_error("Piece getter is not set.");

	if (types.size() == 0)
		return typeid(nullptr);

	return b_pieceGetter(types);
}


const Piece* Chessboard::operator[](const Position& p) const { 
	return b_board[p.x()-1][p.y()-1]; 
}

Piece*& Chessboard::operator[](const Position& p) { 
	return b_board[p.x()-1][p.y()-1]; 
}

Piece*& Chessboard::at(const Position& p) {
	return operator[](p);
}

const Piece* Chessboard::at(const Position& p) const {
	return operator[](p);
}

std::ostream& operator<<(std::ostream& os, const Chessboard& cb) {
	static const char* line = 
		"──────────────────────";
	static const char* letters = 
		"   a  b  c  d  e  f  g  h\n";
	os << letters << "  ┌" << line << "┐\n";
	for (int j = 8; j >= 1; j--) {
		os << j << " │";
		for (int i = 1; i <= 8; i++) {
			const Piece* p = cb[{i, j}];

			char letter;
			if (dynamic_cast<const Pawn*>(p))
				letter = 'p';
			else if (dynamic_cast<const Knight*>(p))
				letter = 'k';
			else if (dynamic_cast<const Bishop*>(p))
				letter = 'b';
			else if (dynamic_cast<const Rook*>(p))
				letter = 'r';
			else if (dynamic_cast<const Queen*>(p))
				letter = 'q';
			else if (dynamic_cast<const King*>(p))
				letter = 'x';
			else 
				letter = ((i + j)%2 ? '+' : '#');

			if (p != nullptr and p->color() == Color::White)
				letter = toupper(letter);

			os << letter << "  ";
		}
		os << "\b\b│ " << j << '\n';
	}
	os << "  └" << line << "┘\n" << letters;
	return os;
}

Chessboard::~Chessboard() {
	for (auto & p : b_board) {
		std::for_each(p.begin(), p.end(), [](Piece* p){ delete p; });
	}
	for (auto& p : b_capturedPieces) {
		delete p;
	}
	
}

}
