#ifndef _DCHESS_HPP_
#define _DCHESS_HPP_

#include <array>
#include <forward_list>
#include <list>
#include <ostream>
#include <typeindex>

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
		Position(const std::string&);
		Position(const char* s) : Position(std::string(s)) {};
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
		bool atLeft() const;
		bool atRight() const;
		bool atTop() const;
		bool atBottom() const;
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
		Position to() const { return t_to; };
		Position from() const { return t_from; };
		const Piece* piece() const { return t_piece; };
		const Piece* capture() const { return t_capture; };
		Piece* piece() { return t_piece; };
		Piece* capture() { return t_capture; };
		virtual void apply();
		virtual bool isEqual(const Turn&) const;
		friend bool operator==(const Turn&, const Turn&);
		friend bool operator!=(const Turn&, const Turn&);
		friend std::ostream& operator<<(std::ostream&, const Turn&);
	protected:
		Position t_from;
		Position t_to;
		Piece* t_piece;
		Piece* t_capture;
	};
	class TurnMap : public std::forward_list<Turn*> {
	public:
		using std::forward_list<Turn*>::forward_list;
		~TurnMap();
		friend bool operator==(const TurnMap&, const TurnMap&);
	};
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
	virtual TurnMap moveMap() const = 0;
	const Chessboard& chessboard() const { return p_chessboard; };
	Chessboard& chessboard() { return p_chessboard; };
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
	using PieceTypesArgT = std::list<std::type_index>;
	using PieceTypesRetT = std::type_index;
	using PieceGetterT = std::function<PieceTypesRetT(PieceTypesArgT)>;
public:
	Piece::Color currentTurnColor() const {
		return b_currentTurnColor; 
	};
	Piece::TurnMap possibleMoves(const Piece*) const;
	Piece::TurnMap possibleMoves(
		const Piece::Position&) const;
	const Piece::Turn& makeTurn(const Piece::Position&, 
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
	void setPieceGetter(PieceGetterT g) { b_pieceGetter = g; };
	PieceGetterT& pieceGetter() { return b_pieceGetter; };
	const PieceGetterT& pieceGetter() const  { return b_pieceGetter; };
	friend std::ostream& operator<<(std::ostream&, const Chessboard&);
	~Chessboard();
private:
	Piece::Color b_currentTurnColor = Piece::Color::White;
	BoardTT b_board;
	CapturedT b_capturedPieces;
	HistoryT b_history;
	PieceGetterT b_pieceGetter;
};

class Pawn : public Piece {
public: 
	Pawn(const Position& p, const Color& c, Chessboard& cb) :
		Piece(p, c, cb) {};
	virtual TurnMap moveMap() const override;
	virtual Position move(const Position&) override;
	virtual ~Pawn() = default;
	class Turn : public Piece::Turn {
	public:
		using Piece::Turn::Turn;
	private:
		std::type_index t_promoteTo = typeid(nullptr);
	public:
		bool isEqual(const Piece::Turn &) const override;
		virtual void apply() override;
		const std::type_index& promoteTo() const { return t_promoteTo; };
	};
private:
	bool p_enPassant = false;
public:
	bool enPassant() const { return p_enPassant; };
};

class Knight : public Piece {
public: 
	Knight(const Position& p, const Color& c, Chessboard& cb) :
		Piece(p, c, cb) {};
	virtual TurnMap moveMap() const override { return {}; };
public:
	using Piece::move;
	virtual ~Knight() = default;
};

class Bishop : public Piece {
public: 
	Bishop(const Position& p, const Color& c, Chessboard& cb) :
		Piece(p, c, cb) {};
	virtual TurnMap moveMap() const override { return {}; };
public:
	using Piece::move;
	virtual ~Bishop() = default;
};

class Rook : public Piece {
public: 
	Rook(const Position& p, const Color& c, Chessboard& cb) :
		Piece(p, c, cb) {};
	virtual TurnMap moveMap() const override { return {}; };
public:
	using Piece::move;
	virtual ~Rook() = default;
};

class Queen : public Piece {
public: 
	Queen(const Position& p, const Color& c, Chessboard& cb) :
		Piece(p, c, cb) {};
	virtual TurnMap moveMap() const override { return {}; };
public:
	using Piece::move;
	virtual ~Queen() = default;
};

class King : public Piece {
public: 
	King(const Position& p, const Color& c, Chessboard& cb) :
		Piece(p, c, cb) {};
	virtual TurnMap moveMap() const override { return {}; };
public:
	using Piece::move;
	virtual ~King() = default;
};

}

#endif // !_DCHESS_HPP_
