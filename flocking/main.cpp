#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "vehicleSystem.h"
#include <vector>
#include <string>
#include "vehicle.h"

int main() {
	const int gameWidth = 1280;
	const int gameHeight = 720;

	RenderWindow window(VideoMode(gameWidth, gameHeight), "Flocking");

	VehicleSystem vehicle;

	//int sep = 0;
	//int coh = 0;
	//int ali = 0;

	bool sep = false;
	bool coh = false;
	bool ali = false;

	while (window.isOpen()) {
		Event event;
		Vector2i mouse = Mouse::getPosition(window);

		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}

			else if (event.type ==Event::MouseButtonPressed) 
			{
				 if (event.mouseButton.button == Mouse::Left) 
				 {
					vehicle.addVehicle(Vector2f(event.mouseButton.x, event.mouseButton.y));
				 }
				 else if (event.mouseButton.button == Mouse::Right)
				 {
					 vehicle.reduceVehicle();
				 }
			}

			else if (event.type == Event::TextEntered) {
				if (Keyboard::isKeyPressed(Keyboard::S)) {
					sep = !sep;
				}

				//else if (sf::Keyboard::isKeyPressed(Keyboard::W)) {
				//	sep++;
				//}

				else if (Keyboard::isKeyPressed(Keyboard::C)) {
					coh =! coh;
				}

				/*else if (Keyboard::isKeyPressed(Keyboard::D)) {
					coh++;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Q)) {
					ali++;
				}
				*/
				else if (Keyboard::isKeyPressed(Keyboard::A)) {
					ali =! ali;
				}
			}
		}
		
		//vehicle.updateWeight(sep, coh, ali);
		vehicle.update(sep,coh,ali);
		//sep = coh = ali = 0;


		//vehicle.update();

		window.clear();
		window.draw(vehicle);
		window.display();
	}

	return 0;
}
