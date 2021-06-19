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
	friend bool operator==(const Point &lhs, const Point &rhs) { return (lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z); }
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
			distance_z > (radius + depth_half))
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

ostream &operator<<(ostream &out, const Cuboid &cub)
{
	out << "Center_x: " << cub.x << '\t' << "Center_y: " << cub.y << '\t' << "Center_z: " << cub.z << '\t' << "Range_x: " << cub.w << '\t' << "Range_y: " << cub.h << "Range_z: " << cub.d << std::endl;
	return out;
}

ostream &operator<<(ostream &out, const Point &poi)
{
	out << poi.x << '\t' << poi.y << '\t' << poi.z << std::endl;
	return out;
}

ostream &operator<<(ostream &out, const Sphere &spe)
{
	out << spe.x << '\t' << spe.y << '\t' << spe.z << '\t' << spe.r << std::endl;
	return out;
}

class OCTree
{
	Cuboid boundary;
	int capacity;
	std::vector<Point> points;
	bool devided;

	OCTree *northwest;
	OCTree *northeast;
	OCTree *southwest;
	OCTree *southeast;

public:
	static std::vector<Cuboid> boundaries;

	OCTree(Cuboid inp_boundary, int inp_capacity)
	{
		if (inp_capacity < 1)
		{
			throw std::invalid_argument("received capacity less than 1");
		}
		this->devided = false;
		this->boundary = inp_boundary;
		this->capacity = inp_capacity;
		this->points = std::vector<Point>();

		this->northwest = nullptr;
		this->northeast = nullptr;
		this->southwest = nullptr;
		this->southeast = nullptr;
	}
	std::vector<OCTree *> get_children()
	{
		if (this->northeast != nullptr)
		{
			std::vector<OCTree *> ret = {this->northeast, this->northwest, this->southeast, this->southwest};
			return ret;
		}
		std::vector<OCTree *> ret = {nullptr, nullptr, nullptr, nullptr};
		return ret;
	}

	Cuboid get_boundary()
	{
		return boundary;
	}
	vector<Cuboid> get_boundaries()
	{
		return boundaries;
	}
	void subdevide()
	{
		double x = this->boundary.get_x();
		double y = this->boundary.get_y();
		double w = this->boundary.get_w();
		double h = this->boundary.get_h();

		Cuboid ne = Cuboid(x + w / 4, y - h / 4, w / 2, h / 2); //CHECK
		Cuboid nw = Cuboid(x - w / 4, y - h / 4, w / 2, h / 2); //CHECK
		Cuboid se = Cuboid(x + w / 4, y + h / 4, w / 2, h / 2); //CHECK
		Cuboid sw = Cuboid(x - w / 4, y + h / 4, w / 2, h / 2); //CHECK

		this->northeast = new OCTree(ne, this->capacity);
		this->northwest = new OCTree(nw, this->capacity);
		this->southeast = new OCTree(se, this->capacity);
		this->southwest = new OCTree(sw, this->capacity);

		this->devided = true;
		// cout << "Devided" << std::endl;
	}

	bool insert(Point point)
	{
		if (!this->boundary.contains(point))
		{
			return false;
		}
		if (this->points.size() < this->capacity) //CHECK
		{
			// cout << this->boundary << std::endl;
			// cout << "This boundary has capacity " << this->boundary;
			this->points.push_back(point);
			return true;
		}
		else if (!this->devided)
		{
			// cout << this->boundary << std::endl;
			// cout << "This boundary doesn't have capacity!!! " << this->boundary;
			boundaries.push_back(boundary);
			this->subdevide();
		}

		return (
			this->northeast->insert(point) ||
			this->northwest->insert(point) ||
			this->southeast->insert(point) ||
			this->southwest->insert(point));
	}

	vector<Point> query(Cuboid range, vector<Point> &found)
	{

		if (!range.intersects(this->boundary))
		{
			// cout << "Not intersect";
			return found;
		}
		for (int i = 0; i < this->points.size(); i++)
		{
			count++;
			if (range.contains(this->points[i]))
			{
				found.push_back(this->points[i]);
			}
		}
		if (this->devided)
		{
			if (this->northwest != nullptr && range.intersects(this->northwest->boundary))
			{
				this->northwest->query(range, found);
			}
			if (this->northeast != nullptr && range.intersects(this->northeast->boundary))
			{
				this->northeast->query(range, found);
			}
			if (this->southwest != nullptr && range.intersects(this->southwest->boundary))
			{
				this->southwest->query(range, found);
			}
			if (this->southeast != nullptr && range.intersects(this->southeast->boundary))
			{
				this->southeast->query(range, found);
			}
		}
		return found;
	}

	vector<Point> query(Sphere range, vector<Point> &found)
	{

		if (!range.intersects(this->boundary))
		{
			// cout << "Not intersect";
			return found;
		}
		for (int i = 0; i < this->points.size(); i++)
		{
			if (range.contains(this->points[i]))
			{
				// count++;
				found.push_back(this->points[i]);
			}
		}
		if (this->devided)
		{
			if (this->northwest != nullptr && range.intersects(this->northwest->boundary))
			{
				this->northwest->query(range, found);
			}
			if (this->northeast != nullptr && range.intersects(this->northeast->boundary))
			{
				this->northeast->query(range, found);
			}
			if (this->southwest != nullptr && range.intersects(this->southwest->boundary))
			{
				this->southwest->query(range, found);
			}
			if (this->southeast != nullptr && range.intersects(this->southeast->boundary))
			{
				this->southeast->query(range, found);
			}
		}
		return found;
	}

	// Temporary
	void print_Boundaries()
	{
		if (this->devided)
		{
			this->northwest->print_Boundaries();
			this->northeast->print_Boundaries();
			this->southwest->print_Boundaries();
			this->southeast->print_Boundaries();
		}
		else
		{
			if (this->points.size() > this->capacity)
			{
				cout << this->boundary;
				cout << this->points.size() << std::endl;
			}
		}
	}
	// TODO K nearest neighbor
};

constexpr int MIN = 1;
constexpr int WIDTH = 200;
constexpr int HEIGHT = 200;
constexpr int CAPACITY = 700;
constexpr int center_x = 200;
constexpr int center_y = 200;
