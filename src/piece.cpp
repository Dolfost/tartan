#include "include/dchess.hpp"

namespace dchess {
using Position = Piece::Position;

Piece::Piece(const Position&  p, const Color& c, Chessboard* cb) { 
	p_position = p; 
	p_color = c; 

	if (cb) {
		cb->insertPiece(this);
		p_chessboard = cb;
	}
};

Chessboard* Piece::setChessboard(Chessboard* cb) {
	Chessboard* ret = p_chessboard;
	p_chessboard = cb;
	return ret;
}

Position Piece::move(const Position& p) {
	Position ret = p_position;
	p_position = p;
	p_moveHistory.push_back(p);
	return ret;
}

Piece::TurnMap Piece::diagonalMoves(const Piece* p) {
	TurnMap map;
	Position tpos, pos = p->p_position;
	Piece* enemy;

	if (p->p_color == Piece::Color::Black) {
		pos.setOffsetMode(Position::Mode::Reverse);
		tpos.setOffsetMode(Position::Mode::Reverse);
	}

	using func = bool (Position::*)(void) const;
	std::tuple<func, func, std::pair<int, int>> conds[4] = {
		{&Position::atRight, &Position::atBottom, {1, -1}},
		{&Position::atRight, &Position::atTop, {1, 1}},
		{&Position::atLeft, &Position::atBottom, {-1, -1}},
		{&Position::atLeft, &Position::atTop, {-1, 1}},
	};

	for (auto& v: conds) {
		tpos = pos;
		while (!(tpos.*std::get<0>(v))() and !(tpos.*std::get<1>(v))()) {
			std::pair<int, int> of = std::get<2>(v);
			tpos = tpos.offset(of.first, of.second);
			enemy = p->p_chessboard->at(tpos);
			if (enemy) {
				map.push_front(new Turn(p, tpos, enemy));
				break;
			}
			map.push_front(new Turn(p, tpos));
		}
	}
	
	return map;
}

Piece::TurnMap Piece::straightMoves(const Piece* p) {
	TurnMap map;
	Position tpos, pos = p->p_position;
	Piece* enemy;

	if (p->p_color == Piece::Color::Black) {
		pos.setOffsetMode(Position::Mode::Reverse);
		tpos.setOffsetMode(Position::Mode::Reverse);
	}

	using func = bool (Position::*)(void) const;
	std::tuple<func, std::pair<int, int>> conds[4] = {
		{&Position::atBottom, {0, -1}},
		{&Position::atTop, {0, 1}},
		{&Position::atLeft, {-1, 0}},
		{&Position::atRight, {1, 0}},
	};

	for (auto& v: conds) {
		tpos = pos;
		while (!(tpos.*std::get<0>(v))()) {
			std::pair<int, int> of = std::get<1>(v);
			tpos = tpos.offset(of.first, of.second);
			enemy = p->p_chessboard->at(tpos);
			if (enemy) {
				map.push_front(new Turn(p, tpos, enemy));
				break;
			}
			map.push_front(new Turn(p, tpos));
		}
	}

	return map;
}

}
