class Point2D {
private:
	int xCoordinate;
	int yCoordinate;


public:

	Point2D(){
		xCoordinate = 0;
		yCoordinate = 0;
	}

	~Point2D() {

	}

	Point2D(const int xCoor, const int yCoor) {
		xCoordinate = xCoor;
		yCoordinate = yCoor;
	}

	const int getXCoordinate() {
		return xCoordinate;
	}

	const int getYCoordinate() {
		return yCoordinate;
	}

	void initialiseValues(const int xCoor, const int yCoor) {
		xCoordinate = xCoor;
		yCoordinate = yCoor;
	}

	void setXCoordinate(const int xCoor) {
		xCoordinate = xCoor;
	}

	void setYCoordinate(const int yCoor) {
		yCoordinate = yCoor;
	}

	void addConstant(const int c, const int d) {
		xCoordinate = xCoordinate + c;
		yCoordinate = yCoordinate + d;
	}

	Point2D operator + (const Point2D &a) {
		Point2D p;
		p.xCoordinate = xCoordinate + a.xCoordinate;
		p.yCoordinate = yCoordinate + a.yCoordinate;
		return p;
	}

	Point2D operator + (const int a) {
		Point2D p;
		p.xCoordinate = xCoordinate + a;
		p.yCoordinate = yCoordinate + a;
		return p;
	}

	Point2D operator - (const Point2D& a) {
		Point2D p;
		p.xCoordinate = xCoordinate - a.xCoordinate;
		p.yCoordinate = yCoordinate - a.yCoordinate;
		return p;
	}

	Point2D operator * (const Point2D& a) {
		Point2D p;
		p.xCoordinate = xCoordinate * a.xCoordinate;
		p.yCoordinate = yCoordinate * a.yCoordinate;
		return p;
	}

	Point2D operator - (const int a) {
		Point2D p;
		p.xCoordinate = xCoordinate - a;
		p.yCoordinate = yCoordinate - a;
		return p;
	}

	Point2D operator * (const int a) {
		Point2D p;
		p.xCoordinate = xCoordinate * a;
		p.yCoordinate = yCoordinate * a;
		return p;
	}

	Point2D operator / (const int a) {
		Point2D p;
		p.xCoordinate = xCoordinate / a;
		p.yCoordinate = yCoordinate / a;
		return p;
	}

	Point2D operator / (const Point2D& a) {
		Point2D p;
		p.xCoordinate = xCoordinate / a.xCoordinate;
		p.yCoordinate = yCoordinate / a.yCoordinate;
		return p;
	}

	Point2D operator - () {
		Point2D p;
		p.xCoordinate = -xCoordinate;
		p.yCoordinate = -yCoordinate;
		return p;
	}

	const bool operator == (const Point2D& a) {
		if (xCoordinate == a.xCoordinate && yCoordinate == a.yCoordinate) {
			return true;
		}
		
		return false;
	}

};