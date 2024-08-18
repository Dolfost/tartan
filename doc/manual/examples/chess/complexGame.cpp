#include <tartan/chess.hpp>
#include "tartan/board/exceptions.hpp"

#include <iostream>
#include <string>

// clears the screen
void cls(void);

// recurses to print the explanatory of the exception it holds
void print_exception(const std::exception& e, int level =  0);

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
			std::cout << "Enter valid move: ____\b\b\b\b";
			std::cin.clear();
			std::cin >> turn;
		} while (not std::cin);

		try { // check if from is correct
			from = tt::Piece::Position(turn.substr(0, 2));
		} catch (std::exception& ex) {
			std::cout << "Error: 'from' position is invalid: " 
				<< ex.what() << "\n";
			continue;
		}

		try { // check if to is correct
			to = turn.substr(2, 2); // use of implicit converion
		} catch (std::exception& ex) {
			std::cout << "Error: 'to' position is invalid: " 
				<< ex.what() << "\n";
			continue;
		}

		try { // perform the turn
			board.makeTurn(from, to);
		} catch (tt::ex::tartan& ex) {
			std::cout << "Turn error:\n";
			print_exception(ex);
			continue;
		}

		cls(); // clear the screen
		std::cout << board; // and put board on it
	}

	// announce that game have finished
	std::cout << "\nGame finished!\n" << 
		(board.currentKing()->color() == tt::Piece::Color::White ?
		"White" : "Black") << " king is under checkmate.\n";

	return 0;
}

void cls(void) {
	for (int i = 0; i < 100; i++)
		std::cout.put('\n');
}

void print_exception(const std::exception& e, int level) {
	std::cerr << std::string(level, ' ') << 
		"exception: " << e.what() << '\n';
	try {
		std::rethrow_if_nested(e);
	} catch(const std::exception& e) {
		print_exception(e, level+1);
	} catch(...) {}
}
