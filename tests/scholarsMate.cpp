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
	
	std::list<std::pair<Position, Position>> turns = {
		{"e2", "e4"},
		{"e7", "e5"},
		{"d1", "h5"},
		{"b8", "c6"},
		{"f1", "c4"},
		{"g8", "f6"},
		{"h5", "f7"},
		{"a7", "a6"},
	};

	try {
		play(cb, turns, true);
	} catch (king_is_under_checkmate& ex) {
		cout << endl << "Checkmate: " << ex.what();
	} catch (exception& ex) {
		cout << endl << "Error: " << ex.what();
		return 1;
	}

	return 0;
}
