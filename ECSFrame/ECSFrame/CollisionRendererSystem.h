/**
* @file   CollisionRendererSystem.h
* @brief  コリジョン描画.
* @author Hara Sota.
* @date   //
*/
#ifndef _COLLISION_RENDERER_SYSTEM_H_
#define _COLLISION_RENDERER_SYSTEM_H_

#include "SystemBase.h"
#include "IEntityOperator.h"
#include "ISystemDistributor.h"
#include "IChunkProvider.h"
#ifdef _DEBUG
#include "GuiManager.h"
#include "GuiItemBase.h"
#include "GuiCheckBox.h"
#include "GuiInputFloat.h"
#include "GuiInputColor.h"
#endif // _DEBUG

namespace HaraProject::Framework {

class CollisionRendererSystem : public SystemBase
{
public:
	/**
	* @brief 登録用システム名
	*/
	static constexpr const char* COLLISION_RENDERER_SYSTEM = "CollisionRendererSystem";

	/**
	* @brief コンストラクタ
	*/
	CollisionRendererSystem(IEntityOperator* entityOperator, ISystemDistributor* systemDistributor, IChunkProvider* chunkProvider);

	/**
	* @brief システム更新
	*/
	void UpdateSystem(float deltaTime)override;

#ifdef _DEBUG
	/**
	* @brief Guiとして表示するオプションの作成
	*/
	GuiItemBase* CreateGuiOption(GuiManager* guiManager) {
		GuiItemBase* item = guiManager->CreateGuiTreeNode(COLLISION_RENDERER_SYSTEM, "id");
		return item;
	}
#endif // _DEBUG

private:
	/**
	* @brief コリジョンを描画するか
	*/
	bool m_is_draw_collision;
};

} // namespace HaraProject::Framework

#endif // !_COLLISION_RENDERER_SYSTEM_H_