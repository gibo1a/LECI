//
// Algoritmos e Estruturas de Dados - 2023/2024
//
// COMPLETE the code, according to Square.h
//

#include "Square.h"

#include <cassert>
#include <iostream>
#include <string>

#include "Point.h"
#include "Rectangle.h"

Square::Square(void) {
  // Rectangle of edge=1 and centered at (0,0)
  // COMPLETE
  SetCenter(Point(0,0));
  SetWidth(1);
  SetHeight(1);
}

Square::Square(Point center, const std::string& color, double length){
  SetCenter(center);
  SetColor(color);
  SetWidth(length);
  SetHeight(length);
}

Square::Square(double x, double y, const std::string& color, double length){
  SetCenter(Point(x,y));
  SetColor(color);
  SetWidth(length);
  SetHeight(length);
}

double Square::GetEdgeLength(void) const{return width_;}
void Square::SetEdgeLength(double length){
  assert(length > 0);
  SetWidth(length);
  SetHeight(length);
}

std::string Square::GetClassName(void) const { return "Square";}

std::ostream& operator<<(std::ostream& os, const Square& obj){
  os << "(" << obj.GetCenter() << "," << obj.GetWidth() << "," << obj.GetColor() << ")";
  return os;
}

std::istream& operator>>(std::istream& is, Rectangle& obj) {
  // COMPLETE
  std::cout << "center = ";
  is >> obj.center_;
  std::cout << "edge = ";
  is >> obj.width_;
  std::cout << "color = ";
  is >> obj.color_;
  return is;
}

// WRITE THE MISSING CONSTRUTORS, METHODS AND FRIEND FUNCTIONS
