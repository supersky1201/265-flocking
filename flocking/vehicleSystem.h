#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <vector>
#include <array>
#include <algorithm>
#include <iostream>
#include "vehicle.h"

using namespace std;

class VehicleSystem : public Drawable, public Transformable
{
public:
	int gameWidth = 1280;
	int gameHeight = 720;
	static const int col = 10;
	static const int row = 10;

	int gridWidth;
	int gridHeight;
	int count;


	array<float, 3> weight;
	vector<Vehicle*> mVehicles;
	vector<Vehicle*> grid[row][col];

	VehicleSystem();
	~VehicleSystem();
	int getCount();
	void update(bool sep, bool coh, bool ali);
	void addVehicle(Vector2f loc);
	void reduceVehicle();
	array<float, 3> getWeight();
	virtual void draw(RenderTarget& target, RenderStates states) const;
	//void updateWeight(int sep, int coh, int ali);
	//void updateWeight(bool sep, bool coh, bool ali);
	Vector2i getBucket(Vector2f pos);
	void bucketRemove(Vector2i bucket, Vehicle* obj);
	void bucketAdd(Vector2i bucket, Vehicle* obj);
};

