#ifndef _TARTAN_CHESS_HPP_
#define _TARTAN_CHESS_HPP_

#include <tartan/board.hpp>

namespace tt::chess {

class King;

class Chessboard : public Board {
public:
	using Board::Board;
	virtual const Piece::Turn* makeTurn(const Piece::Position&, const Piece::Position&) override;
	virtual Piece* piece(const std::string& spec) const override;
	virtual Piece* insertPiece(Piece*) override;
	virtual void clear() override;
	virtual bool isEqual(const Board&) const override;
	virtual std::string str() const override;
	virtual Piece::Color setCurrentTurn(Piece::Color) override;
	virtual Piece::TurnMap possibleMoves(const Piece*) const override;
	using Board::possibleMoves;

	const King* whiteKing() const { return c_whiteKing; };
	King* whiteKing() { return c_whiteKing; };
	const King* blackKing() const { return c_blackKing; };
	King* blackKing() { return c_blackKing; };
	King* currentKing() { return c_currentKing; };
	const King* currentKing() const { return c_currentKing; };
	const King* currentEnemyKing() const { return c_currentEnemyKing; };
	King* currentEnemyKing() { return c_currentEnemyKing; };
	PieceSetT defaultPieceSet() const override;
protected:
	King* c_whiteKing = nullptr;
	King* c_blackKing = nullptr;
	King* c_currentKing = nullptr;
	King* c_currentEnemyKing = nullptr;
private:
	void markChecks(Piece::TurnMap&) const;
};

class Pawn : public Piece {
public: 
	using Piece::Piece;
	virtual TurnMap moveMap(bool) const override;
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
};

}

#endif // !_TARTAN_CHESS_HPP_
