#pragma once

#include <glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <vector>

#include "Objects.h"
#include "Material.h"
#include "Mesh.h"

// Persnaje principal
void RenderDekuLink(GLuint uniformModel, Objects& objects,
    glm::vec3 position = glm::vec3(-5.0f, 0.0f, 0.0f),
    float rotation = 0.0f,
    float armSwing = 0.0f,
    float legSwing = 0.0f);

// NPCs
void RenderSalesMan(GLuint uniformModel, Objects& objects,
    glm::vec3 position = glm::vec3(8.0f, 3.5f, 110.0f));

void RenderSkullKid(GLuint uniformModel, Objects& objects,
    glm::vec3 position = glm::vec3(-10.0f, 3.5f, 90.0f));

void RenderNavi(GLuint uniformModel, Objects& objects,
    glm::vec3 position, glm::vec3 rotation);

void RenderCucko(GLuint uniformModel, Objects& objects, GLfloat time);

void RenderLuna(GLuint uniformModel, Objects& objects, GLfloat time, glm::vec3 position = glm::vec3(-0.0f, 70.0f, 100.0f));

// Entorno

void RenderFloor(GLuint uniformModel, GLuint uniformColor, GLuint uniformSpecularIntensity,
    GLuint uniformShininess, Objects& objects, Material& material,
    std::vector<Mesh*>& meshList);

void RenderParedes(GLuint uniformModel, Objects& objects);

void RenderLampara(GLuint uniformModel, Objects& objects);

void RenderPiramide(GLuint uniformModel, Objects& objects,
    glm::vec3 position = glm::vec3(-250.0f, -2.5f, 150.0f));

void RenderAmbiente(GLuint uniformModel, Objects& objects);

void RenderReloj(GLuint uniformModel, Objects& objects, GLfloat time,
    glm::vec3 position = glm::vec3(0.0f, -1.0f, 300.0f));

void RenderRing(GLuint uniformModel, Objects& objects,
    glm::vec3 position = glm::vec3(0.0f, -1.0f, 100.0f));