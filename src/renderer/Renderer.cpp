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

    glUseProgram(shaderID);


    glm::mat4 view = currentCamera->GetCameraMatrix();
    glm::mat4 projection = currentCamera->GetProjectionMatrix(); // finns ingen anledning att få denna varje frame, där den basically bara kommer ändras när skärmen resizar
    unsigned int viewLocation = glGetUniformLocation(shaderID, "view");
    unsigned int projectionLocation = glGetUniformLocation(shaderID, "projection");
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
    
    
    glUniform1i(glGetUniformLocation(shaderID, "texture1"), 0);
    glUniform1i(glGetUniformLocation(shaderID, "texture2"), 1);

    for (Mesh& mesh : _Meshes)
    {
        mesh.Bind();

        unsigned int modelLocation = glGetUniformLocation(shaderID, "model");
        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(mesh.GetModelMatrix()));
        glDrawElements(GL_TRIANGLES, mesh.GetIndexCount() , mesh.GetIndexType(), nullptr);

    }

}

void Renderer::SetCurrentCamera(Camera *cameraToBeSet) // borde probably ha en lista eller något ifall det finns flera kameror
{
    currentCamera = cameraToBeSet;
}

Camera &Renderer::GetCurrentCamera()
{
    return *currentCamera;
}

void Renderer::AddMesh(Mesh& mesh)
{
    _Meshes.emplace_back(mesh);
} 
