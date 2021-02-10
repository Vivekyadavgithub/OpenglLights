#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);


// camera
glm::vec3 cameraPos   = glm::vec3(0.0f, 2.0f,  6.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

int main()
{
    GLFWwindow* window;
    if (!glfwInit())
    {
        std::cout << "no glfw\n";
        return -1;
    }

    window = glfwCreateWindow(900, 700, "opengl", nullptr, nullptr);

    if (!window) {
        glfwTerminate();
        return -1;
    }
    Assimp::Importer importer;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    if (glewInit() != GLEW_OK) {
        std::cout << "Error\n";
    }

    int width, height, nrChannels;
    unsigned char* data = stbi_load("/home/vivekmanjaro/project/opengllights/container.jpg", &width, &height, &nrChannels, 0);

    /*float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
    };*/

    float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  -0.3f, -5.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
        };
    /*float position[] = {
     0.5f/2.0f,  0.5f/2.0f, 0.0f/2.0f,  // top right
     0.5f/2.0f, -0.5f/2.0f, 0.0f/2.0f,  // bottom right
    -0.5f/2.0f, -0.5f/2.0f, 0.0f/2.0f,  // bottom left
    -0.5f/2.0f,  0.5f/2.0f, 0.0f,   // top left
     1.0f     ,  1.0f     , 1.0f
    };
    unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3,    // second triangle
    };
    float texCoords[] = {
            0.0f, 0.0f,  // lower-left corner
            1.0f, 0.0f,  // lower-right corner
            0.5f, 1.0f   // top-center corner
    };*/


    const char* vertexShaderSource =
        R"GLSL(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        //layout(location = 1) in vec3 aColor;
        layout(location = 1) in vec2 aTexCoord;
        //out vec3 ourColor;
        out vec2 TexCoord;
        //out mat4 ambient;
        uniform mat4 model;
        uniform mat4 projection;
        uniform mat4 view;
        void main()
        {
            //ambient = mat4(0.1f, 0.1f, 0.1f, 0.2f);
            gl_Position =   projection * view * model  * vec4(aPos, 1.0f);
            TexCoord = vec2(aTexCoord.x, 1 - aTexCoord.y);
        })GLSL";

    const char* fragmentShaderSource =
        R"GLSL(
        #version 330 core
        out vec4 FragColor;
        //in vec3 ourColor;
        in vec2 TexCoord;
        //in mat4 ambient;
        uniform mat4 objectcolor;
        uniform mat4 lightcolor;
        uniform sampler2D ourTexture;
        uniform float ambstrength;
        void main()
        {
             mat4 ambient = lightcolor * ambstrength;
             FragColor =  vec4(ambient * objectcolor);
        })GLSL";

    const char* vertexShaderSource2 =
        R"GLSL(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        //layout(location = 1) in vec3 aColor;
        layout(location = 1) in vec2 aTexCoord;
        //out vec3 ourColor;
        out vec2 TexCoord;
       // uniform mat4 transform;
        uniform mat4 model;
        uniform mat4 projection;
        uniform mat4 view;
        void main()
        {
        gl_Position =   projection * view * model  * vec4(aPos, 1.0f);
        //ourColor = aColor;
        TexCoord = vec2(aTexCoord.x, 1 - aTexCoord.y);
        })GLSL";

    const char* fragmentShaderSource2 =
        R"GLSL(
        #version 330 core
        out vec4 FragColor;
        //in vec3 ourColor;
        in vec2 TexCoord;

        uniform sampler2D ourTexture;
        void main()
        {
           //if(color == 0){
              FragColor =  vec4(1.0f, 1.0f, 1.0f, 1.0f);

        })GLSL";
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    //glBuffer
    glBufferData(GL_ARRAY_BUFFER, 5 * 6 * 6 * sizeof(float), vertices, GL_STATIC_DRAW);

    //glVertexAttribPointer(0, 8, GL_FLOAT, GL_FALSE, 8 * sizeof(unsigned), 0);
    //glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    //glEnableVertexAttribArray(2);
    /*unsigned int index_buffer;
    glGenBuffers(1, &index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned), indices, GL_STATIC_DRAW);*/



    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(VAO);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

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

    unsigned int vertexShader2;
    vertexShader2 = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader2, 1, &vertexShaderSource2, NULL);
    glCompileShader(vertexShader2);
    unsigned int fragmentShader2;
    fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
    glCompileShader(fragmentShader2);
    unsigned int shaderProgram2;
    shaderProgram2 = glCreateProgram();

    glAttachShader(shaderProgram2, vertexShader2);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);
    glUseProgram(shaderProgram2);
    glValidateProgram(shaderProgram2);
    glDeleteShader(vertexShader2);
    glDeleteShader(fragmentShader2);
    // 0. copy our vertices array in a buffer for OpenGL to use
    /*glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 1. then set the vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // 2. use our shader program when we want to render an object
    glUseProgram(shaderProgram);*/
    // 3. now draw the object
    //someOpenGLFunctionThatDrawsOurTriangle();
    //float timeValue = glfwGetTime();
    //float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    //int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
    //glUseProgram(shaderProgram);
    //glUseProgram(shaderProgram);
    //float timeValue = glfwGetTime();
    //float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    //int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
    //glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
    //glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // be sure to activate the shader before any calls to glUniform
        glUseProgram(shaderProgram);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        float currentFrame = glfwGetTime();
               deltaTime = currentFrame - lastFrame;
               lastFrame = currentFrame;
        processInput(window);
       // const float radius = 10.0f;
       // float camX = sin(glfwGetTime()) * radius;
        //float camZ = cos(glfwGetTime()) * radius;
        glm::mat4 view;
        //view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        //view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
        //glm::mat4 trans = glm::mat4(1.0f);
        //trans = glm::scale(trans, glm::vec3(0.3, 0.3, 0.3));
        //trans = glm::rotate(trans, /*(float)glfwGetTime() **/ glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        //trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
        //unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
        //glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        //glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)700 / (float)700 , 0.1f, 100.0f);
        //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

        unsigned int projection_loc = glGetUniformLocation(shaderProgram, "projection");
        glUniformMatrix4fv(projection_loc, 1, GL_FALSE, glm::value_ptr(projection));
        unsigned int view_loc = glGetUniformLocation(shaderProgram, "view");
        glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));
        glBindVertexArray(VAO);
        int i = 0;
        //glm::mat4 transform = glm::mat4(1.0f);
        // transform = glm::rotate(transform, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        //transform = glm::scale(transform, glm::vec3(1.5f, 1.0f, 1.0f));
        //unsigned int transform_loc = glGetUniformLocation(shaderProgram, "transform");
        //glUniformMatrix4fv(transform_loc, 1, GL_FALSE, glm::value_ptr(transform));
        glm::mat4 model = glm::mat4(1.0f);
       // model = glm::translate(model, glm::vec3(0.0f, -12.5f, 0.0f));
      //  model = glm::scale(model, glm::vec3(400.0f, 4.0f, 400.0f));
        //float angle = 1.0f * (i/1);
        //model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.3f, 0.03f));
        //i++;
        unsigned int postions_loc = glGetUniformLocation(shaderProgram, "model");
        glUniformMatrix4fv(postions_loc, 1, GL_FALSE, glm::value_ptr(model));
        glm::vec4 color;
        /*if(i == 0){
             color = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
        }*/
        color = glm::vec4(0.6f, 0.4f, 0.2f, 1.0f);
        //color = color * 0.1f;
        unsigned objcolor = glGetUniformLocation(shaderProgram, "objectcolor");
        glUniformMatrix4fv(objcolor, 1, GL_FALSE, glm::value_ptr(color));
        unsigned int light = glGetUniformLocation(shaderProgram, "lightcolor");
        glUniformMatrix4fv(light, 1, GL_FALSE, glm::value_ptr(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)));
        unsigned int strength = glGetUniformLocation(shaderProgram, "ambstrength");
        glUniform1f(strength, 0.1f);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glUseProgram(shaderProgram2);
        glm::mat4 model2 = glm::mat4(1.0f);
        model2 = glm::translate(model2, cubePositions[i + 1]);
        unsigned int postions_loc2 = glGetUniformLocation(shaderProgram2, "model");
        glUniformMatrix4fv(postions_loc2, 1, GL_FALSE, glm::value_ptr(model2));
        unsigned int projection_loc2 = glGetUniformLocation(shaderProgram2, "projection");
        glUniformMatrix4fv(projection_loc2, 1, GL_FALSE, glm::value_ptr(projection));
        unsigned int view_loc2 = glGetUniformLocation(shaderProgram2, "view");
        glUniformMatrix4fv(view_loc2, 1, GL_FALSE, glm::value_ptr(view));
        //color = glm::vec4(0.2f, 0.9f, 0.3f, 1.0f);
       // glUniformMatrix4fv(objcolor, 1, GL_FALSE, glm::value_ptr(color));
       // glUniformMatrix4fv(light, 1, GL_FALSE, glm::value_ptr(glm::vec4(0.3f, 1.0f, 0.7f, 1.0f)));
        glDrawArrays(GL_TRIANGLES, 0, 36);


        //glDrawArrays(GL_TRIANGLES, 0, 36);
        glfwSwapBuffers(window);
        // check and call events and swap the buffers
        glfwPollEvents();
    }

    stbi_image_free(data);
    glDeleteVertexArrays(1, &VAO);
    //glDeleteBuffers(1, &index_buffer);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = 2.5 * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
