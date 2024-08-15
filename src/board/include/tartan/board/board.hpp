#ifndef _TARTAN_HPP_
#define _TARTAN_HPP_

#include <array>
#include <forward_list>
#include <list>
#include <ostream>
#include <typeindex>
#include <functional>
#include <initializer_list>

namespace tt {

class Board;

/**
 * @brief Describes generic board memeber piece API.
 *
 * This class should be inherited and used as
 * a way to describe chess piece in every board derived
 * from Board class.
 */
class Piece {
public:
	/**
	 * @brief Piece color.
	 *
	 * @sa setColor(), color()
	 */
	enum class Color {
		Black = 0, White = 1,
	};
	/**
	 * @class Position
	 * @brief Describes Piece position at the Board.
	 */
	class Position {
	public:
		/**
		 * @brief Boolean functions operation mode.
		 *
		 * Describes location of the coordinates origin.
		 * @sa atTop(), atLeft(), atRight(), atBottom(),
		 * offset()
		 */
		enum class Mode {
			Normal = 1, ///< Place origin at the a1
			Reverse = -1, ///< Place origin at the h8
		};
	private:
		short p_x = 1;
		short p_y = 1;
		Mode p_mode = Mode::Normal;
	public:
		Position() = default; ///< Create Position object at a1
		/**
		 * @brief Create Position object with coordinates `x` `y`
		 *
		 * @param x x coordinate
		 * @param y y coordinate
		 * @exception std::out_of_range
		 */
		Position(int x, int y);
		/**
		 * @brief Create Position object with coordinates `ld` (eq. `b3`) 
		 *
		 * @param l letter x coordinate
		 * @param d digit y coordinate
		 * @exception std::out_of_range
		 */
		Position(char l, int d);
		/**
		 * @brief Creates Position object at `str` position
		 *
		 * @param str 2-character letter-digit string representation of position
		 * @exception std::out_of_range
		 */
		Position(const std::string& str);
		/**
		 * @copydoc Position(const std::string&)
		 */
		Position(const char* str) : Position(std::string(str)) {};
	public:
		/**
		 * @brief Copy constructor
		 *
		 * @note Copying does not copy the current mode.
		 */
		Position(const Position&);
		/**
		 * @brief Copy assignment operator
		 * @copydetails Position(const Position&)
		 * @return a new object with same coordinates.
		 */
		Position& operator=(const Position&);
	public:
		/**
		 * @brief x coordinate
		 * @return x coordinate
		 */
		int x() const { return p_x; };
		/**
		 * @brief y coordinate
		 * @return y coordinate
		 */
		int y() const { return p_y; };
		/**
		 * @brief Letter representation of x coordinate
		 *
		 * @return x coordinate in letter representation
		 * @sa x()
		 */
		char letter() const { return p_x + 'a' - 1; };
		/**
		 * @brief Digit representation of y coordinate
		 *
		 * @return y coordinate in digit representation
		 * @sa y()
		 */
		int digit() const { return p_y; };
		/**
		 * @brief Set x coordinate
		 *
		 * @param x new value
		 * @return old value
		 */
		int setX(int x);
		/**
		 * @brief Set y coordinate
		 *
		 * @param y new value
		 * @return old value
		 * @exception std::out_of_range
		 */
		int setY(int y);
		/**
		 * @brief Set x coordinate with string representation
		 *
		 * @param x x coordinate represented as string
		 * @return old value
		 * @exception std::out_of_range
		 */
		char setLetter(char x) { return setX(x-'a'+1) + 'a'-1; };
		/**
		 * @copydoc setY(int)
		 * @exception std::out_of_range
		 * @sa setY(int)
		 */
		int setDigit(short y) { return setY(y); };
		/**
		 * @name Position manipulation
		 * Set of functions that provide boolean operations on the Position object
		 * conditionally depending on it's mode() value.
		 * @{
		 */
		/**
		 * @brief Offset current position
		 *
		 * Returns new position at (x±dx, y±dy). Operation sign
		 * depends on current mode().
		 *
		 * @param dx x coordinate incrementation
		 * @param dy y coordinate incrementation
		 * @return new Position object at (x±dx, y±dy).
		 * @exception std::out_of_range
		 * @sa mode().
		 */
		Position offset(int dx, int dy) const;
		/**
		 * @copybrief offset(int, int) const
		 *
		 * Works as offset(int dx, int dy) but with 
		 * character-digit representation
		 *
		 * @param dc x coordinate incrementation represented as string
		 * @param dd y coordinate incrementation
		 * @return new Position object at (x±dx, y±dy).
		 * @exception std::out_of_range
		 * @sa offsetMode().
		 */
		Position offset(char dc, int dd) const;
		/**
		 * @brief Check if the position are at left border
		 *
		 * @note This function behaivor is influenced by current mode() value.
		 *
		 * @return `true` if position is at left border
		 * `false` otherwise
		 * @sa setMode().
		 */
		bool atLeft() const;
		/**
		 * @brief Check if the position are at right border
		 *
		 * @copydetails atLeft()
		 *
		 * @return `true` if position is at right border
		 * `false` otherwise
		 * @sa mode().
		 */
		bool atRight() const;
		/**
		 * @brief Check if the position are at top border
		 *
		 * @copydetails atLeft()
		 *
		 * @return `true` if position is at top border
		 * `false` otherwise
		 * @sa mode().
		 */
		bool atTop() const;
		/**
		 * @brief Check if the position are at bottom border
		 *
		 * @copydetails atLeft()
		 *
		 * @return `true` if position is at bottom border, 
		 * `false` otherwise
		 * @sa mode().
		 */
		bool atBottom() const;
		/**
		 * @brief Current mode
		 *
		 * @return current mode
		 * @sa setMode(), Mode
		 */
		Mode mode() const { return p_mode; };
		/**
		 * @brief Set offset mode
		 *
		 * @note Depending on the mode() value, functions from 
		 * @ref posmanip group behave differently.
		 *
		 * @param m new offset mode value
		 * @return old offset mode value
		 */
		Mode setMode (Mode m);
		/** @} */
	public:
		/**
		 * @brief String position representation.
		 * @return string representation of current position
		 */
		std::string str() const;
		/**
		 * @brief Addition operator
		 *
		 * @return new object with sum of corresponding 
		 * coordinates of argument objects
		 * @exception std::out_of_range
		 */
		Position operator+(const Position&) const;
		/**
		 * @brief Substraction operator
		 *
		 * @return new object with difference of corresponding 
		 * coordinates of argument objects
		 * @exception std::out_of_range
		 */
		Position operator-(const Position&) const;
		/**
		 * @copydoc operator+(const Position&) cosnt
		 */
		Position operator+=(const Position&);
		/**
		 * @copydoc operator-(const Position&) cosnt
		 */
		Position operator-=(const Position&);
		/**
		 * @copydoc offset(int, int) cosnt
		 */
		Position operator()(int, int) const;
		/**
		 * @copydoc offset(char, int) cosnt
		 */
		Position operator()(char, int) const;
		/**
		 * @brief Comparison operator
		 *
		 * @return `true` if corresponding coordinates 
		 * of both objects are equal
		 */
		friend bool operator==(const Position&, const Position&);
		/**
		 * @brief std::ostream output operator
		 *
		 * Puts string representation of position to 
		 * std::ostream.
		 * @return called std::ostream object
		 * @sa str()
		 */
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
		virtual void apply(int mode = 0);
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
	Board* p_board = nullptr;
	std::size_t p_movesMade = 0;
	std::size_t p_turnIndex = 0;
public:
	Color color() const { return p_color; };
	Color setColor(Color);
	const Position& position() const { return p_position; };
	Position& position() { return p_position; };
	Position setPosition(const Position&);
	virtual Position move(const Position&);
	virtual TurnMap moveMap(int mode = 0) const = 0;
	const Board* chessboard() const { return p_board; };
	Board* chessboard() { return p_board; };
	Board* setChessboard(Board*);
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
class Board : private BoardT {
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
	Board();
	Board(PieceSetT&);

	Board(Board&&) = default;
	Board& operator=(Board&&) = default;
	Board(const Board&) = delete;
	Board& operator=(const Board&) = delete;
public:
	Piece::Color currentTurn() const {
		return b_currentTurnColor; 
	};
	virtual Piece::Color setCurrentTurn(Piece::Color);
	virtual Piece::TurnMap possibleMoves(const Piece*) const;
	Piece::TurnMap possibleMoves(const Piece::Position&) const;
	virtual const Piece::Turn* makeTurn(const Piece::Position&, 
														 const Piece::Position&) = 0;
protected:
	Piece::TurnMap produceTurn(const Piece::Position&,
													const Piece::Position&, Piece::Turn**);
	const Piece::Turn* applyTurn(Piece::Turn*);
public:
	const BoardT& board() const { return static_cast<const BoardT&>(*this); };
	BoardT& board() { return static_cast<BoardT&>(*this); };
	HistoryT& history() { return b_history; };
	const HistoryT& history() const { return b_history; };
	std::size_t movesMade() const { return b_history.size(); }
	std::size_t turnIndex() const { return b_turnIndex; };

	virtual Piece* insertPiece(Piece*);
	virtual void clear();
	void fill();
	void fill(PieceSetT& set);
	void fill(const std::string&);
	template<class Iterator>
	void fill(Iterator, Iterator);
	void fill(std::initializer_list<const std::string>);
	virtual PieceSetT defaultPieceSet() const = 0;
	void refill() { clear(); fill(); };

	virtual bool isEqual(const Board&) const = 0;
	friend bool operator==(const Board&, const Board&);
	friend bool operator!=(const Board&, const Board&);
	Piece*& operator[](const Piece::Position&);
	const Piece* operator[](const Piece::Position&) const;
	Piece*& at(const Piece::Position&);
	const Piece* at(const Piece::Position&) const;
	using BoardT::iterator;
	using BoardT::const_iterator;
	using BoardT::begin;
	using BoardT::end;
	void setPieceGetter(PieceGetterT g) { b_pieceGetter = g; };
	PieceGetterT& pieceGetter() { return b_pieceGetter; };
	PieceTypesRetT getPieceType(PieceTypesArgT);
	const PieceGetterT& pieceGetter() const  { return b_pieceGetter; };
	virtual std::string str() const = 0;
	friend std::ostream& operator<<(std::ostream&, const Board&);
	~Board();
public:
	PieceSetT set(const std::string&) const;
	template<class Iterator>
	PieceSetT set(Iterator, Iterator) const;
	virtual Piece* piece(const std::string&) const = 0;
private:
	void fillBoardWithNullptrs();
protected:
	Piece::Color b_currentTurnColor = Piece::Color::White;
	CapturedT b_capturedPieces;
	HistoryT b_history;
	PieceGetterT b_pieceGetter;
	std::size_t b_turnIndex = 0;
};

}

#endif // !_TARTAN_HPP_
