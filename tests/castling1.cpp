#include <tartan/chess.hpp>

#include <iostream>

int main(int argc, char** argv) {
	using namespace tt;
	using namespace tt::chess;
	using namespace std;

	Chessboard cb;
	Piece* wKing = new King("e1", Piece::Color::White);

	Piece* bKing = new King("e8", Piece::Color::Black);
	Piece* bRook1 = new Rook("a8", Piece::Color::Black);
	Piece* bRook2 = new Rook("h8", Piece::Color::Black);

	Piece* wRook = new Rook("d3", Piece::Color::White);

	cb.insertPiece(wKing);
	cb.insertPiece(bKing);
	cb.insertPiece(bRook1);
	cb.insertPiece(bRook2);
	cb.insertPiece(wRook);

	cb.setCurrentTurn(Piece::Color::Black);

	Piece::TurnMap movemap = cb.possibleMoves(bKing);
	Piece::TurnMap targetmap = {
		new King::Turn{bKing, "g8", nullptr, new Rook::Turn(bRook2, "f8")},
		// new King::Turn{bKing, "c8", nullptr, new Rook::Turn(bRook1, "d8"), false},

		new King::Turn{bKing, "e7"},
		new King::Turn{bKing, "f7"},
		new King::Turn{bKing, "f8"},
		new King::Turn{bKing, "d8", nullptr, nullptr, false},
		new King::Turn{bKing, "d7", nullptr, nullptr, false},
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
