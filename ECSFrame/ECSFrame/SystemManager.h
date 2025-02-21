/**
* @file   SystemManager.h
* @brief  システム管理クラス定義.
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _SYSTEM_MANAGER_H_
#define _SYSTEM_MANAGER_H_

#include <memory>
#include <vector>
#include <string>

#include "nlohmann/json.hpp"

#include "ISystemDistributor.h"
#include "IChunkProvider.h"
#include "IEntityOperator.h"

namespace HaraProject::Framework {

class SystemBase;
class SystemManager : public ISystemDistributor
{
public:
	/**
	* @brief 処理の種類(更新順決定用)
	* @attention 値が小さいほど優先度が高い
	*/
	enum class UpdateProcessType : uint8_t
	{
		PHYSICS,
		NONE,
		MAX_PROCESS_TYPE
	};

	/**
	* @brief 描画レイヤー
	* @attention 値が小さいほど優先度が高い
	*/
	enum class DrawLayer : uint8_t
	{
		UIFRONT,
		UI,
		OBJECT,
		MAX_DRAW_LAYER
	};

	/**
	* @brief 処理レイヤーの数
	*/
	static constexpr uint8_t MAX_PROCESS_TYPE = static_cast<uint8_t>(UpdateProcessType::MAX_PROCESS_TYPE);

	/**
	* @brief 描画レイヤーの数
	*/
	static constexpr uint8_t MAX_DRAW_LAYER = static_cast<uint8_t>(DrawLayer::MAX_DRAW_LAYER);

	/**
	* @brief コンストラクタ
	* @param[in] entityOperator エンティティ操作用
	* @param[in] chunkProvider チャンク取得用
	*/
	SystemManager(IEntityOperator* entityOperator, IChunkProvider* chunkProvider);

	/**
	* @brief デストラクタ
	*/
	~SystemManager();

	/**
	* @brief システム更新
	*/
	void UpdataSystems(float deltaTime);

	/**
	* @brief 描画システム更新
	*/
	void UpdateRenderSystems();

	/**
	* @brief システム登録
	* @param[in] processType 処理の種類
	* @param[in] isShare 他システムと共有するか
	* @param[in] name システム名
	*/
	template<typename T> void AddSystem(UpdateProcessType processType, bool isShare, std::string name);

	/**
	* @brief 描画システム登録
	* @param[in] layer 描画レイヤー
	* @param[in] isShare 他システムと共有するか
	* @param[in] name システム名
	*/
	template<typename T> void AddRenderSystem(DrawLayer layer, bool isShare, std::string name);

	/**
	* @brief システム取得
	* @param[in] bit システム名
	*/
	SystemBase* FindSystem(std::string name)override;

private:
	/**
	* @brief 共有システム解放
	*/
	void ReleaseSharedSystem();

	/**
	* @brief レイヤーごとの通常のシステム
	*/
	std::vector<std::vector<std::unique_ptr<SystemBase>>> m_systems;

	/**
	* @brief 他システムでも利用するシステム
	*/
	std::vector<std::unordered_map<std::string, SystemBase*>> m_shared_systems;

	/**
	* @brief レイヤーごとの描画システム
	*/
	std::vector<std::vector<std::unique_ptr<SystemBase>>> m_render_systems;

	/**
	* @brief 他システムでも利用する描画システム
	*/
	std::vector<std::unordered_map<std::string, SystemBase*>> m_shared_render_systems;

	/**
	* @brief エンティティ操作用
	*/
	IEntityOperator* m_entity_operator;

	/**
	* @brief チャンク取得用
	*/
	IChunkProvider* m_chunk_provider;
};

/**
* @brief システム登録
* @param[in] processType 処理の種類
* @param[in] isShare 他システムと共有するか
* @param[in] name システム名
*/
template<typename T>
inline void SystemManager::AddSystem(UpdateProcessType processType, bool isShare, std::string name)
{
	uint8_t process_type = static_cast<uint8_t>(processType);
	if (isShare)
	{
		if (!m_shared_systems[process_type].contains(name))
		{
			m_shared_systems[process_type][name] = new T(m_entity_operator, this, m_chunk_provider);
		}
	}
	else
	{
		m_systems[process_type].push_back(std::make_unique<T>(m_entity_operator, this, m_chunk_provider));
	}
}

/**
* @brief 描画システム登録
* @param[in] layer 描画レイヤー
* @param[in] isShare 他システムと共有するか
* @param[in] name システム名
*/
template<typename T>
inline void SystemManager::AddRenderSystem(DrawLayer layer, bool isShare, std::string name)
{
	uint8_t draw_layer = static_cast<uint8_t>(layer);
	if (isShare)
	{
		if (!m_shared_render_systems[draw_layer].contains(name))
		{
			m_shared_render_systems[draw_layer][name] = new T(m_entity_operator, this, m_chunk_provider);
		}
	}
	else
	{
		m_render_systems[draw_layer].push_back(std::make_unique<T>(m_entity_operator, this, m_chunk_provider));
	}
}

} // namespace HaraProject::Framework

#endif // !_SYSTEM_MANAGER_H_
