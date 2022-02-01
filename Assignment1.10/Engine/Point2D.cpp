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

	Point2D(int xCoor, int yCoor) {
		xCoordinate = xCoor;
		yCoordinate = yCoor;
	}

	int getXCoordinate() {
		return xCoordinate;
	}

	int getYCoordinate() {
		return yCoordinate;
	}

	void initialiseValues(int xCoor, int yCoor) {
		xCoordinate = xCoor;
		yCoordinate = yCoor;
	}

	void setXCoordinate(int xCoor) {
		xCoordinate = xCoor;
	}

	void setYCoordinate(int yCoor) {
		yCoordinate = yCoor;
	}

	void addConstant(int c, int d) {
		xCoordinate = xCoordinate + c;
		yCoordinate = yCoordinate + d;
	}

	Point2D operator + (Point2D &a) {
		Point2D p;
		p.xCoordinate = xCoordinate + a.getXCoordinate();
		p.yCoordinate = yCoordinate + a.getYCoordinate();
		return p;
	}

	Point2D operator + (int a) {
		Point2D p;
		p.xCoordinate = xCoordinate + a;
		p.yCoordinate = yCoordinate + a;
		return p;
	}

	Point2D operator - (Point2D& a) {
		Point2D p;
		p.xCoordinate = xCoordinate - a.getXCoordinate();
		p.yCoordinate = yCoordinate - a.getYCoordinate();
		return p;
	}

	Point2D operator * (Point2D& a) {
		Point2D p;
		p.xCoordinate = xCoordinate * a.getXCoordinate();
		p.yCoordinate = yCoordinate * a.getYCoordinate();
		return p;
	}

	Point2D operator - (int a) {
		Point2D p;
		p.xCoordinate = xCoordinate - a;
		p.yCoordinate = yCoordinate - a;
		return p;
	}

	Point2D operator * (int a) {
		Point2D p;
		p.xCoordinate = xCoordinate * a;
		p.yCoordinate = yCoordinate * a;
		return p;
	}

	Point2D operator / (int a) {
		Point2D p;
		p.xCoordinate = xCoordinate / a;
		p.yCoordinate = yCoordinate / a;
		return p;
	}

	Point2D operator / (Point2D& a) {
		Point2D p;
		p.xCoordinate = xCoordinate / a.getXCoordinate();
		p.yCoordinate = yCoordinate / a.getYCoordinate();
		return p;
	}

	Point2D operator - () {
		Point2D p;
		p.xCoordinate = -xCoordinate;
		p.yCoordinate = -yCoordinate;
		return p;
	}

	bool operator == (Point2D& a) {
		if (xCoordinate == a.getXCoordinate() && yCoordinate == a.getYCoordinate()) {
			return true;
		}
		
		return false;
	}

};