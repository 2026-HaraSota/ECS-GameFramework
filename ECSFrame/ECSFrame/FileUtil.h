/**
* @file   FileUtil.h
* @brief  �t�@�C���֘A����֐��܂Ƃ�.
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

// �p�X
static constexpr const char* SAVE_DATA_PATH = "Saves/";
static constexpr const char* ASSETS_DATA_PATH = "Assets/";

static constexpr const char* WORLD_DATA_PATH = "World/";
static constexpr const char* SUBSCENE_DATA_PATH = "SubScene/";
static constexpr const char* BEFORE_PLAY_WORLD_DATA_PATH = "BeforePlay/";
static constexpr const char* MODEL_DATA_PATH = "Model/";
static constexpr const char* SHADER_DATA_PATH = "Shader/";
static constexpr const char* UITEXTURE_DATA_PATH = "UITexture/";

// �g���q
static const std::string JSON_EXTENSION = ".json";

/**
* @brief �f�[�^�̎��
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
* @brief �f�[�^�̎�ނɉ������p�X�𐶐�����
* @param[in] fileType �ǂݍ��ރf�[�^�̎��
* @param[in] key �t�@�C����(�g���q����)
*/
std::string CreatePath(FileType fileType, const char* key);

/**
* @brief �t�@�C�������݂��邩�m�F
* @param[in] fileType �ǂݍ��ރf�[�^�̎��
* @param[in] key �t�@�C����(�g���q����)
*/
bool FileExists(FileType fileType, const char* key);

/**
* @brief �p�X���K�w���Ƃɕ������Ĕz��ŕԂ�
* @param[in] path �p�X
*/
std::vector<std::string> SplitPath(std::string path);

}// namespace HaraProject::Framework
#endif // !_FILE_UTIL_H_