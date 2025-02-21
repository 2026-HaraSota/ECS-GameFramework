/**
* @file   DrawFps.h
* @brief  FPS�\���@�\.
* @author Hara Sota.
* @date   2024/1/27
*/

namespace HaraProject::Framework {

class DrawFpsGui
{
public:
	/**
	* @brief �t���[�����Ԑݒ�
	*/
	void SetDeltaTime(float deltaTime) {
		m_delta_time = deltaTime;
	}

	/**
	* @brief �o�ߎ��ԍX�V
	*/
	void UpdateElapsedTime(float deltaTime) {
		m_elapsed_time += deltaTime;
		if (m_elapsed_time >= 0.2f)
		{
			SetDeltaTime(deltaTime);
			m_fps = CalculateFps();
			m_elapsed_time = 0.0f;
		}
	}

	/**
	* @brief Fps�\��
	*/
	void DrawFps();

private:
	/**
	* @brief fps�v�Z
	*/
	float CalculateFps() {
		float fps = m_delta_time != 0.0f ? 1.0f / m_delta_time : 0.0f;
		return fps;
	}

	/**
	* @brief �t���[������
	*/
	float m_delta_time = 0.0f;

	/**
	* @brief �o�ߎ���
	*/
	float m_elapsed_time = 0.0f;

	/**
	* @brief FPS
	*/
	float m_fps = 0.0f;
};

}