#include "tartan/board.hpp"
#include "tartan/board/exceptions.hpp"

#include <algorithm>
#include <iostream>
#include <ostream>
#include <vector>
#include <initializer_list>

namespace tt {
using TurnMap = Piece::TurnMap;
using Position = Piece::Position;
using Turn = Piece::Turn;
using Color = Piece::Color;

Board::Board() {
	fillBoardWithNullptrs();
}

Board::Board(PieceSetT& s) : Board() {
	fill(s);
}

template<class Iterator>
Board::PieceSetT Board::set(Iterator begin, Iterator end) const {
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


Board::PieceSetT Board::set(const std::string& str) const {
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

TurnMap Board::possibleMoves(const Position& p) const {
	return possibleMoves(at(p));
};

TurnMap Board::possibleMoves(const Piece* p) const {
	TurnMap map = p->moveMap();
	return map;
};

Piece* Board::insertPiece(Piece* p) {
	if (p->chessboard())
		throw piece_belongs_to_board_already(p);

	Piece*& dest = at(p->position());
	if (dest)
		throw position_is_taken(p);
	dest = p;

	p->setChessboard(this);

	return p;
}

TurnMap Board::produceTurn(const Position& from, const Position& to, Turn** s) {
	Piece* turnpiece = at(from);
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

	*s = *turn;
	return possible; 
}

const Turn* Board::applyTurn(Turn* t) {
	b_history.push_back(t->clone());
	if (t->capture())
		b_capturedPieces.push_front(t->capture());

	t->apply();

	if (b_currentTurnColor == Color::White)
		setCurrentTurn(Color::Black);
	else
		setCurrentTurn(Color::White);

	return t;
}

Color Board::setCurrentTurn(Color c) {
	Color ret = b_currentTurnColor;

	b_currentTurnColor = c;

	return ret;
}

void Board::fill(PieceSetT& pieces) {
	for (auto const p : pieces) {
		insertPiece(p);
	}
}

template<class Iterator>
void Board::fill(Iterator begin, Iterator end) {
	PieceSetT s = set(begin, end);
	fill(s);
}

void Board::fill() {
	PieceSetT set = defaultPieceSet();
	fill(set);
}

void Board::fill(const std::string& str) {
	PieceSetT s = set(str);
	fill(s);
}

void Board::fill(std::initializer_list<const std::string> l) {
	fill(l.begin(), l.end());
}

void Board::clear() {
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

	b_currentTurnColor = Piece::Color::White;
	b_turnIndex = 0;


	fillBoardWithNullptrs();
}

void Board::fillBoardWithNullptrs() {
	for (auto& row : board()) {
		row.fill(nullptr);
	}
}

Board::PieceTypesRetT Board::getPieceType(
	Board::PieceTypesArgT types) {
	if (!b_pieceGetter)
		throw std::runtime_error("Piece getter is not set.");

	if (types.size() == 0)
		return typeid(nullptr);

	return b_pieceGetter(types);
}


const Piece* Board::operator[](const Position& p) const { 
	return board()[p.x()-1][p.y()-1]; 
}

Piece*& Board::operator[](const Position& p) { 
	return board()[p.x()-1][p.y()-1]; 
}

Piece*& Board::at(const Position& p) {
	return operator[](p);
}

const Piece* Board::at(const Position& p) const {
	return operator[](p);
}

std::ostream& operator<<(std::ostream& os, const Board& cb) {
	return os << cb.str();
}

bool operator!=(const Board& lhs, const Board& rhs) {
	return !(lhs == rhs);
}

bool operator==(const Board& lhs, const Board& rhs) {
	return lhs.isEqual(rhs);
}

Board::~Board() {
	clear();
}

}
