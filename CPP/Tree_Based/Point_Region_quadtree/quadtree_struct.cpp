#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

// Used to hold details of a point
class Point
{
private:
    /* data */
public:
    int x;
    int y;
    Point();
    Point(int, int);
    ~Point();
    friend ostream &operator<<(ostream &out, const Point &poi);
};
Point::Point()
{
    this->x = 0;
    this->y = 0;
}
Point::Point(int input_x, int input_y)
{
    this->x = input_x;
    this->y = input_y;
}

Point::~Point()
{
}

// The objects that we want stored in the quadtree
class Quadtree_Node
{
private:
    /* data */
    // TODO: Make the data private and use get/set
public:
    Point position;
    int data;
    Quadtree_Node();
    Quadtree_Node(Point, int);
    ~Quadtree_Node();
};

Quadtree_Node::Quadtree_Node()
{
    this->data = 0;
}

Quadtree_Node::Quadtree_Node(Point input_position, int input_data)
{
    this->position = input_position;
    this->data = input_data;
}

Quadtree_Node::~Quadtree_Node()
{
}

// The main quadtree class
class Quadtree
{
    // Hold details of the boundary of this node
    Point top_left;
    Point bottom_right;

    // Contains details of node
    Quadtree_Node *n;

    // Children of this
    Quadtree *northwest;
    Quadtree *northeast;
    Quadtree *southwest;
    Quadtree *southeast;

public:
    Quadtree()
    {
        top_left = Point(0, 0);
        bottom_right = Point(0, 0);
        n = NULL;
        northwest = NULL;
        northeast = NULL;
        southwest = NULL;
        southeast = NULL;
    }
    Quadtree(Point input_top_left, Point input_bottom_right)
    {
        top_left = input_top_left;
        bottom_right = input_bottom_right;
        n = NULL;
        northwest = NULL;
        northeast = NULL;
        southwest = NULL;
        southeast = NULL;
    }
    void insert(Quadtree_Node *);
    Quadtree_Node *search(Point);
    bool inBoundary(Point);
};

// Insert a node into the quadtree
void Quadtree::insert(Quadtree_Node *node)
{
    if (node == NULL)
        return;

    // Current Quadtree cannot contain it
    if (!inBoundary(node->position))
        return;

    // We are at a Quadtree of unit area
    // We cannot subdivide this Quadtree further
    if (abs(top_left.x - bottom_right.x) <= 1 &&
        abs(top_left.y - bottom_right.y) <= 1)
    {
        if (n == NULL)
            n = node;
        return;
    }

    if ((top_left.x + bottom_right.x) / 2 >= node->position.x)
    {
        // Indicates northwest
        if ((top_left.y + bottom_right.y) / 2 >= node->position.y)
        {
            if (northwest == NULL)
                northwest = new Quadtree(
                    Point(top_left.x, top_left.y),
                    Point((top_left.x + bottom_right.x) / 2,
                          (top_left.y + bottom_right.y) / 2));
            northwest->insert(node);
        }

        // Indicates southwest
        else
        {
            if (southwest == NULL)
                southwest = new Quadtree(
                    Point(top_left.x,
                          (top_left.y + bottom_right.y) / 2),
                    Point((top_left.x + bottom_right.x) / 2,
                          bottom_right.y));
            southwest->insert(node);
        }
    }
    else
    {
        // Indicates northeast
        if ((top_left.y + bottom_right.y) / 2 >= node->position.y)
        {
            if (northeast == NULL)
                northeast = new Quadtree(
                    Point((top_left.x + bottom_right.x) / 2,
                          top_left.y),
                    Point(bottom_right.x,
                          (top_left.y + bottom_right.y) / 2));
            northeast->insert(node);
        }

        // Indicates southeast
        else
        {
            if (southeast == NULL)
                southeast = new Quadtree(
                    Point((top_left.x + bottom_right.x) / 2,
                          (top_left.y + bottom_right.y) / 2),
                    Point(bottom_right.x, bottom_right.y));
            southeast->insert(node);
        }
    }
}

// Find a node in a quadtree
Quadtree_Node *Quadtree::search(Point p)
{
    // Current Quadtree cannot contain it
    if (!inBoundary(p))
        return NULL;

    // We are at a Quadtree of unit length
    // We cannot subdivide this Quadtree further
    if (n != NULL)
        return n;

    if ((top_left.x + bottom_right.x) / 2 >= p.x)
    {
        // Indicates northwest
        if ((top_left.y + bottom_right.y) / 2 >= p.y)
        {
            if (northwest == NULL)
                return NULL;
            return northwest->search(p);
        }

        // Indicates southwest
        else
        {
            if (southwest == NULL)
                return NULL;
            return southwest->search(p);
        }
    }
    else
    {
        // Indicates northeast
        if ((top_left.y + bottom_right.y) / 2 >= p.y)
        {
            if (northeast == NULL)
                return NULL;
            return northeast->search(p);
        }

        // Indicates southeast
        else
        {
            if (southeast == NULL)
                return NULL;
            return southeast->search(p);
        }
    }
};

// Check if current quadtree contains the point
bool Quadtree::inBoundary(Point p)
{
    return (p.x >= top_left.x &&
            p.x <= bottom_right.x &&
            p.y >= top_left.y &&
            p.y <= bottom_right.y);
}

ostream &operator<<(ostream &out, const Point &poi)
{
    out << "X= " << poi.x << '\t' << "y= " << poi.y << '\t' << std::endl;
    return out;
}

// Defining random range
constexpr int MIN = 0;
constexpr int WIDTH = 12;
constexpr int HEIGHT = 12;

// Driver program
int main()
{
    vector<Point> inputs;
    Quadtree qtree(Point(0, 0), Point(8, 8));
    for (int i = 0; i < 5; i++)
    {
        Point p(rand() % WIDTH, rand() % HEIGHT);
        inputs.push_back(p);
        Quadtree_Node nod(p, i);
        qtree.insert(&nod);
        // cout << p;
    }

    for (int i = 0; i < 5; i++)
    {
        Point p = inputs[i];
        cout << p << '\t';
        Quadtree_Node *nod = qtree.search(p);
        if (nod != nullptr)
        {
            cout << qtree.search(p)->data << '\n';
        }
        else
        {
            cout << "Not in the qtree" << '\n';
        }
    }
    return 0;
}
