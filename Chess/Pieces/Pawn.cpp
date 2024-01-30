#include "pch.h"
#include "Pawn.h"

vector<Vector2Int> Pawn::GetPotentialMoves(const vector<unique_ptr<Piece>>& yourPieces, const vector<unique_ptr<Piece>>& otherPieces)
{
    vector<Vector2Int> moves;
    constexpr int size = 8;
    int add = (mTeam == Team::Black) ? 1 : -1;

    //Foward Spaces
    {
        {
            Vector2Int move(mGridPosition.x, mGridPosition.y + add);
            if (!IsPiecePosition(yourPieces, move) && !IsPiecePosition(otherPieces, move))
            {  
                moves.push_back(move);
            }
        }
    
        if (!hasMoved)
        {
            Vector2Int move(mGridPosition.x, mGridPosition.y + (add * 2));
            if (!IsPiecePosition(yourPieces, move) && !IsPiecePosition(otherPieces, move))
            {  
                moves.push_back(move);
            }
        }
            
    }
   

    //Check For Diagonal Captures
    {
        {
            Vector2Int move(mGridPosition.x + 1, mGridPosition.y + add);
            if (IsPiecePosition(otherPieces, move))
                moves.push_back(move);
        }

        {
            Vector2Int move(mGridPosition.x - 1, mGridPosition.y + add);
            if (IsPiecePosition(otherPieces, move))
                moves.push_back(move);
        }
    }

    RemoveInvalidPositions(yourPieces, moves);

    return moves;
}

void Pawn::MoveTo(Vector2Int gridPosition)
{
    Piece::MoveTo(gridPosition);
    hasMoved = true;
}
