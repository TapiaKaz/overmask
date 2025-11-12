#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include "Model.h"
#include "Skybox.h"
#include "Objects.h"
#include "Render.h"  

#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"

const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;
Objects objects;
Skybox SkyboxDay, SkyboxNight;

Material Material_brillante;
Material Material_opaco;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

DirectionalLight mainLight;
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

static const char* vShader = "shaders/shader_light.vert";
static const char* fShader = "shaders/shader_light.frag";

//variables para keyframes
float reproduciranimacion, habilitaranimacion, guardoFrame, reinicioFrame, ciclo, ciclo2, contador = 0;

void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
    unsigned int vLength, unsigned int normalOffset)
{
    for (size_t i = 0; i < indiceCount; i += 3)
    {
        unsigned int in0 = indices[i] * vLength;
        unsigned int in1 = indices[i + 1] * vLength;
        unsigned int in2 = indices[i + 2] * vLength;
        glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
        glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
        glm::vec3 normal = glm::cross(v1, v2);
        normal = glm::normalize(normal);

        in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
        vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
        vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
        vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
    }

    for (size_t i = 0; i < verticeCount / vLength; i++)
    {
        unsigned int nOffset = i * vLength + normalOffset;
        glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
        vec = glm::normalize(vec);
        vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
    }
}

void CreateObjects()
{
    unsigned int indices[] = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2
    };

    GLfloat vertices[] = {
        -1.0f, -1.0f, -0.6f,    0.0f, 0.0f,     0.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 1.0f,      0.5f, 0.0f,     0.0f, 0.0f, 0.0f,
        1.0f, -1.0f, -0.6f,     1.0f, 0.0f,     0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,       0.5f, 1.0f,     0.0f, 0.0f, 0.0f
    };

    unsigned int floorIndices[] = {
        0, 2, 1,
        1, 2, 3
    };

    GLfloat floorVertices[] = {
        -10.0f, 0.0f, -10.0f,   0.0f, 0.0f,     0.0f, -1.0f, 0.0f,
        10.0f, 0.0f, -10.0f,    10.0f, 0.0f,    0.0f, -1.0f, 0.0f,
        -10.0f, 0.0f, 10.0f,    0.0f, 10.0f,    0.0f, -1.0f, 0.0f,
        10.0f, 0.0f, 10.0f,     10.0f, 10.0f,   0.0f, -1.0f, 0.0f
    };

    unsigned int vegetacionIndices[] = {
       0, 1, 2,
       0, 2, 3,
       4,5,6,
       4,6,7
    };

    GLfloat vegetacionVertices[] = {
        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f,     0.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f,      1.0f, 0.0f,     0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.0f,       1.0f, 1.0f,     0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f,      0.0f, 1.0f,     0.0f, 0.0f, 0.0f,

        0.0f, -0.5f, -0.5f,     0.0f, 0.0f,     0.0f, 0.0f, 0.0f,
        0.0f, -0.5f, 0.5f,      1.0f, 0.0f,     0.0f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.5f,       1.0f, 1.0f,     0.0f, 0.0f, 0.0f,
        0.0f, 0.5f, -0.5f,      0.0f, 1.0f,     0.0f, 0.0f, 0.0f,
    };

    Mesh* obj1 = new Mesh();
    obj1->CreateMesh(vertices, indices, 32, 12);
    meshList.push_back(obj1);

    Mesh* obj2 = new Mesh();
    obj2->CreateMesh(vertices, indices, 32, 12);
    meshList.push_back(obj2);

    Mesh* obj3 = new Mesh();
    obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
    meshList.push_back(obj3);

    Mesh* obj4 = new Mesh();
    obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
    meshList.push_back(obj4);

    calcAverageNormals(indices, 12, vertices, 32, 8, 5);
    calcAverageNormals(vegetacionIndices, 12, vegetacionVertices, 64, 8, 5);
}

void CreateShaders()
{
    Shader* shader1 = new Shader();
    shader1->CreateFromFiles(vShader, fShader);
    shaderList.push_back(*shader1);
}

int main()
{
    mainWindow = Window(1366, 768);
    mainWindow.Initialise();

    CreateObjects();
    CreateShaders();

    // Configuración de cámara
    camera = Camera(
        glm::vec3(0.0f, 15.0f, 15.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        -90.0f,
        -30.0f,
        0.3f,
        0.5f
    );
    camera.setThirdPersonMode(true);
    camera.setThirdPersonDistance(15.0f);
    camera.setThirdPersonHeight(5.0f);

    objects.LoadAll();

	// Crear skyboxes ====================================================
	// Vector de Skybox para noche
    std::vector<std::string> skyboxNightFaces;
    skyboxNightFaces.push_back("Textures/Skybox/Noche/galaxy+X.tga");
    skyboxNightFaces.push_back("Textures/Skybox/Noche/galaxy-X.tga");
    skyboxNightFaces.push_back("Textures/Skybox/Noche/galaxy-Y.tga");
    skyboxNightFaces.push_back("Textures/Skybox/Noche/galaxy+Y.tga");
    skyboxNightFaces.push_back("Textures/Skybox/Noche/galaxy+Z.tga");
    skyboxNightFaces.push_back("Textures/Skybox/Noche/galaxy-Z.tga"); // pos 5

	// Vector de Skybox para día
	std::vector<std::string> skyboxDayFaces;
    skyboxDayFaces.push_back("Textures/Skybox/Dia/clouds1_east.png");
    skyboxDayFaces.push_back("Textures/Skybox/Dia/clouds1_west.png");
    skyboxDayFaces.push_back("Textures/Skybox/Dia/clouds1_down.png");
    skyboxDayFaces.push_back("Textures/Skybox/Dia/clouds1_up.png");
    skyboxDayFaces.push_back("Textures/Skybox/Dia/clouds1_north.png");
	skyboxDayFaces.push_back("Textures/Skybox/Dia/clouds1_south.png"); // pos 11
    
    SkyboxDay = Skybox(skyboxDayFaces);
	SkyboxNight = Skybox(skyboxNightFaces);

    Material_brillante = Material(4.0f, 256);
    Material_opaco = Material(0.3f, 4);

    // =============== LUCES =================
	// Directional light Simula sol | la luz que siempre debe de estar ademas
    mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
        0.8f, 0.6f,
        0.0f, -1.0f, -0.3f);

	// Point Lights, faroles, etc -----------
    unsigned int pointLightCount = 0;

    // Navi - Lo pongo aqui primero, por que su luz no depende del dia ni de la noche
    pointLights[0] = PointLight(0.6f, 0.0f, 0.6f,
        20.0f, 10.0f,
        0.0f, 0.0f, 0.0f,
        1.3f, 1.2f, 1.1f);
    pointLightCount++;

    // Farol 1 - Los de aca son extras que después le tengo que mandar al shader cuando sea de noche
    pointLights[1] = PointLight(1.0f, 1.0f, 1.0f, 
        50.0f, 15.0f,          // Intensidad
        80.0f, 35.0f, 70.0f,  // Posición
        0.3f, 0.2f, 0.1f);   // Atenuación
    pointLightCount++;

    // Farol 2
    pointLights[2] = PointLight(1.0f, 1.0f, 1.0f,
        50.0f, 15.0f,
        -130.0f, 35.0f, 180.0f,
        0.3f, 0.2f, 0.1f);
    pointLightCount++;

    // Farol 3
    pointLights[3] = PointLight(1.0f, 1.0f, 1.0f,
        50.0f, 15.0f,
        -130.0f, 35.0f, 120.0f,
        0.3f, 0.2f, 0.1f);
    pointLightCount++;


	// Spot Lights Linterna navi -----------
    unsigned int spotLightCount = 0;
    spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
        0.3f, 3.0f,                 // intensidades ambiental y difusa
        0.0f, 0.0f, 0.0f,           // posición
        0.0f, -1.0f, 0.0f,          // dirección
        1.0f, 0.045f, 0.0075f,      // atenuación
        20.0f);                     // ángulo más concentrado
    spotLightCount++;

    GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
        uniformSpecularIntensity = 0, uniformShininess = 0;
    GLuint uniformColor = 0;
    glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);

    // Estado del personaje
    glm::vec3 dekuPosition = glm::vec3(0.0f, -1.0f, 0.0f);
    float dekuRotation = 0.0f;
    float dekuSpeed = 1.0f;  

    float walkAnimationTime = 0.0f;
    bool isWalking = false;

    float time = 0.0f;
	float dayDuration = 3000.0f; // Duración completa del ciclo día-noche
    bool booltime = true; 

    // VARIABLES PARA CICLO DÍA/NOCHE
    float dayNightCycle = 0.0f;           // 0.0 a 1.0
    float cycleSpeed = 1.0f / 20.0f;     // Ciclo completo en 120 segundos (2 minutos)
    bool autoCycle = true;                // Ciclo automático activado
    float sunAngle;
    float sunDirX;
    float sunDirY;
    float sunDirZ;

    // Colores según hora del día
    glm::vec3 dayLightColor(1.0f, 0.95f, 0.8f);
    glm::vec3 sunsetColor(1.0f, 0.6f, 0.3f);
    glm::vec3 nightLightColor(0.15f, 0.15f, 0.3f);

    glm::vec3 currentLightColor;

    // Intensidad de la luz del sol
    float currentAmbient, currentDiffuse;

    // Variables para apagar luces en el dia
    GLuint activeLightCount;

    // Loop principal
    while (!mainWindow.getShouldClose())
    {
        GLfloat now = glfwGetTime();
        deltaTime = now - lastTime;
        deltaTime += (now - lastTime) / limitFPS;
        lastTime = now;

        glfwPollEvents();

		// ===== CONFIGURACIÓN DE ILUMINACIÓN SEGÚN HORA DEL DÍA =====
        // Normalizar el tiempo al ciclo (0.0 a 1.0)
        dayNightCycle = time / dayDuration;

        // Transición de colores sincronizada con skybox ========
        if (dayNightCycle < 0.4f)
        {
            currentLightColor = dayLightColor;
        }
        else if (dayNightCycle < 0.5f)
        {
            float t = (dayNightCycle - 0.4f) / 0.1f;
            currentLightColor = glm::mix(dayLightColor, sunsetColor, t);
        }
        else if (dayNightCycle < 0.6f)
        {
            float t = (dayNightCycle - 0.5f) / 0.1f;
            currentLightColor = glm::mix(sunsetColor, nightLightColor, t);
        }
        else
        {
            currentLightColor = nightLightColor;
        }

        if (dayNightCycle < 0.5f)
        {
            currentAmbient = 0.8f;
            currentDiffuse = 0.6f;
        }
        else
        {
            float t = (dayNightCycle - 0.5f) / 0.5f;
            currentAmbient = glm::mix(0.8f, 0.15f, t);
            currentDiffuse = glm::mix(0.6f, 0.1f, t);
        }

        // Dirección del sol ========================
        sunAngle = dayNightCycle * 3.14159f;
        sunDirX = sin(sunAngle) * 0.3f;
        sunDirY = -cos(sunAngle);
        sunDirZ = -0.3f;

        mainLight = DirectionalLight(
            currentLightColor.r, currentLightColor.g, currentLightColor.b,
            currentAmbient, currentDiffuse,
            sunDirX, sunDirY, sunDirZ
        );

        // ===== ZOOM CON RUEDA DEL MOUSE =====
        float scrollOffset = mainWindow.getScrollChange();
        if (scrollOffset != 0.0f)
        {
            float currentDistance = camera.getThirdPersonDistance();
            currentDistance -= scrollOffset * 2.0f;

            if (currentDistance < 5.0f) currentDistance = 5.0f;
            if (currentDistance > 300.0f) currentDistance = 300.0f;

            camera.setThirdPersonDistance(currentDistance);
        }

        // ===== MOVIMIENTO DEL PERSONAJE =====
        glm::vec3 movement(0.0f);
        isWalking = false;

        if (mainWindow.isMoving())
        {
            isWalking = true;

            glm::vec3 forward = camera.getCameraDirection();
            forward.y = 0.0f;
            forward = glm::normalize(forward);

            glm::vec3 right = glm::normalize(glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f)));

            if (mainWindow.isMovingForward())
                movement += forward;
            if (mainWindow.isMovingBackward())
                movement -= forward;
            if (mainWindow.isMovingRight())
                movement += right;
            if (mainWindow.isMovingLeft())
                movement -= right;

            if (glm::length(movement) > 0.0f)
            {
                movement = glm::normalize(movement);
                dekuPosition += movement * dekuSpeed * deltaTime;
                dekuRotation = glm::degrees(atan2(movement.x, movement.z));
            }
        }

        // ===== ANIMACION DE CAMINATA =====
        if (isWalking)
        {
            walkAnimationTime += deltaTime * 0.1f;  //  velocidad 
        }

        float armSwing = isWalking ? sin(walkAnimationTime) * 30.0f : 0.0f;
        float legSwing = isWalking ? sin(walkAnimationTime) * 15.0f : 0.0f;

		// Configuración de cámara de link
        camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
        camera.followTarget(dekuPosition + glm::vec3(0.0f, 2.0f, 0.0f), deltaTime);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// ======= == MANEJO DEL TIEMPO (dia, atardecer, noche) ==============
        if (time < dayDuration/2) {
            SkyboxDay.DrawSkybox(camera.calculateViewMatrix(), projection);
        }
        else {
            SkyboxNight.DrawSkybox(camera.calculateViewMatrix(), projection);
            if (time >= dayDuration) {
                time = 0.0f;
			}
		} // cada etapa del dia (noche, dia) corresponde a la mitad del tiempo total
        time++;


        shaderList[0].UseShader();
        uniformModel = shaderList[0].GetModelLocation();
        uniformProjection = shaderList[0].GetProjectionLocation();
        uniformView = shaderList[0].GetViewLocation();
        uniformEyePosition = shaderList[0].GetEyePositionLocation();
        uniformColor = shaderList[0].getColorLocation();
        uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
        uniformShininess = shaderList[0].GetShininessLocation();

        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
        glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);
     
        RenderFloor(uniformModel, uniformColor, uniformSpecularIntensity, uniformShininess, objects, Material_opaco, meshList);
        RenderLampara(uniformModel, objects);
        RenderSalesMan(uniformModel, objects);
        RenderPiramide(uniformModel, objects);
        RenderReloj(uniformModel, objects, glfwGetTime());
        RenderRing(uniformModel, objects);
        RenderSkullKid(uniformModel, objects);
        RenderDekuLink(uniformModel, objects, dekuPosition, dekuRotation, armSwing, legSwing);
        RenderLuna(uniformModel, objects, glfwGetTime());
		RenderParedes(uniformModel, objects);
        RenderCucko(uniformModel, objects, glfwGetTime());
		RenderAmbiente(uniformModel, objects);

        glm::vec3 naviPos(
            dekuPosition.x,
            sin(glfwGetTime() * 3.0f) * 0.5f + 7.0, // leve oscilación
            dekuPosition.z
        );

        RenderNavi(uniformModel, objects, naviPos, glm::vec3(0.0f, dekuRotation, 0.0f));

        // ===== CONFIGURAR SPOT LIGHT (Navi) - Independiente del al ciclo día/noche =====
        unsigned int activeSpotLightCount = 0;

        if (mainWindow.getEstadoNavi())
        {
            // Calcular la dirección hacia donde mira Deku basándose en su rotación
            float dekuRadians = glm::radians(dekuRotation);
            glm::vec3 dekuDirection(
                sin(dekuRadians),  // X
                -0.3f,             // Y (apuntando un poco acia abajo)
                cos(dekuRadians)   // Z
            );

            spotLights[0].SetFlash(naviPos, dekuDirection);
            activeSpotLightCount = 1;
        }
        else
        {
            activeSpotLightCount = 0; // Navi apagada, no se envía al shader
        }
        
        // =================== CONFIGURACIÓN DE POINT LIHGTS PARA DIA Y NOCHE ==============

		// Luz puntual de navi (con la que brilla) ==============
		pointLights[0].setPosition(naviPos);

		activeLightCount = 1; // La cuenta empieza en 1, por que la luz de navi siempre esta activa

        bool isNight = (dayNightCycle >= 0.575f); // Lo puse un poco mas después de las 0.5 para que se note como se apagan y prenden las luces

        if (isNight) activeLightCount = pointLightCount; // Todas las point lights activas (La de los faros)
        else activeLightCount = 1; // NO se envían point lights al shader (Excepto la de Navi)
        
        // ===== ENVIAR LUCES AL SHADER =====
        shaderList[0].SetDirectionalLight(&mainLight);
        shaderList[0].SetPointLights(pointLights, activeLightCount);
        shaderList[0].SetSpotLights(spotLights, activeSpotLightCount);   

        glDisable(GL_BLEND);
        glUseProgram(0);
        mainWindow.swapBuffers();
    }
    return 0;
}