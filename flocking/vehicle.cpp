#include "vehicle.h"
#include<cmath>

using namespace std;



Vehicle::Vehicle(float x, float y)
{

	location = new PVector(x, y);
	velocity = new PVector(0, 0);
	acceleration = new PVector((rand() % 200 - 100) * 0.01, (rand() % 200 - 100) * 0.01);

	width_B = 25.0;
	weight[0] = 1.f;
	weight[1] = 1.f;
	weight[2] = 1.f;
	r = 2.5;
	this->maxspeed = 0.4f;
	this->maxforce = 0.003f;

	triangle.setPointCount(3);
	triangle.setPoint(0, Vector2f(r, 0));
	triangle.setPoint(1, Vector2f(r * 0.5, r * 1.866));
	triangle.setPoint(2, Vector2f(r * 1.5, r * 1.866));
	triangle.setScale(10, 10);
	triangle.setFillColor(Color::White);
	triangle.setOrigin(r, r);
	triangle.setPosition(location->x, location->y);
}

void Vehicle::update()
{
	velocity->add(*acceleration);
	velocity->limit(maxspeed);
	location->add(*velocity);
	acceleration->mult(0);
	triangle.setPosition(location->x, location->y);
	triangle.setRotation(velocity->rotation());

	if (triangle.getPosition().x > 1275)
	{
		triangle.setPosition(5, triangle.getPosition().y);
		location->x = triangle.getPosition().x;
		location->y = triangle.getPosition().y;
	}
	if (triangle.getPosition().x < 5)
	{
		triangle.setPosition(1275, triangle.getPosition().y);
		location->x = triangle.getPosition().x;
		location->y = triangle.getPosition().y;
	}
	if (triangle.getPosition().y > 715)
	{
		triangle.setPosition(triangle.getPosition().x, 5);
		location->x = triangle.getPosition().x;
		location->y = triangle.getPosition().y;
	}
	if (triangle.getPosition().y < 5)
	{
		triangle.setPosition(triangle.getPosition().x, 715);
		location->x = triangle.getPosition().x;
		location->y = triangle.getPosition().y;
	}

}

PVector Vehicle::seek(PVector target)
{
	PVector* desired = new PVector(0, 0);
	desired->sub(target, *location);

	float dis = desired->mag();

	desired->normalize();

	if (dis < 100)
	{
		float m = lmap(dis, Vector2f(0, 0), Vector2f(100.f, maxspeed));
		desired->mult(m);
	}
	else {
		desired->mult(maxspeed);
	}

	PVector* steer = new PVector(0, 0);
	steer->sub(*desired, *velocity);

	steer->limit(maxforce);

	return *steer;
	//applyForce(*steer);
}

Vector2f Vehicle::getPosition()
{
	return Vector2f(location->x, location->y);
}
void Vehicle::applyForce(PVector force)
{
	acceleration->x += force.x;
	acceleration->y += force.y;
}

float Vehicle::lmap(float val, Vector2f min, Vector2f max)
{
	return min.y + ((max.y - min.y) * (val - min.x)) / (max.x - min.x);
}

void Vehicle::boundaries()
{
	PVector desired(0, 0);

	if (location->x < width_B)
	{
		desired.x = maxspeed;
		desired.y = velocity->y;
	}
	else if (location->x > gameWidth - width_B)
	{
		desired.x = -maxspeed;
		desired.y = velocity->y;
	}

	if (location->y < width_B)
	{
		desired.x = velocity->x;
		desired.y = maxspeed;
	}
	else if (location->y > gameHeight - width_B) {
		desired.x = velocity->x;
		desired.y = -maxspeed;
	}

	if (Vector2f(desired.x, desired.y) != Vector2f(0, 0)) {
		desired.normalize();
		desired.mult(maxspeed);
		PVector steer(desired.x - velocity->x, desired.y - velocity->y);
		steer.limit(maxforce);
		applyForce(steer);
	}
}

void Vehicle::vehicleSystem(vector<Vehicle*>* const Vehiclee, bool sep, bool coh, bool ali)
{
	PVector sepV = separate(Vehiclee);
	PVector aliV = align(Vehiclee);
	PVector cohV = cohesion(Vehiclee);
	float n_sep;
	float n_ali;
	float n_coh;

	if (sep == true)
	{
		 n_sep = 1.9;
	}
	else
	{
		n_sep = 0;
	}
	if (ali == true)
	{
		n_ali = 1.1;
	}
	else {
		n_ali = 0; 
	}
	if (coh == true)
	{
		n_coh = 0.175;
	}
	else {
		n_coh = 0;
	}

	sepV.mult(n_sep);
	aliV.mult(n_ali);
	cohV.mult(n_coh);

	applyForce(sepV);
	applyForce(aliV);
	applyForce(cohV);
}

PVector Vehicle::separate(std::vector<Vehicle*>* const Vehiclee) {
	float desiredseparation = 25.0f;
	PVector steer(0, 0);
	int count = 0;
	float maxsteer = 0.01;
	std::vector<Vehicle*> t = *Vehiclee;

	for (Vehicle *other : t) {
		PVector dis(location->x - other->location->x, location->y - other->location->y);
		float d = dis.mag();
		if ((d > 0) && (d < desiredseparation)) {
			PVector diff(0, 0);
			diff.sub(*location, *other->location);
			diff.normalize();
			diff.div(d);
			steer.add(diff);
			count++;
		}
	}

	if (count > 0) {
		steer.div(count * 1.f);
	}
	if (steer.mag() > 0) {
		steer.normalize();
		steer.mult(maxspeed);
		steer.sub(steer, *velocity);
		steer.limit(maxforce);
	}
	return steer;
}

PVector Vehicle::cohesion(vector<Vehicle*>* const Vehiclee)
{
	float neighbordist = 50.;
	PVector sum(0, 0);
	int count = 0;
	vector<Vehicle*> t = *Vehiclee;
	for (auto *other : t) {
		PVector dis(location->x - other->location->x, location->y - other->location->y);
		float d = dis.mag();
		if ((d > 0) && (d < neighbordist)) {
			sum.add(*other->location);
			count++;
		}
	}
	if (count > 0) {
		sum.div(count * 1.f);
		return seek(sum);
	}
	else {
		return PVector(0, 0);
	}
}

PVector Vehicle::align(vector<Vehicle*>* const Vehiclee) {
	float neighbordist = 50.f;
	PVector sum(0, 0);
	int count = 0;
	std::vector<Vehicle*> t = *Vehiclee;
	for (auto *other : t) {
		PVector dis(location->x - other->location->x, location->y - other->location->y);
		float d = dis.mag();
		if ((d > 0) && (d < neighbordist)) {
			sum.add(*other->velocity);
			count++;
		}
	}
	if (count > 0) {
		sum.div(count * 1.f);
		sum.normalize();
		sum.mult(maxspeed);
		PVector steer(sum.x - velocity->x, sum.y - velocity->y);
		steer.limit(maxforce);
		return steer;
	}
	else {
		return PVector(0, 0);
	}
}

/*void Vehicle::setWeight(float sep, float coh, float ali)
{
	weight[0] = sep;
	weight[1] = coh;
	weight[2] = ali;
}
*/

void Vehicle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.texture = NULL;
	target.draw(triangle, states);
}