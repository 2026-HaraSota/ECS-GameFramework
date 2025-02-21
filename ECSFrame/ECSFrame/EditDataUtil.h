/**
* @file   EditDataUtil.h
* @brief  �ҏW�f�[�^�̓ǂݍ��݁A��������
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _EDIT_DATA_UTIL_H_
#define _EDIT_DATA_UTIL_H_

#include <map>
#include <string>
#include <memory>

#include "ComponentDataBase.h"
#include "ComponentMask.h"
#include "SystemBase.h"
#include "SystemManager.h"

#include "SystemManager.h"
#include "EditorManager.h"
#include "Transform.h"

namespace HaraProject::Framework {

/**
* @brief �T�u�V�[���L�[��
*/
static constexpr const char* SUBSCENES_JSON_KEY = "SubScenes";

/**
* @brief json�������ݎ��̃C���f���g
*/
static constexpr uint8_t JSON_DATA_DUMP = 4;

/**
* @brief �n���h�������
* @param[in] entityValueHandler �n���h��
*/
void ReleaceEntityValueHandler(std::unordered_map<ComponentBits, ComponentDataBase*> entityValueHandler);

} // namespace HaraProject::Framework::EditDataUtil

#endif // !_EDIT_DATA_UTIL_H_