#include <vector>

#include "MovementSystem.h"
#include "SystemBase.h"
#include "Transform.h"
#include "Velocity.h"
#include "ComponentDataChunk.h"
#include "ComponentMask.h"
#include "MathUtil.h"

namespace HaraProject::Framework {

/**
* @brief �R���X�g���N�^
*/
MovementSystem::MovementSystem(IEntityOperator* entityOperator, ISystemDistributor* systemDistributor, IChunkProvider* chunkProvider)
	: SystemBase(entityOperator, systemDistributor, chunkProvider)
{
}

/**
* @brief �V�X�e���X�V
*/
void MovementSystem::UpdateSystem(float deltaTime)
{
	// �ʒu�Ƒ��x���܂ރ`�����N��S�Ď擾
	std::vector<ComponentDataChunk*> chunks = FindChunks<Transform, Velocity>();
	if (chunks.empty())return;

	// �`�����N���Ƃɏ���
	for (auto& chunk : chunks)
	{
		// �擪�̈ʒu�Ƒ��x���擾
		Transform* transform = reinterpret_cast<Transform*>(chunk->CalculateComponentDataPointer(ComponentMask<Transform>::bit, 0));
		Velocity* velocity = reinterpret_cast<Velocity*>(chunk->CalculateComponentDataPointer(ComponentMask<Velocity>::bit, 0));
		
		// �`�����N���̃G���e�B�e�B�����擾
		uint32_t num_entities = chunk->GetNumEntities();

		// �G���e�B�e�B���Ƃɏ���
		for (int i = 0; i < num_entities; ++i)
		{
			// �����łȂ����
			if (transform->IsAble() && transform != nullptr && velocity->IsAble() && velocity != nullptr)
			{
				// �ړ����x�ɉ����Ĉʒu���X�V
				transform->position = MathUtil::AddFloat3(transform->position,
					MathUtil::ScalingFloat3(velocity->linearVelocity, deltaTime)
				);

				// ��]���x�ɉ����ĉ�]���X�V
				transform->rotation = MathUtil::AddFloat3(transform->rotation, 
					MathUtil::ScalingFloat3(velocity->angularVelocity, deltaTime)
				);
			}

			// ���̃G���e�B�e�B�֐i�߂�
			++transform;
			++velocity;
		}
	}
}

}//!namespace HaraProject::Framework
