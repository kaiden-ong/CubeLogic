#include "shaderClass.h"

std::string get_file_contents(const char* filename) {
    std::cout << "Trying to open file: " << filename << std::endl;
    std::ifstream in(filename, std::ios::binary);
    if (in) {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return(contents);
    }
    throw std::runtime_error("Failed to open file: " + std::string(filename) + " (errno: " + std::to_string(errno) + ")");
}

Shader::Shader(const char* vertexFile, const char* fragmentFile) {
    std::cout << "Getting vert file" << std::endl;
    std::string vertexCode = get_file_contents(vertexFile);
    std::cout << "Getting frag file" << std::endl;
    std::string fragmentCode = get_file_contents(fragmentFile);

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);   
}

void Shader::Activate() {
    glUseProgram(ID);
}

void Shader::Delete() {
    glDeleteProgram(ID);
}