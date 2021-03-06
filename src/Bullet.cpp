#include "..\include\Bullet.h"


Bullet::Bullet()
{
	damage = 5;
	ai.setGraphic('@');
}

Bullet::Bullet(Position sPos, double damage, DIRECTION direction)
{
	this->damage = damage;
	ai.setDirection(direction);
	ai.setPosition(sPos);
}

Bullet::~Bullet()
{
}

void Bullet::setDamage(double damage)
{
	this->damage = damage;
}

double Bullet::getDamage()
{
	return damage;
}

void Bullet::setDirection(DIRECTION direction)
{
	ai.setDirection(direction);
}

void Bullet::setPosition(Position pos)
{
	ai.setPosition(pos);
}

void Bullet::setGraphic(char g)
{
	ai.setGraphic(g);
}

void Bullet::update()
{
	if (ai.isDestroyed() == true)
	{
		ai.clean();
		return;
	}
	ai.update();
}

bool Bullet::hasComponent(int id)
{
	return false;
}

bool Bullet::isKilled()
{
	return ai.isDestroyed();
}

void Bullet::kill()
{
	ai.clean();
	ai.isDestroyed(true);
}

void Bullet::clean()
{
	ai.clean();
}
