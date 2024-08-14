#include <tartan/chess.hpp>

#include <iostream>

int main(int argc, char** argv) {
	using namespace tt;
	using namespace tt::chess;
	using namespace std;

	Chessboard cb;
	Piece* bKing = new King("g7", Piece::Color::Black);
	Piece* wKing = new King("c1", Piece::Color::White);

	Piece* rook = new Rook("c7", Piece::Color::Black);
	Piece* knight = new Knight("d4", Piece::Color::Black);
	Piece* pawn = new Pawn("c3", Piece::Color::White);
	cb.insertPiece(wKing);
	cb.insertPiece(bKing);

	cb.insertPiece(knight);
	cb.insertPiece(pawn);
	cb.insertPiece(rook);

	Piece::TurnMap movemap = cb.possibleMoves(pawn);
	Piece::TurnMap targetmap = {
		new Pawn::Turn{pawn, "d4", knight, false},
		new Pawn::Turn{pawn, "c5"},
		new Pawn::Turn{pawn, "c4"},
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
