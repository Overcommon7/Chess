#include "pch.h"
#include "PlayerManager.h"

namespace
{
    unique_ptr<PlayerManager> fPlayerManager = nullptr;
}

PlayerManager& PlayerManager::Get()
{
    if (!fPlayerManager)
        fPlayerManager = make_unique<PlayerManager>();

    return *fPlayerManager.get();
}

void PlayerManager::Update(float deltaTime)
{
    auto& currentPlayer = GetCurrentPlayer();
    auto& otherPlayerPieces = GetOtherPlayer().mPieces;

    if (currentPlayer.Update(deltaTime, otherPlayerPieces))
        SwapPlayers();
}

void PlayerManager::Draw()
{
    mPlayers[0]->Draw(mPlayers[1]->mPieces);
    mPlayers[1]->Draw(mPlayers[0]->mPieces);

    mPlayers[0]->LateDraw(mPlayers[1]->mPieces);
    mPlayers[1]->LateDraw(mPlayers[0]->mPieces);
}

PlayerManager::PlayerManager()
    : mPlayers({nullptr})
    , mCurrentPlayerIndex(0)
{
    mPlayers[0] = std::make_unique<Player>(Team::White);
    mPlayers[1] = std::make_unique<Player>(Team::Black);

    mPlayers[0]->SetTurn(true);
}

Player& PlayerManager::GetCurrentPlayer()
{
    return *mPlayers[mCurrentPlayerIndex];
}

Player& PlayerManager::GetOtherPlayer()
{
    return *mPlayers[mCurrentPlayerIndex == 1 ? 0 : 1];
}

void PlayerManager::SwapPlayers()
{
    mPlayers[mCurrentPlayerIndex]->SetTurn(false);

    if (mCurrentPlayerIndex == 0)
        mCurrentPlayerIndex = 1;
    else
        mCurrentPlayerIndex = 0;

    mPlayers[mCurrentPlayerIndex]->SetTurn(true);
    mPlayers[mCurrentPlayerIndex]->OnTurnBegin(GetOtherPlayer().mPieces);

    if (mPlayers[mCurrentPlayerIndex]->HasLost())
    {
        cout << magic_enum::enum_name(GetOtherPlayer().mTeam) << " Has Won\n";
    }
}
