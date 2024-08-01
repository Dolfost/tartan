#include "dchess.hpp"

#include "testutils.hpp"

#include <iostream>

int main(int argc, char** argv) {
	using namespace dchess;
	using  Position = dchess::Piece::Position;
	using namespace std;

	Chessboard cb;
	Piece* pb = new Pawn({'d', 7}, Piece::Color::Black, cb);
	Piece* pw = new Pawn({'e', 2}, Piece::Color::White, cb);
	
	std::list<std::pair<Position, Position>> turns = {
		{{'e', 2}, {'e', 4}},
		{{'d', 7}, {'d', 6}},
		{{'e', 4}, {'e', 5}},
		{{'d', 6}, {'e', 5}},
	};
	
	play(cb, turns);

	return 0;
}
