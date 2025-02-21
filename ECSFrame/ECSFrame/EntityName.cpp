#include "EntityName.h"

namespace HaraProject::Framework
{

/**
* @brief コンストラクタ
*/
EntityName::EntityName()
	: name("unknown") 
{}

/**
* @brief コピーコンストラクタ
* @param[in] base EntityNameが入った基底クラスポインタ
*/
EntityName::EntityName(ComponentDataBase* base)
{
	EntityName* value = dynamic_cast<EntityName*>(base);
	strcpy_s(name, value->name);
}

/**
* @brief Jsonデータから値を設定する
* @param[in] json jsonオブジェクト
*/
void EntityName::SetDataFromJson(nlohmann::json jsonData)
{
	strcpy_s(name, std::string(jsonData[ENTITY_NAME_NAME_NAME]).c_str());
}

}