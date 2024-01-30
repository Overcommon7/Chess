#include "pch.h"
#include "Queen.h"

vector<Vector2Int> Queen::GetPotentialMoves(const vector<unique_ptr<Piece>>& yourPieces,const vector<unique_ptr<Piece>>& otherPieces)
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

    //Diagonals
    {
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
    }
    
    //Horizantals
    {
        

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
    }
    

    RemoveInvalidPositions(yourPieces, moves);
    return moves;
}
