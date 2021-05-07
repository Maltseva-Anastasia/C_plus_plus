#ifndef __MANAGER_H_
#define __MANAGER_H_
#include "GVector.h"
#include <vector>
#include <Windows.h>

using namespace std;

const double PI = 3.141592653589793;

class Manager {
private:
  double speed;
  vector<GVector*> objects;
  void limit();
  void demping();
public:
  Manager();
  ~Manager();
  void update();
  void paint(HDC& hdc);
  Manager& operator+=(double speed); //приращение скорости
  Manager& operator-=(double speed); //уменьшение скорости
  Manager& operator<<(double angle); //поворот против часовой стрелки
  Manager& operator>>(double angle); //поворот по часовой стрелке
  Manager& operator++(); //увеличение размера отрезка
  Manager& operator--(); //уменьшение размера отрезка
};

#endif

