#include <tartan/chess.hpp>

#include "testutils.hpp"

#include <iostream>

int main(int argc, char** argv) {
	using namespace tt;
	using namespace tt::chess;
	using C = tt::Piece::Color;
	using Position = tt::Piece::Position;
	using namespace std;

	Chessboard cb;
	cb.setPieceGetter(getQueen);

	cb.fill();
	
	std::list<std::pair<Position, Position>> turns = {
		{"e2", "e4"},
		{"h7", "h6"},
		{"e4", "e5"},
		{"d7", "d5"},
		{"e5", "d6"},
		{"c7", "c5"},
		{"d2", "d4"},
		{"c5", "c4"},
		{"b2", "b4"},
		{"c4", "b3"},
		{"c2", "c3"},
		{"b3", "b2"},
		{"b1", "a3"},
		{"e7", "e5"},
		{"a3", "b5"},
		{"b2", "b1"},
		{"h2", "h3"},
		{"b1", "b2"},
		{"c1", "h6"},
		{"d8", "e7"},
		{"f1", "e2"},
		{"a7", "a6"},
		{"e2", "f1"},
	};

	Chessboard target;
	target.fill({
		"ra8", "kb8", "bc8", "xe8", "bf8", "kg8", "rh8",
		"pb7", "qe7", "pf7", "pg7",
		"pa6", "Pd6", "Bh6",
		"Kb5", "pe5",
		"Pd4",
		"Pc3", "Ph3",
		"Pa2", "qb2", "Pf2", "Pg2",
		"Ra1", "Qd1", "Xe1", "Bf1", "Kg1", "Rh1"
	});

	try {
		play(cb, turns, true);
	} catch (exception& ex) {
		cout << endl << "Error: " << ex.what();
		return 1;
	}

	cout << "target board:\n" << target;

	return target != cb;
}
