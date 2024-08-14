#include <tartan/chess.hpp>
#include <testutils.hpp>

#include <iostream>

int main(int argc, char** argv) {
	using namespace tt;
	using namespace tt::chess;
	using namespace std;

	Chessboard cb;
	placeKings(cb);
	Piece* pawn1 = new Pawn("h4", Piece::Color::Black);
	Piece* pawn2 = new Pawn("d7", Piece::Color::Black);
	Piece* pawn3 = new Pawn("g7", Piece::Color::Black);
	Piece* queen = new Queen("d4", Piece::Color::White);
	cb.insertPiece(pawn1);
	cb.insertPiece(pawn2);
	cb.insertPiece(pawn3);
	cb.insertPiece(queen);

	Piece::TurnMap movemap = cb.possibleMoves(queen);
	Piece::TurnMap targetmap = {
		new Queen::Turn{queen, "h4", pawn1},
		new Queen::Turn{queen, "g4"},
		new Queen::Turn{queen, "f4"},
		new Queen::Turn{queen, "e4"},
		new Queen::Turn{queen, "a4"},
		new Queen::Turn{queen, "b4"},
		new Queen::Turn{queen, "c4"},

		new Queen::Turn{queen, "d7", pawn2},
		new Queen::Turn{queen, "d6"},
		new Queen::Turn{queen, "d5"},
		new Queen::Turn{queen, "d1"},
		new Queen::Turn{queen, "d2"},
		new Queen::Turn{queen, "d3"},
		
		new Queen::Turn{queen, "a7"},
		new Queen::Turn{queen, "b6"},
		new Queen::Turn{queen, "c5"},

		new Queen::Turn{queen, "a1"},
		new Queen::Turn{queen, "b2"},
		new Queen::Turn{queen, "c3"},

		new Queen::Turn{queen, "g7", pawn3},
		new Queen::Turn{queen, "f6"},
		new Queen::Turn{queen, "e5"},

		new Queen::Turn{queen, "g1"},
		new Queen::Turn{queen, "f2"},
		new Queen::Turn{queen, "e3"},
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
