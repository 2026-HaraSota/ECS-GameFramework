#include "ModelHandle.h"

namespace HaraProject::Framework
{

/**
* @brief �R���X�g���N�^
*/
ModelHandle::ModelHandle()
	: model(nullptr)
	, modelName("nothing")
{}

/**
* @brief �R�s�[�R���X�g���N�^
* @param[in] base �l�����������N���X�|�C���^
*/
ModelHandle::ModelHandle(ComponentDataBase* base)
{
	ModelHandle* value = dynamic_cast<ModelHandle*>(base);
	strcpy_s(modelName, value->modelName);
	model = nullptr;
}

/**
* @brief Json�f�[�^����l��ݒ肷��
* @param[in] json json�I�u�W�F�N�g
*/
void HaraProject::Framework::ModelHandle::SetDataFromJson(nlohmann::json jsonData)
{
	strcpy_s(modelName, std::string(jsonData[MODEL_HANDLE_MODEL_NAME_NAME]).c_str());
}

}