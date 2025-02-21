#include <string>

#include "imgui.h"

#include "DrawFpsGui.h"

namespace HaraProject::Framework {

/**
* @brief Fps表示
*/
void DrawFpsGui::DrawFps()
{
	// ウィンドウ表示
	if (ImGui::Begin("Fps"))
	{
		std::string fps_string = std::to_string(m_fps);
		// ウィンドウに出力
		ImGui::Text(fps_string.c_str());

		ImGui::End();
	}
}

}