

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Windows.h>

#include "Include/ShaderLoader.h"
#include "Include/Camera.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Include/stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
bool processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 900;

//adjustable settings
double Zoom = 1;
double xCoord = 0;
double yCoord = 0;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;


float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader zprogram
    // ------------------------------------
    ShaderLoader ourShader("Shaders/Vertex/vertex.vs", "Shaders/Fragment/fragment.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    //float vertices[] = {
    //    // positions          // texture coords
    //     0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
    //     0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
    //    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
    //    -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
    //};

    float vertices[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
    };

    unsigned int indices[] = {
        0, 1, 2, // first triangle
        0, 3, 2  // second triangle
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    //glEnableVertexAttribArray(1);

    //// color attribute
    //glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    //glEnableVertexAttribArray(2);



    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE); //not sure if this helps for fragments of the same primitive
    // render loop
    // -----------

    std::vector<float> pixel_data(SCR_WIDTH * SCR_HEIGHT, 0.0f);
    float minIterations = 0;
    float maxIterations = 10;
    const int MAXITERATIONS = 2500;
    
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        
        ourShader.setDouble("xCoord", xCoord);
        ourShader.setDouble("yCoord", yCoord);
        ourShader.setFloat("minIterations", minIterations);
        ourShader.setFloat("maxIterations", maxIterations);
        ourShader.setDouble("Zoom", Zoom);

        //ourShader.setInt("Time", loopIterations);
        // input
        // -----

        if (deltaTime < 30) {
            SleepEx(30 - deltaTime, false);
        }
        
        ourShader.use();

        // render
        // ------
        //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //should be gl_ints since but fragdepth is a float, alas
        glReadPixels(0, 0, SCR_WIDTH, SCR_HEIGHT, GL_DEPTH_COMPONENT, GL_FLOAT, pixel_data.data());

        minIterations = 1;
        maxIterations = 0;
        for (int i = 0; i < SCR_WIDTH * SCR_HEIGHT; i++) {
            if (pixel_data[i] < minIterations) 
                minIterations = pixel_data[i];
            if (pixel_data[i] > maxIterations)
                maxIterations = pixel_data[i];
        }
        minIterations *= MAXITERATIONS;
        maxIterations *= MAXITERATIONS;


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        bool activated = processInput(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
bool processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    //2D stuff
    
    int interestedKeys[] = {
         GLFW_KEY_LEFT_SHIFT,
         GLFW_KEY_LEFT_CONTROL,
         GLFW_KEY_W,
         GLFW_KEY_S,
         GLFW_KEY_A,
         GLFW_KEY_D,
    };

    bool keyPressed = false;
    for (int i = 0; i < sizeof(interestedKeys) / sizeof(int); i++) {
        if (glfwGetKey(window, interestedKeys[i]) == GLFW_PRESS)
            keyPressed = true;
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        Zoom *= 1.05f;    
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        Zoom /= 1.05f;     
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        yCoord += 0.06f / Zoom; //if Zoom is a double, your coords also need to be doulbes, otherwise the movement can get 'locked' ~ +- 0
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        yCoord -= 0.06f / Zoom;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        xCoord -= 0.06f / Zoom; 
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        xCoord += 0.06f / Zoom;

    //camera stuff
    float cameraSpeed = 5.0f * deltaTime; // adjust accordingly

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        cameraSpeed *= 3;
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.ProcessKeyboard(UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWN, deltaTime);

    return keyPressed;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}