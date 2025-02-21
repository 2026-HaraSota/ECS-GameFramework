#include "ModelHandle.h"

namespace HaraProject::Framework
{

/**
* @brief コンストラクタ
*/
ModelHandle::ModelHandle()
	: model(nullptr)
	, modelName("nothing")
{}

/**
* @brief コピーコンストラクタ
* @param[in] base 値が入った基底クラスポインタ
*/
ModelHandle::ModelHandle(ComponentDataBase* base)
{
	ModelHandle* value = dynamic_cast<ModelHandle*>(base);
	strcpy_s(modelName, value->modelName);
	model = nullptr;
}

/**
* @brief Jsonデータから値を設定する
* @param[in] json jsonオブジェクト
*/
void HaraProject::Framework::ModelHandle::SetDataFromJson(nlohmann::json jsonData)
{
	strcpy_s(modelName, std::string(jsonData[MODEL_HANDLE_MODEL_NAME_NAME]).c_str());
}

}