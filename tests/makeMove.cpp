#include "dchess.hpp"

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
