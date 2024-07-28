#ifndef _DCHESS_HPP_
#define _DCHESS_HPP_

#include <array>
#include <forward_list>
#include <list>
#include <ostream>

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
					Position offset(int, int) const;
					Position offset(char, int) const;
				public:
					Position operator+(const Position&) const;
					Position operator-(const Position&) const;
					Position operator+=(const Position&);
					Position operator-=(const Position&);
					Position operator()(int, int) const;
					Position operator()(char, int) const;
					Position& operator=(const Position&) = default;
					bool operator==(const Position&) const;
					friend std::ostream& operator<<(
							std::ostream&, const Position&);
			};
			class Turn {
				public:
					Turn(const Piece*, const Position&, const Piece* = nullptr);
					const Position& to() const { return m_to; };
					const Piece* piece() const { return m_piece; };
					const Piece* capture() const { return m_capture; };
				private:
					Position m_to;
					const Piece* m_piece;
					const Piece* m_capture;
			};
			using MoveMapT = std::forward_list<Position>;
			using MoveHistoryT = std::list<Turn>;
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
			virtual Position move(const Position&);
			virtual MoveMapT moveMap() const = 0;
			const MoveHistoryT moveHistory() const { return p_moveHistory; };
			MoveHistoryT moveHistory() { return p_moveHistory; };
			std::size_t movesMade() const { return p_moveHistory.size(); }
		public:
			Piece(const Position&, const Color&, Chessboard&);
			virtual ~Piece() = default;
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
			Piece::Color currentTurnColor() const {
				return b_currentTurnColor; 
			};
			inline Piece::MoveMapT possibleMoves(const Piece*) const;
			inline Piece::MoveMapT possibleMoves(
					const Piece::Position&) const;
			Piece::Turn makeTurn(const Piece::Position&, 
					const Piece::Position&);
			void placePiece(Piece*);
			const BoardTT& board() const { return b_board; };

			Piece* operator[](const Piece::Position& p);
			const Piece* operator[](const Piece::Position& p) const;
			friend std::ostream& operator<<(std::ostream&, const Chessboard&);
			~Chessboard();
	};

	class Pawn : public Piece {
		public: 
			Pawn(const Position& p, const Color& c, Chessboard& cb) :
				Piece(p, c, cb) {};
			virtual MoveMapT moveMap() const override;
			using Piece::move;
			virtual ~Pawn() = default;
	};

}

#endif // !_DCHESS_HPP_
