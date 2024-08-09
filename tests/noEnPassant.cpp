#include "dchess.hpp"
#include "dchess/exceptions.hpp"

#include "testutils.hpp"

#include <iostream>

int main(int argc, char** argv) {
	using namespace dchess;
	using  Position = dchess::Piece::Position;
	using namespace std;

	Chessboard cb;
	cb.fill();

	Piece* pawn = cb["c2"];
	
	std::list<std::pair<Position, Position>> turns = {
		{"d2", "d4"},
		{"e7", "e5"},
		{"d4", "d5"},
		{"e5", "d4"},
	};

	try {
		play(cb, turns, true);
	} catch (illegal_move& ex) {
		cout << "msg: " << ex.what();
		return 0;
	}


	return 1;
}
