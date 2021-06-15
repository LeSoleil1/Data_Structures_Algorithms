// C++ Implementation of Quad Tree
#include <iostream>
#include <cmath>
#include <random>
using namespace std;

// Used to hold details of a point
class Point{
	int x;
	int y;
	public:
		Point(int const &inp_x, int const &inp_y){
			x = inp_x;
			y = inp_y;
		}
		int get_x(){
			return x;
		}
		int get_y(){
			return y;
		}

		friend ostream & operator<<(ostream &out, const Point &poi );

};

class Rectangle{
	int x;
	int y;
	int w;
	int h;
	int left;
	int right;
	int top;
	int bottom;
	public:
	// Default Constructor
	Rectangle(){
		this->x = 0;
		this->y = 0;
		this->w = 0;
		this->h = 0;
		this->left = 0;
		this->right = 0;
		this->top = 0;
		this->bottom = 0;

	}
	Rectangle(int const &inp_x, int const &inp_y,int const &inp_w, int const &inp_h){
		this->x = inp_x;
		this->y = inp_y;
		this->w = inp_w;
		this->h = inp_h;
		this->left = inp_x - inp_w /2 ;
		this->right = inp_x + inp_w / 2;
		this->top = inp_y - inp_h /2;
		this->bottom = inp_y + inp_h/2;
	}
	int get_x(){
		return this->x;
	}
	int get_y(){
		return this->y;
	}
	int get_w(){
		return this->w;
	}
	int get_h(){
		return this->h;
	}
	bool contains(Point point){
		int point_x = point.get_x();
		int point_y = point.get_y();
		return (this->left <= point_x && 
				point_x <= this->right && 
				this->top <= point_y && 
				point_y <=this->bottom);
	}
	friend ostream & operator<<(ostream &out, const Rectangle &rec );
};

ostream & operator<<(ostream &out, const Rectangle &rec ) {
	out << rec.x << '\t' << rec.y << '\t' << rec.w << '\t' << rec.h<<std::endl;
	return out;
}

ostream & operator<<(ostream &out, const Point &poi ) {
	out << poi.x << '\t' << poi.y << '\t' << std::endl;
	return out;
}


class QuadTree{
	Rectangle boundary;
	int capacity;
	std::vector<Point> points;
	bool devided = false;

	QuadTree *northwest;
	QuadTree *northeast;
	QuadTree *southwest;
	QuadTree *southeast;


	public:
		QuadTree(Rectangle inp_boundary,int n){
			boundary = inp_boundary;
			capacity = n;
			northwest = nullptr;
			northeast = nullptr;
			southwest = nullptr;
			southeast = nullptr;
		}
		Rectangle get_boundary(){
			return boundary;
		}
		void subdevide(){
			int x = this->boundary.get_x();
			int y = this->boundary.get_y();
			int w = this->boundary.get_w();
			int h = this->boundary.get_h();

			Rectangle ne =  Rectangle(x + w /2, y - h/2, w / 2, h/2);
			Rectangle nw =  Rectangle(x - w /2, y - h/2, w / 2, h/2);
			Rectangle se =  Rectangle(x + w /2, y + h/2, w / 2, h/2);
			Rectangle sw =  Rectangle(x - w /2, y + h/2, w / 2, h/2);

			this->northwest = new QuadTree(nw,this->capacity);
			this->northeast = new QuadTree(ne,this->capacity);
			this->southwest = new QuadTree(sw,this->capacity);
			this->southeast = new QuadTree(se,this->capacity);

			this->devided = true;
			cout << "Devided" << std::endl;
		}
		bool insert(Point point){
			if (!this->boundary.contains(point)){
				return false;
			}
			if(this->points.size() < this->capacity){
				this->points.push_back(point);
				return true;
			}else{
				if (!this->devided){int
					subdevide();
				}
			}
			return (
			this->northeast->insert(point) ||
			this->northwest->insert(point) ||
			this->southeast->insert(point) ||
			this->southwest->insert(point));
		}
};


// Defining random range
constexpr int MIN = 1;
constexpr int WIDTH = 200;
constexpr int HEIGHT = 200;

// Driver program
int main()
{
	Rectangle boundary(200,200,200,200);
	// Point p(10,15);
	// cout << boundary.contains(p);
	QuadTree qt(boundary,4);
	for (int i = 0; i <50 ; i++){
		Point p(rand() % WIDTH,rand() % HEIGHT);
		bool res = qt.insert(p);
		cout<< "inserted\t" << res << std::endl;
		cout << p;
		cout << boundary.contains(p)<<std::endl;

	}
	// cout << qt.get_boundary();
	return 0;

}
