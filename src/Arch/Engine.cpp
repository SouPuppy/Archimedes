#include "Arch/Engine.h"
#include <iostream>
#include <stdexcept>

namespace Arch {

const char* Engine::vertexShaderSrc = R"(
#version 330 core
layout (location = 0) in vec3 position;
void main() { gl_Position = vec4(position, 1.0); }
)";

const char* Engine::fragmentShaderSrc = R"(
#version 330 core
out vec4 color;
void main() { color = vec4(1.0, 0.5, 0.2, 1.0); }
)";

Engine::Engine(int width, int height, const std::string& title)
    : width(width), height(height), title(title) {
    if (!glfwInit())
        throw std::runtime_error("GLFW init failed");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("GLFW window failed");
    }
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
        throw std::runtime_error("GLEW init failed");
    glViewport(0, 0, width, height);
    initShader();
}
Engine::~Engine() {
    glDeleteProgram(shaderProgram);
    glfwTerminate();
}
void Engine::initShader() {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}
Arch::Object* Engine::add_object(std::unique_ptr<Object> obj) {
    Object* ptr = obj.get();
    objects.push_back(std::move(obj));
    return ptr;
}
void Engine::run() {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        render();
        glfwSwapBuffers(window);
    }
}
void Engine::render() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    for (auto& obj : objects) {
        obj->draw();
    }
    glUseProgram(0);
}

}
