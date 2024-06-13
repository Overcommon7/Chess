    #include "pch.h"
    #include "Camera/Camera.h"
    #include "Player/PlayerManager.h"

int main()
{
    SetConfigFlags(ConfigFlags::FLAG_WINDOW_RESIZABLE | ConfigFlags::FLAG_MSAA_4X_HINT);
    InitWindow(800, 800, "Chess");
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
    {
        
        Render::Camera camera;
        Piece::StaticInitialize("Textures/Pieces/");
        Texture2D board = LoadTexture("Textures/Board.png");
        auto& playerManager = PlayerManager::Get();


        while (!WindowShouldClose())
        {
            float deltaTime = GetFrameTime();

            camera.Update();
            playerManager.Update(deltaTime);

            camera.BeginDrawing();
            {
                DrawTexture(board, 0, 0, WHITE);
                playerManager.Draw();
            }
            camera.EndDrawing();

            BeginDrawing();
            ClearBackground(BLACK);
            Render::Camera::DrawFrameBuffer();
            EndDrawing();
        }

        UnloadTexture(board);
        Piece::StaticTerminate();
    }
    CloseWindow();
}