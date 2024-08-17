#include <tartan/chess.hpp>
#include <tartan/board/exceptions.hpp>

#include "testutils.hpp"

#include <iostream>

int main(int argc, char** argv) {
	using namespace tt;
	using namespace tt::chess;
	using  Position = tt::Piece::Position;
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


	Chessboard target;
	target.fill(
		"ra8 kb8 bc8 qd8 xe8 bf8 kg8 rh8 "
		"pa7 pb7 pc7 pd7 pf7 pg7 ph7 "
		"Pd5 pe5 "
		"Pa2 Pb2 Pc2 Pe2 Pf2 Pg2 Ph2 "
		"Ra1 Kb1 Bc1 Qd1 Xe1 Bf1 Kg1 Rh1 "
	);


	try {
		play(cb, turns, true);
	} catch (tt::ex::illegal_move& ex) {
		std::cerr << "OK ";
		print_exception(ex);
	}

	cout << "target board: \n" << target;

	return cb != target;
}
