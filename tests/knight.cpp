#include "dchess.hpp"
#include "testutils.hpp"

#include <iostream>

int main(int argc, char** argv) {
	using namespace dchess;
	using namespace std;

	Chessboard cb;
	placeKings(cb);
	Piece* pawn = new Pawn("c3", Piece::Color::Black);
	Piece* bishop = new Pawn("e7", Piece::Color::Black);
	Piece* knight = new Knight("d5", Piece::Color::White);
	cb.insertPiece(pawn);
	cb.insertPiece(bishop);
	cb.insertPiece(knight);

	Piece::TurnMap movemap = cb.possibleMoves(knight);
	Piece::TurnMap targetmap = {
		new Knight::Turn{knight, "f4"},
		new Knight::Turn{knight, "e3"},
		new Knight::Turn{knight, "c3", pawn},
		new Knight::Turn{knight, "b4"},

		new Knight::Turn{knight, "f6"},
		new Knight::Turn{knight, "e7", bishop},
		new Knight::Turn{knight, "c7"},
		new Knight::Turn{knight, "b6"},
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
