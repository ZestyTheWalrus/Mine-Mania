#include "Position.h"

using namespace std;

Position::Position()
{
	x_ = 1;
	y_ = 1;
    isValid_=true;
}

Position::Position(int _x, int _y)
{
    x_=_x;
    y_=_y;
    isValid_=true;
    return;
}

Position::~Position()
{
    //dtor
}

void Position::setX(int _x)
{
    x_=_x;
}

void Position::setY(int _y)
{
    y_=_y;
}

void Position::isValid(bool isValid)
{
    isValid_=isValid;
}

int Position::getX() const
{
    return x_;
}

int Position::getY() const
{
    return y_;
}

int& Position::getRefX()
{
    return x_;
}

int& Position::getRefY()
{
    return y_;
}

bool Position::isValid() const
{
    return isValid_;
}

void Position::incrementX(int i)
{
    x_++;
}

void Position::incrementY(int i)
{
    y_++;
}

void Position::decrementX(int i)
{
    x_--;
}

void Position::decrementY(int i)
{
    y_--;
}

void Position::up()
{
	if (y_ == 0)
		return;
	else
		y_--;
}

void Position::down()
{
	y_++;
}

void Position::left()
{
	if (x_ == 0)
		return;
	else
		x_--;
}

void Position::right()
{
	x_++;
}

bool Position::operator<(const Position& r) const
{
    if (getX() < r.getX())  return true;
    if (getX() > r.getX())  return false;
    // Otherwise a are equal
    if (getY() < r.getY())  return true;
    if (getY() > r.getY())  return false;
    // Otherwise both are equal
    return false;
}

void Position::operator()(int _x, int _y)
{
	_x = x_;
	_y = y_;
}

void Position::operator=(Position& pos)
{
	x_ = pos.x_;
	y_ = pos.y_;
	isValid_ = pos.isValid_;
}

void Position::operator=(const Position& pos)
{
	x_ = pos.x_;
	y_ = pos.y_;
	isValid_ = pos.isValid_;
}

std::pair<int, int> Position::getPair()
{
    pair<int, int> newPair;
    newPair.first=x_;
    newPair.second=y_;
    return newPair;
}