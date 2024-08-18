#include <tartan/chess.hpp>
#include "tartan/board/exceptions.hpp"

#include <iostream>
#include <string>

int main() {
	// create Board object
	tt::chess::Chessboard board;
	// fill board with default piece set
	board.fill();

	std::string turn;
	tt::Piece::Position from, to;

	// print chessboard to screen
	std::cout << board;

	while (not board.currentKing()->checkmate()) {
		do { // parse for turn
			std::cout << "Enter valid move: ";
			std::cin.clear();
			std::cin >> turn;
		} while (not std::cin);

		try { // check if Positions are correct
			from = tt::Piece::Position(turn.substr(0, 2));
			to = turn.substr(2, 2); // use of implicit converion
		} catch (std::exception& ex) {
			std::cout << "Error: position is invalid: " 
				<< ex.what() << "\n";
			continue;
		}
		try { // perform the turn
			board.makeTurn(from, to);
		} catch (tt::ex::tartan& ex) {
			std::cout << "Turn error:\n";
			continue;
		}

		std::cout << board;
	}

	std::cout << "\nGame finished!\n";

	return 0;
}
