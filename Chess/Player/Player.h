#pragma once
#include "Pieces/Piece.h"

class King;

class Player
{
public:
	bool Update(float deltaTime, const vector<unique_ptr<Piece>>& otherPieces);
	void Draw(const vector<unique_ptr<Piece>>& otherPieces) const;
	void LateDraw(const vector<unique_ptr<Piece>>& otherPieces) const;

	void SetTurn(bool isTurn) { mIsTurn = isTurn; }
	bool IsTurn() { return mIsTurn; }
	bool HasLost() const { return mHasLost; }

	void OnTurnBegin(const vector<unique_ptr<Piece>>& otherPieces);

	Player(Team team);
	~Player();
private:
	friend class PlayerManager;

	vector<unique_ptr<Piece>> mPieces;
	vector<Vector2Int> currentMoves;
	Piece* mSelectedPiece;
	King* king;
	bool mIsTurn;
	const Team mTeam;
	bool mInCheck;
	bool mHasLost;

	void RemoveMovesThatCheck(const vector<unique_ptr<Piece>>& otherPieces, vector<Vector2Int>& moves, const unique_ptr<Piece>& piece);
	static Piece* TryGetPiece(const vector<unique_ptr<Piece>>& pieces, Vector2Int position);
public:
	Player(const Player& p) = delete;
	Player(const Player&& p) = delete;
	Player& operator=(const Player& p) = delete;
	Player& operator=(const Player&& p) = delete;

};

