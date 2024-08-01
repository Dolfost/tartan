#ifndef _DCHESS_TEST_UTILS_HPP_
#define _DCHESS_TEST_UTILS_HPP_

#include "dchess.hpp"
using namespace dchess;

#include <iostream>
using namespace std;

inline void play(Chessboard& cb, 
					Chessboard::TurnsT t, 
					bool rethrow = false) {
	int no = 1;
	cout << "Board:\n" << cb;
	for (auto& t : t) {
		cout << "\n" << "Turn №" << no++ << ": " 
			<< t.first << "->" << t.second << endl;
		try {
			cb.makeTurn(t.first, t.second);
		} catch (logic_error& e) {
			if (rethrow)
				throw e;
			cout << e.what() << endl;
			continue;
		}
		cout << cb << flush;
	}
}

#endif // !_DCHESS_TEST_UTILS_HPP_
