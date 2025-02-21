/**
* @file   CollisionBase.h
* @brief　当たり判定用基底コンポーネント
* @author Hara Sota.
*/
#ifndef _COLLISION_BASE_H_
#define _COLLISION_BASE_H_

#include <DirectXMath.h>

#include <cstdint>

#include "ComponentDataBase.h"

namespace HaraProject::Framework
{

class CollisionBase : public ComponentDataBase
{
public:
	/**
	* @brief データ名
	*/
	static constexpr const char* COLLISION_BOX_NAME = "CollisionBox";
	static constexpr const char* COLLISION_BOX_CENTER_NAME = "center";
	static constexpr const char* COLLISION_BOX_SIZE_NAME = "size";

	/**
	* @brief デフォルトコンストラクタ
	*/
	CollisionBase() = default;

	/**
	* @brief Jsonデータから値を設定する
	* @param[in] json jsonオブジェクト
	*/
	void SetDataFromJson(nlohmann::json jsonData)override{}

#ifdef _DEBUG
	/**
	* @brief 現在の値をJsonデータに変換する
	*/
	nlohmann::json WriteDataToJson()override{}
#endif // _DEBUG

};

}// !namespace HaraProject::Framework

#endif // !_COLLISION_BASE_H_