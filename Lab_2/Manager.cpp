#include "Manager.h"

Manager::Manager() {
  objects.resize(15);
  for (size_t i = 0; i < objects.size(); i++)
    objects[i] = new GVector;
}

Manager::~Manager() {
  for (auto obj : objects)
    delete obj;
}

Manager& Manager::operator+=(double speed) {
  this->speed += speed;
  return *this;
}

Manager& Manager::operator-=(double speed) {
  this->speed -= speed;
  return *this;
}

Manager& Manager::operator<<(double angle) {
  for (size_t i = 0; i < objects.size(); i++) {
    double temp = objects[i]->getAngle();
    objects[i]->setAngle(temp += angle / (i + 1));
  }
  return *this;
}

Manager& Manager::operator>>(double angle) {
  for (size_t i = 0; i < objects.size(); i++) {
    double temp = objects[i]->getAngle();
    objects[i]->setAngle(temp -= angle / (i + 1));
  }
  return *this;
}

Manager& Manager::operator++() {
  for (size_t i = 0; i < objects.size(); i++) {
    double temp = objects[i]->getLength();
    if (temp <= 10 * GVector::defLen)
      objects[i]->setLength(temp += GVector::defLen * (1 - i * 0.01));
  }
  return *this;
}

Manager& Manager::operator--() {
  for (size_t i = 0; i < objects.size(); i++) {
    double temp = objects[i]->getLength();
    if (temp > GVector::defLen)
      objects[i]->setLength(temp -= GVector::defLen * (1 - i * 0.01));
  }
  return *this;
}

void Manager::limit() {
  double ang = objects[0]->getAngle();
  if (objects[0]->getPosX() >= 1 || objects[0]->getPosY() >= 1
    || objects[0]->getPosX() <= -1 || objects[0]->getPosY() <= -1) {
    objects[0]->setAngle(ang += PI);
  }
  if (objects[0]->getPosX() < -1) {
    objects[0]->setPos(-1, objects[0]->getPosY());
    objects[0]->setAngle(ang += PI);
  }
  if (objects[0]->getPosY() < -1) {
    objects[0]->setPos(objects[0]->getPosX(), -1);
    objects[0]->setAngle(ang += PI);
  }
  if (objects[0]->getPosX() > 1) {
    objects[0]->setPos(1, objects[0]->getPosY());
    objects[0]->setAngle(ang += PI);
  }
  if (objects[0]->getPosY() > 1) {
    objects[0]->setPos(objects[0]->getPosX(), 1);
    objects[0]->setAngle(ang += PI);
  }
}

void Manager::demping()
{
  if (speed > 0)
    speed -= GVector::defLen; //speed unit
  if (speed < 0)
    speed += GVector::defLen;
}

void Manager::update() {
  objects[0]->setPos(objects[0]->getPosX() + speed * cos(objects[0]->getAngle()),
    objects[0]->getPosY() + speed * sin(objects[0]->getAngle()));
  limit();
  demping();
  for(size_t i = objects.size() - 1; i > 0; i--)
  {
    objects[i]->setPos(objects[i - 1]->getPosX(), objects[i - 1]->getPosY());
    objects[i]->setLength(objects[i - 1]->getLength());
    objects[i]->setAngle(objects[i - 1]->getAngle());
  }
}

void Manager::paint(HDC& hdc) {
  for (auto obj : objects)
    obj->paint(hdc);
}