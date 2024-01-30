#include "pch.h"
#include "Player.h"

#include "Pieces/Bishop.h"
#include "Pieces/King.h"
#include "Pieces/Knight.h"
#include "Pieces/Pawn.h"
#include "Pieces/Queen.h"
#include "Pieces/Rook.h"

namespace
{
	constexpr int NUM_OF_PAWNS = 8;
	constexpr int NUM_OF_ROOKS = 2;
	constexpr int NUM_OF_BISHOPS = 2;
	constexpr int NUM_OF_KNIGHTS = 2;
	constexpr int NUM_OF_QUEENS = 1;
	constexpr int NUM_OF_KINGS = 1;

	constexpr int TOTAL_PIECES =
		NUM_OF_PAWNS +
		NUM_OF_ROOKS +
		NUM_OF_BISHOPS +
		NUM_OF_KNIGHTS +
		NUM_OF_QUEENS +
		NUM_OF_KINGS;
}

bool Player::Update(float deltaTime, const vector<unique_ptr<Piece>>& otherPieces)
{
	if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		return false;

	if (!mIsTurn)
		return false;

	Vector2 mousePosition = GetMousePosition();
	for (const auto& piece : mPieces)
	{
		if (!CheckCollisionPointRec(mousePosition, piece->Collider())) 
			continue;

		piece->SetSelected(!piece->IsSelected());

		if (mSelectedPiece)
			mSelectedPiece->SetSelected(false);

		if (piece->IsSelected())
		{
			mSelectedPiece = piece.get();
			currentMoves = mSelectedPiece->GetPotentialMoves(mPieces, otherPieces);
			RemoveMovesThatCheck(otherPieces, currentMoves, piece);
		}	
		else
		{
			mSelectedPiece = nullptr;
			currentMoves.clear();
		}
			

		return false;		
	}

	if (!mSelectedPiece)	
		return false;



	for (auto position : currentMoves)
	{
		Vector2 screenPosition = Piece::ToScreenPosition(position);
		auto tile = Rectangle(screenPosition.x, screenPosition.y, TILE_SIZE, TILE_SIZE);
		if (!CheckCollisionPointRec(mousePosition, tile)) 
			continue;

		auto capturedPiece = TryGetPiece(otherPieces, position);
		if (capturedPiece != nullptr)
			capturedPiece->SetCaptured(true);

		mSelectedPiece->MoveTo(position);
		mSelectedPiece->SetSelected(false);
		mSelectedPiece = nullptr;
		return true;
	}

	return false;
}

void Player::Draw(const vector<unique_ptr<Piece>>& otherPieces) const
{
	for (const auto& piece : mPieces)
	{
		piece->Draw();
    }
}

void Player::LateDraw(const vector<unique_ptr<Piece>>& otherPieces) const
{
	if (!mIsTurn) return;
	if (!mSelectedPiece) return;

	constexpr Color regular = { 120, 120, 120, 120 };
	constexpr Color take = { 255, 161, 0, 120 };

	for (auto position : currentMoves)
	{
		auto screenPosition = Vector2AddValue(Piece::ToScreenPosition(position), 50);
		bool isTake = mSelectedPiece->IsPiecePosition(otherPieces, position);

		DrawCircle(screenPosition.x, screenPosition.y, 10.f, isTake ? take : regular);
	}
}

void Player::OnTurnBegin(const vector<unique_ptr<Piece>>& otherPieces)
{
	if (king->IsCaptured())
	{
		mHasLost = true;
		return;
	}

	mInCheck = king->IsCheck(mPieces, otherPieces);

	auto it = mPieces.begin();
	
	while (it != mPieces.end())
	{
		if ((*it)->IsCaptured())
			it = mPieces.erase(it);
		else ++it;
	}

	if (mPieces.size() == 1)
	{
		mHasLost = true;
		return;
	}

	if (!mInCheck) return;

	for (auto& piece : mPieces)
	{
		auto potentialMoves = piece->GetPotentialMoves(mPieces, otherPieces);
		RemoveMovesThatCheck(otherPieces, potentialMoves, piece);
		if (!potentialMoves.empty())
			return;
	}

	mHasLost = true;
}

Player::Player(Team team)
	: mSelectedPiece(nullptr)
	, mTeam(team)
	, mIsTurn(false)
	, mHasLost(false)
	, mInCheck(false)
{
	Vector2Int gridPosition = 
		(team == Team::Black) ? 
		Vector2Int(0, 1) : Vector2Int(0, 6);

	//Place Row Of Pawns
	for (gridPosition.x = 0; gridPosition.x < NUM_OF_PAWNS; ++gridPosition.x)
	{
		mPieces.emplace_back(new Pawn(team, gridPosition));
	}
	
	//Go To Second Row Depending On Team Color
	if (team == Team::Black)
		gridPosition.y = 0;
	else
		gridPosition.y = 7;
	
	//Place Rooks
	{
		gridPosition.x = 7;
		mPieces.emplace_back(new Rook(team, gridPosition));
		gridPosition.x = 0;
		mPieces.emplace_back(new Rook(team, gridPosition));
	}

	//Place Knights
	{
		gridPosition.x = 6;
		mPieces.emplace_back(new Knight(team, gridPosition));
		gridPosition.x = 1;
		mPieces.emplace_back(new Knight(team, gridPosition));
	}

	//Place Bishops
	{
		gridPosition.x = 5;
		mPieces.emplace_back(new Bishop(team, gridPosition));
		gridPosition.x = 2;
		mPieces.emplace_back(new Bishop(team, gridPosition));
	}

	//Place Royalty
	{
		gridPosition.x = (team == Team::Black) ? 3 : 4;
		mPieces.emplace_back(new Queen(team, gridPosition));

		gridPosition.x = (team == Team::Black) ? 4 : 3;
		king = new King(team, gridPosition);
		mPieces.emplace_back(king);
	}
}

Player::~Player()
{
	mSelectedPiece = nullptr;
}

void Player::RemoveMovesThatCheck(const vector<unique_ptr<Piece>>& otherPieces, vector<Vector2Int>& moves, const unique_ptr<Piece>& piece)
{
	//Go through all moves and check to see if that move would result in a Check If It Does Reemove it
	auto it = std::remove_if(moves.begin(), moves.end(), [this, &piece, &otherPieces](const Vector2Int move) {

		auto oldPosition = piece->GetGridPosition();
		piece->SetPosition(move);

		Piece* killingPiece = TryGetPiece(otherPieces, move);
		bool isCheck = king->IsCheck(mPieces, otherPieces, killingPiece);
		piece->SetPosition(oldPosition);
		return isCheck;

	});

	moves.erase(it, moves.end());
}

Piece* Player::TryGetPiece(const vector<unique_ptr<Piece>>& pieces, Vector2Int position)
{
	auto it = std::find_if(pieces.begin(), pieces.end(), [&position](const unique_ptr<Piece>& piece) {
		return piece->GetGridPosition() == position;
	});

	if (it == pieces.end())
		return nullptr;

	return it->get();
}
