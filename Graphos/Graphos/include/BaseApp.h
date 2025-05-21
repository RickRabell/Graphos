#pragma once
#include <Prerequisites.h>
#include "Window.h"

class 
	BaseApp {
public:
	BaseApp() = default;
	~BaseApp();

	//Funci�n encargada de ejecutar la aplicaci�n en main
	int 
	run();

	//Funci�n de inicializaci�n
	bool
	init();

	//Funci�n que se actualiza por frame
	void
	update();

	//Funci�n de renderizado
	void
	render();

	void
	destroy();

private:
	//Son punteros globales para poder gestionar los recursos que utilizan
	//Inician con m_ porque son miembros de una clase. Si estuvieran en main de forma global ser�an g_
	//sf::RenderWindow* m_window; -> Se creo una clase a parte para no depender de SFMLN
	Window* m_window;
	sf::CircleShape* m_circle;
};