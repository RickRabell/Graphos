#include <SFML/Graphics.hpp>

//Son punteros globales para poder gestionar los recursos que utilizan
sf::RenderWindow* window;
sf::CircleShape* circle;


//Este es el gameloop de la aplicación
void 
init() {
    window = new sf::RenderWindow(sf::VideoMode(800, 600), "Graphos");
    circle = new sf::CircleShape(100.0f);
    circle->setFillColor(sf::Color::Green);
    circle->setPosition(200.f, 150.f);
}

void 
handleEvents() {
    sf::Event event;
    while (window->pollEvent(event)) {
        // Cerrar la ventana si el usuario lo indica
        if (event.type == sf::Event::Closed) {
            window->close();
        }
    }
}

void 
update() {
    //Aquí va la lógica
}

void 
render() {
    // Limpiar, dibujar y mostrar
    window->clear();
    window->draw(*circle);
    window->display();
}

void 
destroy() {
    delete window;
    delete circle;
}

int 
main()
{
    init();

    while (window->isOpen())
    {
        handleEvents();
        update();
        render();
    }

    destroy();
}