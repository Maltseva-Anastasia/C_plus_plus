#include "GVector.h"

int GVector::winWidth = 5;
int GVector::winHeight = 5;
double const GVector::defLen = 0.04;

GVector::GVector() : posX(0), posY(0), 
                          length(defLen), angle(0), 
                                 width(defLen / 2) {};

void GVector::setWindowSize(int width, int height) {
  winWidth = width;
  winHeight = height;
}

void GVector::transform() {
  for (int i = 0; i < sizeof(vertex) / sizeof(pair<double, double>); i++) {
    vertex[i].first = margin + (1.0 / 2) * (vertex[i].first + 1) * (winWidth - 2 * margin);
    vertex[i].second = margin + (-1.0 / 2) * (vertex[i].second - 1) * (winHeight - 2 * margin);
  }
}

void GVector::changeAxes() {
  vertex[0].first = -length / 2 * cos(angle) - width / 2 * sin(angle) + posX;
  vertex[0].second = -length / 2 * sin(angle) + width / 2 * cos(angle) + posY;
  vertex[1].first = -length / 2 * cos(angle) + width / 2 * sin(angle) + posX;
  vertex[1].second = -length / 2 * sin(angle) - width / 2 * cos(angle) + posY;
  vertex[2].first = length / 2 * cos(angle) - width / 2 * sin(angle) + posX;
  vertex[2].second = length / 2 * sin(angle) + width / 2 * cos(angle) + posY;
  vertex[3].first = length / 2 * cos(angle) + width / 2 * sin(angle) + posX;
  vertex[3].second = length / 2 * sin(angle) - width / 2 * cos(angle) + posY;
  vertex[4].first = 3 * length / 4 * cos(angle) + posX;
  vertex[4].second = 3 * length / 4 * sin(angle) + posY;
  vertex[5].first = -length / 4 * cos(angle) + posX;
  vertex[5].second = -length / 4 * sin(angle) + posY;
}


void GVector::paint(HDC &hdc) {
  changeAxes();
  transform();

  MoveToEx(hdc, (int)vertex[0].first, (int)vertex[0].second, NULL);
  LineTo(hdc, (int)vertex[5].first, (int)vertex[5].second);
  MoveToEx(hdc, (int)vertex[5].first, (int)vertex[5].second, NULL);
  LineTo(hdc, (int)vertex[1].first, (int)vertex[1].second);
  MoveToEx(hdc, (int)vertex[1].first, (int)vertex[1].second, NULL);
  LineTo(hdc, (int)vertex[3].first, (int)vertex[3].second);
  MoveToEx(hdc, (int)vertex[3].first, (int)vertex[3].second, NULL);
  LineTo(hdc, (int)vertex[4].first, (int)vertex[4].second);
  MoveToEx(hdc, (int)vertex[4].first, (int)vertex[4].second, NULL);
  LineTo(hdc, (int)vertex[2].first, (int)vertex[2].second);
  MoveToEx(hdc, (int)vertex[2].first, (int)vertex[2].second, NULL);
  LineTo(hdc, (int)vertex[0].first, (int)vertex[0].second);
}
