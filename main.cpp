/*#include <QCoreApplication>
#include <iostream>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    std::cout << "hi";
    return a.exec();
}
*/
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
//#include "imgui/imgui.h"
//#include "imgui/imgui_impl_glfw_gl3.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

const char* vertexShaderSource =
                                 R"GLSL(#version 330 core
                                 layout(location = 0) in vec3 aPos;
                                 void main()
                                 {
                                     gl_Position = vec4(aPos.x,aPos.y, aPos.z,  1.0);
                                 })GLSL";

const char* fragmentShaderSource =
                                   R"GLSL(#version 330 core
                                   out vec4 FragColor;
                                   void main()
                                   {
                                       FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
                                   })GLSL";
int main()
{
     GLFWwindow* window;

     if(!glfwInit())
     {
         std::cout << "enable to load glfw\n";
         return -1;
     }
     window = glfwCreateWindow(1980, 1080, "lights", nullptr, nullptr);
     glfwMakeContextCurrent(window);
     glfwSwapInterval(1);

     if (!window) {
         glfwTerminate();
         return -1;
     }

     if(glewInit() != GLEW_OK){
         std::cout << "glew error\n";
         return -1;
     }

     float vertices[] = {
               0.5f,  0.5f, 0.0f,
              -0.5f,  0.5f, 0.0f,
               0.0f, -0.5f, 0.0f
     };
     unsigned int VAO;
         glGenVertexArrays(1, &VAO);
         glBindVertexArray(VAO);

     unsigned int vertexBuffer;
     glGenBuffers(1, &vertexBuffer);
     glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
     glBufferData(GL_ARRAY_BUFFER, 3 * 3 * sizeof(float), vertices, GL_STATIC_DRAW);

     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0 );
     glEnableVertexAttribArray(0);

     glBindBuffer(GL_ARRAY_BUFFER, 0);
         glBindVertexArray(VAO);
     unsigned int vertexShader;
     vertexShader = glCreateShader(GL_VERTEX_SHADER);
     glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
     glCompileShader(vertexShader);

     unsigned int fragmentShader;
     fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
     glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
     glCompileShader(fragmentShader);

     unsigned int shaderProgram;
     shaderProgram = glCreateProgram();

     glAttachShader(shaderProgram, vertexShader);
     glAttachShader(shaderProgram, fragmentShader);
     glLinkProgram(shaderProgram);
     glUseProgram(shaderProgram);
     glValidateProgram(shaderProgram);
     glDeleteShader(vertexShader);
     glDeleteShader(fragmentShader);

     while(!glfwWindowShouldClose(window))
     {
         glClear(GL_COLOR_BUFFER_BIT);
         glDrawArrays(GL_TRIANGLES, 0, 9);
         glfwSwapBuffers(window);
         glfwPollEvents();
     }
     glDeleteVertexArrays(1, &VAO);
     glDeleteProgram(shaderProgram);
     glfwTerminate();
     return 0;
}






















