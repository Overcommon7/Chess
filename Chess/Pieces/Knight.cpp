#include "pch.h"
#include "Knight.h"

vector<Vector2Int> Knight::GetPotentialMoves(const vector<unique_ptr<Piece>>& yourPieces, const vector<unique_ptr<Piece>>& otherPieces)
{
    vector<Vector2Int> moves;
    constexpr int size = 8;

    moves.emplace_back(mGridPosition.x - 2, mGridPosition.y + 1);
    moves.emplace_back(mGridPosition.x + 2, mGridPosition.y + 1);
    moves.emplace_back(mGridPosition.x + 2, mGridPosition.y - 1);
    moves.emplace_back(mGridPosition.x - 2, mGridPosition.y - 1);

    moves.emplace_back(mGridPosition.x + 1, mGridPosition.y + 2);
    moves.emplace_back(mGridPosition.x - 1, mGridPosition.y + 2);
    moves.emplace_back(mGridPosition.x + 1, mGridPosition.y - 2);
    moves.emplace_back(mGridPosition.x - 1, mGridPosition.y - 2);

    RemoveInvalidPositions(yourPieces, moves);

    return moves;
}
