#include "Sprite.h"

namespace HaraProject::Framework {

/**
* @brief コンストラクタ
*/
Sprite::Sprite()
    : texture(nullptr)
    , textureName("nothing")
    , textureSize(100.0f, 100.0f)
    , uvPosition(0.0f, 0.0f)
    , uvScale(1.0f, 1.0f)
    , textureColor(1.0f, 1.0f, 1.0f, 1.0f) 
{
}

/**
* @brief コピーコンストラクタ
* @param[in] base コピー元のSprite
*/
Sprite::Sprite(ComponentDataBase* base) 
{
    Sprite* value = dynamic_cast<Sprite*>(base);
    strcpy_s(textureName, value->textureName);
    textureSize = value->textureSize;
    uvPosition = value->uvPosition;
    uvScale = value->uvScale;
    textureColor = value->textureColor;
    texture = nullptr;
}

/**
* @brief Jsonデータから値を設定する
* @param[in] json jsonオブジェクト
*/
void Sprite::SetDataFromJson(nlohmann::json jsonData) 
{
    strcpy_s(textureName, std::string(jsonData[SPRITE_TEXTURE_NAME_NAME]).c_str());

    textureSize = DirectX::XMFLOAT2(
        jsonData[SPRITE_TEXTURE_SIZE_NAME][0],
        jsonData[SPRITE_TEXTURE_SIZE_NAME][1]
    );

    uvPosition = DirectX::XMFLOAT2(
        jsonData[SPRITE_UV_POSITION_NAME][0],
        jsonData[SPRITE_UV_POSITION_NAME][1]
    );

    uvScale = DirectX::XMFLOAT2(
        jsonData[SPRITE_UV_SCALE_NAME][0],
        jsonData[SPRITE_UV_SCALE_NAME][1]
    );

    textureColor = DirectX::XMFLOAT4(
        jsonData[SPRITE_TEXTURE_COLOR_NAME][0],
        jsonData[SPRITE_TEXTURE_COLOR_NAME][1],
        jsonData[SPRITE_TEXTURE_COLOR_NAME][2],
        jsonData[SPRITE_TEXTURE_COLOR_NAME][3]
    );
}

} // namespace HaraProject::Framework
