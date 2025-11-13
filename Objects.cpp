#include "Objects.h"

Objects::Objects()
{
    // Constructor vacío
}

Objects::~Objects()
{
    // Destructor vacío (OpenGL limpia automáticamente)
}

void Objects::LoadTextures()
{
    // Cargar texturas básicas
    brickTexture = Texture("Textures/brick.png");
    brickTexture.LoadTextureA();

    dirtTexture = Texture("Textures/dirt.png");
    dirtTexture.LoadTextureA();

    plainTexture = Texture("Textures/plain.png");
    plainTexture.LoadTextureA();

    // Textura del piso (usa la que tengas activa)
    pisoTexture = Texture("Textures/pisomadera.png");
    pisoTexture.LoadTextureA();
}

void Objects::LoadModels()
{
    // Cargar modelo de Navi
    Navi = Model();
    Navi.LoadModel("Models/Navi.obj");

    // Cargar modelo de la Lampara
    Lamp = Model();
    Lamp.LoadModel("Models/Lamp.obj");

	// Cargar modelo de la Choza
	Choza = Model();
	Choza.LoadModel("Models/Choza.obj");

    // Cargar Modelos de Deku Link

	DekuBase = Model();
	DekuBase.LoadModel("Models/DekuLink/DekuBase.obj");

	DekuBrazo = Model();
	DekuBrazo.LoadModel("Models/DekuLink/DekuBrazo.obj");

	DekuPierna = Model();
	DekuPierna.LoadModel("Models/DekuLink/DekuPierna.obj");

    // Cargar Luna
	Luna = Model();
	Luna.LoadModel("Models/Luna.obj");

    // Cargar hombre de las mascaras:
    Salesman = Model();
	Salesman.LoadModel("Models/Salesman.obj");

    // Cargar Piramide
    Piramide = Model();
	Piramide.LoadModel("Models/Piramide.obj");

	// Carga Modelos para Reloj
	Reloj = Model();
	Reloj.LoadModel("Models/Reloj/Reloj.obj");

	Manecillas = Model();
	Manecillas.LoadModel("Models/Reloj/Manecillas.obj");

	// Cargar Ring
	Ring = Model();
	Ring.LoadModel("Models/Ring.obj");

	// Cargar SkullKid
	SkullKid = Model();
	SkullKid.LoadModel("Models/SkullKid.obj");

	// Cargar Modelos delimitadores de mapa
	Cerca = Model();
	Cerca.LoadModel("Models/Paredes/Cerca.obj");

	Pared = Model();
	Pared.LoadModel("Models/Paredes/Pared.obj");

	Puesto = Model();
	Puesto.LoadModel("Models/Paredes/Puesto.obj");
    
	// Cargar Modelos de Cucko
	CuckoBase = Model();
	CuckoBase.LoadModel("Models/Cucko/CuckoBase.obj");

	CuckoAlaL = Model();
	CuckoAlaL.LoadModel("Models/Cucko/CuckoAlaL.obj");

	CuckoAlaR = Model();
	CuckoAlaR.LoadModel("Models/Cucko/CuckoAlaR.obj");

	CuckoPata = Model();
	CuckoPata.LoadModel("Models/Cucko/CuckoPata.obj");

	// Cargar Modelo de Mesa
	Mesa = Model();
	Mesa.LoadModel("Models/MesaCaja.obj");

	// Cargar Modelo de Nuez
	Nuez = Model();
	Nuez.LoadModel("Models/DekuLink/Nuez.obj");
}   

void Objects::LoadAll()
{
    LoadTextures();
    LoadModels();
}