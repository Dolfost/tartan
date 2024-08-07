#include <algorithm>
#include <dchess.hpp>

namespace dchess {
using Position = Piece::Position;
using TurnMap = Piece::TurnMap;

TurnMap King::moveMap() const {
	TurnMap map, m;
	Position tpos, pos = p_position;

	if (p_color == Piece::Color::Black) {
		pos.setOffsetMode(Position::Mode::Reverse);
		tpos.setOffsetMode(Position::Mode::Reverse);
	}

	std::pair<int, int> ofs[8] = {
	 {1, 1}, {1, 0}, {1, -1}, {0, -1},
	 {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}
	};

	for (auto& of : ofs) {
		try {
			tpos = pos.offset(of.first, of.second);
		} catch (std::out_of_range& ex) {
			continue;
		}
		map.push_front(new Turn(this, tpos, p_chessboard->at(tpos)));
	}

	if (!k_castled and movesMade() == 0 and pos.letter() == 'e' and pos.atBottom()) {
		int variants[2] = {1, -1};
		for (auto v : variants) {
			tpos = pos;
			while (true) {
				try {
					tpos = tpos(v, 0);
				} catch (std::out_of_range& ex) {
					break;
				}
				Piece* target = p_chessboard->at(tpos);
				Rook* rook = dynamic_cast<Rook*>(target);
				if (rook and target->movesMade() == 0)
					map.push_front(new Turn(this, pos(2*v, 0), nullptr, new Rook::Turn(rook, pos(v, 0))));
				else if (target != nullptr)
					break;
			}
		}
	}

	return map;
}

bool King::check() {
	for (auto& row : p_chessboard->board()) {
		for (auto& p : row) {
			if (!p or p->color() == p_color)
				continue;
			TurnMap enemyTurns = p->moveMap();

			TurnMap::iterator e = std::find_if(
				enemyTurns.begin(), 
				enemyTurns.end(), 
				[this](Piece::Turn* t){
					return (t->capture() == this);
				}
			);

			if (e != enemyTurns.end())
				return true;
		}
	}
	return false;
}

}
