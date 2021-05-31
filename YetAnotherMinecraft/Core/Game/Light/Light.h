#include "../GameObject/GameObject.h"

namespace REngine {
    class Light : public IGameObject {
    public:
        virtual void Move(glm::vec3 newCoords) override;
        virtual void Scale(glm::vec3 scaleVec) override;
        virtual void OnUpdate() override;
        virtual glm::mat4& GetModelMatrix() override;

        inline glm::vec3& GetDirection() { return direction; }
        inline glm::vec3& GetAmbientColor() { return ambientColor; }
        inline glm::vec3& GetDiffuseColor() { return diffuseColor; }

        void SetDirection(glm::vec3& direction);
        void SetAmbientColor(glm::vec3& color);
        void SetDiffuseColor(glm::vec3& color);

        Light() : direction(3.0f, 5.0f, 0.0f), diffuseColor(1.0f), ambientColor(0.8f) {}
    private:
        glm::vec3 direction;
        glm::vec3 ambientColor;
        glm::vec3 diffuseColor;
    };
}