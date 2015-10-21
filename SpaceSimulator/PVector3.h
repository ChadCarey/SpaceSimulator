/**
* PVector3 is a vector class designed for high precision
* it is intended to not have a value greater than FLOAT_MAX to allow it's use in openGL 
* but has the decimal precision of a long double
*/

class PVector3
{
public:
	PVector3();
	PVector3(const PVector3& origonal);
	long double getX() const;
	long double getY() const;
	long double getZ() const;
	void set(const PVector3& newV);
	void set(const long double& newX, const long double& newY, const long double& newZ);
	void setX(const long double& newX);
	void setY(const long double& newY);
	void setZ(const long double& newZ);
	PVector3 operator*(const long double& rhs) const;
	PVector3 operator/(const long double& rhs) const;
	PVector3 operator+(const PVector3& rhs) const;
	PVector3 operator-(const PVector3& rhs) const;
	PVector3& operator=(const PVector3& rhs);
	PVector3 operator*=(const long double& rhs);
	long double getLength() const;
	void invert();

private:
	long double x;
	long double y;
	long double z;
	long double& boundsFilter(const long double& newValue);
};