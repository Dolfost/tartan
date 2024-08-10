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

	Chessboard target(
		"ra8 bc8 qd8 xe8 bf8 rh8 "
		"pa7 pb7 pc7 pd7 Qf7 pg7 ph7 "
		"kc6 kf6 "
		"pe5 "
		"pe4 Bc4 "
		"Pa2 Pb2 Pc2 Pd2 Pf2 Pg2 Ph2 "
		"Ra1 Kb1 Bc1 Xe1 Kg1 Rh1"
	);
	
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
		cout << endl << "OK: " << ex.what();
	} catch (exception& ex) {
		cout << endl << "Error: " << ex.what();
		return 1;
	}

	return target != cb;
}
