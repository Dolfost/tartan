#include "dchess.hpp"
#include "testutils.hpp"

#include <iostream>

int main(int argc, char** argv) {
	using namespace dchess;
	using namespace std;

	Chessboard cb;
	placeKings(cb);
	Piece* pawn1 = new Pawn("d8", Piece::Color::Black);
	Piece* pawn2 = new Pawn("g7", Piece::Color::Black);
	Piece* bishop = new Bishop("d4", Piece::Color::White);
	cb.insertPiece(pawn1);
	cb.insertPiece(pawn2);
	cb.insertPiece(bishop);

	Piece::TurnMap movemap = cb.possibleMoves(bishop);
	Piece::TurnMap targetmap = {
		new Bishop::Turn{bishop, "a7"},
		new Bishop::Turn{bishop, "b6"},
		new Bishop::Turn{bishop, "c5"},

		new Bishop::Turn{bishop, "a1"},
		new Bishop::Turn{bishop, "b2"},
		new Bishop::Turn{bishop, "c3"},

		new Bishop::Turn{bishop, "g7", pawn2},
		new Bishop::Turn{bishop, "f6"},
		new Bishop::Turn{bishop, "e5"},

		new Bishop::Turn{bishop, "g1"},
		new Bishop::Turn{bishop, "f2"},
		new Bishop::Turn{bishop, "e3"},
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
