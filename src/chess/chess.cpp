#include <iostream>
#include <tartan/chess.hpp>
#include <tartan/chess/exceptions.hpp>

#include <sstream>
#include <cctype>

namespace tt::chess {
using TurnMap = Piece::TurnMap;
using Position = Piece::Position;
using Turn = Piece::Turn;
using Color = Piece::Color;

Piece* Chessboard::piece(const std::string& spec) const {
	if (spec.size() > 3)
		throw tt::ex::bad_piece_spec(spec, "Specification is too long");
	if (spec.size() < 3)
		throw tt::ex::bad_piece_spec(spec, "Specification is too short");

	char p = spec[0];
	Piece::Color color;
	if (!isalpha(p))
		throw tt::ex::bad_piece_spec(spec, "Specified piece type is unknown");

	if (isupper(p))
		color = Piece::Color::White;
	else
		color = Piece::Color::Black;

	Position position;
	try {
		position = spec.substr(1, 2);
	} catch (std::out_of_range& ex) {
		std::throw_with_nested(tt::ex::bad_piece_spec(
			spec, "Specified position is out of range"
		));
	}
	
	Piece* newPiece;
	switch (tolower(p)) {
		case 'p': {
			newPiece = new Pawn;
			break;
		}
		case 'b': {
			newPiece = new Bishop;
			break;
		}
		case 'k': {
			newPiece = new Knight;
			break;
		}
		case 'r': {
			newPiece = new Rook;
			break;
		}
		case 'q': {
			newPiece = new Queen;
			break;
		}
		case 'x': {
			newPiece = new King;
			break;
		}
		default:
			throw tt::ex::bad_piece_spec(spec, "Specified piece type is unknown");
	}

	newPiece->setColor(color);
	newPiece->setPosition(position);

	return newPiece;
}

Piece* Chessboard::insertPiece(Piece* p) {
	King* king = dynamic_cast<King*>(p);
	if (king) {
		if (king->color() == Piece::Color::White) {
			if (!c_whiteKing) {
				c_whiteKing = king;
				c_currentKing = king;
			} else
				throw ex::duplicate_king(p);
		} else if (king->color() == Piece::Color::Black) {
			if (!c_blackKing) {
				c_blackKing = king;
				c_currentEnemyKing = king;
			} else
				throw ex::duplicate_king(p);
		}
	}
		
	return Board::insertPiece(p);
}

Piece::TurnMap Chessboard::possibleMoves(const Piece* p) const {
	TurnMap map = Board::possibleMoves(p);
	markChecks(map);
	return map;
}

const Turn* Chessboard::makeTurn(const Position& from, const Position& to) {
	Turn* selected;
	TurnMap map = Board::produceTurn(from, to, &selected);

	if (c_currentKing->checkmate())
		throw ex::king_is_under_checkmate(selected->piece(), selected->to(), c_currentKing);

	if (!selected->possible())
		throw ex::king_is_under_check(selected->piece(), selected->to(), c_currentKing);

	return applyTurn(selected);
}

void Chessboard::markChecks(TurnMap& tm) const {
	if (!c_currentKing)
		throw ex::no_king(b_currentTurnColor);

	for (auto& t : tm) {
		(*t).apply(true);
		(*t).setPossible(!c_currentKing->check());
		(*t).undo();
	}
}

Piece::Color Chessboard::setCurrentTurn(Piece::Color c) {
	Piece::Color ret = Board::setCurrentTurn(c);

	if (b_currentTurnColor == Color::White) {
		c_currentKing = c_whiteKing;
		c_currentEnemyKing = c_blackKing;
	} else { 
		c_currentKing = c_blackKing;
		c_currentEnemyKing = c_whiteKing;
	}

	return ret;
}

void Chessboard::clear() {
	Board::clear();
	c_currentKing = nullptr;
	c_currentEnemyKing = nullptr;
	c_blackKing = nullptr;
	c_whiteKing = nullptr;
}

Board::PieceSetT Chessboard::defaultPieceSet() const {
	PieceSetT pieces = {
		new Bishop("c1", Piece::Color::White),
		new Bishop("f1", Piece::Color::White),
		new Bishop("c8", Piece::Color::Black),
		new Bishop("f8", Piece::Color::Black),

		new Knight("b1", Piece::Color::White),
		new Knight("g1", Piece::Color::White),
		new Knight("b8", Piece::Color::Black),
		new Knight("g8", Piece::Color::Black),

		new Rook("a1", Piece::Color::White),
		new Rook("h1", Piece::Color::White),
		new Rook("a8", Piece::Color::Black),
		new Rook("h8", Piece::Color::Black),

		new Queen("d1", Piece::Color::White),
		new Queen("d8", Piece::Color::Black),

		new King("e1", Piece::Color::White),
		new King("e8", Piece::Color::Black),
	};

	for (int i = 0; i < 8; i++) {
		pieces.push_back(new Pawn({i+1, 2}, Piece::Color::White));
		pieces.push_back(new Pawn({i+1, 7}, Piece::Color::Black));
	}

	return pieces;
}

std::string Chessboard::str() const {
	std::ostringstream os;
	static const char* line = 
		"──────────────────────";
	static const char* letters = 
		"   a  b  c  d  e  f  g  h\n";
	os << letters << "  ┌" << line << "┐\n";
	for (int j = 8; j >= 1; j--) {
		os << j << " │";
		for (int i = 1; i <= 8; i++) {
			const Piece* p = at({i, j});

			char letter;
			if (dynamic_cast<const Pawn*>(p))
				letter = 'p';
			else if (dynamic_cast<const Knight*>(p))
				letter = 'n';
			else if (dynamic_cast<const Bishop*>(p))
				letter = 'b';
			else if (dynamic_cast<const Rook*>(p))
				letter = 'r';
			else if (dynamic_cast<const Queen*>(p))
				letter = 'q';
			else if (dynamic_cast<const King*>(p))
				letter = 'k';
			else 
				letter = ((i + j)%2 ? '+' : '#');

			if (p != nullptr and p->color() == Color::White)
				letter = toupper(letter);

			os << letter << "  ";
		}
		os << "\b\b│ " << j << '\n';
	}
	os << "  └" << line << "┘\n" << letters;
	return os.str();
}

bool Chessboard::isEqual(const Board& rhs) const {
	if (!dynamic_cast<const Chessboard*>(&rhs))
		return false;

	BoardT::const_iterator lRow = begin();
	BoardT::const_iterator rRow = rhs.begin();
	while (lRow != end() and rRow != rhs.end()) {
		auto lPiece = lRow->begin();
		auto rPiece = rRow->begin();
		for ( ; lPiece != lRow->end() and rPiece != rRow->end(); lPiece++, rPiece++) {
			if (*lPiece == *rPiece)
				continue;
			else if (dynamic_cast<Pawn*>(*lPiece) and dynamic_cast<Pawn*>(*rPiece))
					continue;
			else if (dynamic_cast<Bishop*>(*lPiece) and dynamic_cast<Bishop*>(*rPiece))
					continue;
			else if (dynamic_cast<Knight*>(*lPiece) and dynamic_cast<Knight*>(*rPiece))
					continue;
			else if (dynamic_cast<Rook*>(*lPiece) and dynamic_cast<Rook*>(*rPiece))
					continue;
			else if (dynamic_cast<Queen*>(*lPiece) and dynamic_cast<Queen*>(*rPiece))
					continue;
			else if (dynamic_cast<King*>(*lPiece) and dynamic_cast<King*>(*rPiece))
					continue;
			else
					return false;
		}
		lRow++, rRow++;
	}
	return true;
}

}
