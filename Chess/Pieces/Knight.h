#pragma once
#include "Piece.h"
class Knight :
    public Piece
{
public:
    Knight(Team team, Vector2Int gridPosition)
        : Piece(Type::Knight, team, gridPosition) {}

    virtual vector<Vector2Int> GetPotentialMoves(const vector<unique_ptr<Piece>>& yourPieces,const vector<unique_ptr<Piece>>& otherPieces);
};

