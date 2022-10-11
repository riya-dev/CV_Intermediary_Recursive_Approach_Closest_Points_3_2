// cd project3
// g++ -std=c++11 -o l032  -Wall l032.cpp
// ./l032

#include <iostream>
#include <fstream>
#include <iomanip>  // set precision
#include <climits>  // int_max
#include <list>     // list
#include <math.h>
#include <ctime>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>    // std::sort

const int size = 800;
std::ofstream results;
double duration1;
double duration2;

// point class
// private, getters, setters, constructors
class Point {
public:
    void setX(double x);
    double getX(void);
    void setY(double y);
    double getY(void);
    bool diff(Point p2);
    //int Compare(Point d);
    static bool sortFunct(Point i, Point j) { return (j.getX() > i.getX()); }
    static std::vector<Point> getSorted(std::vector<Point> p) {
        std::sort(p.begin(), p.end(), sortFunct);
        return p;
    }
    void print();
    Point(double x, double y);  // constructor
    Point(void);
private:
    double x;
    double y;
};
Point::Point(void) {
    x = 0;
    y = 0;
}
Point::Point(double xval, double yval) {
    x = xval;
    y = yval;
}
void Point::setX(double xval) {
    x = xval;
}
double Point::getX(void) {
    return x;
}
void Point::setY(double yval) {
    y = yval;
}
double Point::getY(void) {
    return y;
}
bool Point::diff(Point p2) {
    if (getX() != p2.getX() && getY() != p2.getY())
        return true;
    return false;
}
void Point::print() {
    std::cout << std::fixed;
    std::cout << std::setprecision(23) << "(" << getX() << " , " << getY() << ")";
    //std::cout << std::setprecision(23) << getX() << "  " << getY();
}

class Distance {
public:
    void setdist(double d);
    double getdist(void);
    void setp1(Point p);
    Point getp1(void);
    void setp2(Point p);
    Point getp2(void);
    Distance compare(Distance d1, Distance d2);
    /*static bool sortFunct(Point i, Point j) { return (j.getX() > i.getX()); }
    static std::vector<Point> getSorted(std::vector<Point> p) {
        std::sort(p.begin(), p.end(), sortFunct);
        return p;
    }*/
    void print();
    Distance(double dist, Point p1, Point p2);  // constructors
    Distance(void);
private:
    double dist;
    Point p1;
    Point p2;
};
Distance::Distance(void) {
    dist = 0;
    p1 = Point();
    p2 = Point();
}
Distance::Distance(double d, Point p1val, Point p2val) {
    dist = d;
    p1 = p1val;
    p2 = p2val;
}
void Distance::setdist(double d) {
    dist = d;
}
double Distance::getdist(void) {
    return dist;
}
void Distance::setp1(Point p) {
    p1 = p;
}
Point Distance::getp1(void) {
    return p1;
}
void Distance::setp2(Point p) {
    p2 = p;
}
Point Distance::getp2(void) {
    return p2;
}
Distance Distance::compare(Distance d1, Distance d2) {
    if (d1.getdist() < d2.getdist())
        return d1;
    return d2;
}
void Distance::print() {
    std::cout << std::fixed;
    std::cout << std::setprecision(23) << dist << "\t";
    getp1().print();
    std::cout << "\t";
    getp2().print();
}

void illuminate(int** arr, int y, int x, int color) {
    if (color == 0)
        arr[x][y] = 0;
    else if (color == 1)
        arr[x][y] = 1;
    else if (color == 2)
        arr[x][y] = 2;
    else if (color == 3)
        arr[x][y] = 3;
}

void notoutofbounds(int** array, int x, int y, int color) {
    if (x >= 0 && x < size && y >= 0 && y < size)
        //array[x][y] = 0;
        illuminate(array, x, y, color);
}

double distance(double x1, double y1, double x2, double y2) {
    double t1 = pow(x1 - x2, 2);
    double t2 = pow(y1 - y2, 2);
    //std::cout << t1 << " " << t2 << " " << sqrt(t1 + t2) << "\n";
    return (double)(sqrt(t1 + t2));
}

void circle(int** array, int xcenter, int ycenter, int R, int color) {
    int y = R;
    int xmax = (int)(R * 0.70710678);
    int ysquare = y * y;
    int ty = (2 * y) - 1;
    int y2_new = ysquare;

    //std::cout << y << " " << xmax << " " << ysquare << " " << ty << " " << y2_new << "\n";

    for (int x = 0; x <= xmax + 1; x++) {
        if ((ysquare - y2_new) >= ty) {
            ysquare -= ty;
            y -= 1;
            ty -= 2;
        }
        notoutofbounds(array, y + xcenter, x + ycenter, color);
        notoutofbounds(array, -y + xcenter, x + ycenter, color);
        notoutofbounds(array, y + xcenter, -x + ycenter, color);
        notoutofbounds(array, -y + xcenter, -x + ycenter, color);

        notoutofbounds(array, x + xcenter, y + ycenter, color);
        notoutofbounds(array, -x + xcenter, y + ycenter, color);
        notoutofbounds(array, x + xcenter, -y + ycenter, color);
        notoutofbounds(array, -x + xcenter, -y + ycenter, color);

        y2_new -= (2 * x) - 3;
    }
}

Distance part1() {
    std::ofstream points;
    points.open("points.txt");
    std::list <Point*> pointlist;

    // make array
    int** array;
    array = new int* [size];

    // fill with 1s
    for (int row = 0; row < size; ++row)
        array[row] = new int[size];
    for (int row = 0; row < size; ++row)
        for (int col = 0; col < size; ++col)
            array[row][col] = 1;

    srand(time(NULL));
    for (int i = 0; i <= 999; i++) {
        double x = double(rand()) / INT_MAX;
        double y = double(rand()) / INT_MAX;
        pointlist.push_back(new Point(x, y));
        circle(array, (int)(x * size), (int)(y * size), 3, 0);
        points << std::fixed;
        points << std::setprecision(23) << x << "  " << y << "\n";
    }
    points.close();

    // make ppm
    std::ofstream ppm;
    ppm.open("points1.ppm");
    ppm << "P3 " << size << " " << size << " 255\n";

    std::clock_t start = std::clock();

    // iterator
    double d = INT_MAX;
    Point dp1;
    Point dp2;
    Point temp1;
    Point temp2;
    std::list <Point*> ::iterator it1;
    std::list <Point*> ::iterator it2;
    for (it1 = pointlist.begin(); it1 != pointlist.end(); it1++) {
        for (it2 = it1++; it2 != pointlist.end(); it2++) {
            temp1 = **it1;
            temp2 = **it2;
            if (temp1.diff(temp2)) {
                double dist = distance(temp1.getX(), temp1.getY(), temp2.getX(), temp2.getY());
                if (dist < d) {
                    d = dist;
                    dp1 = temp1;
                    dp2 = temp2;
                }
            }
        }
    }

    double duration = ((double)std::clock() - (double)start) / (double)CLOCKS_PER_SEC;
    duration1 = duration;

    circle(array, (int)(dp1.getX() * size), (int)(dp1.getY() * size), 2, 2);
    circle(array, (int)(dp1.getX() * size), (int)(dp1.getY() * size), 3, 2);
    circle(array, (int)(dp2.getX() * size), (int)(dp2.getY() * size), 2, 2);
    circle(array, (int)(dp2.getX() * size), (int)(dp2.getY() * size), 3, 2);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (array[i][j] == 0)
                ppm << array[i][j] << " " << array[i][j] << " " << array[i][j] << ' ';
            else if (array[i][j] == 2)
                ppm << 255 << " " << 0 << " " << 0 << " ";
            else
                ppm << 255 << " " << 255 << " " << 255 << ' ';
        }
        ppm << std::endl;
    }
    ppm << "\n";

    ppm.close();

    Distance dist = Distance(d, Point(dp1.getX(), dp1.getY()), Point(dp2.getX(), dp2.getY()));

    return dist;
}

Distance stripClosest(std::vector<Point> pointlist) {
    double d = INT_MAX;
    Point dp1;
    Point dp2;
    Point temp1;
    Point temp2;
    for (size_t i = 0; i < pointlist.size(); i++) {
        for (size_t j = 0; j < pointlist.size(); j++) {
            temp1 = pointlist[i];
            temp2 = pointlist[j];
            if (temp1.diff(temp2)) {
                double dist = distance(temp1.getX(), temp1.getY(), temp2.getX(), temp2.getY());
                if (dist < d) {
                    d = dist;
                    dp1 = temp1;
                    dp2 = temp2;
                }
            }
        }
    }
    return Distance(d, dp1, dp2);
}

Distance recursive(std::vector<Point> v) {
    std::vector<Point> left;
    std::vector<Point> right;

    for (int i = 0; i != (int)v.size() / 2; i++)
        left.push_back(v[i]);
    for (int i = v.size() / 2; i < (int)v.size(); i++)
        right.push_back(v[i]);

    if (left.size() == 2 || left.size() == 3) { // base case left strip
        double dl;
        double d1 = distance(left[0].getX(), left[0].getY(), left[1].getX(), left[1].getY());
        if (left.size() == 3) {
            double d2 = distance(left[1].getX(), left[1].getY(), left[2].getX(), left[2].getY());
            double d3 = distance(left[0].getX(), left[0].getY(), left[2].getX(), left[2].getY());
            dl = std::min(d3, std::min(d1, d2));
            if (dl == d2) {
                return Distance(dl, left[1], left[2]);
            }
            if (dl == d3) {
                return Distance(dl, left[0], left[2]);
            }
        }
        dl = d1;
        return Distance(dl, left[0], left[1]);
    }
    if (right.size() == 2 || right.size() == 3) { // base case right strip
        double dr;
        double d1 = distance(right[0].getX(), right[0].getY(), right[1].getX(), right[1].getY());
        if (right.size() == 3) {
            double d2 = distance(right[1].getX(), right[1].getY(), right[2].getX(), right[2].getY());
            double d3 = distance(right[0].getX(), right[0].getY(), right[2].getX(), right[2].getY());
            dr = std::min(d3, std::min(d1, d2));
            if (dr == d2) {
                return Distance(dr, right[1], right[2]);
            }
            if (dr == d3) {
                return Distance(dr, right[0], right[2]);
            }
        }
        dr = d1;
        return Distance(dr, right[0], right[1]);
    }

    // Find the middle point
    int mid = v.size() / 2;
    Point midPoint = v[mid];

    // Consider the vertical line passing through the middle point calculate
    // the smallest distance dl on left of middle point and dr on right side
    Distance dl = recursive(left);
    Distance dr = recursive(right);

    // Find the smaller of two distances
    Distance d = dl.compare(dl, dr);

    // Build an array strip[] that contains points close (closer than d)
    // to the line passing through the middle point
    std::vector<Point> strip;
    for (size_t i = 0; i < v.size(); i++)
        if (abs(v[i].getX() - midPoint.getX()) < d.getdist())
            strip.push_back(v[i]);

    // Find the closest points in strip. Return the minimum of d and closest distance is strip[]
    return d.compare(d, stripClosest(strip));
}

Distance part2() {
    //std::cout << "@1\n";
    std::vector<Point> v = {};

    //pulling the numbers from the file
    std::vector<std::string> vec = {};
    std::string line;
    std::ifstream points("points.txt");
    //std::cout << "@2\n";

    if (points.is_open()) {
        //std::cout << "@3\n";
        while (getline(points, line)) {
            std::stringstream ss(line);
            while (getline(ss, line, ' ')) {
                if (line.length() > 2)
                    vec.push_back(line);
            }
        }
        //std::cout << "@4\n";
        points.close();
    }
    else
        std::cout << "Unable to open file";
    //std::cout << "@5\n";

    //std::cout << "@5.5\n";
    std::vector<std::string>::iterator it;
    //std::cout << "@6\n";
    for (it = vec.begin(); it != vec.end(); it++) {
        std::string s1 = *it;
        //std::cout << *it << " first value\n";
        it++;
        //std::cout << *it << " second value\n";
        std::string s2 = *it;
        v.push_back(Point(std::stod(s1), std::stod(s2)));
        //v.back().print();
    }

    //std::cout << "@7\n";

    std::clock_t start = std::clock();

    /* Your algorithm here */
    v = Point::getSorted(v);

    Distance d = recursive(v);
    double duration = ((double)std::clock() - (double)start) / (double)CLOCKS_PER_SEC;
    duration2 = duration;

    // make array
    int** array;
    array = new int* [size];
    // fill with 1s
    for (int row = 0; row < size; ++row)
        array[row] = new int[size];
    for (int row = 0; row < size; ++row)
        for (int col = 0; col < size; ++col)
            array[row][col] = 1;
    // draw all circles
    for (size_t i = 0; i <= v.size(); i++) {
        circle(array, (int)(v[i].getX() * size), (int)(v[i].getY() * size), 3, 0);
    }
    // make ppm
    std::ofstream ppm;
    ppm.open("points2.ppm");
    ppm << "P3 " << size << " " << size << " 255\n";

    circle(array, (int)(d.getp1().getX() * size), (int)(d.getp1().getY() * size), 2, 3);
    circle(array, (int)(d.getp1().getX() * size), (int)(d.getp1().getY() * size), 3, 3);
    circle(array, (int)(d.getp2().getX() * size), (int)(d.getp2().getY() * size), 2, 3);
    circle(array, (int)(d.getp2().getX() * size), (int)(d.getp2().getY() * size), 3, 3);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (array[i][j] == 0)
                ppm << array[i][j] << " " << array[i][j] << " " << array[i][j] << ' ';
            else if (array[i][j] == 1)
                ppm << 255 << " " << 255 << " " << 255 << " ";
            else if (array[i][j] == 2)
                ppm << 255 << " " << 0 << " " << 0 << " ";
            else if (array[i][j] == 3)
                ppm << 0 << " " << 255 << " " << 128 << " ";
        }
        ppm << std::endl;
    }
    ppm << "\n";
    ppm.close();

    return d;
}

int main() {
    results.open("results.txt");

    Distance d1 = part1();
    results << std::fixed;
    results << std::setprecision(23) << d1.getdist() << "\t";
    results << "(" << d1.getp1().getX() << " , " << d1.getp1().getY() << ")";
    std::cout << "  ";
    results << "(" << d1.getp2().getX() << " , " << d1.getp2().getY() << ")";
    results << "\nduration: " << duration1 << " seconds";

    d1.print();
    std::cout << "\nduration: " << duration1 << " seconds\n";

    Distance d2 = part2();
    results << std::fixed;
    results << std::setprecision(23) << "\n" << d2.getdist() << "\t";
    results << "(" << d2.getp1().getX() << " , " << d2.getp1().getY() << ")";
    std::cout << "  ";
    results << "(" << d2.getp2().getX() << " , " << d2.getp2().getY() << ")";
    results << "\nduration: " << duration2 << " seconds";

    d2.print();
    std::cout << "\nduration: " << duration2 << " seconds\n";

    results.close();
}