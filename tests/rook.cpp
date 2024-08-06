#include "dchess.hpp"
#include "testutils.hpp"

#include <iostream>

int main(int argc, char** argv) {
	using namespace dchess;
	using namespace std;

	Chessboard cb;
	placeKings(cb);
	Piece* pawn1 = new Pawn("h4", Piece::Color::Black);
	Piece* pawn2 = new Pawn("d7", Piece::Color::Black);
	Piece* rook = new Rook("d4", Piece::Color::White);
	cb.insertPiece(pawn1);
	cb.insertPiece(pawn2);
	cb.insertPiece(rook);

	Piece::TurnMap movemap = cb.possibleMoves(rook);
	Piece::TurnMap targetmap = {
		new Rook::Turn{rook, "h4", pawn1},
		new Rook::Turn{rook, "g4"},
		new Rook::Turn{rook, "f4"},
		new Rook::Turn{rook, "e4"},
		new Rook::Turn{rook, "a4"},
		new Rook::Turn{rook, "b4"},
		new Rook::Turn{rook, "c4"},

		new Rook::Turn{rook, "d7", pawn2},
		new Rook::Turn{rook, "d6"},
		new Rook::Turn{rook, "d5"},
		new Rook::Turn{rook, "d1"},
		new Rook::Turn{rook, "d2"},
		new Rook::Turn{rook, "d3"},
	};

	cout << "expected:" << endl;
	for (auto x : targetmap)
		cout << *x << ' ';
	cout << endl << "got:" << endl;
	for (auto x : movemap)
		cout << *x << ' ';
	
	cout << endl << cb;

	return !(movemap == targetmap);
}
