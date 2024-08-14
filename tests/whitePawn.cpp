#include <tartan/chess.hpp>
#include <testutils.hpp>

#include <iostream>

int main(int argc, char** argv) {
	using namespace tt;
	using namespace tt::chess;
	using namespace std;

	Chessboard cb;
	Piece* pawn1 = new Pawn({'c', 2}, Piece::Color::White);
	Piece* pawn2 = new Pawn({'d', 3}, Piece::Color::Black);
	
	placeKings(cb);
	cb.insertPiece(pawn1);
	cb.insertPiece(pawn2);

	Piece::TurnMap movemap = cb.possibleMoves({'c', 2});
	Piece::TurnMap targetmap = {
		new Pawn::Turn{pawn1, {'d', 3}, pawn2},
		new Pawn::Turn{pawn1, {'c', 4}}, 
		new Pawn::Turn{pawn1, {'c', 3}},
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
