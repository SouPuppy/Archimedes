#pragma once
#include <Math/Vec2.h>

namespace Arch {

  class Object {
  public:
    virtual void draw() = 0;
    virtual void resize(const Math::Vec2& a, const Math::Vec2& b) = 0;
    virtual ~Object() {}
  };

  class Triangle final : public Object {
  public:
    Triangle();
    ~Triangle() override;

    void draw() override;
    void resize(const Math::Vec2& a, const Math::Vec2& b) override;
  private:
    unsigned int VAO = 0, VBO = 0;
    Math::Vec2 v0 = {0, 0.5f}, v1 = {-0.5f, -0.5f}, v2 = {0.5f, -0.5f};
    void updateBuffer();
  };

}
