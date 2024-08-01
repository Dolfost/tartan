#include "dchess.hpp"

#include <iostream>

int main(int argc, char** argv) {
	using namespace dchess;
	using  Position = dchess::Piece::Position;
	using namespace std;

	Chessboard cb;
	std::vector<Pawn*> black(8), white(8);
	for (int i = 0; i < 8; i++) {
		white[i] = new Pawn({i+1, 2}, Piece::Color::White, cb);
		black[i] = new Pawn({i+1, 7}, Piece::Color::Black, cb);
	}
	
	
	std::list<std::pair<Position, Position>> turns = {
		{{'c', 2}, {'c', 4}},
		{{'g', 7}, {'g', 6}},
		{{'c', 4}, {'c', 5}},
		{{'d', 7}, {'d', 5}},
		{{'c', 5}, {'d', 6}},
	};

		cout << "start state:\n" << cb;

	int no = 1;
	for (auto& t : turns) {
		cout << "\nperforming turn " << no++ << ": " 
			<< t.first << "->" << t.second << endl;
		try {
			cb.makeTurn(t.first, t.second);
		} catch (logic_error& e) {
			cout << e.what() << endl;
			continue;
		}
		cout << cb << flush;
	}
	

	return 0;
}
