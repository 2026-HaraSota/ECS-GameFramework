/**
* @file   Sprite.h
* @brief  �X�v���C�g�R���|�[�l���g�f�[�^��`.
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <DirectXMath.h>

#ifdef _DEBUG
#include "GuiManager.h"
#include "GuiItemBase.h"
#include "GuiTreeNode.h"
#include "GuiInputFloat2.h"
#include "GuiInputColor.h"
#endif // _DEBUG
#include "GuiInputText.h"

#include "Defines.h"
#include "Texture.h"
#include "ComponentDataBase.h"

namespace HaraProject::Framework {

/**
* @brief �X�v���C�g�R���|�[�l���g�f�[�^
*/
class Sprite : public ComponentDataBase {
public:
    /**
    * @brief �f�[�^��
    */
    static constexpr const char* SPRITE_NAME = "Sprite";
    static constexpr const char* SPRITE_TEXTURE_NAME_NAME = "textureName";
    static constexpr const char* SPRITE_TEXTURE_SIZE_NAME = "textureSize";
    static constexpr const char* SPRITE_UV_POSITION_NAME = "uvPosition";
    static constexpr const char* SPRITE_UV_SCALE_NAME = "uvScale";
    static constexpr const char* SPRITE_TEXTURE_COLOR_NAME = "textureColor";

    /**
    * @brief �e�N�X�`���t�@�C����
    */
    char textureName[GuiInputText::MAX_INPUT_TEXT_LENGTH];

    /**
    * @brief �e�N�X�`���T�C�Y
    */
    DirectX::XMFLOAT2 textureSize;

    /**
    * @brief UV���W
    */
    DirectX::XMFLOAT2 uvPosition;

    /**
    * @brief UV�X�P�[��
    */
    DirectX::XMFLOAT2 uvScale;

    /**
    * @brief �J���[
    */
    DirectX::XMFLOAT4 textureColor;

    /**
    * @brief �e�N�X�`���I�u�W�F�N�g�ւ̃|�C���^
    */
    Texture* texture;

    /**
    * @brief �R���X�g���N�^
    */
    Sprite();

    /**
    * @brief �R�s�[�R���X�g���N�^
    * @param[in] base �R�s�[����Sprite
    */
    Sprite(ComponentDataBase* base);

    /**
    * @brief �f�X�g���N�^
    */
    ~Sprite() = default;

    /**
    * @brief Json�f�[�^����l��ݒ肷��
    * @param[in] json json�I�u�W�F�N�g
    */
    void SetDataFromJson(nlohmann::json jsonData) override;

#ifdef _DEBUG
    /**
    * @brief ���݂̒l��Json�f�[�^�ɕϊ�����
    */
    nlohmann::json WriteDataToJson() override
    {
        nlohmann::json jsonData;

        jsonData[SPRITE_NAME][SPRITE_TEXTURE_NAME_NAME] = std::string(textureName);
        jsonData[SPRITE_NAME][SPRITE_TEXTURE_SIZE_NAME] = { textureSize.x, textureSize.y };
        jsonData[SPRITE_NAME][SPRITE_UV_POSITION_NAME] = { uvPosition.x, uvPosition.y };
        jsonData[SPRITE_NAME][SPRITE_UV_SCALE_NAME] = { uvScale.x, uvScale.y };
        jsonData[SPRITE_NAME][SPRITE_TEXTURE_COLOR_NAME] = {
            textureColor.x, textureColor.y, textureColor.z, textureColor.w
        };

        return jsonData;
    }

    /**
    * @brief �C���X�y�N�^�\�\���쐬
    */
    GuiItemBase* CreateDetailContent(GuiManager* guiManager) override
    {
        GuiTreeNode* sprite_gui = guiManager->CreateGuiTreeNode(SPRITE_NAME, "id");
        sprite_gui->AddChildren(
            guiManager->CreateGuiInputText(SPRITE_TEXTURE_NAME_NAME, "id", GuiInputBase::OverWriteMode::RETURN, textureName),
            guiManager->CreateGuiInputFloat2(SPRITE_TEXTURE_SIZE_NAME, "id", &textureSize),
            guiManager->CreateGuiInputFloat2(SPRITE_UV_POSITION_NAME, "id", &uvPosition),
            guiManager->CreateGuiInputFloat2(SPRITE_UV_SCALE_NAME, "id", &uvScale),
            guiManager->CreateGuiInputColor(SPRITE_TEXTURE_COLOR_NAME, "id", &textureColor)
        );
        return sprite_gui;
    }
#endif // _DEBUG
};

} // namespace HaraProject::Framework

#endif // !_SPRITE_H_
