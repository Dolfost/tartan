#include "dchess.hpp"

#include <iostream>
#include <set>

int main(int argc, char** argv) {
	using namespace dchess;
	using namespace std;

	Chessboard cb;
	Piece* pawn1 = new Pawn({'c', 2}, Piece::Color::White, cb);
	Piece* pawn2 = new Pawn({'d', 3}, Piece::Color::Black, cb);

	Piece::MoveMapT movemap = pawn1->moveMap();
	set<Piece::Position> moveset = set<Piece::Position>(movemap.begin(), movemap.end());
	set<Piece::Position> targetset = {{'c', 3}, {'c', 4}, {'d', 3}};

	for (auto x : moveset) {
		cout << x << ' ';
	}
	
	cout << endl;

	return moveset == targetset;
}
