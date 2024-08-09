#include "dchess.hpp"
#include "dchess/exceptions.hpp"

#include <algorithm>
#include <iostream>
#include <ostream>
#include <vector>
#include <cctype>
#include <initializer_list>

namespace dchess {
using TurnMap = Piece::TurnMap;
using Position = Piece::Position;
using Turn = Piece::Turn;
using Color = Piece::Color;

Chessboard::Chessboard() {
	fillBoardWithNullptrs();
}

Chessboard::Chessboard(PieceSetT& s) : Chessboard() {
	fill(s);
}

Chessboard::Chessboard(const std::string& str) : Chessboard() {
	PieceSetT s = set(str);
	fill(s);
}


Chessboard::Chessboard(std::initializer_list<const std::string> l) : Chessboard() {
	PieceSetT s = set(l.begin(), l.end());
	fill(s);
}

template<class Iterator>
Chessboard::PieceSetT Chessboard::set(Iterator begin, Iterator end) {
	PieceSetT pieces;
	try {
		while (begin != end) {
			pieces.push_back(piece(*begin));
			++begin;
		}
	} catch (invalid_piece_spec& ex) {
		std::for_each(pieces.begin(), pieces.end(), 
								[](Piece* p) { delete p; });
		std::throw_with_nested(can_not_produce_set());
	}

	return pieces;
}


Chessboard::PieceSetT Chessboard::set(const std::string& str) {
	std::size_t start = 0, end = 0;

	std::vector<std::string> tokens;

	while ((start = str.find(' ', end)) != std::string::npos) {
		std::string token;
		token = str.substr(end, start - end);

		if (token.length() == 0) {
			end++;
			continue;
		}

		tokens.push_back(std::move(token));
		end = start + 1;
	}
	tokens.push_back(str.substr(end));

	if (tokens.back().length() == 0)
		tokens.pop_back();

	return set(tokens.begin(), tokens.end());
}

Piece* Chessboard::piece(const std::string& spec) {
	if (spec.size() > 3)
		throw invalid_piece_spec(spec, "Specification is too long");
	if (spec.size() < 3)
		throw invalid_piece_spec(spec, "Specification is too short");


	char p = spec[0];
	Piece::Color color;
	if (!isalpha(p))
		throw invalid_piece_spec(spec, "Specified piece type is unknown");

	if (isupper(p))
		color = Piece::Color::White;
	else
		color = Piece::Color::Black;

	Position position;
	try {
		position = spec.substr(1, 2);
	} catch (std::out_of_range& ex) {
		std::throw_with_nested(invalid_piece_spec(
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
			throw invalid_piece_spec(spec, "Specified piece type is unknown");
	}

	newPiece->setColor(color);
	newPiece->setPosition(position);

	return newPiece;
}

Piece* Chessboard::insertPiece(Piece* p) {
	if (p->chessboard())
		throw piece_belongs_to_board_already(p);

	King* king = dynamic_cast<King*>(p);
	if (king) {
		if (king->color() == Piece::Color::White) {
			if (!b_whiteKing) {
				b_whiteKing = king;
				b_currentKing = king;
			} else
				throw duplicate_king(p);
		} else if (king->color() == Piece::Color::Black) {
			if (!b_blackKing) {
				b_blackKing = king;
				b_currentEnemyKing = king;
			} else
				throw duplicate_king(p);
		}
	}
		
	Piece*& dest = at(p->position());
	if (dest)
		throw position_is_taken(p);
	dest = p;

	p->setChessboard(this);
	return p;
}

inline TurnMap Chessboard::possibleMoves(const Position& p) const {
	return possibleMoves(operator[](p));
};

inline TurnMap Chessboard::possibleMoves(const Piece* p) const {
	Piece::TurnMap map = p->moveMap();
	markChecks(map);
	return map;
};

const Turn* Chessboard::makeTurn(const Position& from, const Position& to) {
	Piece* turnpiece = operator[](from);
	if (!turnpiece) 
		throw tile_is_empty(from, to);

	if (turnpiece->color() != b_currentTurnColor)
		throw piece_in_wrong_color(turnpiece, to);

	TurnMap possible = possibleMoves(from);

	if (possible.empty())
		throw can_not_move(turnpiece, to);

	TurnMap::iterator turn = find_if(
		possible.begin(), 
		possible.end(), 
		[&from, &to](Turn*& v) { 
			return (v->from() == from and v->to() == to);
		}
	);

	if (turn == possible.end())
		throw no_such_move(turnpiece, to);

	Turn* t = *turn; 

	if (b_currentKing->checkmate())
		throw king_is_under_checkmate(t->piece(), t->to(), b_currentKing);

	if (!t->possible())
		throw king_is_under_check(t->piece(), t->to(), b_currentKing);

	b_history.push_back(t->clone());
	if (t->capture())
		b_capturedPieces.push_front(t->capture());

	t->apply();

	if (b_currentTurnColor == Color::White) {
		b_currentTurnColor = Color::Black;
	} else {
		b_currentTurnColor = Color::White;
	}

	std::swap(b_currentKing, b_currentEnemyKing);

	return b_history.back();
}

void Chessboard::markChecks(TurnMap& tm) const {
	if (!b_currentKing)
		throw no_king(b_currentTurnColor);

	for (auto& t : tm) {
		(*t).apply(true);
		(*t).setPossible(!b_currentKing->check());
		(*t).undo();
	}
}

Color Chessboard::setCurrentTurn(Color c) {
	Color ret = b_currentTurnColor;

	b_currentTurnColor = c;

	if (b_currentTurnColor == Color::White) {
		b_currentKing = b_whiteKing;
		b_currentEnemyKing = b_blackKing;
	} else { 
		b_currentKing = b_blackKing;
		b_currentEnemyKing = b_whiteKing;
	}

	return ret;
}

Chessboard::PieceSetT Chessboard::defaultPieceSet() {
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

void Chessboard::fill(PieceSetT& pieces) {
	for (auto const p : pieces) {
		insertPiece(p);
	}
}

void Chessboard::fill() {
	PieceSetT set = Chessboard::defaultPieceSet();
	fill(set);
}

void Chessboard::clear() {
	for (auto & p : board()) {
		std::for_each(p.begin(), p.end(), [](Piece* p){ delete p; });
	}
	for (auto& p : b_capturedPieces) {
		delete p;
	}
	b_capturedPieces.clear();

	for (auto& t : b_history) {
		delete t;
	}
	b_history.clear();

	b_currentKing = nullptr;
	b_currentEnemyKing = nullptr;
	b_blackKing = nullptr;
	b_whiteKing = nullptr;
	b_currentTurnColor = Piece::Color::White;
	b_turnIndex = 0;

	fillBoardWithNullptrs();
}

void Chessboard::fillBoardWithNullptrs() {
	for (auto& row : board()) {
		row.fill(nullptr);
	}
}

Chessboard::PieceTypesRetT Chessboard::getPieceType(
	Chessboard::PieceTypesArgT types) {
	if (!b_pieceGetter)
		throw std::runtime_error("Piece getter is not set.");

	if (types.size() == 0)
		return typeid(nullptr);

	return b_pieceGetter(types);
}


const Piece* Chessboard::operator[](const Position& p) const { 
	return board()[p.x()-1][p.y()-1]; 
}

Piece*& Chessboard::operator[](const Position& p) { 
	return board()[p.x()-1][p.y()-1]; 
}

Piece*& Chessboard::at(const Position& p) {
	return operator[](p);
}

const Piece* Chessboard::at(const Position& p) const {
	return operator[](p);
}

std::ostream& operator<<(std::ostream& os, const Chessboard& cb) {
	static const char* line = 
		"──────────────────────";
	static const char* letters = 
		"   a  b  c  d  e  f  g  h\n";
	os << letters << "  ┌" << line << "┐\n";
	for (int j = 8; j >= 1; j--) {
		os << j << " │";
		for (int i = 1; i <= 8; i++) {
			const Piece* p = cb[{i, j}];

			char letter;
			if (dynamic_cast<const Pawn*>(p))
				letter = 'p';
			else if (dynamic_cast<const Knight*>(p))
				letter = 'k';
			else if (dynamic_cast<const Bishop*>(p))
				letter = 'b';
			else if (dynamic_cast<const Rook*>(p))
				letter = 'r';
			else if (dynamic_cast<const Queen*>(p))
				letter = 'q';
			else if (dynamic_cast<const King*>(p))
				letter = 'x';
			else 
				letter = ((i + j)%2 ? '+' : '#');

			if (p != nullptr and p->color() == Color::White)
				letter = toupper(letter);

			os << letter << "  ";
		}
		os << "\b\b│ " << j << '\n';
	}
	os << "  └" << line << "┘\n" << letters;
	return os;
}

bool operator==(const Chessboard& lhs, const Chessboard& rhs) {
	BoardT::const_iterator lRow = lhs.begin();
	BoardT::const_iterator rRow = rhs.begin();
	while (lRow != lhs.end() and rRow != rhs.end()) {
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

Chessboard::~Chessboard() {
	clear();
}

}
