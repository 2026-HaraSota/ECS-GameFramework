/**
* @file   Sprite.h
* @brief  スプライトコンポーネントデータ定義.
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
* @brief スプライトコンポーネントデータ
*/
class Sprite : public ComponentDataBase {
public:
    /**
    * @brief データ名
    */
    static constexpr const char* SPRITE_NAME = "Sprite";
    static constexpr const char* SPRITE_TEXTURE_NAME_NAME = "textureName";
    static constexpr const char* SPRITE_TEXTURE_SIZE_NAME = "textureSize";
    static constexpr const char* SPRITE_UV_POSITION_NAME = "uvPosition";
    static constexpr const char* SPRITE_UV_SCALE_NAME = "uvScale";
    static constexpr const char* SPRITE_TEXTURE_COLOR_NAME = "textureColor";

    /**
    * @brief テクスチャファイル名
    */
    char textureName[GuiInputText::MAX_INPUT_TEXT_LENGTH];

    /**
    * @brief テクスチャサイズ
    */
    DirectX::XMFLOAT2 textureSize;

    /**
    * @brief UV座標
    */
    DirectX::XMFLOAT2 uvPosition;

    /**
    * @brief UVスケール
    */
    DirectX::XMFLOAT2 uvScale;

    /**
    * @brief カラー
    */
    DirectX::XMFLOAT4 textureColor;

    /**
    * @brief テクスチャオブジェクトへのポインタ
    */
    Texture* texture;

    /**
    * @brief コンストラクタ
    */
    Sprite();

    /**
    * @brief コピーコンストラクタ
    * @param[in] base コピー元のSprite
    */
    Sprite(ComponentDataBase* base);

    /**
    * @brief デストラクタ
    */
    ~Sprite() = default;

    /**
    * @brief Jsonデータから値を設定する
    * @param[in] json jsonオブジェクト
    */
    void SetDataFromJson(nlohmann::json jsonData) override;

#ifdef _DEBUG
    /**
    * @brief 現在の値をJsonデータに変換する
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
    * @brief インスペクタ―表示作成
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
