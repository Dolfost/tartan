#ifndef _DCHESS_TEST_UTILS_HPP_
#define _DCHESS_TEST_UTILS_HPP_

#include "dchess.hpp"
using namespace dchess;

#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
using namespace std;

inline void move(Chessboard& cb,
								 Piece::Position from,
								 Piece::Position to,
								 bool rethrow = false) {
		try {
			cb.makeTurn(from, to);
		} catch (logic_error& e) {
			if (rethrow)
				throw e;
			cout << e.what() << endl;
		}
}

inline void play(Chessboard& cb, 
					Chessboard::TurnsT t, 
					bool rethrow = false) {
	int no = 1;
	cout << "Board:\n" << cb;
	for (auto& t : t) {
		cout << "\n" << "Turn №" << no++ << ": " 
			<< t.first << "->" << t.second << endl;
		try {
			move(cb, t.first, t.second, rethrow);
		} catch (std::exception& ex) {
			throw ex;
		}
		cout << cb << flush;
	}
}

inline void interactive_play(Chessboard& cb, bool rethrow = false) {
	string mv;
	Piece::Position from, to;
	int no = 0;
	cout << "Board:\n" << cb;
	while (cout << "Enter move: " and cin >> mv) {
		if (mv == "q")
			return;
		if (mv == "b") {
			cout << cb << flush;
			continue;
		}
		try {
			from = Piece::Position(mv.substr(0, 2));
			to = Piece::Position(mv.substr(2, 2));
		} catch (std::exception& ex) {
			if (rethrow)
				throw ex;
			cerr << "Error: " << ex.what() << endl;
			continue;
		}
		cout << "Turn №" << ++no << ": " 
			<< from << "->" << to << endl;
		move(cb, from, to, rethrow);
		cout << cb << flush;
	}
	cin.clear();
}

#endif // !_DCHESS_TEST_UTILS_HPP_
