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
#include <cmath>

using namespace sf;
using namespace std;

class PVector
{
public:
	float x;
	float y;

	const float PI = 3.14;
	PVector() {}
	PVector(float x_, float y_)
	{

		this->x = x_;
		this->y = y_;

	}
	void add(PVector v);
	void sub(PVector a, PVector b);
	void normalize();
	void div(float n);
	void mult(float n);
	void limit(float max);
	float mag();
	float rotation();
};

