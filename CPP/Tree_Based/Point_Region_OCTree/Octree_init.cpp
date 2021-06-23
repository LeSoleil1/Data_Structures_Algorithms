#include <iostream>
#include <cmath>
#include <random>
#include <math.h>
#include <tuple>
#include <chrono>

#include <GL/glut.h>

using namespace std;
using namespace std::chrono;

int count = 0;
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
		this->top = inp_y + inp_h / 2;
		this->bottom = inp_y - inp_h / 2;
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
				this->bottom <= point_y &&
				point_y <= this->top &&
				this->back <= point_z &&
				point_z <= this->front);
	}
	bool intersects(Cuboid range)
	{
		return !(
			this->right < range.left || range.right < this->left ||
			this->top < range.bottom || range.top < this->bottom ||
			this->front < range.back || range.front < this->back);
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
		if (this->bottom <= point.get_y() && point.get_y() <= this->top)
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
		return min(abs(point.get_z() - this->back), abs(point.get_z() - this->front));
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
	out << "Center_x: " << cub.x << '\t' << "Center_y: " << cub.y << '\t' << "Center_z: " << cub.z << '\t' << "Range_x: " << cub.w << '\t' << "Range_y: " << cub.h << '\t' << "Range_z: " << cub.d << std::endl;
	return out;
}

ostream &operator<<(ostream &out, const Point &poi)
{
	out << "X: " << poi.x << '\t' << "Y: " << poi.y << '\t' << "Z: " << poi.z << std::endl;
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

	OCTree *northwestFront;
	OCTree *northeastFront;
	OCTree *southwestFront;
	OCTree *southeastFront;
	OCTree *northwestBack;
	OCTree *northeastBack;
	OCTree *southwestBack;
	OCTree *southeastBack;

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

		this->northwestFront = nullptr;
		this->northeastFront = nullptr;
		this->southwestFront = nullptr;
		this->southeastFront = nullptr;
		this->northwestBack = nullptr;
		this->northeastBack = nullptr;
		this->southwestBack = nullptr;
		this->southeastBack = nullptr;
	}
	std::vector<OCTree *> get_children()
	{
		if (this->northeastFront != nullptr)
		{
			std::vector<OCTree *> ret = {this->northwestFront, this->northeastFront, this->southwestFront, this->southeastFront,
										 this->northwestBack, this->northeastBack, this->southwestBack, this->southeastBack};
			return ret;
		}
		std::vector<OCTree *> ret = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
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
		double z = this->boundary.get_z();
		double w = this->boundary.get_w();
		double h = this->boundary.get_h();
		double d = this->boundary.get_d();

		Cuboid nef = Cuboid(x + w / 4, y + h / 4, z + d / 4, w / 2, h / 2, d / 2); //CHECK
		Cuboid nwf = Cuboid(x - w / 4, y + h / 4, z + d / 4, w / 2, h / 2, d / 2); //CHECK
		Cuboid sef = Cuboid(x + w / 4, y - h / 4, z + d / 4, w / 2, h / 2, d / 2); //CHECK
		Cuboid swf = Cuboid(x - w / 4, y - h / 4, z + d / 4, w / 2, h / 2, d / 2); //CHECK
		Cuboid neb = Cuboid(x + w / 4, y + h / 4, z - d / 4, w / 2, h / 2, d / 2); //CHECK
		Cuboid nwb = Cuboid(x - w / 4, y + h / 4, z - d / 4, w / 2, h / 2, d / 2); //CHECK
		Cuboid seb = Cuboid(x + w / 4, y - h / 4, z - d / 4, w / 2, h / 2, d / 2); //CHECK
		Cuboid swb = Cuboid(x - w / 4, y - h / 4, z - d / 4, w / 2, h / 2, d / 2); //CHECK

		this->northeastFront = new OCTree(nef, this->capacity);
		this->northwestFront = new OCTree(nwf, this->capacity);
		this->southeastFront = new OCTree(sef, this->capacity);
		this->southwestFront = new OCTree(swf, this->capacity);
		this->northeastBack = new OCTree(neb, this->capacity);
		this->northwestBack = new OCTree(nwb, this->capacity);
		this->southeastBack = new OCTree(seb, this->capacity);
		this->southwestBack = new OCTree(swb, this->capacity);

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
			count++;
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
			this->northeastFront->insert(point) ||
			this->northwestFront->insert(point) ||
			this->southeastFront->insert(point) ||
			this->southwestFront->insert(point) ||
			this->northeastBack->insert(point) ||
			this->northwestBack->insert(point) ||
			this->southeastBack->insert(point) ||
			this->southwestBack->insert(point));
	}

	vector<Point> query(Cuboid range, vector<Point> &found)
	{

		if (!range.intersects(this->boundary))
		{
			cout << "Not intersect";
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
			if (this->northwestFront != nullptr && range.intersects(this->northwestFront->boundary))
			{
				this->northwestFront->query(range, found);
			}
			if (this->northeastFront != nullptr && range.intersects(this->northeastFront->boundary))
			{
				this->northeastFront->query(range, found);
			}
			if (this->southwestFront != nullptr && range.intersects(this->southwestFront->boundary))
			{
				this->southwestFront->query(range, found);
			}
			if (this->southeastFront != nullptr && range.intersects(this->southeastFront->boundary))
			{
				this->southeastFront->query(range, found);
			}
			if (this->northwestBack != nullptr && range.intersects(this->northwestBack->boundary))
			{
				this->northwestBack->query(range, found);
			}
			if (this->northeastBack != nullptr && range.intersects(this->northeastBack->boundary))
			{
				this->northeastBack->query(range, found);
			}
			if (this->southwestBack != nullptr && range.intersects(this->southwestBack->boundary))
			{
				this->southwestBack->query(range, found);
			}
			if (this->southeastBack != nullptr && range.intersects(this->southeastBack->boundary))
			{
				this->southeastBack->query(range, found);
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
				found.push_back(this->points[i]);
			}
		}
		if (this->devided)
		{
			if (this->northwestFront != nullptr && range.intersects(this->northwestFront->boundary))
			{
				this->northwestFront->query(range, found);
			}
			if (this->northeastFront != nullptr && range.intersects(this->northeastFront->boundary))
			{
				this->northeastFront->query(range, found);
			}
			if (this->southwestFront != nullptr && range.intersects(this->southwestFront->boundary))
			{
				this->southwestFront->query(range, found);
			}
			if (this->southeastFront != nullptr && range.intersects(this->southeastFront->boundary))
			{
				this->southeastFront->query(range, found);
			}
			if (this->northwestBack != nullptr && range.intersects(this->northwestBack->boundary))
			{
				this->northwestBack->query(range, found);
			}
			if (this->northeastBack != nullptr && range.intersects(this->northeastBack->boundary))
			{
				this->northeastBack->query(range, found);
			}
			if (this->southwestBack != nullptr && range.intersects(this->southwestBack->boundary))
			{
				this->southwestBack->query(range, found);
			}
			if (this->southeastBack != nullptr && range.intersects(this->southeastBack->boundary))
			{
				this->southeastBack->query(range, found);
			}
		}
		return found;
	}

	// Temporary
	void print_Boundaries()
	{
		if (this->devided)
		{
			this->northwestFront->print_Boundaries();
			this->northeastFront->print_Boundaries();
			this->southwestFront->print_Boundaries();
			this->southeastFront->print_Boundaries();
			this->northwestBack->print_Boundaries();
			this->northeastBack->print_Boundaries();
			this->southwestBack->print_Boundaries();
			this->southeastBack->print_Boundaries();
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
constexpr int DEPTH = 200;
constexpr int CAPACITY = 400;
constexpr int center_x = 0;
constexpr int center_y = 0;
constexpr int center_z = 0;

// I define two global variables here to use them when I want to draw.
// The display function that I use in openGL in glutDisplayFunc dont take parameters.
vector<Point> inserted_points = vector<Point>();
vector<Point> query_pointz = vector<Point>();

std::vector<Cuboid> OCTree::boundaries = std::vector<Cuboid>();

double rnd(double lo, double hi)
{
	return lo + (hi - lo) * (rand() / static_cast<double>(RAND_MAX));
}

double angle = 0.0;
void timer(int value)
{
	angle += 1.0;
	glutTimerFunc(16, timer, 0);
	glutPostRedisplay();
}

void display()
{
	glClearColor(0, 0, 0, 0);
	float x;
	float y;
	float z;
	int x_int;
	int y_int;
	int z_int;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double w = glutGet(GLUT_WINDOW_WIDTH);
	double h = glutGet(GLUT_WINDOW_HEIGHT);
	gluPerspective(60.0, w / h, 0.1, 1000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(200, 200, 200, 0, 0, 0, 0, 0, 1);

	glRotated(angle, 0, 0, 1);

	// Line x axis
	glColor3ub(254, 0, 0);
	glBegin(GL_LINES);
	// glVertex3f(0.0f, 0.0f, 0.0f);
	// glVertex3f(1.0f, 0.0f, 0.0f);
	glVertex3d(0, 0, 0);
	glVertex3d(150, 0, 0);
	glEnd();

	// Line y axis
	glColor3ub(0, 255, 0);
	glBegin(GL_LINES);
	// glVertex3f(0.0f, 0.0f, 0.0f);
	// glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 150, 0);
	glEnd();

	// Line z axis
	glColor3ub(0, 0, 255);
	glBegin(GL_LINES);
	// glVertex3f(0.0f, 0.0f, 0.0f);
	// glVertex3f(0.0f, 0.0f, 1.0f);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, 150);
	glEnd();

	// All points in the space
	glPointSize(3);
	glBegin(GL_POINTS);
	for (auto point : inserted_points)
	{
		x_int = point.get_x();
		y_int = point.get_y();
		z_int = point.get_z();

		// x = (x_int - center_x) / (WIDTH / 2.0);
		// y = (y_int - center_y) / (HEIGHT / 2.0);
		// z = (z_int - center_z) / (DEPTH / 2.0);

		// glColor3f(rnd(-1.0,1.0), rnd(-1.0,1.0), rnd(-1.0,1.0));
		// glVertex3f(x, y, z);

		x = (x_int - center_x);
		y = (y_int - center_y);
		z = (z_int - center_z);
		// glColor3f(rnd(-1.0,1.0), rnd(-1.0,1.0), rnd(-1.0,1.0));
		glColor3f(0.5, 1, 0);

		glVertex3d(x, y, z);
	}
	glEnd();
	glutSwapBuffers();

	// Only points that returned by the algorithms within the range
	glPointSize(3);
	glBegin(GL_POINTS);
	for (auto point : query_pointz)
	{
		x_int = point.get_x();
		y_int = point.get_y();
		z_int = point.get_z();

		// x = (x_int - center_x) / (WIDTH / 2.0);
		// y = (y_int - center_y) / (HEIGHT / 2.0);
		// z = (z_int - center_z) / (DEPTH / 2.0);

		// glColor3f(rnd(-1.0,1.0), rnd(-1.0,1.0), rnd(-1.0,1.0));
		// glVertex3f(x, y, z);

		x = (x_int - center_x);
		y = (y_int - center_y);
		z = (z_int - center_z);
		// glColor3f(rnd(-1.0,1.0), rnd(-1.0,1.0), rnd(-1.0,1.0));
		glColor3f(1, 0, 0);

		glVertex3d(x, y, z);
	}
	glEnd();
	glutSwapBuffers();
}

int drawing(int argc, char **argv)
{
	// Drawing ///////////////
	// -lGL -lGLU -lglut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(900, 900);
	glutCreateWindow("Test");
	// glClearColor(1.0, 1.0, 1.0, 1.0); // Background color
	// glClearColor(0, 0, 0, 0);
	// float x;
	// float y;
	// float z;
	// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// glMatrixMode(GL_PROJECTION);
	// glLoadIdentity();
	// double w = glutGet(GLUT_WINDOW_WIDTH);
	// double h = glutGet(GLUT_WINDOW_HEIGHT);
	// gluPerspective(60.0, w / h, 0.1, 1000.0);

	// glMatrixMode(GL_MODELVIEW);
	// glLoadIdentity();
	// gluLookAt(200, 200, 200, 0, 0, 0, 0, 0, 1);

	// glRotated(angle, 0, 0, 1);

	// counter = 0;

	// Plotting Boundaries
	// int x_int;;
	// int y_int;
	// int w_int;
	// int h_int;
	// int d_int;
	// for (auto boundary : boundaries)
	// {
	// 	x_int = boundary.get_x();
	// 	y_int = boundary.get_y();
	// 	z_int = boundary.get_z();
	// 	w_int = boundary.get_w();
	// 	h_int = boundary.get_h();
	// 	d_int = boundary.get_d();
	// 	float x_start = x_int - w_int / 2.0;
	// 	float x_stop = x_int + w_int / 2.0;
	// 	float y_start = y_int - h_int / 2.0;
	// 	float y_stop = y_int + h_int / 2.0;
	// 	float z_start = z_int - d_int / 2.0;
	// 	float z_stop = z_int + d_int / 2.0;
	// 	x_start = (x_start - center_x) / (WIDTH / 2.0);
	// 	x_stop = (x_stop - center_x) / (WIDTH / 2.0);
	// 	x = (x_int - center_x) / (WIDTH / 2.0);
	// 	y_start = (y_start - center_y) / (HEIGHT / 2.0);
	// 	y_stop = (y_stop - center_y) / (HEIGHT / 2.0);
	// 	y = (y_int - center_y) / (HEIGHT / 2.0);

	// 	z_start = (z_start - center_z) / (DEPTH / 2.0);
	// 	z_stop = (z_stop - center_z) / (DEPTH / 2.0);
	// 	z = (z_int - center_z) / (DEPTH / 2.0);
	// 	// cout << x_start << '\t' << x_stop << '\t' << y << std::endl;
	// 	// cout << y_start << '\t' << y_stop << '\t' << x << std::endl;

	// 	// Line x axis
	// 	glColor3ub(254, 0, 0);
	// 	glBegin(GL_LINES);
	// 	glVertex3f(x_start, y, z);
	// 	glVertex3f(x_stop, y, z);
	// 	glEnd();

	// 	// Line y axis
	// 	glColor3ub(31, 255, 0);
	// 	glBegin(GL_LINES);
	// 	glVertex3f(x, y_start, z);
	// 	glVertex3f(x, y_stop, z);
	// 	glEnd();

	// 	// Line z axis
	// 	glColor3ub(31, 255, 0);
	// 	glBegin(GL_LINES);
	// 	glVertex3f(x, y, z_start);
	// 	glVertex3f(x, y, z_stop);
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
	// // Cuboid
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
	// srand(0);
	// glBegin(GL_LINES);
	// for (size_t i = 0; i<100;i++){
	// 	glColor3d(rnd(0.0,1.0),rnd(0.0,1.0),rnd(0.0,1.0));
	// 	glVertex3d(rnd(-50,50),rnd(-50,50),rnd(-50,50));
	// 	glVertex3d(rnd(-50,50),rnd(-50,50),rnd(-50,50));
	// }
	// glEnd();
	// glutSwapBuffers();
	// srand(0);
	// glPointSize(5);
	// glBegin(GL_POINTS);
	// for (size_t i = 0; i<100;i++){
	// 	glColor3d(rnd(0.0,1.0),rnd(0.0,1.0),rnd(0.0,1.0));
	// 	glVertex3d(rnd(-50,50),rnd(-50,50),rnd(-50,50));
	//     // glVertex3f(rnd(-1.0,1.0),rnd(-1.0,1.0),rnd(-1.0,1.0));
	// }
	// glEnd();
	// glutSwapBuffers();

	// // Line x axis
	// glColor3ub(254, 0, 0);
	// glBegin(GL_LINES);
	// // glVertex3f(0.0f, 0.0f, 0.0f);
	// // glVertex3f(1.0f, 0.0f, 0.0f);
	// glVertex3d(0, 0, 0);
	// glVertex3d(150, 0, 0);
	// glEnd();

	// // Line y axis
	// glColor3ub(0, 255, 0);
	// glBegin(GL_LINES);
	// // glVertex3f(0.0f, 0.0f, 0.0f);
	// // glVertex3f(0.0f, 1.0f, 0.0f);
	// glVertex3d(0, 0, 0);
	// glVertex3d(0, 150, 0);
	// glEnd();

	// // Line z axis
	// glColor3ub(0, 0, 255);
	// glBegin(GL_LINES);
	// // glVertex3f(0.0f, 0.0f, 0.0f);
	// // glVertex3f(0.0f, 0.0f, 1.0f);
	// glVertex3d(0, 0, 0);
	// glVertex3d(0, 0, 150);
	// glEnd();

	// // All points in the space
	// glPointSize(3);
	// glBegin(GL_POINTS);
	// for (auto point : points)
	// {
	// 	x_int = point.get_x();
	// 	y_int = point.get_y();
	// 	z_int = point.get_z();

	// 	// x = (x_int - center_x) / (WIDTH / 2.0);
	// 	// y = (y_int - center_y) / (HEIGHT / 2.0);
	// 	// z = (z_int - center_z) / (DEPTH / 2.0);

	// 	// glColor3f(rnd(-1.0,1.0), rnd(-1.0,1.0), rnd(-1.0,1.0));
	// 	// glVertex3f(x, y, z);

	// 	x = (x_int - center_x);
	// 	y = (y_int - center_y);
	// 	z = (z_int - center_z);
	// 	// glColor3f(rnd(-1.0,1.0), rnd(-1.0,1.0), rnd(-1.0,1.0));
	// 	glColor3f(0, 1, 0);

	// 	glVertex3d(x, y, z);
	// }
	// glEnd();
	// glutSwapBuffers();

	// // Only points that returned by the algorithms within the range
	// glPointSize(3);
	// glBegin(GL_POINTS);
	// for (auto point : query_pointz)
	// {
	// 	x_int = point.get_x();
	// 	y_int = point.get_y();
	// 	z_int = point.get_z();

	// 	// x = (x_int - center_x) / (WIDTH / 2.0);
	// 	// y = (y_int - center_y) / (HEIGHT / 2.0);
	// 	// z = (z_int - center_z) / (DEPTH / 2.0);

	// 	// glColor3f(rnd(-1.0,1.0), rnd(-1.0,1.0), rnd(-1.0,1.0));
	// 	// glVertex3f(x, y, z);

	// 	x = (x_int - center_x);
	// 	y = (y_int - center_y);
	// 	z = (z_int - center_z);
	// 	// glColor3f(rnd(-1.0,1.0), rnd(-1.0,1.0), rnd(-1.0,1.0));
	// 	glColor3f(1, 0, 0);

	// 	glVertex3d(x, y, z);
	// }
	// glEnd();
	// glutSwapBuffers();

	// // glFlush();

	// // cout << counter;
	glutDisplayFunc(display);
	glutTimerFunc(0, timer, 0);
	glutMainLoop();
	// //////////////////////////////////////
	return 0;
}

int main(int argc, char **argv)
{
	auto mean_x = center_x;
	auto mean_y = center_y;
	auto mean_z = center_z;
	auto stddev_x = WIDTH / 4;
	auto stddev_y = HEIGHT / 4;
	auto stddev_z = DEPTH / 4;

	std::random_device rd;
	std::mt19937 e2(rd());
	std::normal_distribution<> dist_width(mean_x, stddev_x);
	std::normal_distribution<> dist_height(mean_y, stddev_y);
	std::normal_distribution<> dist_depth(mean_z, stddev_z);

	Cuboid boundary(center_x, center_y, center_z, WIDTH, WIDTH, DEPTH);
	OCTree ot(boundary, CAPACITY);
	// vector<Point> inserted_points = vector<Point>();
	int counter = 0;
	int x_int;
	int y_int;
	int z_int;

	auto start = chrono::high_resolution_clock::now();
	for (int i = 0; i < 70000; i++)
	{
		x_int = round(dist_width(e2));
		y_int = round(dist_height(e2));
		z_int = round(dist_depth(e2));
		Point p(x_int, y_int, z_int);
		// cout << p;
		bool res = ot.insert(p);
		if (res == 1)
		{
			counter++;
			inserted_points.push_back(p);
		}
		// cout << "inserted\t" << res << std::endl;
		// cout << boundary.contains(p) << std::endl;
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);

	// To get the value of duration use the count()
	// member function on the duration object
	cout << "Generating the tree takes " << duration.count() << " microseconds" << std::endl;
	// cout << count;
	// for (auto point:inserted_points){
	// 	if(boundary.contains(point)){
	// 		cout << point;
	// 	}
	// }

	// ot.print_Boundaries();

	vector<Cuboid> boundaries = ot.get_boundaries();
	Cuboid test_range(center_x, center_y, center_z, WIDTH, HEIGHT, DEPTH);
	// cout << test_range << std::endl;
	vector<Point> points;
	points = ot.query(test_range, points);
	cout << " Number of points inserted: " << points.size() << std::endl;

	// cout << ot.get_boundary();
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
		// int z_rand = 100 + rand() % 201; // (200 -100 + 1)
		// Cuboid range(x_rand, y_rand, z_rand, 20, 20, 20);
		// Sphere range(x_rand, y_rand, z_rand, 50);
		// Cuboid range(0, 0, 0, 10,10,10);
		Sphere range(0, 0, 0, 20);
		vector<Point> query_pointz;

		// OCTree approach
		auto start_q = chrono::high_resolution_clock::now();
		query_pointz = ot.query(range, query_pointz);
		auto stop_q = high_resolution_clock::now();
		duration_q += (stop_q - start_q);

		// Brute Force
		vector<Point> pointz_test;
		auto start_all = chrono::high_resolution_clock::now();
		for (auto point : points)
		{
			count_brute++;
			if (range.contains(point))
			{
				pointz_test.push_back(point);
			}
		}
		auto stop_all = chrono::high_resolution_clock::now();
		duration_all += (stop_all - start_all);

		// cout << (pointz.size() == pointz_test.size());
		cout << (query_pointz == pointz_test);
	}
	cout << "Time for OCTree: " << duration_cast<microseconds>(duration_q).count() / max_iter << std::endl;
	cout << "OCTree: Number of points checked to find the points within the range: " << count << std::endl;
	cout << "Time for BRUTE: " << duration_cast<microseconds>(duration_all).count() / max_iter << std::endl;
	cout << "BRUTE: Number of points checked to find the points within the range: " << count_brute << std::endl;

	// PASS A RANGE AND GET THE POINTS IN THAT RANGE
	srand((unsigned)time(NULL)); // make it change everytime we run the code
	int x_rand = rnd(-5.0, 5.0);
	int y_rand = rnd(-5.0, 5.0);
	int z_rand = rnd(-5.0, 5.0);
	// Cuboid range(x_rand, y_rand, z_rand, 200, 200, 200);
	// Cuboid range(40, 20, 20, 25,25,25);
	Sphere range(50, 20, 20, 50);
	// vector<Point> query_pointz;
	query_pointz = ot.query(range, query_pointz);
	cout << query_pointz.size() << " Number of points are in the: "
		 << "range: " << range << std::endl;
	cout << "Number of points checked to find the points within the range: " << count << std::endl;

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

	drawing(argc,argv);

	return 0;
}
