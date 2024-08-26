#include <tartan/chess.hpp>

#include <algorithm>

namespace tt::chess {
using Position = Piece::Position;
using TurnMap = Piece::TurnMap;

TurnMap King::moveMap(int mode) const {
	TurnMap map, m;
	Position tpos, pos = p_position;
	Piece* enemy;

	if (p_color == Piece::Color::Black) {
		pos.setMode(Position::Mode::Reverse);
		tpos.setMode(Position::Mode::Reverse);
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
		enemy = p_board->at(tpos);
		if (enemy and enemy->color() != p_color)
			map.push_front(new Turn(this, tpos, enemy));
		else if (!enemy)
			map.push_front(new Turn(this, tpos));
	}

	if (mode != Chessboard::CheckingMode and 
		!k_castled and (movesMade() == 0) and 
		(pos.letter() == 'e') and 
		pos.atBottom() and !check()) {
		bool valid = false;
		Rook* rook;
		int variants[2] = {1, -1};
		for (auto v : variants) {			tpos = pos;
			while (true) {
				try {
					tpos = tpos(v, 0);
				} catch (std::out_of_range& ex) {
					break;
				}
				Piece* target = p_board->at(tpos);
				rook = dynamic_cast<Rook*>(target);
				if (rook and rook->movesMade() == 0) {
					valid = true;
					break;
				} else if (target != nullptr) {
					break;
				}
			}
			if (valid) {
				Turn t(this, pos(v, 0));
				t.apply();
				bool c = check();
				t.undo();
				if (!c)
					map.push_front(new Turn(this, pos(2*v, 0), nullptr, new Rook::Turn(rook, pos(v, 0))));
			}
		}
	}

	return map;
}

bool King::check() const {
	if (k_checkTurnIndex != board()->turnIndex()) {
		k_check = calculateCheck();
		k_checkTurnIndex = board()->turnIndex();
	}
	return k_check;
}

bool King::calculateCheck() const {
	for (auto& row : p_board->board()) {
		for (auto& p : row) {
			if (!p or p->color() == p_color)
				continue;
			TurnMap enemyTurns = p->moveMap(
				dynamic_cast<King*>(p) ? 
				Chessboard::CheckingMode : 
				Chessboard::DefaultMode
			);

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


bool King::checkmate() const {
	if (k_checkmateTurnIndex != board()->turnIndex()) {
		k_checkmate = calculateCheckmate();
		k_checkmateTurnIndex = board()->turnIndex();
	}
	return k_checkmate;
}

bool King::calculateCheckmate() const {
	if (!check() or p_board->possibleMoves(this).possible())
		return false;

	for (auto& row : p_board->board()) {
		for (auto& p : row) {
			if (!p or p->color() != p_color or p == this)
				continue;
			TurnMap allyTurns = p->moveMap();

			for (auto const& t : allyTurns) {
				t->apply(true);
				bool underCheck = check();
				t->undo();
				if (!underCheck)
					return false;
			}
		}
	}

	return true;
}

}
