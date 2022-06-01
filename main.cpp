#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <load_shader.h>
#include <camera.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SOIL.h>
#include <generateMesh.h>

#define WIDTH 800
#define HEIGHT 800

Camera camera(glm::vec3(0.0f, 5.0f, 10.0f));
float lastX = (float)WIDTH / 2.0;
float lastY = (float)HEIGHT / 2.0;
bool firstMouse = true;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
float deltaTime = 0.0f;
float lastFrame = 0.0f;


int main() {
    Gen_mesh mesh1(glm::vec3(-8.0,0.0,-8.0),glm::vec3(8.0,0.0,-8.0),glm::vec3(-8.0,0.0,8.0),16);
    Gen_mesh mesh2(glm::vec3(8.0,0.0,8.0),glm::vec3(8.0,0.0,-8.0),glm::vec3(-8.0,0.0,8.0),16);
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,5);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window=glfwCreateWindow(WIDTH,HEIGHT,"learnOpenGl", nullptr, nullptr);
    if (window == nullptr){
        std::cout<<"Fail in open window!"<<std::endl;
        glfwTerminate();
        return 0;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glEnable(GL_DEPTH_TEST);
    Shader shader("vertice.vert","fragment.frag");


    shader.use();

    GLuint VAO[2],VBO[2];
    glCreateBuffers(2,VBO);
    glCreateVertexArrays(2,VAO);

    glBindVertexArray(VAO[0]);
    glNamedBufferStorage(VBO[0], mesh1.size()*sizeof(float),mesh1.getDate(),0);
    glBindBuffer(GL_ARRAY_BUFFER,VBO[0]);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO[1]);
    glNamedBufferStorage(VBO[1], mesh2.size()*sizeof(float),mesh2.getDate(),0);
    glBindBuffer(GL_ARRAY_BUFFER,VBO[1]);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);


    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    shader.setMat4("projection", projection);
    shader.setVec3("lightColor",1,1,1);
    shader.setVec3("lightPos", glm::vec3( 0.0f,  0.0f, 2.0f));
    shader.setInt("count",4);
    shader.setVec2("D[0]",0,-1);
    shader.setVec4("param[0]",0,0.1,2,2);
    glm::vec2 d1(-1,3);
    d1/=d1.length();
    shader.setVec2("D[1]",d1);
    shader.setVec4("param[1]",0,0.1,2,2);
    glm::vec2 d2(1,2);
    d2/=d2.length();
    shader.setVec2("D[2]",d2);
    shader.setVec4("param[2]",0.6,0.2,2,2);
    glm::vec2 d3(1,4);
    d3/=d3.length();
    shader.setVec2("D[3]",d3);
    shader.setVec4("param[2]",0,0.2,0.8,3);

    while (!glfwWindowShouldClose(window)){
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glm::mat4 view = camera.GetViewMatrix();
        shader.setMat4("view", view);
        shader.setVec2("time",lastFrame,0.0f);
        shader.use();


//        shader.setVec3("viewPos", camera.Position);

        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_LINES, 0, mesh1.size()/3);
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_LINES, 0, mesh2.size()/3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos){
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
