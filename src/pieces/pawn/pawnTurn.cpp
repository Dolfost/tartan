#include <dchess.hpp>
#include <dchess/exceptions.hpp>

namespace dchess {
using Turn = Pawn::Turn;

void Turn::apply() {
	Piece::Turn::apply();

	Position pos = t_to;
	if (t_piece->color() == Color::Black)
		pos.setOffsetMode(Position::Mode::Reverse);

	t_promoteTo = typeid(nullptr);
	if (pos.atTop()) {
		Chessboard& cb = t_piece->chessboard();
		t_promoteTo = cb.pieceGetter()({
			typeid(Queen), typeid(Bishop), typeid(Rook), typeid(Knight)
		});

		Piece* tmp = cb[pos];
		cb[pos] = nullptr;
		if (t_promoteTo == typeid(Queen))
			new Queen(pos, t_piece->color(), cb);
		else if (t_promoteTo == typeid(Bishop))
			new Bishop(pos, t_piece->color(), cb);
		else if (t_promoteTo == typeid(Rook))
			new Rook(pos, t_piece->color(), cb);
		else if (t_promoteTo == typeid(Knight))
			new Knight(pos, t_piece->color(), cb);
		else {
			t_promoteTo = typeid(nullptr);
			cb[pos] = tmp;
			throw illegal_getter_type();
		}
		delete tmp;
	}
}

bool Turn::isEqual(const Piece::Turn& rhs) const {
	const Pawn::Turn* crhs = dynamic_cast<const Pawn::Turn*>(&rhs);
	if (!crhs)
		return false;

	return Piece::Turn::isEqual(rhs) and t_promoteTo == crhs->t_promoteTo;
}


}
