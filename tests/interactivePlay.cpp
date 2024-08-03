#include "dchess.hpp"
#include "dchess/version.hpp"
#include "testutils.hpp"

#include <iostream>

int main(int argc, char** argv) {
	using namespace dchess;
	using namespace std;
	
	cerr << "dchess v" 
		<< versionMajor() << ' ' 
		<< versionMinor() << ' ' 
		<< versionPatch() << ' ' 
		<< versionTweak() << endl;

	Chessboard cb;
	cb.setPieceGetter(getPiece);
	std::vector<Pawn*> black(8), white(8);
	for (int i = 0; i < 8; i++) {
		white[i] = new Pawn({i+1, 2}, Piece::Color::White);
		black[i] = new Pawn({i+1, 7}, Piece::Color::Black);
		cb.insertPiece(white[i]);
		cb.insertPiece(black[i]);
	}

	interactive_play(cb);

	return 0;
}
