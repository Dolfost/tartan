#include "dchess.hpp"

#include <iostream>

int main(int argc, char** argv) {
	using namespace std;
	using namespace dchess;

	Chessboard cb;
	cb.insertPiece(new Pawn("e7", Piece::Color::White));
	try {
		cb.makeTurn("e7", "e8");
	} catch (logic_error& ex) {
		cout << ex.what();
		return 0;
	} catch (exception& ex) {
		return 1;
	}

	return 1;
}
