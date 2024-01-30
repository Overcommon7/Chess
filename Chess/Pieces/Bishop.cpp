#include "pch.h"
#include "Bishop.h"

vector<Vector2Int> Bishop::GetPotentialMoves(const vector<unique_ptr<Piece>>& yourPieces, const vector<unique_ptr<Piece>>& otherPieces)
{
	vector<Vector2Int> moves;
    constexpr int size = 8;

    auto TryAddMove = [&moves, &yourPieces, &otherPieces](const Vector2Int& move) -> bool
        {
            if (IsPiecePosition(yourPieces, move))
                return false;

            moves.push_back(move);
            return !IsPiecePosition(otherPieces, move);
        };

    // Iterate over upward diagonals
    for (int i = 1; mGridPosition.x + i < size && mGridPosition.y + i < size; ++i) {
        Vector2Int move(mGridPosition.x + i, mGridPosition.y + i);
        if (!TryAddMove(move))
            break;
    }

    for (int i = 1; mGridPosition.x - i >= 0 && mGridPosition.y - i >= 0; ++i) {
        Vector2Int move(mGridPosition.x - i, mGridPosition.y - i);
        if (!TryAddMove(move))
            break;
    }

    // Iterate over downward diagonals
    for (int i = 1; mGridPosition.x + i < size && mGridPosition.y - i >= 0; ++i) {
        Vector2Int move(mGridPosition.x + i, mGridPosition.y - i);
        if (!TryAddMove(move))
            break;
    }

    for (int i = 1; mGridPosition.x - i >= 0 && mGridPosition.y + i < size; ++i) {
        Vector2Int move(mGridPosition.x - i, mGridPosition.y + i);
        if (!TryAddMove(move))
            break;
    }  

    RemoveInvalidPositions(yourPieces, moves);
	return moves;
}
