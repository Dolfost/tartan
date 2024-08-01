#include "include/dchess.hpp"
#include "include/dchess/exceptions.hpp"

#include <algorithm>
#include <ostream>
#include <iostream>

namespace dchess {
using BoardT = Chessboard::BoardT;
using MoveMapT = Piece::MoveMapT;
using Position = Piece::Position;
using Turn = Piece::Turn;
using Color = Piece::Color;

Chessboard::Chessboard() {
	std::for_each(b_board.begin(), b_board.end(), 
							 [](BoardT& a){ a.fill(nullptr); });
}

void Chessboard::placePiece(Piece* p) {
	Piece*& dest = 
		b_board[p->position().x()-1][p->position().y()-1];
	if (dest)
		throw illegal_place("Two pieces can't be placed on same tile.");
	dest = p;
}

inline MoveMapT Chessboard::possibleMoves(const Position& p) const {
	return possibleMoves(operator[](p));
};

inline MoveMapT Chessboard::possibleMoves(const Piece* p) const {
	return p->moveMap();
};

const Turn Chessboard::makeTurn(const Position& from, const Position& to) {
	Piece* turnpiece = operator[](from);
	if (turnpiece->color() != b_currentTurnColor)
		throw illegal_move("Selected piece is in wrong color.");

	MoveMapT possible = possibleMoves(from);

	if (possible.empty())
		throw illegal_move("Selected piece can't move.");

	MoveMapT::iterator turn = find_if(
		possible.begin(), 
		possible.end(), 
		[&](Turn& v) { 
			return (v.from() == from and v.to() == to);
		}
	);

	if (turn == possible.end())
		throw illegal_move("Selected piece can't perform such move.");
						
	apply_turn(*turn);

	if (b_currentTurnColor == Color::White)
		b_currentTurnColor = Color::Black;
	else
		b_currentTurnColor = Color::White;

	return *turn;
}

void Chessboard::apply_turn(Turn& t) {
	b_history.push_back(t);
	
	if (t.capture()) {
		at(t.capture()->position()) = nullptr;
		b_capturedPieces.push_front(t.capture());
	}

	at(t.from()) = nullptr;
	at(t.to()) = t.piece();
	t.piece()->move(t.to());
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
				letter = 'k';
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
}

}
