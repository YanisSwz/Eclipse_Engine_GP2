#pragma once
#include "Camera/Camera.hpp"

namespace Core
{
	class CameraSystem
	{
	public:
		CameraSystem();
		~CameraSystem();

		ECLIPSE_ENGINE Camera* AddCamera();
		ECLIPSE_ENGINE void SetCurrentCamera(Camera* _camera);

	private:
		static const int MAX_CAMERA_SIZE = 10;
		int m_currentCameraCount = 0;
		Camera m_cameras[MAX_CAMERA_SIZE];

		Camera* m_activeCamera = nullptr;
	};
}