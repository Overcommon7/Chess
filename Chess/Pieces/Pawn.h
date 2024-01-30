#pragma once
#include "Piece.h"
class Pawn final :
    public Piece
{
public:
    Pawn(Team team, Vector2Int gridPosition)
        : Piece(Type::Pawn, team, gridPosition) {}

    virtual vector<Vector2Int> GetPotentialMoves(const vector<unique_ptr<Piece>>& yourPieces, const vector<unique_ptr<Piece>>& otherPieces);
    virtual void MoveTo(Vector2Int gridPosition) override;
private:
    bool hasMoved = false;
};

