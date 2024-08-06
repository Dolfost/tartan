#include "dchess.hpp"

#include <iostream>
#include <stdexcept>

int main(int argc, char** argv) {
	using namespace std;
	using namespace dchess;

	Chessboard cb;
	cb.insertPiece(new Pawn("e7", Piece::Color::White));
	try {
		cb.makeTurn("e7", "e8");
	} catch (std::runtime_error& ex) {
		cout << ex.what();
		return 0;
	} catch (exception& ex) {
		cout << ex.what();
		return 1;
	}

	return 1;
}
