#ifndef __GVECTOR_H_
#define __GVECTOR_H_
#include <Windows.h>
#include <utility>

using namespace std;

class GVector 
{
private:
  double posX, posY, length, angle, width;
  static int winWidth;
  static int winHeight;
  pair<double, double> vertex[6];
  static const int margin = 10;
  void transform();
  void changeAxes();

public:

  static const double defLen;
  GVector();

  void setPos(double x, double y) { posX = x; posY = y; }
  void setLength(double length) { this->length = length; }
  void setAngle(double angle) { this->angle = angle; }
  void setWidth(double width) { this->width = width; }
  //void setSpeed(double speed) { this->speed = speed; }

  double getPosX() { return posX; }
  double getPosY() { return posY; }
  double getLength() { return length; }
  double getAngle() { return angle; }
  double getWidth() { return width; }
  //double getSpeed() { return speed; }

  static void setWindowSize(int width, int height);
  void paint(HDC &hdc);
};

#endif


