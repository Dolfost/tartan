#include "dchess.hpp"

#include <iostream>
#include <list>

int main(int argc, char** argv) {
	using Position = dchess::Piece::Position;
	using namespace std;

	std::list<bool> result = {
		Position('a', 2) == Position('a', 2),
		Position('f', 3) == Position('d', 4),
		Position(4, 3) == Position(3, 4),
		Position('h', 4) == Position('h', 4),
	};
	std::list<bool> target = {
		true,
		false,
		false,
		true
	};
		
	cout << "expected:\n";
	for (auto& b : target) {
		cout << b << ' ';
	}
	cout << "\ngot:\n";
	for (auto& b : result) {
		cout << b << ' ';
	}
	
	cout << endl;

	return !(target == result);
}
