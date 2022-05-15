
#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class ShaderLoader
{
public:
    // the program ID
    unsigned int ID;

    // constructor reads and builds the shader
    ShaderLoader(const char* vertexPath, const char* fragmentPath);
    // use/activate the shader
    void use();
    // utility uniform functions
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec3(const std::string& name, float value1, float value2, float value3) const;
    void setVec3(const std::string& name, glm::vec3 val) const;
    void setMat4(const std::string& name, glm::mat4 mat) const;
private:
    void checkCompileErrors(unsigned int shader, std::string type);
};