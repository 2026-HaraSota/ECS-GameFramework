/**
* @file   Transform.h
* @brief　当たり判定用ボックス
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _COLLISION_BOX_H_
#define _COLLISION_BOX_H_

#include <DirectXMath.h>

#include "ComponentDataBase.h"

#ifdef _DEBUG
#include "GuiManager.h"
#include "GuiItemBase.h"
#include "GuiTreeNode.h"
#include "GuiInputFloat3.h"
#endif // _DEBUG

namespace HaraProject::Framework
{

class CollisionBox : public ComponentDataBase
{
public:
	/**
	* @brief コンポーネント名"CollisionjBox"
	*/
	static constexpr const char* COLLISION_BOX_NAME = "CollisionBox";

	/**
	* @brief 各プロパティ記録用の名前
	*/
	static constexpr const char* COLLISION_BOX_CENTER_NAME = "center";
	static constexpr const char* COLLISION_BOX_SIZE_NAME = "size";

	/**
	* @brief デフォルトコンストラクタ
	*/
	CollisionBox() = default;

	/**
	* @brief コピーコンストラクタ
	* @param[in] base Transformが入った基底クラスポインタ
	*/
	CollisionBox(ComponentDataBase* base);

	/**
	* @brief Jsonデータから値を設定する
	* @param[in] json jsonオブジェクト
	*/
	void SetDataFromJson(nlohmann::json jsonData)override;

#ifdef _DEBUG
	/**
	* @brief 現在の値をJsonデータに変換する
	*/
	nlohmann::json WriteDataToJson()override
	{
		nlohmann::json jsonData;

		jsonData[COLLISION_BOX_NAME][COLLISION_BOX_CENTER_NAME] = { center.x,center.y,center.z };
		jsonData[COLLISION_BOX_NAME][COLLISION_BOX_SIZE_NAME] = { size.x,size.y,size.z };

		return jsonData;
	}

	/**
	* @brief インスペクタ―表示作成
	*/
	GuiItemBase* CreateDetailContent(GuiManager* guiManager)override
	{
		GuiTreeNode* transform_gui = guiManager->CreateGuiTreeNode(COLLISION_BOX_NAME, "id");
		transform_gui->AddChildren(
			guiManager->CreateGuiInputDragFloat3(COLLISION_BOX_CENTER_NAME, "id", &center, 0.1f),
			guiManager->CreateGuiInputDragFloat3(COLLISION_BOX_SIZE_NAME, "id", &size, 0.1f)
		);
		return transform_gui;
	};
#endif // _DEBUG

	/**
	* @brief ローカル空間での中央位置
	*/
	DirectX::XMFLOAT3 center;

	/**
	* @brief サイズ
	*/
	DirectX::XMFLOAT3 size;

#if _DEBUG
	/**
	* @brief 選択されているか
	*/
	bool isSelect;
#endif
};

}// !namespace HaraProject::Framework

#endif // !_COLLISION_BOX_H_