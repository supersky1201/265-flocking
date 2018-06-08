#include "vehicleSystem.h"


VehicleSystem::VehicleSystem() {
	count = 0;
	weight[0] = 1.f;
	weight[1] = 1.f;
	weight[2] = 1.f;
	gridWidth = gameWidth / col;
	gridHeight = gameHeight / row;
}

VehicleSystem::~VehicleSystem() {
	mVehicles.clear();
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++) {
			grid[i][j].clear();
		}
}

void VehicleSystem::update(bool sep, bool coh, bool ali) {
	for (auto &vehicle : mVehicles) {
		Vector2i curBucket = getBucket(vehicle->getPosition());
		if (vehicle != nullptr)
			vehicle->update();
		Vector2i newBucket = getBucket(vehicle->getPosition());

		if (curBucket != newBucket) {
			bucketRemove(curBucket, vehicle);
			bucketAdd(newBucket, vehicle);
		}

		vector<Vehicle*>*  Vehiclee = nullptr;
		if (&grid[newBucket.x][newBucket.y] != nullptr)
			Vehiclee = &grid[newBucket.x][newBucket.y];
		if (Vehiclee != nullptr)
			vehicle->vehicleSystem(Vehiclee,sep,coh,ali);
	}
}

void VehicleSystem::draw(RenderTarget& target, RenderStates states) const {
	states.transform *= getTransform();
	states.texture = NULL;

	if (&mVehicles != nullptr)
	{
		for (auto p : mVehicles) {
			target.draw(*p, states);
		}
	}
}

int VehicleSystem::getCount() {
	return count;
}

void VehicleSystem::addVehicle(sf::Vector2f loc) {
	Vehicle *mVehicle = new Vehicle(loc.x, loc.y);
	//std::cout<< mVehicle->location.x<<endl;
	mVehicles.push_back(mVehicle);
	count++;
}

void VehicleSystem::reduceVehicle() {
	if (count <= 0) {
		return;
	}
	else if (count == 1) {
		mVehicles.pop_back();
		count--;
		return;
	}
	else {
		for (int target = count / 2; count > target; count--) {
			mVehicles.pop_back();
		}
	}
}

array<float, 3> VehicleSystem::getWeight() {
	return weight;
}


//void VehicleSystem::updateWeight(int sep, int coh, int ali) {
/*void VehicleSystem::updateWeight(bool sep, bool coh, bool ali) {
	weight[0] += 0.1 * sep;
	weight[1] += 0.1* coh;
	weight[2] += 0.1 * ali;

	if (sep == true)
	{
		num_sep = 
	}

	if (&mVehicles != nullptr)
	{
		for (auto &Vehicle : mVehicles) {
			Vehicle->setWeight(weight[0], weight[1], weight[2]);
		}
	}
}
*/


Vector2i VehicleSystem::getBucket(Vector2f pos) {
	return Vector2i(pos.x / gridWidth, pos.y / gridHeight);
}

void VehicleSystem::bucketRemove(Vector2i bucket, Vehicle* obj) {
	if (obj != nullptr)
	{
		auto i = find(grid[bucket.x][bucket.y].begin(), grid[bucket.x][bucket.y].end(), obj);
		if (i != grid[bucket.x][bucket.y].end()) {
			grid[bucket.x][bucket.y].erase(i);
		}
	}
}

void VehicleSystem::bucketAdd(sf::Vector2i bucket, Vehicle* obj) {
	if (obj != nullptr)
		grid[bucket.x][bucket.y].push_back(obj);
}
