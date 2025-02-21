/**
* @file   FileUtil.h
* @brief  ファイル関連操作関数まとめ.
* @author Hara Sota.
* @date   2024/10/26
*/
#ifndef _FILE_UTIL_H_
#define _FILE_UTIL_H_

#include <filesystem>
#include <sstream>
#include <string>
#include <vector>

namespace HaraProject::Framework {

// パス
static constexpr const char* SAVE_DATA_PATH = "Saves/";
static constexpr const char* ASSETS_DATA_PATH = "Assets/";

static constexpr const char* WORLD_DATA_PATH = "World/";
static constexpr const char* SUBSCENE_DATA_PATH = "SubScene/";
static constexpr const char* BEFORE_PLAY_WORLD_DATA_PATH = "BeforePlay/";
static constexpr const char* MODEL_DATA_PATH = "Model/";
static constexpr const char* SHADER_DATA_PATH = "Shader/";
static constexpr const char* UITEXTURE_DATA_PATH = "UITexture/";

// 拡張子
static const std::string JSON_EXTENSION = ".json";

/**
* @brief データの種類
*/
enum class FileType : uint8_t
{
	WORLD_DATA,
	SUBSCENE_DATA,
	BEGIN_WORLD_DATA,
	SHADER_BINARY,
	MODEL_DATA,
	UI_TEXTURE,
	SOUND_SE,
	SOUND_BGM
};

/**
* @brief データの種類に応じたパスを生成する
* @param[in] fileType 読み込むデータの種類
* @param[in] key ファイル名(拡張子抜き)
*/
std::string CreatePath(FileType fileType, const char* key);

/**
* @brief ファイルが存在するか確認
* @param[in] fileType 読み込むデータの種類
* @param[in] key ファイル名(拡張子抜き)
*/
bool FileExists(FileType fileType, const char* key);

/**
* @brief パスを階層ごとに分割して配列で返す
* @param[in] path パス
*/
std::vector<std::string> SplitPath(std::string path);

}// namespace HaraProject::Framework
#endif // !_FILE_UTIL_H_