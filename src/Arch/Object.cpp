#include "Arch/Object.h"
#include <GL/glew.h>

namespace Arch {

  Triangle::Triangle() { updateBuffer(); }
  Triangle::~Triangle() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
  }
  void Triangle::updateBuffer() {
    float vertices[] = {v0.x, v0.y, 0.0f, v1.x, v1.y, 0.0f, v2.x, v2.y, 0.0f};

    if (!VAO)
      glGenVertexArrays(1, &VAO);
    if (!VBO)
      glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }
  void Triangle::draw() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
  }
  void Triangle::resize(const Math::Vec2 &a, const Math::Vec2 &b) {
    v0 = a;
    v1 = b;
    v2 = a + b;
    updateBuffer();
  }


} // namespace Arch
