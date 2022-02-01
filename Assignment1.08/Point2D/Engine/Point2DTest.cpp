#include "Entity.cpp"
#include <assert.h>
#include <iostream>

void Point2DTest() {
	Point2D a = Point2D(4, 6);
	Point2D b = Point2D(2, 3);

	bool bEqual = (a == b);   
	assert(bEqual == false);
	
	Point2D c = a + b;
	assert((a + b) == *new Point2D(6, 9));

	assert((a - b) == *new Point2D(2, 3));

	assert((a * b) == *new Point2D(8, 18));

	assert((a / b) == *new Point2D(2, 2));

	assert((a + 2) == *new Point2D(6, 8));

	assert((a - 2) == *new Point2D(2, 4));

	assert((a * 2) == *new Point2D(8, 12));

	assert((a / 2) == *new Point2D(2, 3));

	assert((-a) == *new Point2D(-4, -6));

	Point2D  x = Point2D(4, 6);
	const Point2D  y = Point2D(2, 3);

	bool bEqual1 = (x == y);
	assert(bEqual1 == false);

	assert((x + y) == *new Point2D(6, 9));

	assert((x - y) == *new Point2D(2, 3));

	assert((x * y) == *new Point2D(8, 18));

	assert((x / y) == *new Point2D(2, 2));

	assert((x + 2) == *new Point2D(6, 8));

	assert((x - 2) == *new Point2D(2, 4));

	assert((x * 2) == *new Point2D(8, 12));

	assert((x / 2) == *new Point2D(2, 3));

	assert((-x) == *new Point2D(-4, -6));
}