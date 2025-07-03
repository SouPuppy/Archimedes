#include <Arch/Engine.h>
#include <Arch/Object.h>
#include <Math/Vec2.h>

int main() {
  Arch::Engine engine(800, 600, "Arch Minimal Engine");
  auto* tri = engine.add_object(std::make_unique<Arch::Triangle>());
  tri->resize(Math::Vec2(-0.8f, -0.5f), Math::Vec2(0.2f, -0.5f));
  engine.run();
  return 0;
}
