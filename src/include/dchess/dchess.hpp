#ifndef _DCHESS_HPP_
#define _DCHESS_HPP_

#include <array>
#include <forward_list>
#include <list>
#include <ostream>
#include <typeindex>
#include <functional>
#include <initializer_list>

namespace dchess {

class Chessboard;

class Piece {
public:
	enum class Color {
		Black = 0, White = 1,
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
		Position(const Position&);
		Position& operator=(const Position&);
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
		std::string str() const;
		Position operator+(const Position&) const;
		Position operator-(const Position&) const;
		Position operator+=(const Position&);
		Position operator-=(const Position&);
		Position operator()(int, int) const;
		Position operator()(char, int) const;
		friend bool operator==(const Position&, const Position&);
		friend std::ostream& operator<<(
			std::ostream&, const Position&);
	};
	class Turn {
	public:
		Turn(const Piece*, const Position&, const Piece* = nullptr, bool = true);
		Position to() const { return t_to; };
		Position from() const { return t_from; };
		const Piece* piece() const { return t_piece; };
		const Piece* capture() const { return t_capture; };
		Piece* piece() { return t_piece; };
		Piece* capture() { return t_capture; };
		bool possible() const { return t_possible; };
		bool setPossible(bool c) { return !(t_possible = c); };
		virtual std::string str() const;
		virtual void apply(bool = false);
		virtual void undo();
		virtual bool isEqual(const Turn&) const;
		friend bool operator==(const Turn&, const Turn&);
		friend bool operator!=(const Turn&, const Turn&);
		friend std::ostream& operator<<(std::ostream&, const Turn&);
		virtual auto clone() const -> std::decay<decltype(*this)>::type*;
		virtual ~Turn() = default;
	protected:
		Position t_from;
		Position t_to;
		Piece* t_piece;
		Piece* t_capture;
		bool t_possible;
	};
	class TurnMap : public std::list<Turn*> {
	public:
		using std::list<Turn*>::list;
		TurnMap(const TurnMap&);
		TurnMap(TurnMap&&);
		TurnMap& operator=(const TurnMap&);
		TurnMap& operator=(TurnMap&&);
		bool possible() const;
		~TurnMap();
		friend bool operator==(const TurnMap&, const TurnMap&);
	};
protected:
	Color p_color;
	Position p_position;
	Chessboard* p_chessboard = nullptr;
	std::size_t p_movesMade = 0;
	std::size_t p_turnIndex = 0;
public:
	Color color() const { return p_color; };
	Color setColor(Color);
	const Position& position() const { return p_position; };
	Position& position() { return p_position; };
	Position setPosition(const Position&);
	virtual Position move(const Position&);
	virtual TurnMap moveMap(bool checking = false) const = 0;
	const Chessboard* chessboard() const { return p_chessboard; };
	Chessboard* chessboard() { return p_chessboard; };
	Chessboard* setChessboard(Chessboard*);
	std::size_t movesMade() const { return p_movesMade; }
	std::size_t turnIndex() const { return p_turnIndex; }
public:
	static TurnMap diagonalMoves(const Piece*);
	static TurnMap straightMoves(const Piece*);
public:
	Piece(const Position& = {1,1}, Color = Color::White);
	virtual ~Piece() = default;
};

using BoardT = std::array<std::array<Piece*, 8>, 8>;
class King;
class Chessboard : private BoardT {
	friend class Piece::Turn;
public:
	using CapturedT = std::forward_list<const Piece*>;
	using HistoryT = std::list<const Piece::Turn*>;
	using TurnsT = std::list<std::pair<Piece::Position, Piece::Position>>;
	using PieceSetT = std::list<Piece*>;
	using PieceTypesArgT = std::list<std::type_index>;
	using PieceTypesRetT = std::type_index;
	using PieceGetterT = std::function<PieceTypesRetT(PieceTypesArgT)>;
public:
	Chessboard();
	Chessboard(const std::string&);
	Chessboard(std::initializer_list<const std::string>);
	Chessboard(PieceSetT&);
public:
	Piece::Color currentTurn() const {
		return b_currentTurnColor; 
	};
	Piece::Color setCurrentTurn(Piece::Color);
	Piece::TurnMap possibleMoves(const Piece*) const;
	Piece::TurnMap possibleMoves(const Piece::Position&) const;
	const Piece::Turn* makeTurn(const Piece::Position&, 
														 const Piece::Position&);
	const BoardT& board() const { return static_cast<const BoardT&>(*this); };
	BoardT& board() { return static_cast<BoardT&>(*this); };
	HistoryT& history() { return b_history; };
	const HistoryT& history() const { return b_history; };
	std::size_t movesMade() const { return b_history.size(); }
	const King* whiteKing() const { return b_whiteKing; };
	King* whiteKing() { return b_whiteKing; };
	const King* blackKing() const { return b_blackKing; };
	King* blackKing() { return b_blackKing; };
	King* currentKing() { return b_currentKing; };
	const King* currentKing() const { return b_currentKing; };
	const King* currentEnemyKing() const { return b_currentEnemyKing; };
	King* currentEnemyKing() { return b_currentEnemyKing; };
	std::size_t turnIndex() const { return b_turnIndex; };

	Piece* insertPiece(Piece*);
	void clear();
	void fill();
	void fill(PieceSetT&);
	void fill(const std::string&);
	static PieceSetT defaultPieceSet();
	void refill() { clear(); fill(); };

	friend bool operator==(const Chessboard&, const Chessboard&);
	friend bool operator!=(const Chessboard&, const Chessboard&);
	Piece*& operator[](const Piece::Position&);
	const Piece* operator[](const Piece::Position&) const;
	Piece*& at(const Piece::Position&);
	const Piece* at(const Piece::Position&) const;
	using BoardT::iterator;
	using BoardT::const_iterator;
	void setPieceGetter(PieceGetterT g) { b_pieceGetter = g; };
	PieceGetterT& pieceGetter() { return b_pieceGetter; };
	PieceTypesRetT getPieceType(PieceTypesArgT);
	const PieceGetterT& pieceGetter() const  { return b_pieceGetter; };
	friend std::ostream& operator<<(std::ostream&, const Chessboard&);
	~Chessboard();
public:
	static PieceSetT set(const std::string&);
	template<class Iterator>
	static PieceSetT set(Iterator, Iterator);
	static Piece* piece(const std::string&);
private:
	void markChecks(Piece::TurnMap&) const;
	void fillBoardWithNullptrs();
private:
	Piece::Color b_currentTurnColor = Piece::Color::White;
	CapturedT b_capturedPieces;
	HistoryT b_history;
	PieceGetterT b_pieceGetter;
	King* b_whiteKing = nullptr;
	King* b_blackKing = nullptr;
	King* b_currentKing = nullptr;
	King* b_currentEnemyKing = nullptr;
	std::size_t b_turnIndex = 0;
};

class Pawn : public Piece {
public: 
	using Piece::Piece;
	virtual TurnMap moveMap(bool) const override;
	virtual ~Pawn() = default;
	class Turn : public Piece::Turn {
	public:
		using Piece::Turn::Turn;
	private:
		std::type_index t_promoteTo = typeid(nullptr);
	public:
		bool isEqual(const Piece::Turn &) const override;
		virtual void apply(bool = false) override;
		const std::type_index& promoteTo() const { return t_promoteTo; };
	};
};

class Knight : public Piece {
public: 
	using Piece::Piece;
	virtual TurnMap moveMap(bool) const override;
	class Turn : public Piece::Turn {
	public:
		using Piece::Turn::Turn;
	public:
		bool isEqual(const Piece::Turn &) const override;
	};
public:
	using Piece::move;
	virtual ~Knight() = default;
};

class Bishop : public Piece {
public: 
	using Piece::Piece;
	virtual TurnMap moveMap(bool) const override;
	class Turn : public Piece::Turn {
	public:
		using Piece::Turn::Turn;
	public:
		bool isEqual(const Piece::Turn &) const override;
	};
public:
	using Piece::move;
	virtual ~Bishop() = default;
};

class Rook : public Piece {
public: 
	using Piece::Piece;
	virtual TurnMap moveMap(bool) const override;
	class Turn : public Piece::Turn {
	public:
		using Piece::Turn::Turn;
	public:
		bool isEqual(const Piece::Turn &) const override;
	};
public:
	using Piece::move;
	virtual ~Rook() = default;
};

class Queen : public Piece {
public: 
	using Piece::Piece;
	virtual TurnMap moveMap(bool) const override;
	class Turn : public Piece::Turn {
	public:
		using Piece::Turn::Turn;
	public:
		bool isEqual(const Piece::Turn &) const override;
	};
public:
	using Piece::move;
	virtual ~Queen() = default;
};

class King : public Piece {
public: 
	using Piece::Piece;
	virtual TurnMap moveMap(bool) const override;
	class Turn : public Piece::Turn {
	public:
		Turn(
			const Piece* f, 
			const Position& t, 
			const Piece* c = nullptr, 
			Rook::Turn* castling = nullptr,
			bool p = true
		) : Piece::Turn(f, t, c, p) { 
			k_castlingTurn = castling;
		};
	public:
		bool isEqual(const Piece::Turn &) const override;
		virtual void apply(bool = false) override;
		virtual void undo() override;
		virtual std::string str() const override;
		virtual ~Turn() override {
			delete k_castlingTurn;
		}
	private:
		Rook::Turn* k_castlingTurn;
	};
	bool check() const;
	bool checkmate() const;
	bool castled() const { return k_castled; };
private:
	bool k_castled = false;
public:
	using Piece::move;
	virtual ~King() = default;
};

}

#endif // !_DCHESS_HPP_
