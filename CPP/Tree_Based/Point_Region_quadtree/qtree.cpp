
#include <iostream>
#include <cmath>
// #include <cstdlib>
#include <random>
#include <math.h>
#include <tuple>
#include <chrono>

#include <GL/glut.h>

using namespace std;
using namespace std::chrono;

int count = 0;
// TODO make it double or type
class Point
{
	double x;
	double y;

public:
	Point(double const &inp_x, double const &inp_y)
	{
		x = inp_x;
		y = inp_y;
	}
	double get_x()
	{
		return x;
	}
	double get_y()
	{
		return y;
	}
	double distance(const Point &point)
	{
		double distance_x = point.x - this->x;
		double distance_y = point.y - this->y;
		return sqrt(pow(distance_x, 2) + pow(distance_y, 2));
	}
	friend bool operator==(const Point &lhs, const Point &rhs){return (lhs.x == rhs.x && lhs.y == rhs.y);}
	friend ostream &operator<<(ostream &out, const Point &poi);
};

class Rectangle
{
	double x;
	double y;
	double w;
	double h;
	double left;
	double right;
	double top;
	double bottom;

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
	Rectangle(double const &inp_x, double const &inp_y, double const &inp_w, double const &inp_h)
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
	double get_x()
	{
		return this->x;
	}
	double get_y()
	{
		return this->y;
	}
	double get_w()
	{
		return this->w;
	}
	double get_h()
	{
		return this->h;
	}
	bool contains(Point point)
	{
		double point_x = point.get_x();
		double point_y = point.get_y();
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
	double x;
	double y;
	double r;

public:
	Circle(double const &inp_x, double const &inp_y, double const &inp_r)
	{
		this->x = inp_x;
		this->y = inp_y;
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
	double get_r()
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
	out << "Center_x: " << rec.x << '\t' << "Center_y: " << rec.y << '\t' << "Range_x: " << rec.w << '\t' << "Range_y: " << rec.h << std::endl;
	return out;
}

ostream &operator<<(ostream &out, const Point &poi)
{
	out << poi.x << '\t' << poi.y << '\t' << std::endl;
	return out;
}

ostream &operator<<(ostream &out, const Circle &cir)
{
	out << cir.x << '\t' << cir.y << '\t' << cir.r << std::endl;
	return out;
}

class QuadTree
{
	Rectangle boundary;
	int capacity;
	std::vector<Point> points;
	bool devided;

	QuadTree *northwest;
	QuadTree *northeast;
	QuadTree *southwest;
	QuadTree *southeast;

public:
	static std::vector<Rectangle> boundaries;

	QuadTree(Rectangle inp_boundary, int inp_capacity)
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
	std::vector<QuadTree *> get_children()
	{
		if (this->northeast != nullptr)
		{
			std::vector<QuadTree *> ret = {this->northeast, this->northwest, this->southeast, this->southwest};
			return ret;
		}
		std::vector<QuadTree *> ret = {nullptr, nullptr, nullptr, nullptr};
		return ret;
	}

	Rectangle get_boundary()
	{
		return boundary;
	}
	vector<Rectangle> get_boundaries()
	{
		return boundaries;
	}
	void subdevide()
	{
		double x = this->boundary.get_x();
		double y = this->boundary.get_y();
		double w = this->boundary.get_w();
		double h = this->boundary.get_h();

		Rectangle ne = Rectangle(x + w / 4, y - h / 4, w / 2, h / 2); //CHECK
		Rectangle nw = Rectangle(x - w / 4, y - h / 4, w / 2, h / 2); //CHECK
		Rectangle se = Rectangle(x + w / 4, y + h / 4, w / 2, h / 2); //CHECK
		Rectangle sw = Rectangle(x - w / 4, y + h / 4, w / 2, h / 2); //CHECK

		this->northeast = new QuadTree(ne, this->capacity);
		this->northwest = new QuadTree(nw, this->capacity);
		this->southeast = new QuadTree(se, this->capacity);
		this->southwest = new QuadTree(sw, this->capacity);

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

	vector<Point> query(Rectangle range, vector<Point> &found)
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

	vector<Point> query(Circle range, vector<Point> &found)
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

// void display1(void)
// {

// 	// Line x axis
// 	glColor3ub(254, 0, 0);
// 	glBegin(GL_LINES);
// 	glVertex2f(-1.0, 0.0);
// 	glVertex2f(1.0, 0.0);
// 	glEnd();

// 	// Line y axis
// 	glColor3ub(31, 255, 0);
// 	glBegin(GL_LINES);
// 	glVertex2f(0.0, -1.0);
// 	glVertex2f(0.0, 1.0);
// 	glEnd();

// 	glFlush();
// }
std::vector<Rectangle> QuadTree::boundaries = std::vector<Rectangle>();

int main(int argc, char **argv)
{
	auto mean_x = center_x;
	auto mean_y = center_y;
	auto stddev_x = WIDTH / 4;
	auto stddev_y = HEIGHT / 4;

	std::random_device rd;
	std::mt19937 e2(rd());
	std::normal_distribution<> dist_width(mean_x, stddev_x);
	std::normal_distribution<> dist_height(mean_y, stddev_y);

	Rectangle boundary(center_x, center_y, WIDTH, WIDTH);
	QuadTree qt(boundary, CAPACITY);
	int counter = 0;
	int x_int;
	int y_int;

	auto start = chrono::high_resolution_clock::now();
	for (int i = 0; i < 70000; i++)
	{
		x_int = round(dist_width(e2));
		y_int = round(dist_height(e2));
		Point p(x_int, y_int);
		// Point p(rand() % WIDTH, rand() % HEIGHT);
		// cout << p;
		bool res = qt.insert(p);
		// if (res == 1)
		// {
		// 	counter++;
		// }
		// cout << "inserted\t" << res << std::endl;
		// cout << boundary.contains(p) << std::endl;
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);

	// To get the value of duration use the count()
	// member function on the duration object
	cout << "Generating the tree takes " << duration.count() << " microseconds" << std::endl;

	qt.print_Boundaries();

	vector<Rectangle> boundaries = qt.get_boundaries();
	Rectangle original_range(center_x, center_y, WIDTH, HEIGHT);
	vector<Point> points;
	points = qt.query(original_range, points);
	cout << " Number of points inserted: " << points.size() << std::endl;

	// cout << qt.get_boundary();
	std::chrono::duration<int64_t, std::nano> duration_q = std::chrono::duration<int64_t, std::nano>();
	std::chrono::duration<int64_t, std::nano> duration_all = std::chrono::duration<int64_t, std::nano>();
	int max_iter = 1000;
	int count_brute = 0;
	srand((unsigned)time(0)); // make it change everytime we run the code
	for (int i = 0; i < max_iter; i++)
	{
		// PASS A RANGE AND GET THE POINTS IN THAT RANGE
		// int x_rand = 100 + rand() % 201; // (200 -100 + 1)
		// int y_rand = 100 + rand() % 201; // (200 -100 + 1)
		// Rectangle range(x_rand, y_rand, 20, 20);
		// Circle range(x_rand, y_rand,50);
		// Rectangle range(200,200,20,20);
		Circle range(200,200,20);
		vector<Point> pointz;

		// QTree approach
		auto start_q = chrono::high_resolution_clock::now();
		pointz = qt.query(range, pointz);
		auto stop_q = high_resolution_clock::now();
		duration_q += (stop_q - start_q);

		// Brute Force
		vector<Point> pointz_test;
		auto start_all = chrono::high_resolution_clock::now();
		for (auto point : points)
		{
			count_brute++;
			if (range.contains(point)){
				pointz_test.push_back(point);
			}
		}
		auto stop_all = chrono::high_resolution_clock::now();
		duration_all += (stop_all - start_all);

		// cout << (pointz.size() == pointz_test.size());
		cout << (pointz == pointz_test);
	}
	cout << "QTREE: " << duration_cast<microseconds>(duration_q).count() / max_iter << std::endl;
	cout << "QTREE: Number of points checked to find the points within the range: " << count << std::endl;
	cout << "BRUTE: " << duration_cast<microseconds>(duration_all).count() / max_iter << std::endl;
	cout << "BRUTE: Number of points checked to find the points within the range: " << count_brute << std::endl;


	// // PASS A RANGE AND GET THE POINTS IN THAT RANGE
	// srand((unsigned)time(NULL));	 // make it change everytime we run the code
	// int x_rand = 100 + rand() % 201; // (200 -100 + 1)
	// int y_rand = 100 + rand() % 201; // (200 -100 + 1)
	// Rectangle range(x_rand, y_rand, 50, 50);
	// vector<Point> pointz;
	// pointz = qt.query(range, pointz);
	// cout << pointz.size() << " Number of points are in the: "
	// 	 << "range: " << range << std::endl;
	// cout << "Number of points checked to find the points within the range: " << count << std::endl;

	// // PRINT ALL THE BOUNDARIES
	// cout << '\n'
	// 	 << "BOUNDARIES:" << '\n';
	// for (auto boundary : boundaries)
	// {
	// 	cout << boundary << std::endl;
	// }

	// // PRINT ALL THE POINTS
	// cout << '\n'
	// 	 << "POINTS:" << '\n';
	// for (auto point : points)
	// {
	// 	cout << point << ' ';
	// }

	// // Drawing ///////////////
	// glutInit(&argc, argv);
	// glutInitWindowSize(900, 900);
	// glutCreateWindow("Test");
	// glClearColor(1.0, 1.0, 1.0, 1.0); // Background color
	// float x;
	// float y;
	// glClear(GL_COLOR_BUFFER_BIT);
	// // counter = 0;

	// // Plotting Boundaries
	// // int x_int;;
	// // int y_int;
	// int w_int;
	// int h_int;
	// for (auto boundary : boundaries)
	// {
	// 	x_int = boundary.get_x();
	// 	y_int = boundary.get_y();
	// 	w_int = boundary.get_w();
	// 	h_int = boundary.get_h();
	// 	float x_start = x_int - w_int / 2.0;
	// 	float x_stop = x_int + w_int / 2.0;
	// 	float y_start = y_int - h_int / 2.0;
	// 	float y_stop = y_int + h_int / 2.0;
	// 	x_start = (x_start - center_x) / (WIDTH / 2.0);
	// 	x_stop = (x_stop - center_x) / (WIDTH / 2.0);
	// 	x = (x_int - center_x) / (WIDTH / 2.0);
	// 	y_start = (y_start - center_y) / (HEIGHT / 2.0);
	// 	y_stop = (y_stop - center_y) / (HEIGHT / 2.0);
	// 	y = (y_int - center_y) / (HEIGHT / 2.0);
	// 	// cout << x_start << '\t' << x_stop << '\t' << y << std::endl;
	// 	// cout << y_start << '\t' << y_stop << '\t' << x << std::endl;

	// 	// Line x axis
	// 	glColor3ub(254, 0, 0);
	// 	glBegin(GL_LINES);
	// 	glVertex2f(x_start, y);
	// 	glVertex2f(x_stop, y);
	// 	glEnd();

	// 	// Line y axis
	// 	glColor3ub(31, 255, 0);
	// 	glBegin(GL_LINES);
	// 	glVertex2f(x, y_start);
	// 	glVertex2f(x, y_stop);
	// 	glEnd();

	// 	glFlush();
	// }

	// // Plotting points
	// for (auto point : points)
	// {
	// 	x_int = point.get_x();
	// 	y_int = point.get_y();
	// 	x = (x_int - center_x) / (WIDTH / 2.0);
	// 	y = (y_int - center_y) / (HEIGHT / 2.0);
	// 	glPointSize(3);
	// 	glBegin(GL_POINTS);
	// 	glColor3f(0.5, 0, 0);
	// 	glVertex2f(x, y);
	// 	glEnd();
	// 	glFlush();
	// }

	// // PLOTTING THE SPECIFIC POINTS IN THE SPECIFIED REGION
	// // FIRST PLOT THE REGION
	// // Rectangle
	// x_int = range.get_x();
	// y_int = range.get_y();
	// w_int = range.get_w();
	// h_int = range.get_h();
	// float x_start = x_int - w_int / 2.0;
	// float x_stop = x_int + w_int / 2.0;
	// float y_start = y_int - h_int / 2.0;
	// float y_stop = y_int + h_int / 2.0;
	// x_start = (x_start - center_x) / (WIDTH / 2.0);
	// x_stop = (x_stop - center_x) / (WIDTH / 2.0);
	// y_start = (y_start - center_y) / (HEIGHT / 2.0);
	// y_stop = (y_stop - center_y) / (HEIGHT / 2.0);
	// cout << x_start << '\t' << x_stop << std::endl;
	// cout << y_start << '\t' << y_stop << std::endl;
	// // if (x_start < -1) {	x_start = -.99;}
	// // if (x_start > 1) {	x_start = .99;}
	// // if (x_stop < -1) {	x_stop = -.99;}
	// // if (x_stop > 1) {	x_stop = .99;}
	// // if (y_start < -1) {	y_start = -.99;}
	// // if (y_start > 1) {	y_start = .99;}
	// // if (y_stop < -1) {	y_stop = -.99;}
	// // if (y_stop > 1) {	y_stop = .99;}

	// cout << x_start << '\t' << x_stop << std::endl;
	// cout << y_start << '\t' << y_stop << std::endl;
	// glLineWidth(5);
	// glBegin(GL_LINE_LOOP);{
	// 	glColor3ub(0, 0, 250);
	// 	glColor4f(1.0, 0.0, 0.0, 0.5);
	// 	glVertex2f(x_start,y_stop);
	// 	glVertex2f(x_stop, y_stop);
	// 	glVertex2f(x_stop, y_start);
	// 	glVertex2f(x_start, y_start);
	// }
	// glEnd();
	// // POINTS
	// for (auto point : pointz)
	// {
	// 	x_int = point.get_x();
	// 	y_int = point.get_y();
	// 	x = (x_int - center_x) / (WIDTH / 2.0);
	// 	y = (y_int - center_y) / (HEIGHT / 2.0);
	// 	glPointSize(3);
	// 	glBegin(GL_POINTS);
	// 	glColor3f(0, 1, 0);
	// 	glVertex2f(x, y);
	// 	glEnd();
	// 	glFlush();
	// }

	// // cout << counter;
	// // glutDisplayFunc(display1);
	// glutMainLoop();
	// //////////////////////////////////////
	return 0;
}
