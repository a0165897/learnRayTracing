#pragma once
#include<cmath>
class vec3 {
public:
	vec3() :e1(0.0f), e2(0.0f), e3(0.0f),e4(1.0f){}//0
	vec3(const double& e, const double& e4 = 1.0f) :e1(e), e2(e), e3(e), e4(e4) {}//1,2
	vec3(const double& e1, const double& e2, const double& e3, const double& e4 = 1.0f) :e1(e1), e2(e2), e3(e3), e4(e4) {}//3,4
	//visit
	inline double x() const { return e1; };
	inline double y() const { return e2; };
	inline double z() const { return e3; };
	inline double r() const { return e1; };
	inline double g() const { return e2; };
	inline double b() const { return e3; };
	//operator
	inline const vec3& operator+()const { return *this; }
	inline vec3 operator-() const {return vec3(-e1,-e2,-e3);}
	inline vec3 operator+(const vec3& v2) const { return vec3(this->x() + v2.x(), this->y() + v2.y(), this->z() + v2.z()); }
	inline vec3 operator-(const vec3& v2) const { return vec3(this->x() - v2.x(), this->y() - v2.y(), this->z() - v2.z()); }
	inline vec3 operator*(const vec3& v2) const { return vec3(this->x() * v2.x(), this->y() * v2.y(), this->z() * v2.z()); }
	inline vec3 operator/( const vec3& v2) const { return vec3(this->x() / v2.x(), this->y() / v2.y(), this->z() / v2.z()); }
	inline vec3& operator+=(const vec3& v2) { *this = *this + v2; return *this; }
	inline vec3& operator-=(const vec3& v2) {*this = *this - v2; return *this; }
	inline vec3& operator*=(const vec3& v2) { *this = *this * v2; return *this; }
	inline vec3& operator/=(const vec3& v2) { *this = *this / v2; return *this; }
	inline vec3& operator*=(const double& t) { *this = *this * vec3(t); return *this; }
	inline vec3& operator/=(const double& t) { *this = *this / vec3(t); return *this; }
	//tricks
	inline double length() const { return sqrt(e1 * e1 + e2 * e2 + e3 * e3); }
	inline double squared_length() const { return e1 * e1 + e2 * e2 + e3 * e3; }
	inline double dot(const vec3& v2) const { return this->x() * v2.x() + this->y() * v2.y() + this->z() * v2.z(); }
	inline vec3 cross(const vec3& v2) const {
		return vec3(
			this->y()*v2.z()-this->z()*v2.y(),
			-this->x()*v2.z()+this->z()*v2.x(),
			this->x()*v2.y()-this->y()*v2.x()
		);
	}
	inline vec3 normalized() const { return  (*this) / this->length(); };
private:
	double e1,e2,e3,e4;
};
