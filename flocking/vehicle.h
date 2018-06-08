#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <vector>
#include <iostream>
#include "pvector.h"


using namespace sf;
using namespace std;

class Vehicle : public Drawable, public Transformable
{
public:
	ConvexShape triangle;
	PVector* location;
	PVector* velocity;
	PVector* acceleration;

	float maxspeed;
	float maxforce;
	float r;
	float width_B;
	float weight[3];
	float x, y;

	const int gameWidth = 1280;
	const int gameHeight = 720;





	Vehicle(float x, float y);

	void update();
	PVector seek(PVector target);
	void applyForce(PVector force);
	float lmap(float val, Vector2f min, Vector2f max);
	Vector2f getPosition();
	void boundaries();
	void vehicleSystem(vector<Vehicle*>* const vehicle, bool sep, bool coh, bool ali);
	PVector separate(std::vector<Vehicle*>* const boids);
	PVector align(std::vector<Vehicle*>* const boids);
	PVector cohesion(std::vector<Vehicle*>* const boids);
	//void setWeight(float sep, float coh, float ali);
	virtual void draw(RenderTarget& target, RenderStates states) const;


private:
	RenderWindow * window;
	bool followMousePos = true;
};



