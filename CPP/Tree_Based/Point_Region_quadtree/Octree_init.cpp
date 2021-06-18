#include <iostream>
#include <cmath>
#include <random>
#include <math.h>
#include <tuple>
#include <chrono>

#include <GL/glut.h>

using namespace std;
using namespace std::chrono;

// int count = 0;
class Point
{
	double x;
	double y;
	double z;

public:
	Point(double const &inp_x, double const &inp_y, double const &inp_z)
	{
		this->x = inp_x;
		this->y = inp_y;
		this->z = inp_z;
	}
	double get_x()
	{
		return this->x;
	}
	double get_y()
	{
		return this->y;
	}
	double get_z()
	{
		return this->z;
	}
	double distance(const Point &point)
	{
		double distance_x = point.x - this->x;
		double distance_y = point.y - this->y;
		double distance_z = point.z - this->z;
		return sqrt(pow(distance_x, 2) + pow(distance_y, 2) + pow(distance_z, 2));
	}

	friend ostream &operator<<(ostream &out, const Point &poi);
};

class Cuboid
{
	double x;
	double y;
	double z;
	double w;
	double h;
	double d;
	double left;
	double right;
	double top;
	double bottom;
	double front;
	double back;

public:
	Cuboid()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
		this->w = 0;
		this->h = 0;
		this->d = 0;
		this->left = 0;
		this->right = 0;
		this->top = 0;
		this->bottom = 0;
		this->front = 0;
		this->back = 0;
	}
	Cuboid(double const &inp_x, double const &inp_y, double const &inp_z, double const &inp_w, double const &inp_h, double const &inp_d)
	{
		this->x = inp_x;
		this->y = inp_y;
		this->z = inp_z;
		this->w = inp_w;
		this->h = inp_h;
		this->d = inp_d;
		this->left = inp_x - inp_w / 2;
		this->right = inp_x + inp_w / 2;
		this->top = inp_y - inp_h / 2;
		this->bottom = inp_y + inp_h / 2;
		this->front = inp_z + inp_d / 2;
		this->back = inp_z - inp_d / 2;
	}
	double get_x()
	{
		return this->x;
	}
	double get_y()
	{
		return this->y;
	}
	double get_z()
	{
		return this->z;
	}
	double get_w()
	{
		return this->w;
	}
	double get_h()
	{
		return this->h;
	}
	double get_d()
	{
		return this->d;
	}
	bool contains(Point point)
	{
		double point_x = point.get_x();
		double point_y = point.get_y();
		double point_z = point.get_z();
		return (this->left <= point_x &&
				point_x <= this->right &&
				this->top <= point_y &&
				point_y <= this->bottom &&
				this->back <= point_z &&
				point_z <= this->front);
	}
	bool intersects(Cuboid range)
	{
		return !(
			this->right < range.left || range.right < this->left ||
			this->bottom < range.top || range.bottom < this->top ||
			this->back < range.front || range.back < this->front);
	}
	double x_distance(Point point)
	{
		if (this->left <= point.get_x() && point.get_x() <= this->right)
		{
			return 0;
		}
		return min(abs(point.get_x() - this->left), abs(point.get_x() - this->right));
	}
	double y_distance(Point point)
	{
		if (this->top <= point.get_y() && point.get_y() <= this->bottom)
		{
			return 0;
		}
		return min(abs(point.get_y() - this->bottom), abs(point.get_y() - this->bottom));
	}
	double z_distance(Point point)
	{
		if (this->back <= point.get_z() && point.get_z() <= this->front)
		{
			return 0;
		}
		return min(abs(point.get_z() - this->front), abs(point.get_z() - this->back));
	}
	double distance(Point point)
	{
		double distance_x = x_distance(point);
		double distance_y = y_distance(point);
		double distance_z = z_distance(point);
		return sqrt(pow(distance_x, 2) + pow(distance_y, 2) + pow(distance_z, 2));
	}

	friend ostream &operator<<(ostream &out, const Cuboid &rec);
};

class Sphere
{
	double x;
	double y;
	double z;
	double r;

public:
	Sphere(double const &inp_x, double const &inp_y, double const &inp_z, double const &inp_r)
	{
		this->x = inp_x;
		this->y = inp_y;
		this->z = inp_z;
		this->r = inp_r;
	}
	double get_x()
	{
		return this->x;
	}
	double get_y()
	{
		return this->y;
	}
	double get_z()
	{
		return this->z;
	}
	double get_r()
	{
		return this->r;
	}
	double distnace_center(Point point)
	{
		return sqrt(pow((this->x - point.get_x()), 2) + pow((this->y - point.get_y()), 2) + pow((this->z - point.get_z()), 2));
	}
	bool contains(Point point)
	{
		double dist = this->distnace_center(point);
		return (dist <= this->r);
	}
	bool intersects(Cuboid range)
	{
		double distance_x = abs(range.get_x() - this->x);
		double distance_y = abs(range.get_y() - this->y);
		double distance_z = abs(range.get_z() - this->z);

		double radius = this->r;
		double width_half = range.get_w() / 2;
		double height_half = range.get_h() / 2;
		double depth_half = range.get_d() / 2;

		if (distance_x > (radius + width_half) ||
			distance_y > (radius + height_half) ||
			distance_z > (radius + height_half))
		{
			return false;
		}
		if (distance_x <= width_half || distance_y <= height_half || distance_z <= depth_half)
		{
			return true;
		}

		double edges = pow((distance_x - width_half), 2) + pow((distance_y - height_half), 2) + pow((distance_z - depth_half), 2);
		return (edges <= pow(this->r, 2));
	}

	friend ostream &operator<<(ostream &out, const Sphere &spe);
};