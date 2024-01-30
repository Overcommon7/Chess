#pragma once
#include "Player/Team.h"

class Piece
{
public:
	enum class Type
	{
		Pawn,
		Rook,
		Bishop,
		Knight,
		Queen,
		King
	};
public:
	Rectangle Collider();
	Vector2 GetScreenSpacePosition();
	Vector2Int GetGridPosition();
	Team GetTeam() const { return mTeam; }
	Type GetType() const { return mType; }
	virtual void MoveTo(Vector2Int gridPosition);
	void SetPosition(Vector2Int gridPosition);
	void Draw() const;


	void SetSelected(bool selected) { mIsSelected = selected; }
	void SetCaptured(bool captured) { mIsCaptured = captured; }
	bool IsSelected() const { return mIsSelected; }
	bool IsCaptured() { return mIsCaptured; }

	virtual vector<Vector2Int> GetPotentialMoves(const vector<unique_ptr<Piece>>& yourPieces, const vector<unique_ptr<Piece>>& otherPieces) = 0;
	
	Piece(Type type, Team color, Vector2Int gridPosition);

public:
	static void StaticInitialize(const fs::path& texturesDirectory);
	static void StaticTerminate();
	static Vector2 ToScreenPosition(Vector2Int gridPosition);
	static Vector2Int ToGridPosition(Vector2 screenPosition);

	static bool IsPiecePosition(const vector<unique_ptr<Piece>>& pieces, Vector2Int position);
protected:
	const Texture2D mTexture;
	const Type mType;
	const Team mTeam;
	Vector2 mPosition;
	Vector2Int mGridPosition;
	bool mIsSelected;
	bool mIsCaptured;

	constexpr Color GetColor() const { return mTeam == Team::Black ? DARKGRAY : WHITE; }
	virtual void RemoveInvalidPositions(const vector<unique_ptr<Piece>>& yourPieces, vector<Vector2Int>& moves);
	
private:
	inline static unordered_map<Type, Texture2D> sTextures;

	
public:

	Piece(const Piece& p) = delete;
	Piece(const Piece&& p) = delete;
	Piece& operator=(const Piece& p) = delete;
	Piece& operator=(const Piece&& p) = delete;
};

