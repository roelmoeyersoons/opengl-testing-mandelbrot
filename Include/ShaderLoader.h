
#include <glad/glad.h> // include glad to get all the required OpenGL headers

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
    void setDouble(const std::string& name, double value) const;
private:
    void checkCompileErrors(unsigned int shader, std::string type);
};