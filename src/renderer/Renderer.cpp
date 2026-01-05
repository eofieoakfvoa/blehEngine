#include "Renderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <Services/InputService.h>

Renderer::Renderer(unsigned int shader)
    : UniformLocation(glGetUniformLocation(shader, "_Color")), shaderID(shader)
{
}

Renderer::~Renderer()
{
}

void Renderer::RenderFrame()
{
    
    float timeValue = glfwGetTime();
    float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    glUseProgram(shaderID);
    
    glm::mat4 model, view, projection;
    model = view = projection = glm::mat4(1.0f);

    model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f)); 
    view = currentCamera->GetCameraMatrix();
    projection = currentCamera->GetProjectionMatrix(); //finns ingen anledning att få denna varje frame, där den basically bara kommer ändras när skärmen resizar



    unsigned int modelLoc = glGetUniformLocation(shaderID, "model");
    unsigned int viewLoc  = glGetUniformLocation(shaderID, "view");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shaderID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));


    glUniform4f(UniformLocation, 0.0f, greenValue, 0.8f, 0.8f);
    glUniform1i(glGetUniformLocation(shaderID, "texture1"), 0);
    glUniform1i(glGetUniformLocation(shaderID, "texture2"), 1);

}

void Renderer::SetCurrentCamera(Camera* cameraToBeSet) //borde probably ha en lista eller något ifall det finns flera kameror
{
    currentCamera = cameraToBeSet;
}

Camera &Renderer::GetCurrentCamera()
{
    return *currentCamera;
}
