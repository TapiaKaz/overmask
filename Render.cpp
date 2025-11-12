#include "Render.h"
#include <math.h>
void RenderFloor(GLuint uniformModel, GLuint uniformColor, GLuint uniformSpecularIntensity,
    GLuint uniformShininess, Objects& objects, Material& material,
    std::vector<Mesh*>& meshList)
{
    glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(90.0f, 1.0f, 60.0f));

    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    glUniform3fv(uniformColor, 1, glm::value_ptr(color));

    objects.pisoTexture.UseTexture();
    material.UseMaterial(uniformSpecularIntensity, uniformShininess);
    meshList[2]->RenderMesh();
}

void RenderLampara(GLuint uniformModel, Objects& objects)
{
    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(-130.0f, -1.0f, 180.0f));
	model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.Lamp.RenderModel();

    model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(-130.0f, -1.0f, 120.0f));
    model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.Lamp.RenderModel();
}


void RenderLuna(GLuint uniformModel, Objects& objects, GLfloat time, glm::vec3 position)
{
    glm::mat4 model = glm::mat4(1.0);
    // Origen
    model = glm::translate(model, position);

	// Movimiento orbital
    model = glm::rotate(model, glm::radians(time*30), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(60.0f, 30.0f*std::sin(time), 0.0f)); // radio y ondulación
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // rota sobre su eje
	
    // Colocación inicial del objeto
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(135.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.Luna.RenderModel();
}

void RenderPiramide(GLuint uniformModel, Objects& objects, glm::vec3 position)
{
    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(2.0f, 1.5f, 2.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.Piramide.RenderModel();
}

void RenderReloj(GLuint uniformModel, Objects& objects, GLfloat time, glm::vec3 position)
{
    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(850.0f, 750.0f, 850.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.Reloj.RenderModel();

    model = glm::mat4(1.0);
    model = glm::translate(model, position+glm::vec3(-1.5f,74.0f,-28.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(time * 26.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(850.0f, 850.0f, 850.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.Manecillas.RenderModel();
}

void RenderRing(GLuint uniformModel, Objects& objects, glm::vec3 position)
{
    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(3.5f, 3.0f, 3.5f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.Ring.RenderModel();
 
}

// Render Limitadores de mapa

void RenderParedes(GLuint uniformModel, Objects& objects)
{
    // PAREDES =======
    // Pared 0
    glm::mat4 model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(0.0f, -1.0f, -49.0f));
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.Pared.RenderModel();

	// Pared 1
    model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(120.0f, -1.0f, 24.0f));
    model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.Pared.RenderModel();

	// Pared 2
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(165.0f, -1.0f, 144.0f));
	model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	objects.Pared.RenderModel();

    // Pared 3
    model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(165.0f, -1.0f, 309.0f));
    model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.Pared.RenderModel();

    // Pared 4
    model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(164.7f, -1.0f, 429.0f));
    model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.Pared.RenderModel();

	// Pared 5
    model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(46.0f, -1.0f, 485.0f));
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.Pared.RenderModel();

    // Pared 6
    model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(-66.0f, -1.0f, 485.0f));
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.Pared.RenderModel();

    // Pared 7
    model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(-142.0f, -1.0f, 414.0f));
    model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.Pared.RenderModel();

    // Pared 8
    model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(-274.0, -1.0f, 326.0f));
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.Pared.RenderModel();

    // Pared 9
    model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(-378.0, -1.0f, 326.0f));
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.Pared.RenderModel();

    // PUESTOS ======
	// Puesto 0
    model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(-80.0f, -1.5f, -50.0f));
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.Puesto.RenderModel();
	
    // Puesto 1
    model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(80.0f, -1.5f, -50.0f));
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.Puesto.RenderModel();

    // Puesto 2
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(166.0f, -1.5f, 229.0f));
	model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	objects.Puesto.RenderModel();

    // Puesto 3
    model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(126.0f, -1.5f, 483.0f));
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.Puesto.RenderModel();

    // Puesto 4
    model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(-143.0f, -1.5f, 449.0f));
    model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.Puesto.RenderModel();

    // Puesto 5
    model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(-194.0, -1.5f, 327.0f));
    model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.Puesto.RenderModel();

	// CERCAS =======
    model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(-197.0f, -1.5f, -36.0f));
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.Cerca.RenderModel();

    model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(-355.5f, -1.5f, -36.0f));
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.Cerca.RenderModel();

    // Cerca 0
    model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(-440.0f, -1.5f, 230.0f));
    model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.Cerca.RenderModel();

	// Cerca 1
    model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(-440.0f, -1.5f, 57.5f));
    model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.Cerca.RenderModel();
}

// DekuLink

void RenderDekuLink(GLuint uniformModel, Objects& objects, glm::vec3 position,
    float rotation, float armSwing, float legSwing)
{
    glm::vec3 scale = glm::vec3(0.15f, 0.15f, 0.15f);

    // CUERPO BASE
    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, scale);
    glm::mat4 modelBase = model;

    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.DekuBase.RenderModel();

    // BRAZO DERECHO
    model = modelBase;
    model = glm::translate(model, glm::vec3(-2.0f, 12.0f, 0.0f));
    model = glm::rotate(model, glm::radians(armSwing), glm::vec3(1.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.DekuBrazo.RenderModel();

    // BRAZO IZQUIERDO
    model = modelBase;
    model = glm::translate(model, glm::vec3(2.0f, 12.0f, 0.0f));
    model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(-armSwing), glm::vec3(1.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.DekuBrazo.RenderModel();

    // PIERNA DERECHA
    model = modelBase;
    model = glm::rotate(model, glm::radians(legSwing), glm::vec3(1.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.DekuPierna.RenderModel();

    // PIERNA IZQUIERDA
    model = modelBase;
    model = glm::translate(model, glm::vec3(-4.75f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(-legSwing), glm::vec3(1.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.DekuPierna.RenderModel();
}
// NPCs
void RenderSalesMan(GLuint uniformModel, Objects& objects, glm::vec3 position)
{
    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model, position);
	model = glm::rotate(model, glm::radians(215.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.Salesman.RenderModel();
}

void RenderSkullKid(GLuint uniformModel, Objects& objects, glm::vec3 position)
{
    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model, position);
	model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.002f, 0.002f, 0.002f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.SkullKid.RenderModel();
}

void RenderNavi(GLuint uniformModel, Objects& objects, glm::vec3 position, glm::vec3 rotation)
{
    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.Navi.RenderModel();
}

void RenderCucko(GLuint uniformModel, Objects& objects, GLfloat time) {
    glm::mat4 model = glm::mat4(1.0);
    
    // === CICLO DE MOVIMIENTO ===
    GLfloat cycle = fmod(time, 8.0f);
    bool forward = cycle < 4.0f;
    GLfloat progress = forward ? cycle / 4.0f : (cycle - 4.0f) / 4.0f;
    GLfloat move = forward ? progress * 15.0f : 15.0f - progress * 15.0f;
    GLfloat rot = forward ? 0.0f : 180.0f;
    
    model = glm::translate(model, glm::vec3(-100.0f, -1.0f, 57.5f - move));
    model = glm::rotate(model, glm::radians(180.0f + rot), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
    glm::mat4 modelaux = model;
    
    modelaux = glm::translate(modelaux, glm::vec3(0.0f, sin(time * 5.0f) * 0.15f, 0.0f));
    modelaux = glm::rotate(modelaux, glm::radians(sin(time * 3.0f) * 2.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelaux));
    objects.CuckoBase.RenderModel();
    
    GLfloat wing = sin(time * 8.0f) * 45.0f + 15.0f;
    
    model = modelaux;
    model = glm::translate(model, glm::vec3(-1.0f, 2.2f, 0.0f));
    model = glm::rotate(model, glm::radians(-wing), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::rotate(model, glm::radians(sin(time * 8.0f) * 10.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.CuckoAlaL.RenderModel();
    
    model = modelaux;
    model = glm::translate(model, glm::vec3(1.0f, 2.2f, 0.0f));
    model = glm::rotate(model, glm::radians(wing), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::rotate(model, glm::radians(sin(time * 8.0f) * 10.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.CuckoAlaR.RenderModel();
    
    model = modelaux;
    model = glm::translate(model, glm::vec3(-0.5f, 0.5f + abs(sin(time * 4.0f)) * 0.2f, -0.95f));
    model = glm::rotate(model, glm::radians(sin(time * 4.0f) * 25.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(sin(time * 4.0f) * 5.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.CuckoPata.RenderModel();
    
    model = modelaux;
    model = glm::translate(model, glm::vec3(0.5f, 0.5f + abs(sin(time * 4.0f + 3.14159f)) * 0.2f, -0.95f));
    model = glm::rotate(model, glm::radians(sin(time * 4.0f + 3.14159f) * 25.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(sin(time * 4.0f + 3.14159f) * 5.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.CuckoPata.RenderModel();
}
// Ambiente
void RenderAmbiente(GLuint uniformModel, Objects& objects)
{
    // Choza
    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(58.0f, -1.0f, -15.0f));
    model = glm::scale(model, glm::vec3(13.0f, 13.0f, 25.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.Choza.RenderModel();

    // Mesa Caja
    model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(90.0f, -1.0f, 25.0f));
    model = glm::scale(model, glm::vec3(15.0f, 10.0f, 20.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.Mesa.RenderModel();
}