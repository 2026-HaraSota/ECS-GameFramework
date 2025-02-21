/**
* @file   SystemManager.h
* @brief  �V�X�e���Ǘ��N���X��`.
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
	* @brief �����̎��(�X�V������p)
	* @attention �l���������قǗD��x������
	*/
	enum class UpdateProcessType : uint8_t
	{
		PHYSICS,
		NONE,
		MAX_PROCESS_TYPE
	};

	/**
	* @brief �`�惌�C���[
	* @attention �l���������قǗD��x������
	*/
	enum class DrawLayer : uint8_t
	{
		UIFRONT,
		UI,
		OBJECT,
		MAX_DRAW_LAYER
	};

	/**
	* @brief �������C���[�̐�
	*/
	static constexpr uint8_t MAX_PROCESS_TYPE = static_cast<uint8_t>(UpdateProcessType::MAX_PROCESS_TYPE);

	/**
	* @brief �`�惌�C���[�̐�
	*/
	static constexpr uint8_t MAX_DRAW_LAYER = static_cast<uint8_t>(DrawLayer::MAX_DRAW_LAYER);

	/**
	* @brief �R���X�g���N�^
	* @param[in] entityOperator �G���e�B�e�B����p
	* @param[in] chunkProvider �`�����N�擾�p
	*/
	SystemManager(IEntityOperator* entityOperator, IChunkProvider* chunkProvider);

	/**
	* @brief �f�X�g���N�^
	*/
	~SystemManager();

	/**
	* @brief �V�X�e���X�V
	*/
	void UpdataSystems(float deltaTime);

	/**
	* @brief �`��V�X�e���X�V
	*/
	void UpdateRenderSystems();

	/**
	* @brief �V�X�e���o�^
	* @param[in] processType �����̎��
	* @param[in] isShare ���V�X�e���Ƌ��L���邩
	* @param[in] name �V�X�e����
	*/
	template<typename T> void AddSystem(UpdateProcessType processType, bool isShare, std::string name);

	/**
	* @brief �`��V�X�e���o�^
	* @param[in] layer �`�惌�C���[
	* @param[in] isShare ���V�X�e���Ƌ��L���邩
	* @param[in] name �V�X�e����
	*/
	template<typename T> void AddRenderSystem(DrawLayer layer, bool isShare, std::string name);

	/**
	* @brief �V�X�e���擾
	* @param[in] bit �V�X�e����
	*/
	SystemBase* FindSystem(std::string name)override;

private:
	/**
	* @brief ���L�V�X�e�����
	*/
	void ReleaseSharedSystem();

	/**
	* @brief ���C���[���Ƃ̒ʏ�̃V�X�e��
	*/
	std::vector<std::vector<std::unique_ptr<SystemBase>>> m_systems;

	/**
	* @brief ���V�X�e���ł����p����V�X�e��
	*/
	std::vector<std::unordered_map<std::string, SystemBase*>> m_shared_systems;

	/**
	* @brief ���C���[���Ƃ̕`��V�X�e��
	*/
	std::vector<std::vector<std::unique_ptr<SystemBase>>> m_render_systems;

	/**
	* @brief ���V�X�e���ł����p����`��V�X�e��
	*/
	std::vector<std::unordered_map<std::string, SystemBase*>> m_shared_render_systems;

	/**
	* @brief �G���e�B�e�B����p
	*/
	IEntityOperator* m_entity_operator;

	/**
	* @brief �`�����N�擾�p
	*/
	IChunkProvider* m_chunk_provider;
};

/**
* @brief �V�X�e���o�^
* @param[in] processType �����̎��
* @param[in] isShare ���V�X�e���Ƌ��L���邩
* @param[in] name �V�X�e����
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
* @brief �`��V�X�e���o�^
* @param[in] layer �`�惌�C���[
* @param[in] isShare ���V�X�e���Ƌ��L���邩
* @param[in] name �V�X�e����
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
