#include <tartan/chess.hpp>
#include <tartan/chess/exceptions.hpp>

#include "testutils.hpp"

#include <iostream>

int main(int argc, char** argv) {
	using namespace tt;
	using namespace tt::chess;
	using C = tt::Piece::Color;
	using  Position = tt::Piece::Position;
	using namespace std;

	Chessboard cb;

	string init = 
		"Ra1 Xc1 Kg1 Rh1 Qf6 Bg5 Pe5 "
		"xe7 rd8 qe8 bf8 rh8 pa7 pc7 pd7 pf7 ph7";

	cb.fill(init);
	cb.setCurrentTurn(C::Black);

	Chessboard target;
	target.fill(init);
	
	std::list<std::pair<Position, Position>> turns = {
		{"c7", "c6"},
	};

	try {
		play(cb, turns, true);
	} catch (tt::chess::ex::checkmate& ex) {
		cout << endl << "OK: " << ex.what();
	} catch (exception& ex) {
		cout << endl << "Error: " << ex.what();
	}

	cout << "target: \n" << target;

	return target != cb;
}
