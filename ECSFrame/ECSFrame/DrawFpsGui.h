/**
* @file   DrawFps.h
* @brief  FPS表示機能.
* @author Hara Sota.
* @date   2024/1/27
*/

namespace HaraProject::Framework {

class DrawFpsGui
{
public:
	/**
	* @brief フレーム時間設定
	*/
	void SetDeltaTime(float deltaTime) {
		m_delta_time = deltaTime;
	}

	/**
	* @brief 経過時間更新
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
	* @brief Fps表示
	*/
	void DrawFps();

private:
	/**
	* @brief fps計算
	*/
	float CalculateFps() {
		float fps = m_delta_time != 0.0f ? 1.0f / m_delta_time : 0.0f;
		return fps;
	}

	/**
	* @brief フレーム時間
	*/
	float m_delta_time = 0.0f;

	/**
	* @brief 経過時間
	*/
	float m_elapsed_time = 0.0f;

	/**
	* @brief FPS
	*/
	float m_fps = 0.0f;
};

}