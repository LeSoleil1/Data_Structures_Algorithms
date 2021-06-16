
#include <iostream>
#include <cmath>
#include <random>
#include <math.h>
using namespace std;

class Point
{
	int x;
	int y;

public:
	Point(int const &inp_x, int const &inp_y)
	{
		x = inp_x;
		y = inp_y;
	}
	int get_x()
	{
		return x;
	}
	int get_y()
	{
		return y;
	}
	double distance(const Point &point)
	{
		double distance_x = point.x - this->x;
		double distance_y = point.y - this->y;
		return sqrt(pow(distance_x, 2) + pow(distance_y, 2));
	}

	friend ostream &operator<<(ostream &out, const Point &poi);
};

class Rectangle
{
	int x;
	int y;
	int w;
	int h;
	int left;
	int right;
	int top;
	int bottom;

public:
	Rectangle()
	{
		this->x = 0;
		this->y = 0;
		this->w = 0;
		this->h = 0;
		this->left = 0;
		this->right = 0;
		this->top = 0;
		this->bottom = 0;
	}
	Rectangle(int const &inp_x, int const &inp_y, int const &inp_w, int const &inp_h)
	{
		this->x = inp_x;
		this->y = inp_y;
		this->w = inp_w;
		this->h = inp_h;
		this->left = inp_x - inp_w / 2;
		this->right = inp_x + inp_w / 2;
		this->top = inp_y - inp_h / 2;
		this->bottom = inp_y + inp_h / 2;
	}
	int get_x()
	{
		return this->x;
	}
	int get_y()
	{
		return this->y;
	}
	int get_w()
	{
		return this->w;
	}
	int get_h()
	{
		return this->h;
	}
	bool contains(Point point)
	{
		int point_x = point.get_x();
		int point_y = point.get_y();
		return (this->left <= point_x &&
				point_x <= this->right &&
				this->top <= point_y &&
				point_y <= this->bottom);
	}
	bool intersects(Rectangle range)
	{
		return !(
			this->right < range.left || range.right < this->left ||
			this->bottom < range.top || range.bottom < this->top);
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
	double distance(Point point)
	{
		double distance_x = x_distance(point);
		double distance_y = y_distance(point);
		return sqrt(pow(distance_x, 2) + pow(distance_y, 2));
	}

	friend ostream &operator<<(ostream &out, const Rectangle &rec);
};

class Circle
{
	int x;
	int y;
	int r;

public:
	Circle(int const &inp_x, int const &inp_y, int const &inp_r)
	{
		this->x = inp_x;
		this->y = inp_y;
		this->r = inp_r;
	}
	int get_x()
	{
		return this->x;
	}
	int get_y()
	{
		return this->y;
	}
	int get_r()
	{
		return this->r;
	}
	double distnace_center(Point point)
	{
		return sqrt(pow((this->x - point.get_x()), 2) + pow((this->y - point.get_y()), 2));
	}
	bool contains(Point point)
	{
		double dist = this->distnace_center(point);
		return (dist <= this->r);
	}
	bool intersects(Rectangle range)
	{
		double distance_x = abs(range.get_x() - this->x);
		double distance_y = abs(range.get_y() - this->y);

		double radius = this->r;
		double width_half = range.get_w() / 2;
		double height_half = range.get_h() / 2;

		if (distance_x > (radius + width_half) ||
			distance_y > (radius + height_half))
		{
			return false;
		}
		if (distance_x <= width_half || distance_y <= height_half)
		{
			return true;
		}

		double edges = pow((distance_x - width_half), 2) + pow((distance_y - height_half), 2);
		return (edges <= pow(this->r, 2));
	}

	friend ostream &operator<<(ostream &out, const Circle &rec);
};


ostream &operator<<(ostream &out, const Rectangle &rec)
{
	out << rec.x << '\t' << rec.y << '\t' << rec.w << '\t' << rec.h << std::endl;
	return out;
}

ostream &operator<<(ostream &out, const Point &poi)
{
	out << poi.x << '\t' << poi.y << '\t' << std::endl;
	return out;
}

ostream &operator<<(ostream &out, const Circle &cir)
{
	out << cir.x << '\t' << cir.y << '\t' << cir.r <<  std::endl;
	return out;
}

class QuadTree
{
	Rectangle boundary;
	int capacity;
	std::vector<Point> points;
	bool devided = false;

	QuadTree *northwest;
	QuadTree *northeast;
	QuadTree *southwest;
	QuadTree *southeast;

public:
	QuadTree(Rectangle inp_boundary, int n)
	{
		boundary = inp_boundary;
		capacity = n;
		northwest = nullptr;
		northeast = nullptr;
		southwest = nullptr;
		southeast = nullptr;
	}
	Rectangle get_boundary()
	{
		return boundary;
	}
	void subdevide()
	{
		int x = this->boundary.get_x();
		int y = this->boundary.get_y();
		int w = this->boundary.get_w();
		int h = this->boundary.get_h();

		Rectangle ne = Rectangle(x + w / 4, y - h / 4, w / 2, h / 2);
		Rectangle nw = Rectangle(x - w / 4, y - h / 4, w / 2, h / 2);
		Rectangle se = Rectangle(x + w / 4, y + h / 4, w / 2, h / 2);
		Rectangle sw = Rectangle(x - w / 4, y + h / 4, w / 2, h / 2);

		this->northwest = new QuadTree(nw, this->capacity);
		this->northeast = new QuadTree(ne, this->capacity);
		this->southwest = new QuadTree(sw, this->capacity);
		this->southeast = new QuadTree(se, this->capacity);

		this->devided = true;
		// cout << "Devided" << std::endl;
	}
	bool insert(Point point)
	{
		if (!this->boundary.contains(point))
		{
			return false;
		}
		if (this->points.size() < this->capacity)
		{
			this->points.push_back(point);
			return true;
		}
		else
		{
			if (!this->devided)
			{
				this->subdevide();
			}
		}
		return (
			this->northeast->insert(point) ||
			this->northwest->insert(point) ||
			this->southeast->insert(point) ||
			this->southwest->insert(point));
	}

	vector<Point> query(Rectangle range, vector<Point> &found)
	{
		// if (!found.size())
		// {
		// 	cout << "here";
		// 	vector<Point> found;
		// }

		if (!range.intersects(this->boundary))
		{
			// cout << "Not intersect";
			return found;
		}
		for (int i = 0; i < this->points.size(); i++)
		{
			if (range.contains(this->points[i]))
			{
				found.push_back(this->points[i]);
			}
		}
		if (this->devided)
		{
			this->northwest->query(range, found);
			this->northeast->query(range, found);
			this->southwest->query(range, found);
			this->southeast->query(range, found);
		}
		return found;
	}

	// TODO K nearest neighbor
};

constexpr int MIN = 1;
constexpr int WIDTH = 200;
constexpr int HEIGHT = 200;
constexpr int CAPACITY = 4;

int main()
{
	std::random_device rd;
	std::mt19937 e2(rd());
	std::normal_distribution<> dist_width(WIDTH / 2, WIDTH / 8);
	std::normal_distribution<> dist_height(HEIGHT / 2, HEIGHT / 8);

	Rectangle boundary(200, 200, 200, 200);
	// Point p(10,15);
	// cout << boundary.contains(p);
	QuadTree qt(boundary, CAPACITY);
	int counter = 0;
	for (int i = 0; i < 5000; i++)
	{
		int x = round(dist_width(e2));
		int y = round(dist_height(e2));
		Point p(x, y);

		// Point p(rand() % WIDTH, rand() % HEIGHT);
		// cout << p;
		bool res = qt.insert(p);
		if (res == 1)
		{
			counter++;
			cout << p;
		}
		// cout << "inserted\t" << res << std::endl;
		// cout << boundary.contains(p) << std::endl;
	}
	cout << counter << std::endl;
	// cout << qt.get_boundary();
	Rectangle range(200, 200, 100, 100);
	vector<Point> points;
	points = qt.query(range, points);
	cout << points.size() << std::endl;
	for (auto point : points)
	{
		cout << point << ' ';
	}

	// std::random_device rd;
	// std::mt19937 e2(rd());
	// std::normal_distribution<> dist(200,200);
	// vector<int> p;
	// for (int i = 0; i <100 ; i++){
	// 	p.push_back(round(dist(e2)));
	// }
	// for (auto i : p){
	// 	std::cout << i << ' ';
	// }
	// cout<<p.size();
	return 0;
}
