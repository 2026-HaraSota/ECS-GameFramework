#include <string>

#include "imgui.h"

#include "DrawFpsGui.h"

namespace HaraProject::Framework {

/**
* @brief Fps�\��
*/
void DrawFpsGui::DrawFps()
{
	// �E�B���h�E�\��
	if (ImGui::Begin("Fps"))
	{
		std::string fps_string = std::to_string(m_fps);
		// �E�B���h�E�ɏo��
		ImGui::Text(fps_string.c_str());

		ImGui::End();
	}
}

}