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
	enum class Color {
		Unknown, White, Black
	};
	class Position {
	public:
		enum class Mode {
			Normal = 1,
			Reverse = -1,
		};
	private:
		short p_x = 1;
		short p_y = 1;
		Mode p_mode = Mode::Normal;
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
		Mode offsetMode() const { return p_mode; };
		Mode setOffsetMode (Mode m);
	public:
		Position operator+(const Position&) const;
		Position operator-(const Position&) const;
		Position operator+=(const Position&);
		Position operator-=(const Position&);
		Position operator()(int, int) const;
		Position operator()(char, int) const;
		Position& operator=(const Position&);
		friend bool operator==(const Position&, const Position&);
		friend std::ostream& operator<<(
			std::ostream&, const Position&);
	};
	class Turn {
	public:
		Turn(const Piece*, const Position&, const Piece* = nullptr);
		Position to() const { return m_to; };
		Position from() const { return m_from; };
		const Piece* piece() const { return m_piece; };
		const Piece* capture() const { return m_capture; };
		Piece* piece() { return m_piece; };
		Piece* capture() { return m_capture; };
		friend bool operator==(const Turn&, const Turn&);
		friend std::ostream& operator<<(std::ostream&, const Turn&);
	private:
		Position m_from;
		Position m_to;
		Piece* m_piece;
		Piece* m_capture;
	};
	using MoveMapT = std::forward_list<Turn>;
	using MoveHistoryT = std::list<Position>;
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
	const MoveHistoryT history() const { return p_moveHistory; };
	MoveHistoryT history() { return p_moveHistory; };
	std::size_t movesMade() const { return p_moveHistory.size(); }
public:
	Piece(const Position&, const Color&, Chessboard&);
	virtual ~Piece() = default;
};

class Chessboard {
public:
	Chessboard();
public:
	using BoardT = std::array<Piece*, 8>;
	using BoardTT = std::array<std::array<Piece*, 8>, 8>;
	using CapturedT = std::forward_list<const Piece*>;
	using HistoryT = std::list<const Piece::Turn>;
	using TurnsT = std::list<std::pair<Piece::Position, Piece::Position>>;
public:
	Piece::Color currentTurnColor() const {
		return b_currentTurnColor; 
	};
	Piece::MoveMapT possibleMoves(const Piece*) const;
	Piece::MoveMapT possibleMoves(
		const Piece::Position&) const;
	const Piece::Turn makeTurn(const Piece::Position&, 
											const Piece::Position&);
	void placePiece(Piece*);
	const BoardTT& board() const { return b_board; };
	BoardTT& board() { return b_board; };
	HistoryT& history() { return b_history; };
	const HistoryT& history() const { return b_history; };
	std::size_t movesMade() const { return b_history.size(); }

	Piece*& operator[](const Piece::Position&);
	const Piece* operator[](const Piece::Position&) const;
	Piece*& at(const Piece::Position&);
	const Piece* at(const Piece::Position&) const;
	friend std::ostream& operator<<(std::ostream&, const Chessboard&);
	~Chessboard();
private:
	Piece::Color b_currentTurnColor = Piece::Color::White;
	BoardTT b_board;
	CapturedT b_capturedPieces;
	HistoryT b_history;
private:
	void apply_turn(Piece::Turn&);
};

class Pawn : public Piece {
public: 
	Pawn(const Position& p, const Color& c, Chessboard& cb) :
		Piece(p, c, cb) {};
	virtual MoveMapT moveMap() const override;
	virtual Position move(const Position&) override;
	virtual ~Pawn() = default;
private:
	bool p_enPassant = false;
public:
	bool enPassant() const { return p_enPassant; };
};

class Knight : public Piece {
public: 
	Knight(const Position& p, const Color& c, Chessboard& cb) :
		Piece(p, c, cb) {};
	virtual MoveMapT moveMap() const override { return {}; };
	using Piece::move;
	virtual ~Knight() = default;
};

class Bishop : public Piece {
public: 
	Bishop(const Position& p, const Color& c, Chessboard& cb) :
		Piece(p, c, cb) {};
	virtual MoveMapT moveMap() const override { return {}; };
	using Piece::move;
	virtual ~Bishop() = default;
};

class Rook : public Piece {
public: 
	Rook(const Position& p, const Color& c, Chessboard& cb) :
		Piece(p, c, cb) {};
	virtual MoveMapT moveMap() const override { return {}; };
	using Piece::move;
	virtual ~Rook() = default;
};

class Queen : public Piece {
public: 
	Queen(const Position& p, const Color& c, Chessboard& cb) :
		Piece(p, c, cb) {};
	virtual MoveMapT moveMap() const override { return {}; };
	using Piece::move;
	virtual ~Queen() = default;
};

class King : public Piece {
public: 
	King(const Position& p, const Color& c, Chessboard& cb) :
		Piece(p, c, cb) {};
	virtual MoveMapT moveMap() const override { return {}; };
	using Piece::move;
	virtual ~King() = default;
};

}

#endif // !_DCHESS_HPP_
