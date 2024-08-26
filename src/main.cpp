#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "VAO.h"
#include "shaderClass.h"
#include "EBO.h"
#include "VBO.h"

GLFWwindow* createWindow();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInputs(GLFWwindow* window);
void drawTriangle(Shader shaderProgram, VAO VAO);
// GLuint loadShaders(const char* vertex_shader, const char* fragment_shader);
void cleanup(GLFWwindow* window, VAO VAO, VBO VBO, EBO EBO, Shader shaderProgram);

// triangle vertices
GLfloat vertices[] = {
    -1.0f, -1.0f, 0.0f, // bottom left
    1.0f, -1.0f, 0.0f, // bottom right
    0.0f, 1.0f, 0.0f, // top middle
    // smaller inside triangle
    0.0f, -1.0f, 0.0f, // bottom middle
    0.5f, 0.0f, 0.0f, // top left
    -0.5f, 0.0f, 0.0f // top right
};

GLuint indices[] = {
    0, 3, 5,
    3, 1, 4,
    5, 4, 2
};

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    std::cout << "Making Window" << std::endl;
    GLFWwindow* window = createWindow();
    if (window == NULL) {
        exit(EXIT_FAILURE);
    }
    // at this point screen will show up but close immediately

    std::cout << "Making Shader Program" << std::endl;

    Shader shaderProgram("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");

    std::cout << "Making VAO" << std::endl;
    VAO VAO1;
    std::cout << "Binding VAO" << std::endl;
    VAO1.Bind();

    std::cout << "Making VBO" << std::endl;
    VBO VBO1(vertices, sizeof(vertices));
    std::cout << "Making EBO" << std::endl;
    EBO EBO1(indices, sizeof(indices));

    std::cout << "Linking VBO to VAO" << std::endl;
    VAO1.LinkVBO(VBO1, 0);
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    // GLuint shaderProgram = loadShaders("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");

    // GLuint vertexbuffer, VAO, EBO;
    // glGenVertexArrays(1, &VAO);
    // glBindVertexArray(VAO);

    // glGenBuffers(1, &vertexbuffer);
    // glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // glGenBuffers(1, &EBO);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);

    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindVertexArray(0);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    while(glfwWindowShouldClose(window) == 0) {
        processInputs(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        drawTriangle(shaderProgram, VAO1);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    cleanup(window, VAO1, VBO1, EBO1, shaderProgram);
    exit(EXIT_SUCCESS);
}

GLFWwindow* createWindow() {
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return NULL;
    }
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // OpenGL 4.6
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // For Mac
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CubeLogic", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to initialize OPENGL window" << std::endl;
        glfwTerminate();
        return NULL;
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(EXIT_FAILURE);
    }
    return window;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInputs(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        std::cout << "W key is pressed" << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        std::cout << "S key is pressed" << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        std::cout << "A key is pressed" << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        std::cout << "D key is pressed" << std::endl;
    }
}

// void drawTriangle(GLuint vertexbuffer) {
//     glEnableVertexAttribArray(0);
//     glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

//     // Draws the triangle
//     glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0); // Starting from vertex 0 -> 3
//     glDisableVertexAttribArray(0);
// }

// std::string readShaderFile(const char* filePath) {
//     std::ifstream shaderFile;
//     shaderFile.open(filePath);
//     if (!shaderFile.is_open()) {
//         std::cerr << "Failed to open shader file: " << filePath << std::endl;
//         exit(EXIT_FAILURE);
//     }
//     std::stringstream shaderStream;
//     shaderStream << shaderFile.rdbuf();
//     shaderFile.close();
//     return shaderStream.str();
// }

// GLuint loadShaders(const char* vertex_shader, const char* fragment_shader) {
//     std::string vertexCode = readShaderFile(vertex_shader);
//     std::string fragmentCode = readShaderFile(fragment_shader);
//     const char* vertexShaderSource = vertexCode.c_str();
//     const char* fragmentShaderSource = fragmentCode.c_str();

//     GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
//     glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//     glCompileShader(vertexShader);

//     GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//     glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//     glCompileShader(fragmentShader);

//     GLuint shaderProgram = glCreateProgram();
//     glAttachShader(shaderProgram, vertexShader);
//     glAttachShader(shaderProgram, fragmentShader);
//     glLinkProgram(shaderProgram);
    
//     glDeleteShader(vertexShader);
//     glDeleteShader(fragmentShader);
//     return shaderProgram;
// }

void drawTriangle(Shader shaderProgram, VAO VAO) {
    shaderProgram.Activate();
    VAO.Bind();
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0); // Starting from vertex 0 -> 3
}

void cleanup(GLFWwindow* window, VAO VAO, VBO VBO, EBO EBO, Shader shaderProgram) {
    VAO.Delete();
    VBO.Delete();
    EBO.Delete();
    shaderProgram.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
}