#include <tartan/chess.hpp>
#include <tartan/version.hpp>
#include "testutils.hpp"

#include <iostream>
#include <vector>

int main(int argc, char** argv) {
	using namespace tt;
	using namespace tt::chess;
	using namespace std;
	
	cerr << "dchess v" 
		<< versionMajor() << '.' 
		<< versionMinor() << '.' 
		<< versionPatch() << '.' 
		<< versionTweak() << endl;

	Chessboard cb;
	cb.setPieceGetter(getPiece);

	std::vector<Piece*> pieces = {
		new Bishop("c1", Piece::Color::White),
		new Bishop("f1", Piece::Color::White),
		new Bishop("c8", Piece::Color::Black),
		new Bishop("f8", Piece::Color::Black),

		new Knight("b1", Piece::Color::White),
		new Knight("g1", Piece::Color::White),
		new Knight("b8", Piece::Color::Black),
		new Knight("g8", Piece::Color::Black),

		new Rook("a1", Piece::Color::White),
		new Rook("h1", Piece::Color::White),
		new Rook("a8", Piece::Color::Black),
		new Rook("h8", Piece::Color::Black),

		new Queen("d1", Piece::Color::White),
		new Queen("d8", Piece::Color::Black),

		new King("e1", Piece::Color::White),
		new King("e8", Piece::Color::Black),
	};
	std::vector<Piece*> black(8), white(8);
	for (int i = 0; i < 8; i++) {
		pieces.push_back(new Pawn({i+1, 2}, Piece::Color::White));
		pieces.push_back(new Pawn({i+1, 7}, Piece::Color::Black));
	}

	for (auto const& p : pieces)
		cb.insertPiece(p);

	interactive_play(cb);

	cout << "Turns:\n";
	for (auto& x : cb.history()) {
		cout << "\t{\"" << (*x).from() << "\", \"" << (*x).to() << "\"},\n";
	}
	

	return 0;
}
