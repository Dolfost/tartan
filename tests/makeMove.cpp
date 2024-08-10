#include "dchess.hpp"

#include "testutils.hpp"
#include <iostream>
#include <exception>

int main(int argc, char** argv) {
	using namespace dchess;
	using  Position = dchess::Piece::Position;
	using namespace std;


	Chessboard cb;
	placeKings(cb);

	Piece* pb = new Pawn({'d', 7}, Piece::Color::Black);
	Piece* pw = new Pawn({'e', 2}, Piece::Color::White);
	cb.insertPiece(pb);
	cb.insertPiece(pw);

	Chessboard target(
		"xe8 pe5 Xe1"
	);

	std::list<std::pair<Position, Position>> turns = {
		{{'e', 2}, {'e', 4}},
		{{'d', 7}, {'d', 6}},
		{{'e', 4}, {'e', 5}},
		{{'d', 6}, {'e', 5}},
	};
	
	try {
		play(cb, turns, true);
	} catch (exception& ex) {
		cerr << "ERROR: " << ex.what();
	}

	return target != cb;
}
