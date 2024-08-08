#include "dchess.hpp"
#include "dchess/exceptions.hpp"

#include "testutils.hpp"

#include <iostream>

int main(int argc, char** argv) {
	using namespace dchess;
	using C = dchess::Piece::Color;
	using Position = dchess::Piece::Position;
	using namespace std;

	Chessboard cb;

	cb.fill();
	
	std::list<std::pair<Position, Position>> turns = {
		{"e2", "e3"},
		{"e7", "e5"},
		{"e3", "e4"},
		{"e8", "e7"},
		{"d1", "g4"},
		{"d8", "e8"},
		{"d2", "d4"},
		{"e5", "d4"},
		{"f1", "c4"},
		{"b8", "c6"},
		{"h2", "h3"},
		{"c6", "d8"},
		{"g4", "e6"},
		{"f7", "e6"},
		{"c4", "e2"},
		{"a7", "a6"},
		{"a2", "a3"},
		{"g7", "g5"},
		{"a3", "a4"},
		{"g5", "g4"},
		{"a4", "a5"},
		{"g4", "g3"},
		{"c2", "c4"},
		{"a8", "b8"},
		{"c4", "c5"},
		{"b8", "a8"},
		{"e2", "h5"},
		{"a8", "b8"},
		{"c1", "g5"},
		{"g8", "f6"},
		{"e4", "e5"},
		{"b8", "a8"},
		{"g5", "f6"},
		{"a8", "b8"},
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
