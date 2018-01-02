#include "../../../include/txt_file.hpp"
#include "protoline.pb.h"

Line* createNewLine(const std::string& name) {
  // create a line from (10, 20) to (30, 40)
  Line* line = new Line;
  line->mutable_start()->set_x(10);
  line->mutable_start()->set_y(20);
  line->mutable_end()->set_x(30);
  line->mutable_end()->set_y(40);
  line->set_label(name);
  return line;
}

Polyline* createNewPolyline() {
  // create a polyline with points at (10,10) and (20,20)
  Polyline* polyline = new Polyline;
  Point* point1 = polyline->add_point();
  point1->set_x(10);
  point1->set_y(10);
  Point* point2 = polyline->add_point();
  point2->set_x(20);
  point2->set_y(20);
  return polyline;
}

int main()
{
  return 0;
}
