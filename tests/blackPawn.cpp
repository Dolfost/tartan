#include "dchess.hpp"

#include <iostream>

int main(int argc, char** argv) {
	using namespace dchess;
	using namespace std;

	Chessboard cb;
	Piece* pawn1 = new Pawn({'d', 7}, Piece::Color::Black, cb);
	Piece* pawn2 = new Pawn({'c', 6}, Piece::Color::White, cb);
	Piece* pawn3 = new Pawn({'e', 6}, Piece::Color::White, cb);

	Piece::MoveMapT movemap = cb.possibleMoves({'d', 7});
	Piece::MoveMapT targetmap = {
		{pawn1, {'c', 6}, pawn2},
		{pawn1, {'e', 6}, pawn3},
		{pawn1, {'d', 5}},
		{pawn1, {'d', 6}},
	};;

	cout << "expected:" << endl;
	for (auto x : targetmap)
		cout << x << ' ';
	cout << endl << "got:" << endl;
	for (auto x : movemap)
		cout << x << ' ';
	
	cout << endl << cb;

	return !(movemap == targetmap);
}
