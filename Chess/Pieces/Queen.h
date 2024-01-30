#pragma once
#include "Piece.h"
class Queen :
    public Piece
{
public:
    Queen(Team team, Vector2Int gridPosition)
        : Piece(Type::Queen, team, gridPosition) {}

    virtual vector<Vector2Int> GetPotentialMoves(const vector<unique_ptr<Piece>>& yourPieces,const vector<unique_ptr<Piece>>& otherPieces);
};

