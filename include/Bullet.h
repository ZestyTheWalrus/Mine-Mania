#pragma once
#include <BulletAIComponent.h>
#include <Position.h>

class Bullet : public Entity
{
public:
	Bullet();
	Bullet(Position sPos, double damage, DIRECTION direction);
	~Bullet();

	void setDamage(double damage);
	
	double getDamage();

	void setDirection(DIRECTION direction);
	void setPosition(Position pos);

	void setGraphic(char g);

	virtual void update();
	virtual bool hasComponent(int id);
	virtual bool isKilled();
	virtual void kill();
	virtual void clean();
private:
	double damage;

	BulletAIComponent ai;
};

