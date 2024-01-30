#include "pch.h"
#include "Camera.h"

namespace Render
{
	void Camera::BeginDrawing()
	{
		BeginTextureMode(renderTexture);
		ClearBackground(clearColor);
		BeginMode2D(camera);
	}

	void Camera::EndDrawing()
	{
		EndMode2D();
		EndTextureMode();

		::BeginDrawing();
		{
			DrawTexturePro(renderTexture.texture,
				{ 0, 0, (float)renderTexture.texture.width, -(float)renderTexture.texture.height },
				{ renderPosition.x, renderPosition.y, renderSize.x, renderSize.y },
				{ 0, 0 }, 0, tintColor);
		}
		::EndDrawing();
	}

	void Camera::SetClearColor(Color color)
	{
		clearColor = color;
	}

	void Camera::SetTintColor(Color color)
	{
		tintColor = color;
	}

	void Camera::Center(bool center)
	{
		this->center = center;
	}

	Camera::Camera()
		: camera({})
		, renderPosition({})
		, clearColor(BLACK)
		, tintColor(WHITE)
		, terminated(false)
		, center(true)
	{
		if (!IsWindowReady())
			throw std::exception("Window Must Be Created Before Camera Can Be Loaded");

		renderSize.x = (float)GetScreenWidth();
		renderSize.y = (float)GetScreenHeight();

		camera.zoom = 1;
		camera.offset = { };
		renderTexture = LoadRenderTexture((int)renderSize.x, (int)renderSize.y);

		aspectRatio = renderSize.x / renderSize.y;
		SetRenderPosition();
	}

	Camera::~Camera()
	{
		if (!terminated) 
			Terminate();
	}

	void Camera::Terminate()
	{
		UnloadRenderTexture(renderTexture);
		terminated = true;
	}

	void Camera::Update()
	{
		if (!IsWindowResized())	return;

		Vector2 size = renderSize;

		renderSize.y = (float)GetScreenHeight();
		int screenWidth = GetScreenWidth();
		renderSize.x = aspectRatio * renderSize.y;

		if (renderSize.x > screenWidth)
		{
			renderSize.y = aspectRatio * screenWidth;
			renderSize.x = screenWidth;
		}

		SetRenderPosition();	
	}
	void Camera::SetRenderPosition()
	{
		if (!center) return;

		int screenWidth = GetScreenWidth();
		int screenHeight = GetScreenHeight();

		if (renderSize.x >= screenWidth)
		{
			renderPosition.x = 0;
		}
		else
		{
			renderPosition.x = (screenWidth - renderSize.x) * 0.5f;
		}

		if (renderSize.y >= screenHeight)
		{
			renderPosition.y = 0;
		}
		else
		{
			renderPosition.y = (screenHeight - renderSize.y) * 0.5f;
		}	
	}
}
