#ifndef VIOLET_CAMERA_H_
#define VIOLET_CAMERA_H_

#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace Violet {
  class Camera {
        public:
              const glm::mat4& getProjectionMatrix() const { return m_ProjectionMatrix; }
              const glm::mat4& getViewMatrix() const { return m_ViewMatrix; }
              const glm::mat4& getViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
        protected:
              glm::mat4 m_ProjectionMatrix;
              glm::mat4 m_ViewMatrix;
              glm::mat4 m_ViewProjectionMatrix;
  };

  class OrthographicCamera: public Camera {
      public:
      OrthographicCamera(float left, float right, float bottom, float top);

      const glm::vec3& getPosition() const { return m_Position; }
      void setPosition(const glm::vec3 position) { m_Position = position; recalculateViewProjectionMatrix(); }

      float getRotation() const { return m_Rotation; }
      void setRotation(float rotation) { m_Rotation = rotation; recalculateViewProjectionMatrix(); }
      private:
      void recalculateViewProjectionMatrix();

      glm::vec3 m_Position = {0.0f, 0.0f, 0.0f};
      float m_Rotation = 0.0f;
  };
}


#endif // VIOLET_CAMERA_H_
