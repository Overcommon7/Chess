#include "pch.h"
#include "Rook.h"

vector<Vector2Int> Rook::GetPotentialMoves(const vector<unique_ptr<Piece>>& yourPieces,const vector<unique_ptr<Piece>>& otherPieces)
{
    constexpr int size = 8;
    vector<Vector2Int> moves;

    auto TryAddMove = [this, &moves, &yourPieces, &otherPieces](const Vector2Int& move) -> bool
        {
            if (IsPiecePosition(yourPieces, move))
                return false;

            moves.push_back(move);
            return !IsPiecePosition(otherPieces, move);
        };

    for (int x = mGridPosition.x - 1; x >= 0; x--)
    {
        Vector2Int move(x, mGridPosition.y);
        if (!TryAddMove(move))
            break;
    }

    for (int x = mGridPosition.x + 1; x < size; x++)
    {
        Vector2Int move(x, mGridPosition.y);
        if (!TryAddMove(move))
            break;
    }

    for (int y = mGridPosition.y - 1; y >= 0; y--)
    {
        Vector2Int move(mGridPosition.x, y);
        if (!TryAddMove(move))
            break;
    }

    for (int y = mGridPosition.y + 1; y < size; y++)
    {
        Vector2Int move(mGridPosition.x, y);
        if (!TryAddMove(move))
            break;
    }
       
    
    RemoveInvalidPositions(yourPieces, moves);
    return moves;
}
