#include <tartan/board.hpp>

namespace tt {
using Position = Piece::Position;

Piece::Piece(const Position&  p, Color c) { 
	p_position = p; 
	p_color = c; 
};

Board* Piece::setBoard(Board* cb) {
	Board* ret = p_board;
	p_board = cb;
	return ret;
}

Position Piece::move(const Position& p) {
	Position ret = p_position;

	p_movesMade++;
	p_turnIndex = p_board->turnIndex();

	p_board->at(p_position) = nullptr;
	p_board->at(p) = this;

	p_position = p;
	return ret;
}

Position Piece::setPosition(const Position& p) {
	Position ret = p_position;
	p_position = p;
	return ret;
}

Piece::Color Piece::setColor(Color c) {
	Color ret = p_color;
	p_color = c;
	return ret;
}

Piece::TurnMap Piece::diagonalMoves(const Piece* p) {
	TurnMap map;
	Position tpos, pos = p->p_position;
	Piece* enemy;

	if (p->p_color == Piece::Color::Black) {
		pos.setMode(Position::Mode::Reverse);
		tpos.setMode(Position::Mode::Reverse);
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
			enemy = p->p_board->at(tpos);
			if (!enemy)
				map.push_front(new Turn(p, tpos));
			else if (enemy->p_color != p->p_color) {
				map.push_front(new Turn(p, tpos, enemy));
				break;
			} else if (enemy->p_color == p->p_color) 
				break;
		}
	}
	
	return map;
}

Piece::TurnMap Piece::straightMoves(const Piece* p) {
	TurnMap map;
	Position tpos, pos = p->p_position;
	Piece* enemy;

	if (p->p_color == Piece::Color::Black) {
		pos.setMode(Position::Mode::Reverse);
		tpos.setMode(Position::Mode::Reverse);
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
			enemy = p->p_board->at(tpos);
			if (!enemy)
				map.push_front(new Turn(p, tpos));
			else if (enemy->p_color != p->p_color) {
				map.push_front(new Turn(p, tpos, enemy));
				break;
			} else if (enemy->p_color == p->p_color) 
				break;
		}
	}

	return map;
}

}
