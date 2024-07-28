#ifndef _DCHESS_HPP_
#define _DCHESS_HPP_

#include <array>
#include <forward_list>
#include <list>

namespace dchess {

	class Chessboard;

	class Piece {
		public:
			class Position {
				private:
					short p_x = 1;
					short p_y = 1;
				public:
					Position() = default;
					Position(int, int);
					Position(char, int);
				public:
					int x() const { return p_x; };
					int y() const { return p_y; };
					char letter() const { return p_x + 'a' - 1; };
					int digit() const { return p_y; };
					int setX(int);
					int setY(int);
					char setLetter(char x) { return setX(x-'a'+1) + 'a'-1; };
					int setDigit(short y) { return setY(y); };
				public:
					Position operator+(const Position&) const;
					Position operator-(const Position&) const;
					Position operator+=(const Position&);
					Position operator-=(const Position&);
			};
			using MoveMapT = std::forward_list<Position>;
			using MoveHistoryT = std::list<Position>;
			enum class Color {
				Unknown, White, Black
			};
		protected:
			Color p_color;
			Position p_position;
			MoveHistoryT p_moveHistory;
			Chessboard& p_chessboard;
		public:
			Color color() const { return p_color; };
			Position position() const { return p_position; };
			virtual Position move(const Position& p);
			virtual MoveMapT moveMap() const = 0;
			const MoveHistoryT moveHistory() const { return p_moveHistory; };
			MoveHistoryT moveHistory() { return p_moveHistory; };
			std::size_t movesMade() const { return p_moveHistory.size(); }
		public:
			inline Piece(const Position&, const Color&, Chessboard&);
			virtual ~Piece();
	};

	class Chessboard {
		public:
			Chessboard();
		public:
			using BoardTT = std::array<std::array<Piece*, 8>, 8>;
			using BoardT = std::array<Piece*, 8>;
			using CapturedT = std::forward_list<Piece*>;
		private:
			Piece::Color b_currentTurnColor = Piece::Color::White;
			BoardTT b_board;
			CapturedT b_capturedPieces = CapturedT(32);
		public:
			Piece::Color currentTurnColor() const {return b_currentTurnColor; };
			Piece::MoveMapT possibleMoves(const Piece*) const;
			inline Piece::MoveMapT possibleMoves(const Piece::Position&) const;

			Piece* operator[](const Piece::Position& p);
			const Piece* operator[](const Piece::Position& p) const ;
			~Chessboard();
	};

	class Pawn : public Piece {
		public: 
			virtual MoveMapT moveMap() const override;
	};

}

#endif // !_DCHESS_HPP_
