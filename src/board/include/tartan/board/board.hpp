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
	 * @brief Piece position at the Board.
	 */
	class Position {
	public:
		/**
		 * @brief Boolean functions operation mode.
		 *
		 * Describes location of the coordinates origin.
		 * @sa atTop(), atLeft(), atRight(), atBottom(),
		 * offset(), setMode(), mode()
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
		 */
		Position(int x, int y);
		/**
		 * @brief Create Position object with coordinates `ld` (eq. `b3`) 
		 *
		 * @param l letter x coordinate
		 * @param d digit y coordinate
		 */
		Position(char l, int d);
		/**
		 * @brief Creates Position object at `str` position
		 *
		 * The `str` arguments has the form of 
		 * ```
		 * <x><y>
		 * ```
		 * where the `<x>` is the lowercase letter in range 
		 * a-h inclusive, `<y>` is a number from range [1;8].
		 *
		 * Table for `<x>` letter-to-digit mapping
		 * Letter | Digit
		 * :-----:|:----:
		 * `a`    | `1`
		 * `b`    | `2`
		 * `c`    | `3`
		 * `d`    | `4`
		 * `e`    | `5`
		 * `f`    | `6`
		 * `g`    | `7`
		 * `h`    | `8`
		 *
		 * Example arguments: 
		 * Argument | x() | y() 
		 * :--------|:---:|:---: 
		 * `"d4"`   |  4  |  4
		 * `"e7"`   |  5  |  7
		 * `"h3"`   |  8  |  3
		 *
		 * @param str 2-character letter-digit string representation of position
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
		 * @exception std::out_of_range if `x` is < 1 or > 8
		 */
		int setX(int x);
		/**
		 * @brief Set y coordinate
		 *
		 * @param y new value
		 * @return old value
		 * @exception std::out_of_range if `y` is < 1 or > 8
		 */
		int setY(int y);
		/**
		 * @brief Set x coordinate with string representation
		 *
		 * @param x x coordinate represented as string
		 * @return old value
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
		 * @anchor posmanip
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
		 * \ref posmanip "Position manipulation" 
		 * group behave differently.
		 *
		 * @param m new offset mode value
		 * @return old offset mode value
		 */
		Mode setMode (Mode m);
		//! @}
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
		 */
		Position operator+(const Position&) const;
		/**
		 * @brief Substraction operator
		 *
		 * @return new object with difference of corresponding 
		 * coordinates of argument objects
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
		 * @copydoc offset(int, int) const
		 */
		Position operator()(int dx, int dy) const;
		/**
		 * @copydoc offset(char, int) const
		 */
		Position operator()(char dc, int dd) const;
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
/**
 * @brief 8x8 game board
 *
 * This class is used to host Piece objects 
 * and should be inherited to use. Also You have
 * reimlemtent all pure virtual methods to use 
 * the class.
 *
 * Class exceptions are described in 
 * tartan/board/exceptions.hpp.
 */
class Board : private BoardT {
	friend class Piece::Turn;
public:
	//! Type for list of captured Piece objects that no more on the board
	using CapturedT = std::forward_list<const Piece*>;
	//! Type for internal move history representation
	using HistoryT = std::list<const Piece::Turn*>;
	//! Type for representation a sequence of turns
	using TurnsT = std::list<std::pair<Piece::Position, Piece::Position>>;
	//! Type for representing set of pointers to Piece objects
	using PieceSetT = std::list<Piece*>;
	//! Type used as argument to getPieceType()
	using PieceTypesArgT = std::list<std::type_index>;
	//! Type that getPieceType() should return
	using PieceTypesRetT = std::type_index;
	//! Type of pieceGetter()
	using PieceGetterT = std::function<PieceTypesRetT(PieceTypesArgT)>;
public:
	//! Construct empty Board object
	Board();
	/**
	 * @brief Consturct empty Board object and populate it with `set`
	 *
	 * @param set set of pieces to populate the Board with
	 */
	Board(PieceSetT& set);

	//! Move constructor
	Board(Board&&) = default;
	//! Move assignment operator
	Board& operator=(Board&&) = default;
	Board(const Board&) = delete;
	Board& operator=(const Board&) = delete;
public:
	/**
	 * @brief Current turn color
	 *
	 * @return Color which have to make next turn on Board
	 */
	Piece::Color currentTurn() const {
		return b_currentTurnColor; 
	};
	/**
	 * @brief Set current turn Color
	 *
	 * Sets the b_currentTurnColor to `col`.
	 *
	 * @param col new Color value
	 */
	virtual Piece::Color setCurrentTurn(Piece::Color col);
	/**
	 * @brief Possible moves of a Piece by it's adress
	 *
	 * This function returns the final TurnMap object
	 * with all Turn members marked as possible or not,
	 * so user can see what turns they can perform. Could 
	 * be useful for GUI board games.
	 *
	 * @param p pointer to desired Piece
	 * @exception ex::null_piece if `p` is `nullptr`
	 * @exception ex::foreign_piece if `p` does not belong 
	 * to this Board object
	 * @sa possibleMoves(const Piece::Position&) const
	 */
	virtual Piece::TurnMap possibleMoves(const Piece* p) const;
	/**
	 * @brief Possible moves of a Piece by it's location 
	 * on board.
	 *
	 * This function calls the possibleMoves(const Piece*) const 
	 * after resolving the Piece object by it's position.
	 *
	 * @param pos Position of desired Piece on board
	 * @sa possibleMoves(const Piece*) const
	 */
	Piece::TurnMap possibleMoves(const Piece::Position& pos) const;
	/**
	 * @brief Make the turn 
	 *
	 * This function shall be reimplemented 
	 * in child class. It have to call produceTurn() to get 
	 * started.
	 *
	 * @param from Piece Position to move
	 * @param to Piece Position of target
	 * @return Turn object that has been applied
	 * @sa produceTurn()
	 */
	virtual const Piece::Turn* makeTurn(const Piece::Position& from, 
														 const Piece::Position& to) = 0;
protected:
	/**
	 * @brief Just places the Piece object on the Board
	 *
	 * @warning This function does not do any checks
	 * on Piece object it places. Use with care.
	 *
	 * @param p placed Piece
	 * @return `p` object pointer
	 * @sa canInsert()
	 */
	virtual Piece* placePiece(Piece* p);
	/**
	 * @brief Make Turn object based on `from` and `to`
	 *
	 * Function checks selected Piece object for empty tile,
	 * piece in wrong color, no possible moves, no moves at all.
	 * If some of the basic conditions aren't satisfied, corresponding
	 * exception is thrown. Then it makes basic Turn object 
	 * from selected Piece Piece::TurnMap. Function should be called from
	 * reimplemented makeTurn(), and alter Turn acceptance logic.
	 *
	 * @param from Piece::Position of Piece to move
	 * @param to Piece::Position to move the Piece to
	 * @param[in] turn produced Piece::Turn object pointer selected 
	 * as valid from returned TurnMap object
	 * @return TrunMap object of all possible moves
	 * @exception ex::tile_is_empty if p.position() is empty on board
	 * @exception ex::piece_in_wrong_color if `p` color does not match
	 * b_currentTurnColor.
	 * @exception ex::can_not_move `p` can not move 
	 * @exception ex::no_such_move `p` does not have such move at all.
	 */
	Piece::TurnMap produceTurn(const Piece::Position& from,
													const Piece::Position& to, Piece::Turn** turn);
	/**
	 * @brief Apply valid turn
	 *
	 * This function should describe things to do before 
	 * the Turn::apply(int) is called. Current implementation
	 * adds Turn::capture() to b_capturedPieces, then flips 
	 * b_currentTurnColor to opposite.
	 *
	 * @param turn Turn object to apply
	 */
	virtual const Piece::Turn* applyTurn(Piece::Turn* turn);
public:
	/**
	 * @brief Internal board data structure
	 * @return internal board data structure type object tt::BoardT
	 */
	const BoardT& board() const { return static_cast<const BoardT&>(*this); };
	/**
	* @copydoc board() const
	*/
	BoardT& board() { return static_cast<BoardT&>(*this); };
	/**
	 * @brief Turns history
	 *
	 * @return HistoryT data type object
	 * @sa b_history
	 */
	HistoryT& history() { return b_history; };
	/**
	* @copydoc history()
	*/
	const HistoryT& history() const { return b_history; };
	/**
	 * @brief Total count of moves made on Board
	 *
	 * @return Moves count or history().size()
	 * @sa b_history
	 */
	std::size_t movesMade() const { return b_history.size(); }
	/**
	 * @brief Turn index
	 *
	 * @return last Piece::Turn index
	 * @sa b_turnIndex
	 */
	std::size_t turnIndex() const { return b_turnIndex; };

	/**
	 * @brief Throws an exception if Piece cannot be placed 
	 * at the Board
	 *
	 * @param p checked Piece object
	 * @return `p` object
	 * @exception ex::foreign_piece if `p` belongs 
	 * to other Board already
	 * @exception ex::position_is_taken if tile 
	 * at p.position() is taken
	 */
	virtual Piece* canInsert(Piece* p) const;
	/**
	 * @brief Place piece on Board
	 *
	 * Default implementation
	 * checks if `p` can be placed on Board with 
	 * canInsert(), if it can, then it places 
	 * the `p` in the current Board object with placePiece().
	 *
	 * @note Board object takes the ownership of inserted pieces.
	 *
	 * @param p Piece pointer to insert 
	 * @return `p` pointer
	 */
	virtual Piece* insertPiece(Piece* p);
	/**
	 * @brief Clears current Board 
	 *
	 * Fills board with `nullptr`s and deletes every Piece
	 * object on the way with `delete`.
	 */
	virtual void clear();
	/**
	 * @name Fill functions 
	 * Every fill() function passes the ownership of  
	 * recieved Piece objects to underlying Board object. 
	 *
	 * Functions that take the 
	 * string Piece specialization allocates new objects
	 * with piece() function.
	 *
	 * The insertPiece() is used on each produces/recieved Piece object. 
	 * This function throws corresponding exceptions on errors.
	 *
	 * @sa insertPiece(), piece()
	 */
	//! @{
	/**
	 * @brief Fills current Board with default pieces 
	 *
	 * The default pieces is given by defaultPieceSet() function.
	 */
	void fill();
	/**
	 * @brief Fill Board with piece set
	 *
	 * Fills the board with Piece objects in `set`. 	 *
	 * @param set set of Piece objects to put on Board
	 */
	void fill(PieceSetT& set);
	/**
	 * @brief Fill Board with string 
	 * representation of Piece objects
	 *
	 * Function allocates memory for new Pieces objects
	 * and puts them on board
	 *
	 * @param str space separated set of piece specs
	 * @sa piece(), set()
	 */
	void fill(const std::string& str);
	/**
	 * @brief Fill Board from STL container of pointers to Piece objects
	 *
	 * Calls the set(const std::string) const to produce 
	 * PieceSetT, then fill(PieceSetT) to actually fill
	 * the Board.
	 *
	 * @tparam Iterator STL iterator type
	 * @param begin start of STL container
	 * @param end end of STL container
	 * @sa set(const std::string) const
	 */
	template<class Iterator>
	void fill(Iterator begin, Iterator end);
	/**
	 * @brief Fill Board from std::initializer_list<cosnt std::string> 
	 *
	 * @param arg list of string piece specs
	 * @se piece()
	 */
	void fill(std::initializer_list<const std::string> list);
	 //! Clear and fill Board with default piece set
	void refill() { clear(); fill(); };
	//! @}
	/**
	 * @brief Default piece set for the Board
	 *
	 * This function should be reimplemented 
	 * in child class to match it's game layout.
	 *
	 * @return defaultPieceSet for current Board implementation
	 */
	virtual PieceSetT defaultPieceSet() const = 0;

	/**
	 * @brief Compare 2 Board objects.
	 *
	 * @param other Board object to compare with
	 * @return `true` if corresponding tiles have equal adress
	 * or cast to same Piece type, `false` otherwise
	 */
	virtual bool isEqual(const Board& other) const = 0;
	/**
	 * @brief Equal to operator
	 *
	 * This is a bind to function `lhs.isEqua(rhs)`.
	 * @sa isEqual()
	 */
	friend bool operator==(const Board& lhs, const Board& rhs);
	/**
	 * @brief Not equal to operator
	 *
	 * This is a bind to function `!lhs.isEqua(rhs)`.
	 * @sa isEqual()
	 */
	friend bool operator!=(const Board&, const Board&);
	/**
	 * @brief Position subscript operator
	 *
	 * @param pos target Position object
	 * @return Piece object pointer at position `pos`, 
	 * `nullptr` if tile is empty.
	 * @sa at()
	 */
	Piece*& operator[](const Piece::Position& pos);
	/**
	* @copydoc operator[](const Piece::Position&)
	*/
	const Piece* operator[](const Piece::Position& pos) const;
	/**
	 * @brief Board member access by Position
	 *
	 * @copydetails operator[](const Piece::Position&)
	 */
	Piece*& at(const Piece::Position& pos);
	/**
	 * @copydoc at(const Piece::Position&)
	 */
	const Piece* at(const Piece::Position& pos) const;
	using BoardT::iterator;
	using BoardT::const_iterator;
	using BoardT::begin;
	using BoardT::end;
	/**
	 * @brief Set the Piece getter functor
	 *
	 * @param g piece getter
	 * @sa b_pieceGetter
	 */
	void setPieceGetter(PieceGetterT g) { b_pieceGetter = g; };
	/**
	 * @brief Get current piece getter functor
	 *
	 * @return current Piece getter functor
	 * @sa b_pieceGetter
	 */
	PieceGetterT& pieceGetter() { return b_pieceGetter; };
	/**
	 * @copydoc setPieceGetter(PieceGetterT)
	 */
	const PieceGetterT& pieceGetter() const  { return b_pieceGetter; };
	/**
	 * @brief Get user provided Piece std::type_index 
	 *
	 * This function calls the b_pieceGetter functor 
	 * that were set via setPieceGetter(). If b_pieceGetter
	 * were not set and this function were called, the
	 * std::runtime_error exception is thrown.
	 *
	 * @param possible STL contaier of possible types
	 * @return selected std::type_index
	 * @exception std::runtime_error if b_pieceGetter is not set.
	 * @sa b_pieceGetter, setPieceGetter()
	 */
	PieceTypesRetT getPieceType(PieceTypesArgT possible);
	/**
	 * @brief String representation of Board
	 *
	 * Useful for debugging purposes.
	 * Should be reimplemented in child class.
	 *
	 * @return string of current board state visualized
	 */
	virtual std::string str() const = 0;
	/**
	 * @brief Bitwise left shift operator on std::ostream
	 *
	 * This function puts the str() function result
	 * to `os` object with `<<` operator.
	 *
	 * @param os calling object
	 * @param b Board object for display
	 * @return calling `os` object
	 */
	friend std::ostream& operator<<(std::ostream& os, const Board& b);
	~Board();
public:
	/**
	 * @brief Produce piece set from std::string
	 *
	 * Function uses piece() to allocate actual 
	 * Pice object from std::string spec.
	 *
	 * @param str input string with space separated piece specs 
	 * @return resulting piece set
	 * @sa piece()
	 */
	PieceSetT set(const std::string& str) const;
	/**
	 * @brief Make piece set out of STL 
	 * container of std::string Piece specs
	 *
	 * @tparam Iterator STL container iterator
	 * @param begin begin iterator of STL container
	 * @param end end iterator of STL container
	 * @return resulting Piece objects set
	 */
	template<class Iterator>
	PieceSetT set(Iterator begin, Iterator end) const;
	/**
	 * @brief Convert std::string Piece spec to
	 * actual Piece object pointer
	 *
	 * This function should convert in-game std::string
	 * notation for Piece objects to actual objects.
	 *
	 * For example, in chess game the qc3 means
	 * the black Queen at c3, Qd5 means the 
	 * white Queen on d5.
	 *
	 * @param spec Piece std::string specification
	 * @return pointer to Piece object constructed from
	 * `spec` string
	 */	
	virtual Piece* piece(const std::string& spec) const = 0;
private:
	void fillBoardWithNullptrs();
protected:
	/**
	 * @brief Current turn color variable
	 * @sa currentTurn()
	 */
	Piece::Color b_currentTurnColor = Piece::Color::White;
	/**
	 * @brief List of captured pieces
	 *
	 * Pieces that have retired and have been removed from 
	 * Board should go to this list. The default applyTurn()
	 * function does that if turn catures something.
	 */
	CapturedT b_capturedPieces;
	/**
	 * @brief Board history of applied Turn objects
	 *
	 * All turn objects that have been passed to 
	 * applyTurn() function go to that list by default 
	 * with help of Turn::clone().
	 * @sa history(), HistoryT
	 */
	HistoryT b_history;
	/**
	 * @brief Piece getter variable
	 *
	 * This variable keeps the functor for getting the 
	 * new user-reuqested Piece std::type_index.
	 *
	 * This could be useful for example in chess game, when
	 * pawn reaches the end of the board and player 
	 * have to choose the piece to exchange it for.
	 */
	PieceGetterT b_pieceGetter;
	/**
	 * @brief Current turn index 
	 *
	 * This varriable is incremented each time 
	 * the Turn::apply() is called on Piece 
	 * that belongs to current Board object.
	 */
	std::size_t b_turnIndex = 0;
};

}

#endif // !_TARTAN_HPP_
