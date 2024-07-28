#include "dchess.hpp"

#include <iostream>

int main(int argc, char** argv) {
	using namespace dchess;
	using namespace std;

	Chessboard cb;
	Piece* pawn1 = new Pawn({'c', 2}, Piece::Color::White, cb);
	Piece* pawn2 = new Pawn({'d', 3}, Piece::Color::Black, cb);

	Piece::MoveMapT movemap = pawn1->moveMap();
	Piece::MoveMapT targetmap = {{'d', 3}, {'c', 4}, {'c', 3}};;

	cout << "expected:" << endl;
	for (auto x : targetmap)
		cout << x << ' ';
	cout << endl << "got:" << endl;
	for (auto x : movemap)
		cout << x << ' ';
	
	cout << endl << cb << endl;

	return movemap == targetmap;
}
