#include <tartan/chess.hpp>
#include <tartan/board/exceptions.hpp>

namespace tt::chess {
using Turn = Pawn::Turn;

void Turn::apply(int mode) {
	Piece::Turn::apply();

	Position pos = t_to;
	if (t_piece->color() == Color::Black)
		pos.setMode(Position::Mode::Reverse);

	t_promoteTo = typeid(nullptr);
	if (pos.atTop() and mode != Chessboard::CheckingMode) {
		Board* cb = t_piece->board();
		t_promoteTo = cb->getPieceType({
			typeid(Queen), typeid(Bishop), typeid(Rook), typeid(Knight)
		});

		Piece* tmp = cb->at(pos);
		Piece* newPiece;
		cb->at(pos) = nullptr;
		if (t_promoteTo == typeid(Queen))
			newPiece = new Queen(pos, t_piece->color());
		else if (t_promoteTo == typeid(Bishop))
			newPiece = new Bishop(pos, t_piece->color());
		else if (t_promoteTo == typeid(Rook))
			newPiece = new Rook(pos, t_piece->color());
		else if (t_promoteTo == typeid(Knight))
			newPiece = new Knight(pos, t_piece->color());
		else {
			t_promoteTo = typeid(nullptr);
			cb->at(pos) = tmp;
			throw tt::ex::bad_piece_type();
		}
		cb->insertPiece(newPiece);
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
