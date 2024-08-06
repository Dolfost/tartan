#include "dchess.hpp"
#include "testutils.hpp"

#include <vector>

int main(int argc, char** argv) {
	using namespace dchess;
	using  Position = dchess::Piece::Position;
	using namespace std;

	Chessboard cb;
	std::vector<Pawn*> black(8), white(8);
	for (int i = 0; i < 8; i++) {
		white[i] = new Pawn({i+1, 2}, Piece::Color::White);
		black[i] = new Pawn({i+1, 7}, Piece::Color::Black);
		cb.insertPiece(white[i]);
		cb.insertPiece(black[i]);
	}
	
	
	std::list<std::pair<Position, Position>> turns = {
		{{'c', 2}, {'c', 4}},
		{{'g', 7}, {'g', 6}},
		{{'c', 4}, {'c', 5}},
		{{'d', 7}, {'d', 5}},
		{{'c', 5}, {'d', 6}},
		{{'e', 7}, {'d', 6}},
		{{'g', 2}, {'g', 3}},
		{{'b', 7}, {'b', 6}},
		{{'g', 3}, {'g', 4}},
		{{'b', 6}, {'b', 5}},
		{{'g', 4}, {'g', 5}},
		{{'b', 5}, {'b', 4}},
		{{'a', 2}, {'a', 4}},
		{{'b', 4}, {'a', 3}},
	};

	play(cb, turns, false);

	return 0;
}
