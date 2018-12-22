#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>

using namespace std;

const double PIx2 = acos(-1) * 2;

class Vector
{
public:
    Vector() : x_(0.0), y_(0.0) {}

    Vector(double x, double y) : x_(x), y_(y) {}

    Vector(const Vector &) = default;
    
    Vector(Vector && other) = default;
    
    Vector& operator=(const Vector & other) = default;
    
    Vector& operator=(Vector && other) = default;

    const Vector operator+(const Vector& v) const {
        return Vector(x_ + v.x_, y_ + v.y_);
    }
    
    const Vector operator-(const Vector& v) const {
        return Vector(x_ - v.x_, y_ - v.y_);
    }
    
    Vector& operator+=(const Vector& v)
    {
        x_ += v.x_;
        y_ += v.y_;
        return *this;
    }
    
    double getLength() const
    {
        return sqrt(x_ * x_ + y_ * y_);
    }
    
    Vector getOrt() const
    {
        double l = this->getLength();
        return Vector(x_ / l, y_ / l);
    }
    
    double getX()
    {
        return x_;
    }
    
    double getY()
    {
        return y_;
    }
    
    friend const Vector operator*(const Vector& v, const double& n);
    friend const Vector operator*(const double& n, const Vector& v);
    friend const Vector operator/(const Vector& v, const double& n);
    
private:
    double x_;
    double y_;
};

const Vector operator*(const Vector& v, const double& n)
{
    return Vector(v.x_ * n, v.y_ * n);
}

const Vector operator*(const double& n, const Vector& v)
{
    return Vector(v.x_ * n, v.y_ * n);
}

const Vector operator/(const Vector& v, const double& n)
{
    return Vector(v.x_ / n, v.y_ / n);
}



class Spring;



class Point
{
public:
    Point(double x, double y, double m);
    void addSpring(Spring &s);
    void update(double t);
    Vector getCoords();
    
private:
    Vector coords_;
    double m_;
    Vector v_;
    vector<Spring*> springs_;
};



class Spring
{
public:
    Spring(double k, double normLength, Point* a, Point* b)
    : k_(k), normLength_(normLength), a_(a), b_(b),
    coordsA_(a->getCoords()), coordsB_(b->getCoords())
    {
        curLength_ = (a->getCoords() - b->getCoords()).getLength();
    }
    
    const Vector getForce(Point* a)
    {
        Vector forceA = ((k_ * (normLength_ - curLength_)) / 2.0 * (coordsA_ - coordsB_).getOrt());
        //
        //cout << "SUDA SMOTRI : " << (coordsA_ - coordsB_).getOrt().getX() << " " << (coordsA_ - coordsB_).getOrt().getY() << endl;
        //
        if (a == a_)
        {
            return forceA;
        }
        else
        {
            return -1.0 * forceA;
        }
    }
    
    void update()
    {
        coordsA_ = a_->getCoords();
        coordsB_ = b_->getCoords();
        curLength_ = (coordsA_ - coordsB_).getLength();
    }
    
private:
    double k_;
    double normLength_;
    double curLength_;
    Point *a_;
    Point *b_;
    Vector coordsA_;
    Vector coordsB_;
};



Point::Point(double x, double y, double m) : coords_(x, y), m_(m), v_(0.0, 0.0) {}

void Point::addSpring(Spring &s)
{
    springs_.push_back(&s);
}

void Point::update(double t)
{
    Vector f;
    for (size_t i = 0; i < springs_.size(); ++i)
    {
        f += springs_[i]->getForce(this);
    }
    //
    //cout << endl << endl << "TUTA :" << f.getX() << ' ' << f.getY() << endl << endl;
    //
    Vector a(f / m_);
    coords_ += v_ * t + a * t * t / 2.0;
    v_ += a * t; //v_ += a * t;
}

Vector Point::getCoords()
{
    return coords_;
}



int main()
{
    freopen("out.out", "w", stdout);
    unsigned int n, m;
    cin >> n >> m;
    vector<double> dists(m);
    vector<unsigned int> from(m);
    vector<unsigned int> to(m);
    double r(0.0);
    for (size_t i = 0; i < m; ++i)
    {
        cin >> from[i] >> to[i] >> dists[i];
        r += dists[i];
    }
    r /= m * 2;// r /= m * 2;
    vector<Point> points;
    double angle(0.0);
    double step = PIx2 / n;
    for (size_t i = 0; i < n; ++i)
    {
        points.emplace_back(Point(r * cos(angle), r * sin(angle), 1e1));
        angle += step;
    }
    vector<Spring> springs;
    for (size_t i = 0; i < m; ++i)
    {
        springs.emplace_back(Spring(1e10, dists[i], &(points[from[i] - 1]), &(points[to[i] - 1])));
        points[from[i] - 1].addSpring(springs[i]);
        points[to[i] - 1].addSpring(springs[i]);
    }
    unsigned int beg = clock();
    unsigned int t(beg), prev(beg);
    cout.precision(12);
    while (t - beg < 1600000)
    {
        prev = t;
        t = clock();
        for (size_t i = 0; i < n; ++i)
        {
            points[i].update((double)(t - prev) / (double)CLOCKS_PER_SEC);
        }
        for (size_t i = 0; i < m; ++i)
        {
            springs[i].update();
        }
        for (size_t i = 0; i < n; ++i)
        {
            Vector coords(points[i].getCoords());
            cout << coords.getX() << ' ' << coords.getY() << endl;
        }
        cout << endl;
    }
    for (size_t i = 0; i < n; ++i)
    {
        Vector coords(points[i].getCoords());
        cout << coords.getX() << ' ' << coords.getY() << endl;
    }
    return 0;
}

/*
3 3
1 2 5
2 3 5
1 3 6
*/
