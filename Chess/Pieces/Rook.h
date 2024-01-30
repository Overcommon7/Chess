#pragma once
#include "Piece.h"
class Rook :
    public Piece
{
public:
    Rook(Team team, Vector2Int gridPosition)
        : Piece(Type::Rook, team, gridPosition) {}

    virtual vector<Vector2Int> GetPotentialMoves(const vector<unique_ptr<Piece>>& yourPieces,const vector<unique_ptr<Piece>>& otherPieces);

};

