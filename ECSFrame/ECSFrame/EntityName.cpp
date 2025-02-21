#include "EntityName.h"

namespace HaraProject::Framework
{

/**
* @brief �R���X�g���N�^
*/
EntityName::EntityName()
	: name("unknown") 
{}

/**
* @brief �R�s�[�R���X�g���N�^
* @param[in] base EntityName�����������N���X�|�C���^
*/
EntityName::EntityName(ComponentDataBase* base)
{
	EntityName* value = dynamic_cast<EntityName*>(base);
	strcpy_s(name, value->name);
}

/**
* @brief Json�f�[�^����l��ݒ肷��
* @param[in] json json�I�u�W�F�N�g
*/
void EntityName::SetDataFromJson(nlohmann::json jsonData)
{
	strcpy_s(name, std::string(jsonData[ENTITY_NAME_NAME_NAME]).c_str());
}

}