#include "pch.h"
#include "King.h"

vector<Vector2Int> King::GetPotentialMoves(const vector<unique_ptr<Piece>>& yourPieces, const vector<unique_ptr<Piece>>& otherPieces)
{
    vector<Vector2Int> moves;
    constexpr int size = 8;

    const Vector2Int start(std::max(mGridPosition.x - 1, 0), std::max(mGridPosition.y - 1, 0));
    const Vector2Int end(std::min(mGridPosition.x + 1, size), std::min(mGridPosition.y + 1, size));

    for (int y = start.y; y <= end.y; ++y)
    {
        for (int x = start.x; x <= end.x; ++x)
        {
            moves.emplace_back(x, y);
        }
    }

    
    RemoveInvalidPositions(yourPieces, moves);
    return moves;
}

bool King::IsCheck(const vector<unique_ptr<Piece>>& yourPieces, const vector<unique_ptr<Piece>>& otherPieces)
{
    for (auto& piece : otherPieces)
    {
        auto pieceMoves = piece->GetPotentialMoves(otherPieces, yourPieces);
        auto it = std::find(pieceMoves.begin(), pieceMoves.end(), mGridPosition);

        if (it != pieceMoves.end())
            return true;
    }

    return false;
}
