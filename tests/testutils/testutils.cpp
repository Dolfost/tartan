#include "include/testutils.hpp"

#include <iostream>

using namespace std;

tt::chess::Chessboard::PieceTypesRetT getPiece(tt::chess::Chessboard::PieceTypesArgT types) {
	char piece; 
	type_index type = typeid(nullptr);

	do {
		cout << "Enter Piece for exchange: ";
		cin >> piece;
		piece = tolower(piece);
		switch (piece) {
			case 'p':
				type = typeid(tt::chess::Pawn);
				break;
			case 'k':
				type = typeid(tt::chess::Knight);
				break;
			case 'b':
				type = typeid(tt::chess::Bishop);
				break;
			case 'r':
				type = typeid(tt::chess::Rook);
				break;
			case 'q':
				type = typeid(tt::chess::Queen);
				break;
		}
	} while(type == typeid(nullptr));

	return type;
}

tt::chess::Chessboard::PieceTypesRetT getQueen(tt::chess::Chessboard::PieceTypesArgT) {
	return typeid(tt::chess::Queen);
}

void move(tt::chess::Chessboard& cb,
								 tt::Piece::Position from,
								 tt::Piece::Position to,
								 bool rethrow) {
		try {
			cb.makeTurn(from, to);
		} catch (logic_error& e) {
			if (rethrow)
				throw;
			cout << e.what() << endl;
		}
}

void play(tt::chess::Chessboard& cb, 
					tt::chess::Chessboard::TurnsT t, 
					bool rethrow) {
	int no = 1;
	cout << "Board:\n" << cb;
	for (auto& t : t) {
		cout << "\n" << "Turn №" << no++ << ": " 
			<< t.first << "->" << t.second << endl;
		try {
			move(cb, t.first, t.second, rethrow);
		} catch (std::exception& ex) {
				throw;
		}
		cout << cb << flush;
	}
}

void interactive_play(tt::chess::Chessboard& cb, bool rethrow) {
	cb.setPieceGetter(getPiece);

	string mv;
	tt::Piece::Position from, to;
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
			from = tt::Piece::Position(mv.substr(0, 2));
			to = tt::Piece::Position(mv.substr(2, 2));
		} catch (std::exception& ex) {
			if (rethrow)
				throw;
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

void placeKings(tt::chess::Chessboard& cb) {
	cb.insertPiece(new tt::chess::King("e1", tt::Piece::Color::White));
	cb.insertPiece(new tt::chess::King("e8", tt::Piece::Color::Black));
}

void print_exception(const std::exception& e, int level) {
	if (level == 0)
		std::cerr << std::endl;
	std::cerr << std::string(level, ' ') << "exception: " << e.what() << '\n';
	try {
		std::rethrow_if_nested(e);
	} catch(const std::exception& e) {
		print_exception(e, level+1);
	} catch(...) {}
}
