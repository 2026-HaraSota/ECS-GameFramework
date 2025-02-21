/**
* @file   DebugSystemOptionWindow.h
* @brief  �f�o�b�O�p�V�X�e���̃I�v�V�����E�B���h�E.
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
	* @brief �E�B���h�E��
	*/
	static constexpr const char* DEBUG_SYSTEM_OPTION_WINDOW_TITLE = "DebugSystemOption";

	/**
	* @brief �E�B���h�E�̃T�C�Y�ƈʒu
	*/
	static constexpr float DEBUG_SYSTEM_OPTION_WINDOW_SIZE_X = 300.0f;
	static constexpr float DEBUG_SYSTEM_OPTION_WINDOW_SIZE_Y = 720;
	static constexpr float DEBUG_SYSTEM_OPTION_WINDOW_POS_X = 1280 - DEBUG_SYSTEM_OPTION_WINDOW_SIZE_X;
	static constexpr float DEBUG_SYSTEM_OPTION_WINDOW_POS_Y = 0.0f;

	/**
	* @brief �R���X�g���N�^
	*/
	DebugSystemOptionWindow(EditorManager* editorManager);

	/**
	* @brief �X�V����
	*/
	void UpdateWindow()override;
};

}// !namespace HaraProject::Framework {


#endif // !_DEBUG_SYSTEM_OPTION_WINDOW_H_
