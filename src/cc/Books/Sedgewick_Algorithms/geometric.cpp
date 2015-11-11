
#include <cassert>
#include <iostream>
#include <tuple>
#include <vector>

#include "geometric.hpp"

using namespace std;

/** Counter clockwise
 * This function determines whether or not a traversal from p0, to p1, to p2 and
 * back to p0 is counter-clockwise.  If the traversal is counter-clockwise, then
 * 1 is returned.  If the traversal is clockwise, then -1 is returned.
 */
int ccw(Point p0, Point p1, Point p2) {
  int dx1, dy1, dx2, dy2;
  dx1 = p1.x - p0.x;
  dy1 = p1.y - p0.y;
  dx2 = p2.x - p0.x;
  dy2 = p2.y - p0.y;

  // if slope p0->p2 is greater than slope p0->p1
  if (dx1*dy2 > dy1*dx2)
    return 1;

  // if slope p0->p2 is less than slope p0->p1
  if (dx1*dy2 < dy1*dx2)
    return -1;

  // otherwise slopes are equal ...

  // If p0 lies between p1 and p2
  if (dx1*dx2 < 0 || dy1*dy2 < 0)
    return -1;

  // If p0 lies between p1 and p2 return 0, otherwise return -1
  // (conditional checks if length of p0->p1 is greater than or equal to the length of p0->p2)
  return ((dx1*dx1 + dy1*dy1) >= (dx2*dx2 + dy2*dy2)) ? 0 : 1;
}

bool intersect(Line l1, Line l2) {
  return ((ccw(l1.p1, l1.p2, l2.p1) * ccw(l1.p1, l1.p2, l2.p2)) <= 0) &&
    ((ccw(l2.p1, l2.p2, l1.p1) * ccw(l2.p1, l2.p2, l1.p2)) <= 0);
}
