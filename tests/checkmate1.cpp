#include "dchess.hpp"
#include "dchess/exceptions.hpp"

#include "testutils.hpp"

#include <iostream>

int main(int argc, char** argv) {
	using namespace dchess;
	using C = dchess::Piece::Color;
	using  Position = dchess::Piece::Position;
	using namespace std;

	Chessboard cb;

	Chessboard::PieceSetT set = {
		new Rook("a1", C::White), 
		new King("c1", C::White), 
		new Knight("g1", C::White), 
		new Rook("h1", C::White), 
		new Queen("f6", C::White), 
		new Bishop("g5", C::White), 
		new Pawn("e6", C::White), 

		new King("e7", C::Black),
		new Rook("d8", C::Black),
		new Queen("e8", C::Black),
		new Bishop("f8", C::Black),
		new Rook("h8", C::Black),
		new Pawn("a7", C::Black),
		new Pawn("c7", C::Black),
		new Pawn("d7", C::Black),
		new Pawn("f7", C::Black),
		new Pawn("h7", C::Black),
	};

	cb.fill(set);
	cb.setCurrentTurn(C::Black);
	
	std::list<std::pair<Position, Position>> turns = {
		{"c7", "c6"},
	};

	try {
		play(cb, turns, true);
	} catch (king_is_under_checkmate& ex) {
		cout << endl << "Checkmate: " << ex.what();
	} catch (exception& ex) {
		cout << endl << "Error: " << ex.what();
		return 1;
	}

	return 0;
}
