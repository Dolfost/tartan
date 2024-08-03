#include "dchess.hpp"
#include "testutils.hpp"

Chessboard::PieceTypesRetT getPiece(Chessboard::PieceTypesArgT t) {
	srand(time(NULL));
	int f = rand() % t.size();
	auto it = t.begin();
	for (int i = 0; i < f; i += 1)
		it++;
	return *it;
}

int main(int argc, char** argv) {
	using namespace dchess;
	using namespace std;

	Chessboard cb;
	cb.setPieceGetter(getPiece);
	std::vector<Pawn*> black(8), white(8);
	for (int i = 0; i < 8; i++) {
		white[i] = new Pawn({i+1, 6}, Piece::Color::White, cb);
		black[i] = new Pawn({i+1, 3}, Piece::Color::Black, cb);
	}

	interactive_play(cb);

	return 0;
}
