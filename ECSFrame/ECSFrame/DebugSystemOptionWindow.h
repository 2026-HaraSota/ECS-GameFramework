/**
* @file   DebugSystemOptionWindow.h
* @brief  デバッグ用システムのオプションウィンドウ.
* @author Hara Sota.
* @date   2024/11/15
*/
#ifndef _DEBUG_SYSTEM_OPTION_WINDOW_H_
#define _DEBUG_SYSTEM_OPTION_WINDOW_H_

#include "WindowBase.h"

namespace HaraProject::Framework {

class EditorManager;

class DebugSystemOptionWindow : public WindowBase
{
public:
	/**
	* @brief ウィンドウ名
	*/
	static constexpr const char* DEBUG_SYSTEM_OPTION_WINDOW_TITLE = "DebugSystemOption";

	/**
	* @brief ウィンドウのサイズと位置
	*/
	static constexpr float DEBUG_SYSTEM_OPTION_WINDOW_SIZE_X = 300.0f;
	static constexpr float DEBUG_SYSTEM_OPTION_WINDOW_SIZE_Y = 720;
	static constexpr float DEBUG_SYSTEM_OPTION_WINDOW_POS_X = 1280 - DEBUG_SYSTEM_OPTION_WINDOW_SIZE_X;
	static constexpr float DEBUG_SYSTEM_OPTION_WINDOW_POS_Y = 0.0f;

	/**
	* @brief コンストラクタ
	*/
	DebugSystemOptionWindow(EditorManager* editorManager);

	/**
	* @brief 更新処理
	*/
	void UpdateWindow()override;
};

}// !namespace HaraProject::Framework {


#endif // !_DEBUG_SYSTEM_OPTION_WINDOW_H_
