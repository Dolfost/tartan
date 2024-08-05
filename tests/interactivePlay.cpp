#include "dchess.hpp"
#include "dchess/version.hpp"
#include "testutils.hpp"

#include <iostream>

int main(int argc, char** argv) {
	using namespace dchess;
	using namespace std;
	
	cerr << "dchess v" 
		<< versionMajor() << '.' 
		<< versionMinor() << '.' 
		<< versionPatch() << '.' 
		<< versionTweak() << endl;

	Chessboard cb;
	cb.setPieceGetter(getPiece);
	std::vector<Pawn*> black(8), white(8);
	for (int i = 0; i < 8; i++) {
		white[i] = new Pawn({i+1, 2}, Piece::Color::White, &cb);
		black[i] = new Pawn({i+1, 7}, Piece::Color::Black, &cb);
	}
	new Bishop("c1", Piece::Color::White, &cb);
	new Bishop("f1", Piece::Color::White, &cb);
	new Bishop("c8", Piece::Color::Black, &cb);
	new Bishop("f8", Piece::Color::Black, &cb);

	new Knight("b1", Piece::Color::White, &cb);
	new Knight("g1", Piece::Color::White, &cb);
	new Knight("b8", Piece::Color::Black, &cb);
	new Knight("g8", Piece::Color::Black, &cb);

	new Rook("a1", Piece::Color::White, &cb);
	new Rook("h1", Piece::Color::White, &cb);
	new Rook("a8", Piece::Color::Black, &cb);
	new Rook("h8", Piece::Color::Black, &cb);

	new Queen("d1", Piece::Color::White, &cb);
	new Queen("d8", Piece::Color::Black, &cb);

	interactive_play(cb);

	return 0;
}
