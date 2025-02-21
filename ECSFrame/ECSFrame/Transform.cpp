#include <DirectXMath.h>

#include "Transform.h"

namespace HaraProject::Framework {

/**
* @brief �R���X�g���N�^
*/
Transform::Transform()
    : position(0.0f, 0.0f, 0.0f)
    , rotation(0.0f, 0.0f, 0.0f)
    , scale(1.0f, 1.0f, 1.0f) {
}

/**
* @brief �R�s�[�R���X�g���N�^
* @param[in] base Transform�����������N���X�|�C���^
*/
Transform::Transform(ComponentDataBase* base) {
    Transform* value = dynamic_cast<Transform*>(base);
    position = value->position;
    rotation = value->rotation;
    scale = value->scale;
}

/**
* @brief Json�f�[�^����l��ݒ肷��
* @param[in] json json�I�u�W�F�N�g
*/
void Transform::SetDataFromJson(nlohmann::json jsonData) {
    position = DirectX::XMFLOAT3(
        jsonData[TRANSFORM_POSITION_NAME][0],
        jsonData[TRANSFORM_POSITION_NAME][1],
        jsonData[TRANSFORM_POSITION_NAME][2]);
    rotation = DirectX::XMFLOAT3(
        jsonData[TRANSFORM_ROTATION_NAME][0],
        jsonData[TRANSFORM_ROTATION_NAME][1],
        jsonData[TRANSFORM_ROTATION_NAME][2]);
    scale = DirectX::XMFLOAT3(
        jsonData[TRANSFORM_SCALE_NAME][0],
        jsonData[TRANSFORM_SCALE_NAME][1],
        jsonData[TRANSFORM_SCALE_NAME][2]);
}

/**
* @brief ���[���h�ϊ��s����쐬
*/
DirectX::XMFLOAT4X4& Transform::CaluculateWorldMatrix() {
    DirectX::XMFLOAT4X4 world{};
    DirectX::XMStoreFloat4x4(&world,
        DirectX::XMMatrixScaling(scale.x, scale.y, scale.z) *
        DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(rotation.x)) *
        DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(rotation.y)) *
        DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(rotation.z)) *
        DirectX::XMMatrixTranslation(position.x, position.y, position.z));
    return world;
}

/**
* @brief == �I�[�o�[���[�h
*/
bool Transform::operator==(const Transform& other) const {
    return MathUtil::Float3Equals(position, other.position) &&
        MathUtil::Float3Equals(rotation, other.rotation) &&
        MathUtil::Float3Equals(scale, other.scale);
}

/**
* @brief != �I�[�o�[���[�h
*/
bool Transform::operator!=(const Transform& other) const {
    return !(*this == other);
}
} // namespace HaraProject::Framework
