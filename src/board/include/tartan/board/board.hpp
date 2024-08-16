#ifndef _TARTAN_HPP_
#define _TARTAN_HPP_

#include <array>
#include <forward_list>
#include <list>
#include <ostream>
#include <typeindex>
#include <functional>
#include <initializer_list>

//! Tartan library namespace
namespace tt {

class Board;

/**
 * @brief Generic board memeber piece API.
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
	 * @brief Piece position at the Board.
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
	/**
	 * @class Turn
	 * @brief Generic Piece Turn on Board
	 *
	 * Class should be defined as derived from Piece::Turn in every class
	 * derives from Piece.
	 */
	class Turn {
	public:
		/**
		 * @brief Construct new Turn object
		 *
		 * @param tpiece turn piece. Piece that performs turn
		 * @param to final location. Location where the `tpiece` 
		 * will end up after the turn is applied
		 * @param cap captured Piece. Should be provided if 
		 * turn captures some pieces
		 * @param possible `true`, if turn is possible, false otherwise
		 */
		Turn(const Piece* tpiece, 
			 const Position& to, 
			 const Piece* cap = nullptr, 
			 bool possible = true);
		/**
		 * @brief Position where piece will end up
		 * after turn
		 *
		 * @return starting turn position
		 */
		Position to() const { return t_to; };
		/**
		 * @brief Position the turn is started at
		 *
		 * @return target turn position
		 */
		Position from() const { return t_from; };
		/**
		 * @brief Turn Piece 
		 *
		 * @return piece whose turn current object describes
		 */
		const Piece* piece() const { return t_piece; };
		/**
		 * @copydoc piece() const
		 */
		Piece* piece() { return t_piece; };
		/**
		 * @brief Captured piece
		 *
		 * @return piece that turn will be 
		 * captured when turn is applied
		 */
		const Piece* capture() const { return t_capture; };
		/**
		 * @copydoc capture() const
		 */
		Piece* capture() { return t_capture; };
		/**
		 * @brief Turn viability
		 *
		 * @return `true`, if turn is possible, false otherwise
		 */
		bool possible() const { return t_possible; };
		/**
		 * @brief Set the turn viability
		 *
		 * @param c new viability value
		 * @return old viability value
		 */
		bool setPossible(bool c) { return !(t_possible = c); };
		/**
		 * @brief String Turn representation
		 *
		 * This function may be redefined in 
		 * Piece::Turn that inherit from Piece 
		 * depending on new piece implementation
		 *
		 * @return string representation of current 
		 * Turn object
		 */
		virtual std::string str() const;
		/**
		 * @brief Apply turn
		 * 
		 * Applies current turn. Should be reimplemented 
		 * in child Piece class if it have to do something
		 * special on move. 
		 *
		 * This does the next:
		 * - erase capture() from piece() Board 
		 * - move the piece() to to()
		 *
		 * You can define unscoped enum and use it
		 * with this fucntion to perform different 
		 * applying logic on demand. 
		 *
		 * @param mode optional apply mode parameter
		 */
		virtual void apply(int mode = 0);
		/**
		 * @brief Undo turn
		 *
		 * Opposite to apply(). Should be reimplemented
		 * in child Piece class if it's apply() function 
		 * does something special on applying.
		 */
		virtual void undo();
		/**
		 * @brief Compare turns
		 *
		 * Should be reimplemented
		 * in child Piece class if
		 * it's Turn logic differs.
		 *
		 * @param rhs Turn object compare to
		 * @return `true` if `rhs` turn is the same as 
		 * current object
		 */
		virtual bool isEqual(const Turn& rhs) const;
		/**
		 * @brief Comparison operator
		 *
		 * @param lhs left object of `==` operator
		 * @param rhs right object of `==` operator
		 * @return the value of lhs.isEqual(rhs)
		 * @sa isEqual()
		 */
		friend bool operator==(const Turn& lhs, const Turn& rhs);
		/**
		 * @brief Inverted comparison operator
		 *
		 * @param lhs left object of `==` operator
		 * @param rhs right object of `==` operator
		 * @return the value of !lhs.isEqual(rhs)
		 * @sa isEqual()
		 */
		friend bool operator!=(const Turn&, const Turn&);
		/**
		 * @brief std::ostream output
		 *
		 * Puts the `t.str()` in `os` object
		 *
		 * @param os invoking `std::ostream` object
		 * @param t Turn object for writting
		 * @return invoking `std::ostream` `os` object
		 */
		friend std::ostream& operator<<(std::ostream& os, const Turn& t);
		/**
		 * @brief Clone current Turn
		 *
		 * @return pointer to new memory with Turn 
		 * object indentical to invoking object
		 */
		virtual auto clone() const -> std::decay<decltype(*this)>::type*;
		virtual ~Turn() = default;
	protected:
		//! %Turn piece starting position
		Position t_from;
		//! %Turn piece finishing position
		Position t_to;
		//! %Turn Piece inself
		Piece* t_piece;
		//! Piece that is captured as the resul of turn
		Piece* t_capture;
		//! Turn viability
		bool t_possible;
	};
	/**
	 * @class TurnMap
	 * @brief List of Turn objects
	 */
	class TurnMap : public std::list<Turn*> {
	public:
		using std::list<Turn*>::list;
		//! Copy constructor
		TurnMap(const TurnMap&);
		//! Move constructor
		TurnMap(TurnMap&&);
		//! Copy assignment operator
		TurnMap& operator=(const TurnMap& other);
		//! Move assignment operator
		TurnMap& operator=(TurnMap&& other);
		/**
		 * @brief Viability of TurnMap
		 *
		 * @return `true` if every member of current object
		 * Turn::possible() method returns `true`, `false` otherwise
		 */
		bool possible() const;
		~TurnMap();
		/**
		 * @brief Comparison operator
		 *
		 * @return `true` if every Turn object of `lhs`
		 * is equal to every corresponding object in `rhs`, 
		 * `false` otherwise
		 */
		friend bool operator==(const TurnMap& lhs, const TurnMap& rhs);
		/**
		 * @brief Inverted comparison operator
		 *
		 * @return `lhs` if every Turn object of `lhs`
		 * is equal to every corresponding object in `rhs`
		 * `true` otherwise
		 */
		friend bool operator!=(const TurnMap& lhs, const TurnMap& rhs);
	};
protected:
	/**
	 * @brief Piece color
	 * @sa color(), setColor()
	 */
	Color p_color;
	/**
	 * @brief Piece Position
	 * @sa position(), setPosition()
	 */
	Position p_position;
	/**
	 * @brief Piece Board 
	 *
	 * Board, to which current piece belongs to
	 * @sa board()
	 */
	Board* p_board = nullptr;
	/**
	 * @brief Turns count
	 * Count of turns Piece have made
	 */
	std::size_t p_movesMade = 0;
	/**
	 * @brief Last turn index
	 *
	 * Board::turnIndex() value at the moment when 
	 * Piece performed some Turn
	 */
	std::size_t p_turnIndex = 0;
public:
	/**
	 * @brief Piece color
	 *
	 * @return current Piece color value
	 */
	Color color() const { return p_color; };
	/**
	 * @brief Set the color
	 *
	 * @param col new Piece color value
	 * @return old color value
	 * @sa Color, p_color
	 */
	Color setColor(Color col);
	/**
	 * @brief Piece Position
	 *
	 * @return current Piece position
	 * @sa Position, p_position
	 */
	const Position& position() const { return p_position; };
	/**
	 * @copydoc position() const
	 */
	Position& position() { return p_position; };
	/**
	 * @brief Set Piece position
	 *
	 * @return old Position value
	 * @sa Position, p_position
	 */
	Position setPosition(const Position&);
	/**
	 * @brief Move piece
	 *
	 * Changes the position() value, 
	 * uses board() interface to move piece
	 * to new location at the underlying Board.
	 *
	 * @param to new Position value
	 * @return old Position vlaue
	 */
	virtual Position move(const Position& to);
	/**
	 * @brief Generic moves
	 *
	 * @note Developer had and intention 
	 * that You will define unscoped enumeration for `mode`
	 * in Your Board class. It's value will be passe 
	 * to function and influence
	 * it's behaivor in some way.
	 *
	 * @param mode optional mode constant to influence 
	 * the moveMap() behaivor in child classes. 	 
	 * @return TurnMap object filled with Turn objects.
	 * May not contain turns that are not possible because 
	 * of piece placement
	 */
	virtual TurnMap moveMap(int mode = 0) const = 0;
	/**
	 * @brief Piece board
	 *
	 * @return Board to which current Piece belongs
	 */
	const Board* board() const { return p_board; };
	/**
	 * @copydoc board() const
	 */
	Board* board() { return p_board; };
	/**
	 * @brief Set Piece Board
	 *
	 * @param b new Board
	 * @return old board
	 * @sa p_board
	 */
	Board* setBoard(Board* b);
	/**
	 * @brief Moves count
	 *
	 * @return total count of moves Piece has made
	 * @sa p_movesMade
	 */
	std::size_t movesMade() const { return p_movesMade; }
	/**
	 * @brief Current turn index
	 *
	 * @return turn index of board() when current piece were 
	 * performing it's move
	 * @sa p_turnIndex
	 */
	std::size_t turnIndex() const { return p_turnIndex; }
public:
	/**
	 * @brief Construct diagonal moves TurnMap
	 *
	 * Constructs new TurnMap object
	 * where the TurnMap::piece() is set to `p`.
	 * It is defined that piece that performs 
	 * moves can not step on or over other Piece objects
	 * at the Board.
	 *
	 * @return TurnMap object with `p` as turn piece
	 */
	static TurnMap diagonalMoves(const Piece* p);
	/**
	 * @brief Construct straight moves (up, down, left, right) TurnMap
	 * @copydetails diagonalMoves()
	 */
	static TurnMap straightMoves(const Piece* p);
public:
	/**
	 * @brief Construct new Piece
	 *
	 * @param pos Piece Position
	 * @param col Piece Color
	 * @sa color(), position()
	 */
	Piece(const Position& pos = {1,1}, Color col = Color::White);
	virtual ~Piece() = default;
};

//! Underlying Board grid representation type
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
