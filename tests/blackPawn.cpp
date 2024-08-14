#include <tartan/chess.hpp>
#include <testutils.hpp>

#include <iostream>

int main(int argc, char** argv) {
	using namespace tt;
	using namespace tt::chess;
	using namespace std;

	Chessboard cb;
	placeKings(cb);
	Piece* pawn1 = new Pawn({'d', 7}, Piece::Color::Black);
	Piece* pawn2 = new Pawn({'c', 6}, Piece::Color::White);
	Piece* pawn3 = new Pawn({'e', 6}, Piece::Color::White);
	cb.insertPiece(pawn1);
	cb.insertPiece(pawn2);
	cb.insertPiece(pawn3);

	Piece::TurnMap movemap = cb.possibleMoves({'d', 7});
	Piece::TurnMap targetmap = {
		new Pawn::Turn{pawn1, {'c', 6}, pawn2},
		new Pawn::Turn{pawn1, {'e', 6}, pawn3},
		new Pawn::Turn{pawn1, {'d', 5}},
		new Pawn::Turn{pawn1, {'d', 6}},
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
