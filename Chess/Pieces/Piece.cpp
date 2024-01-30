#include "pch.h"
#include "Piece.h"

Rectangle Piece::Collider()
{
    return { mPosition.x, mPosition.y, TILE_SIZE, TILE_SIZE };
}

Vector2 Piece::GetScreenSpacePosition()
{
    return mPosition;
}

Vector2Int Piece::GetGridPosition()
{
    return mGridPosition;
}

void Piece::MoveTo(Vector2Int gridPosition)
{
    mGridPosition = gridPosition;
    mPosition = ToScreenPosition(gridPosition);
}

void Piece::SetPosition(Vector2Int gridPosition)
{
    mGridPosition = gridPosition;
}

void Piece::Draw() const
{
    DrawTexture(mTexture, (int)mPosition.x, (int)mPosition.y, GetColor());
    if (mIsSelected)
        DrawTexture(mTexture, (int)mPosition.x, (int)mPosition.y, { 120, 120, 120, 80 });
}

Piece::Piece(Type type, Team color, Vector2Int gridPosition)
    : mType(type)
    , mTeam(color)
    , mTexture(sTextures.at(type))
    , mGridPosition(gridPosition)
    , mPosition(ToScreenPosition(gridPosition))
    , mIsSelected(false)
    , mIsCaptured(false)
{
 
}

void Piece::StaticInitialize(const fs::path& texturesDirectory)
{
    constexpr auto types = magic_enum::enum_names<Type>();

    for (const auto& file : fs::directory_iterator(texturesDirectory))
    {
        const auto path = file.path();
        const auto iter = std::find(types.begin(), types.end(), path.stem().string());
        sTextures.emplace(magic_enum::enum_cast<Type>(*iter).value(), LoadTexture(path.string().c_str()));
    }
}

void Piece::StaticTerminate()
{
    for (auto& [type, texture] : sTextures)
    {
        UnloadTexture(texture);
    }
}

Vector2 Piece::ToScreenPosition(Vector2Int gridPosition) 
{
    return (gridPosition * TILE_SIZE);
}

Vector2Int Piece::ToGridPosition(Vector2 screenPosition) 
{
   return Vector2Scale(screenPosition, 0.01f);
}

void Piece::RemoveInvalidPositions(const vector<unique_ptr<Piece>>& yourPieces, vector<Vector2Int>& moves)
{    
    auto CheckForSpaces = [this, &yourPieces](const Vector2Int& move) -> bool {
        
        constexpr int size = 8;
        if (move == mGridPosition) 
            return true;

        if (move.x >= size || move.x < 0 || move.y >= size || move.y < 0)
            return true;

        for (const auto& piece : yourPieces)
        {  
            if (piece->GetGridPosition() == move)
                return true;
        }
            
        return false;
    };


    std::erase_if(moves, CheckForSpaces);
}

bool Piece::IsPiecePosition(const vector<unique_ptr<Piece>>& pieces, Vector2Int position)
{
    return std::find_if(pieces.begin(), pieces.end(), [&position](const unique_ptr<Piece>& piece) {
        return piece->GetGridPosition() == position;
        }) != pieces.end();
}
