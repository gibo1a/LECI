//
// Algoritmos e Estruturas de Dados - 2023/2024
//
// COMPLETE the code, according to Rectangle.h
//

#include "Rectangle.h"

#include <cassert>
#include <iostream>
#include <string>

#include "Point.h"

Rectangle::Rectangle(void) {
  // Rectangle of width=1 and height=1 and centered at (0,0)
  // COMPLETE
  height_ = 1;
  width_ = 1;
  SetCenter(Point(0.0,0.0));
}

Rectangle::Rectangle(Point center, const std::string& color, double width,
                     double height) {
  // Ensure that the width and height are larger than 0.0
  // COMPLETE
  SetCenter(center);
  SetColor(color);
  width_ = width;
  height_ = height;
}

Rectangle::Rectangle(double x, double y, const std::string& color, double width,
                     double height) {
  // Ensure that the width and height are larger than 0.0
  // COMPLETE
  SetCenter(Point(x,y));
  SetColor(color);
  width_ = width;
  height_ = height;
}

double Rectangle::GetHeight(void) const { return height_; }
void Rectangle::SetHeight(double length) {
  // Ensure that the height is larger than 0.0
  // COMPLETE
  assert(length > 0);
  height_ = length;
}

double Rectangle::GetWidth(void) const { return width_; }
void Rectangle::SetWidth(double length) {
  // Ensure that the width is larger than 0.0
  // COMPLETE
  assert(length > 0);
  width_ = length;
}

std::string Rectangle::GetClassName(void) const { return "Rectangle"; }

double Rectangle::Area(void) const {
  // COMPLETE
  return width_*height_;
}

double Rectangle::Perimeter(void) const {
  // COMPLETE
  return (2*width_)+(2*height_);
}

std::ostream& operator<<(std::ostream& os, const Rectangle& obj) {
  // COMPLETE
  os << "(" << obj.GetCenter() << "," << obj.width_ << "," << obj.height_ << "," << obj.GetColor() << ")";
  return os;
}

std::istream& operator>>(std::istream& is, Rectangle& obj) {
  // COMPLETE
  std::cout << "width = ";
  is >> obj.width_;
  std::cout << "height = ";
  is >> obj.height_;
  return is;
}