#pragma once
#include "Player.h"
class PlayerManager
{
public:

    static PlayerManager& Get();

    void Update(float deltaTime);
    void Draw();

private:    
    std::array<unique_ptr<Player>, 2> mPlayers;
    int mCurrentPlayerIndex;

    Player& GetCurrentPlayer();
    Player& GetOtherPlayer();

    void SwapPlayers();
public: 
    PlayerManager();
    PlayerManager(const PlayerManager& p) = delete;
    PlayerManager(const PlayerManager&& p) = delete;
    PlayerManager& operator=(const PlayerManager& p) = delete;
    PlayerManager& operator=(const PlayerManager&& p) = delete;

};

