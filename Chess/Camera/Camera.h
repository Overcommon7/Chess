#pragma once
namespace Render
{
	class Camera
	{
	public:
		void BeginDrawing();
		void EndDrawing();

		void SetClearColor(Color color);
		void SetTintColor(Color color);
		void Center(bool center);

		Camera();
		~Camera();
		void Terminate();
		void Update();
	private:
		Camera2D camera;
		RenderTexture renderTexture;
		Color clearColor;
		Color tintColor;
		Vector2 renderSize;
		Vector2 renderPosition;
		float aspectRatio;
		bool terminated;
		bool center;

		void SetRenderPosition();
	};
}


