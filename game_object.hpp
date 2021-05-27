#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <memory>

#include "model.hpp"

namespace tvge {

struct TransformComponent {
    glm::vec3 translation{};  // (position offset)
    glm::vec3 scale{1.0f, 1.0f, 1.0f};
    glm::vec3 rotation{};

    // Matrix corresponds to translate * Ry * Rx * Rz * scale transformation
    // Rotation convertion uses tait-bryan angles with axis order Y(1), X(2), Z(3)
    glm::mat4 mat4() {
        auto transform = glm::translate(glm::mat4(1.0f), translation);
        transform = glm::rotate(transform, rotation.y, {0.0f, 1.0f, 0.0f});
        transform = glm::rotate(transform, rotation.x, {1.0f, 0.0f, 0.0f});
        transform = glm::rotate(transform, rotation.z, {0.0f, 0.0f, 1.0f});
        transform = glm::scale(transform, scale);
        return transform;
    }
};

class GameObject {
   public:
    using id_t = unsigned int;

    static GameObject createGameObject() {
        static id_t currentId = 0;
        return GameObject{currentId++};
    }

    GameObject(const GameObject&) = delete;
    GameObject& operator=(const GameObject&) = delete;
    GameObject(GameObject&&) = default;
    GameObject& operator=(GameObject&&) = default;

    id_t id() { return m_id; }

    std::shared_ptr<Model> model{};
    glm::vec3 color{};
    TransformComponent transform{};

   private:
    GameObject(id_t objId) : m_id{objId} {}

    id_t m_id;
};
}  // namespace tvge