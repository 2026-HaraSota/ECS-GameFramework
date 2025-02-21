/**
* @file   TextInputDialog.h
* @brief  �e�L�X�g���̓_�C�A���O.
* @author Hara Sota.
* @date   2024/11/15
*/
#ifndef _TEXT_INPUT_DIALOG_H_
#define _TEXT_INPUT_DIALOG_H_

#include "WindowBase.h"
#include "GuiInputText.h"

namespace HaraProject::Framework {

class EditorManager;



class TextInputDialog : public WindowBase
{
public:
	/**
	* @breif ���̓��[�h
	*/
	enum class InputMode : uint8_t
	{
		NONE,
		RENAME_WORLD,
		RENAME_SUBSCENE,
		LOAD_WORLD,
		LOAD_SUBSCENE,
		CREATE_WORLD,
		CREATE_SUBSCENE,
		ADD_COMPONENTDATA,
	};

	/**
	* @brief �E�B���h�E��
	*/
	static constexpr const char* TEXT_INPUT_DIALOG_TITLE = "TextInputDialogTitle";

	/**
	* @brief �E�B���h�E�̃T�C�Y�ƈʒu
	*/
	static constexpr float TEXT_INPUT_DIALOG_SIZE_X = 400.0f;
	static constexpr float TEXT_INPUT_DIALOG_SIZE_Y = 300.0f;
	static constexpr float TEXT_INPUT_DIALOG_POS_X = 1280.0f / 2.0f - TEXT_INPUT_DIALOG_SIZE_X / 2.0f;
	static constexpr float TEXT_INPUT_DIALOG_POS_Y = 720.0f / 2.0f - TEXT_INPUT_DIALOG_SIZE_Y / 2.0f;

	/**
	* @brief ���̗͂p�r���Ƃ̃^�C�g��
	*/
	static constexpr const char* RENAME_WORLD_DIALOG_TITLE = "Rename World";
	static constexpr const char* RENAME_SUBSCENE_DIALOG_TITLE = "Rename SubScene";
	static constexpr const char* LOAD_WORLD_DIALOG_TITLE = "Load World";
	static constexpr const char* LOAD_SUBSCENE_DIALOG_TITLE = "Load SubScene";
	static constexpr const char* CREATE_WORLD_DIALOG_TITLE = "Create World";
	static constexpr const char* CREATE_SUBSCENE_DIALOG_TITLE = "Create SubScene";
	static constexpr const char* ADD_COMPONENT_DATA_DIALOG_TITLE = "Add ComponentData";

	/**
	* @brief �R���X�g���N�^
	* @param[in] editorManager �G�f�B�^�[�}�l�[�W���[
	*/
	TextInputDialog(EditorManager* editorManager);

	/**
	* @brief �X�V����
	*/
	void UpdateWindow()override;

	/**
	* @brief ���̓��[�h�ݒ�
	* @param[in] inputMode ���̓��[�h
	*/
	void SetInputMode(InputMode inputMode);

	/**
	* @brief �_�C�A���O���J��
	* @param[in] inputMode ���̓��[�h
	*/
	void OpenTextInputDialog(InputMode inputMode);

	/**
	* @brief �_�C�A���O�����
	*/
	void CloseTextInputDialog();

private:
	/**
	* @brief ���݂̓��̓��[�h
	*/
	InputMode m_input_mode;

	/**
	* @brief �e�L�X�g���̓o�b�t�@
	*/
	char m_text_input_buffer[GuiInputText::MAX_INPUT_TEXT_LENGTH];
};

}// !namespace HaraProject::Framework {


#endif // !_TEXT_INPUT_DIALOG_H_
