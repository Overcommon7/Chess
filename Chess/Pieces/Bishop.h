#pragma once
#include "Piece.h"
class Bishop :
    public Piece
{
public:
    Bishop(Team team, Vector2Int gridPosition)
        : Piece(Type::Bishop, team, gridPosition) {}

    virtual vector<Vector2Int> GetPotentialMoves(const vector<unique_ptr<Piece>>& yourPieces,const vector<unique_ptr<Piece>>& otherPieces);
};

