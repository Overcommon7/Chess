#pragma once
#include "Piece.h"
class King :
    public Piece
{
public:
    King(Team team, Vector2Int gridPosition)
        : Piece(Type::King, team, gridPosition) {}

    virtual vector<Vector2Int> GetPotentialMoves(const vector<unique_ptr<Piece>>& yourPieces, const vector<unique_ptr<Piece>>& otherPieces);
    bool IsCheck(const vector<unique_ptr<Piece>>& yourPieces, const vector<unique_ptr<Piece>>& otherPieces, const Piece* ignorePiece = nullptr);
};

