#include "dchess.hpp"
#include "testutils.hpp"

#include <iostream>
#include <stdexcept>

int main(int argc, char** argv) {
	using namespace std;
	using namespace dchess;

	Chessboard cb;
	placeKings(cb);
	cb.insertPiece(new Pawn("g6", Piece::Color::White));
	cb.insertPiece(new Pawn("b3", Piece::Color::Black));
	try {
		cb.makeTurn("g6", "g7");
		cb.makeTurn("b3", "b2");
		cb.makeTurn("g7", "g8");
	} catch (std::runtime_error& ex) {
		cout << ex.what() << std::endl << cb;
		return 0;
	} catch (exception& ex) {
		cout << ex.what() << std::endl << cb;
		return 1;
	}

	return 1;
}
