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
* @brief コンストラクタ
*/
MovementSystem::MovementSystem(IEntityOperator* entityOperator, ISystemDistributor* systemDistributor, IChunkProvider* chunkProvider)
	: SystemBase(entityOperator, systemDistributor, chunkProvider)
{
}

/**
* @brief システム更新
*/
void MovementSystem::UpdateSystem(float deltaTime)
{
	// 位置と速度を含むチャンクを全て取得
	std::vector<ComponentDataChunk*> chunks = FindChunks<Transform, Velocity>();
	if (chunks.empty())return;

	// チャンクごとに処理
	for (auto& chunk : chunks)
	{
		// 先頭の位置と速度を取得
		Transform* transform = reinterpret_cast<Transform*>(chunk->CalculateComponentDataPointer(ComponentMask<Transform>::bit, 0));
		Velocity* velocity = reinterpret_cast<Velocity*>(chunk->CalculateComponentDataPointer(ComponentMask<Velocity>::bit, 0));
		
		// チャンク内のエンティティ数を取得
		uint32_t num_entities = chunk->GetNumEntities();

		// エンティティごとに処理
		for (int i = 0; i < num_entities; ++i)
		{
			// 無効でなければ
			if (transform->IsAble() && transform != nullptr && velocity->IsAble() && velocity != nullptr)
			{
				// 移動速度に応じて位置を更新
				transform->position = MathUtil::AddFloat3(transform->position,
					MathUtil::ScalingFloat3(velocity->linearVelocity, deltaTime)
				);

				// 回転速度に応じて回転を更新
				transform->rotation = MathUtil::AddFloat3(transform->rotation, 
					MathUtil::ScalingFloat3(velocity->angularVelocity, deltaTime)
				);
			}

			// 次のエンティティへ進める
			++transform;
			++velocity;
		}
	}
}

}//!namespace HaraProject::Framework
