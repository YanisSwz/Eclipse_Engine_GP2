#include "Camera/CameraSystem.hpp"
#include "Logger.hpp"

namespace Core
{
	CameraSystem::CameraSystem()
	{
	}
	
	CameraSystem::~CameraSystem()
	{
	}

	Camera* CameraSystem::AddCamera()
	{
		if (m_currentCameraCount >= MAX_CAMERA_SIZE)
		{
			Logging::Logger::GetInstance().Log(Logging::PRIORITY::ERROR, "Maximum capacity of cameras reached!");
			return nullptr;
		}

		for (int i = 0; i < m_currentCameraCount; ++i)
		{
			if (m_cameras[i].IsDestroyed())
			{
				m_cameras[i].~Camera();
				new (&m_cameras[i]) Camera();
				m_cameras[i].SetActive(true);
				if (m_activeCamera == nullptr)
					m_activeCamera = &m_cameras[i];
				return &m_cameras[i];
			}
		}

		m_cameras[m_currentCameraCount].~Camera();
		new (&m_cameras[m_currentCameraCount]) Camera();
		m_cameras[m_currentCameraCount].SetActive(true);

		if (m_activeCamera == nullptr)
			m_activeCamera = &m_cameras[m_currentCameraCount];

		++m_currentCameraCount;

		return &m_cameras[m_currentCameraCount - 1];
	}

	void CameraSystem::SetCurrentCamera(Camera* _camera)
	{
		if (!_camera)
			return;

		m_activeCamera = _camera;
	}

}