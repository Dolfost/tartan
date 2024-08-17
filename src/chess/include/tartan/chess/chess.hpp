#ifndef _TARTAN_CHESS_HPP_
#define _TARTAN_CHESS_HPP_

#include <tartan/board.hpp>

//! Chess game namespace
namespace tt::chess {

class King;

/**
 * @brief Chess game board
 *
 * This class implements tt::Board pure virtual fucntions
 * and builds up the famous chess game. The game rules
 * which this class implements are described at
 * @cite chessWiki.
 *
 * Class exceptions are described in 
 * tartan/chess/exceptions.hpp.
 */
class Chessboard : public Board {
public:
	using Board::Board;
	/**
	 * @brief Make turn on Chessboard
	 *
	 * Function calls the Board::produceTurn() function, 
	 * then it validates for the checks with markChecks(). If 
	 * the move cannot be performed, corresponding exception 
	 * is thrown.
	 *
	 * @param from Position at which the moving Piece is located.
	 * @param to Position at which moving Piece will end up
	 * @return applied Piece::Turn object if everything went okay
	 * @exception ex::check if c_currentKing King::check()
	 * will return `true` after this move.
	 * @exception ex::checkmate if c_currentKing is under checkmate.
	 */
	virtual const Piece::Turn* makeTurn(const Piece::Position& from, 
																		 const Piece::Position& to) override;
	/**
	 * @copybrief tt::Board::piece()
	 *
	 * The `spec` has following syntax:
	 * ```
	 * <p><pos>
	 * ```
	 * where `<p>` is a piece type character, and `<pos>` is it's 
	 * Position. If the `<p>` character is uppercase, Piece::p_color
	 * property will be set to Piece::Color::White. Else if the 
	 * `<p>` is lowercase, the resulting Piece::p_color will 
	 * be set to Piece::Color::Black. The `<pos>` part describes
	 * the Piece object position on the board. `<pos>` orphographic
	 * conventions are the same as for 
	 * tt::Piece::Position(const std::string&) argument.
	 *
	 * String specificators examples:
	 * `spec` | Returned object
	 * :-----:|:---------------
	 * pd4    | new tt::chess::Pawn("d4", tt::Piece::Color::Black);
	 * Kh7    | new tt::chess::King("h7", tt::Piece::Color::White);
	 * bc1    | new tt::chess::Bishop("c1", tt::Piece::Color::Black);
	 * Rg2    | new tt::chess::Rook("g2", tt::Piece::Color::White);
	 *
	 * @param spec string represeantation of chess Piece
	 * @return newly allocated Piece object that corresponds to 
	 * `spec` description
	 */
	virtual Piece* piece(const std::string& spec) const override;
	/**
	 * @copybrief Board::canInsert()
	 *
	 * Checks if the inserted Piece is a King object. 
	 * If it is, then checks that Chessboard does not
	 * already have a King of that color.
	 *
	 * @copydetails Board::canInsert()
	 * @exception ex::duplicate_king inserted King witch such
	 * color already present
	 */
	virtual Piece* canInsert(Piece* p) const override;
	/**
	 * @copybrief tt::Board::insertPiece()
	 *
	 * Calls the canInsert(), if it does not throw 
	 * any exceptions, then it sets the c_whiteKing or 
	 * c_blackKing and c_currentKing 
	 * with c_currentEnemyKing Piece.
	 *
	 * @param p inserted Piece object
	 * @return inserted piece object
	 * @exception ex::duplicate_king `p` is a King object 
	 * of color and king of that color already been set
	 */
	virtual Piece* insertPiece(Piece* p) override;
	/**
	 * @brief Clear current Chessboard
	 *
	 * Resets the c_currentEnemyKing,
	 * c_currentKing, c_blackKing,
	 * c_whiteKing. 
	 * @copydetails Board::clear()
	 */
	virtual void clear() override;
	/**
	 * @copydoc Board::isEqual()
	 */
	virtual bool isEqual(const Board&) const override;
	/**
	 * @brief String represeantation of current
	 * Chessboard
	 *
	 * @return string with Chessboard and it's 
	 * pieces
	 */
	virtual std::string str() const override;
	/**
	 * @copybrief Board::setCurrentTurn()
	 *
	 * Selects proper c_currentKing, c_currentEnemyKing.
	 * @copydetails Board::setCurrentTurn()
	 */
	virtual Piece::Color setCurrentTurn(Piece::Color) override;
	/**
	 * @copybrief Board::possibleMoves(const Piece*) const
	 *
	 * Marks moves that lead to checks with markChecks().
	 * @copydetails Board::possibleMoves(const Piece*) const
	 */
	virtual Piece::TurnMap possibleMoves(const Piece*) const override;
	using Board::possibleMoves;

	/**
	 * @brief Current White King
	 *
	 * @return current white King object
	 * @sa c_whiteKing
	 */
	const King* whiteKing() const { return c_whiteKing; };
	/**
	 * @copydoc whiteKing() const
	 */
	King* whiteKing() { return c_whiteKing; };
	/**
	 * @brief Current Black King
	 *
	 * @return current black King object
	 * @sa c_blackKing
	 */
	const King* blackKing() const { return c_blackKing; };
	/**
	 * @copydoc blackKing() const
	 */
	King* blackKing() { return c_blackKing; };
	/**
	 * @brief King that has the color of currentTurn()
	 *
	 * @return current King object
	 */
	King* currentKing() { return c_currentKing; };
	/**
	 * @copydoc currentKing()
	 */
	const King* currentKing() const { return c_currentKing; };
	/**
	 * @brief King that has the color opposite to currentTurn()
	 *
	 * @return current enemy King object
	 * @sa c_currentEnemyKing
	 * @sa c_currentKing
	 */
	const King* currentEnemyKing() const { return c_currentEnemyKing; };
	/**
	 * @copydoc currentEnemyKing() const
	 */
	King* currentEnemyKing() { return c_currentEnemyKing; };
	/**
	 * @brief Get default chessboard Piece set
	 *
	 * Set contains the next:
	 * Piece | Position | Color
	 * :-----|:--------:|-----:
	 * Rook  |   a1     | White
	 * Knight|   b1     | White
	 * Bishop|   c1     | White
	 * Queen |   d1     | White
	 * King  |   e1     | White
	 * Bishop|   f1     | White
	 * Knight|   g1     | White
	 * Rook  |   h1     | White
	 * Pawn  |   a2     | White
	 * Pawn  |   b2     | White
	 * Pawn  |   c2     | White
	 * Pawn  |   d2     | White
	 * Pawn  |   e2     | White
	 * Pawn  |   f2     | White
	 * Pawn  |   g2     | White
	 * Pawn  |   h2     | White
	 * Rook  |   a8     | Black
	 * Knight|   b8     | Black
	 * Bishop|   c8     | Black
	 * Queen |   d8     | Black
	 * King  |   e8     | Black
	 * Bishop|   f8     | Black
	 * Knight|   g8     | Black
	 * Rook  |   h8     | Black
	 * Pawn  |   a7     | Black
	 * Pawn  |   b7     | Black
	 * Pawn  |   c7     | Black
	 * Pawn  |   d7     | Black
	 * Pawn  |   e7     | Black
	 * Pawn  |   f7     | Black
	 * Pawn  |   g7     | Black
	 * Pawn  |   h7     | Black
	 *
	 * @return default Chessboard Piece set
	 */
	PieceSetT defaultPieceSet() const override;
	/**
	 * @brief Modes to use with Turn::apply 
	 * and Piece::moveMap
	 *
	 * This is used by markChecks().
	 */
	enum Mode : int { 
		DefaultMode = 0, //!< Default mode. Act as usual
		/** 
		 * @brief Apply the turn or produce moveMap as
		 * performing the validation for King check
		 *
		 * This is used to counter infinite recursion in 
		 * King movemap when trying to figure
		 * out should it perform castling or not.
		 *
		 * Also the Pawn promption move uses it to 
		 * not promote pawn and just move it to the 
		 * top of board, because when checking for King 
		 * checks we don't care about exchange piece type.
		 */
		CheckingMode = 1,
	};
protected:
	/**
	 * @brief Marks Tunr objects that 
	 * will put current King in check
	 *
	 * @param[in,out] map input TurnMap of Turn objects
	 * to check if they lead to check
	 */
	void markChecks(Piece::TurnMap& map) const;
protected:
	/**
	 * @brief White King object 
	 *
	 * @sa whiteKing()
	 */
	King* c_whiteKing = nullptr;
	/**
	 * @brief Black King object 
	 *
	 * @sa blackKing()
	 */
	King* c_blackKing = nullptr;
	/**
	 * @brief Current King object 
	 *
	 * King object that will make next Turn.
	 *
	 * @sa currentKing()
	 */
	King* c_currentKing = nullptr;
	/**
	 * @brief Current enemy King object 
	 *
	 * opposite to currentKing().
	 * King object that will make Turn after 
	 * the currentKing().
	 *
	 * @sa currentEnemyKing()
	 */
	King* c_currentEnemyKing = nullptr;
};

class Pawn : public Piece {
public: 
	using Piece::Piece;
	virtual TurnMap moveMap(int = 0) const override;
	class Turn : public Piece::Turn {
	public:
		using Piece::Turn::Turn;
	private:
		std::type_index t_promoteTo = typeid(nullptr);
	public:
		bool isEqual(const Piece::Turn &) const override;
		virtual void apply(int mode = 0) override;
		const std::type_index& promoteTo() const { return t_promoteTo; };
	};
};

class Knight : public Piece {
public: 
	using Piece::Piece;
	virtual TurnMap moveMap(int mode = 0) const override;
	class Turn : public Piece::Turn {
	public:
		using Piece::Turn::Turn;
	public:
		bool isEqual(const Piece::Turn &) const override;
	};
};

class Bishop : public Piece {
public: 
	using Piece::Piece;
	virtual TurnMap moveMap(int mode = 0) const override;
	class Turn : public Piece::Turn {
	public:
		using Piece::Turn::Turn;
	public:
		bool isEqual(const Piece::Turn &) const override;
	};
};

class Rook : public Piece {
public: 
	using Piece::Piece;
	virtual TurnMap moveMap(int mode = 0) const override;
	class Turn : public Piece::Turn {
	public:
		using Piece::Turn::Turn;
	public:
		bool isEqual(const Piece::Turn &) const override;
	};
};

class Queen : public Piece {
public: 
	using Piece::Piece;
	virtual TurnMap moveMap(int mode = 0) const override;
	class Turn : public Piece::Turn {
	public:
		using Piece::Turn::Turn;
	public:
		bool isEqual(const Piece::Turn &) const override;
	};
};

class King : public Piece {
public: 
	using Piece::Piece;
	virtual TurnMap moveMap(int mode = 0) const override;
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
		virtual void apply(int mode = 0) override;
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
};

}

#endif // !_TARTAN_CHESS_HPP_
