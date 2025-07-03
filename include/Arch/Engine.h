#pragma once
#include <vector>
#include <memory>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Arch/Object.h"

namespace Arch {

  class Engine {
  public:
    Engine(int width, int height, const std::string& title);
    ~Engine();

    Object* add_object(std::unique_ptr<Object> obj);
    void run();

  private:
    void initShader();
    void render();

    GLFWwindow* window = nullptr;
    int width, height;
    std::string title;

    std::vector<std::unique_ptr<Object>> objects;
    GLuint shaderProgram = 0;

    static const char* vertexShaderSrc;
    static const char* fragmentShaderSrc;
  };

}
