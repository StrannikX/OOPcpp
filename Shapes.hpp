# ifndef SHAPES_HPP
# define SHAPES_HPP

# include "Base.hpp"
# include "Container.hpp"
# include <cmath>
# include <string>
# include <sstream>

class Shape: public Named {
public:
    Shape(): Named("Unknown shape") {
        ++getCounter();
    }

    Shape(std::string const& str): Named(str) {
        ++getCounter();
    }

    Shape(Shape const& shape): Named(shape.getName()) {
        ++getCounter();
    }

    virtual ~Shape() {
        --getCounter();
    }

    static int getCount() {
        return getCounter();
    }
private:
    static int& getCounter() {
        static int count = 0;
        return count;
    }
};

class Point: public Shape {
public:
    Point(double x, double y): Shape(std::string("Point")) {
        this->x = x;
        this->y = y;
    }

    Point(): Shape(std::string("Point")) {
        x = y = 0;
    }

    double getX() const { return x; }
    double getY() const { return y; }

    std::string print() const {
        return
            getName() + " " +
            std::string("(") +
            std::to_string(x) + std::string(", ") +
            std::to_string(y) +
            std::string(")");
    }

private:
    double x, y;
};

class Circle: public Shape {
public:
    Circle(Point const& center, double radius): Shape(std::string("Circle")) {
        this->center = center;
        this->radius = radius;
    }

    Point const& getCenter() const {
        return center;
    }

    double getRadius() const {
        return radius;
    }

    double getSquare() const {
        return M_PI * radius * radius;
    }

    std::string print() const {
        return getName() + " " +
            std::string("Center[") +
            std::to_string(center.getX()) +
            ", " +
            std::to_string(center.getY()) +
            "]; Radius[" +
            std::to_string(radius) + "]; Square: " + std::to_string(getSquare());
    }

private:
    Point center;
    double radius;
};

class Rect: public Shape {
public:
    Rect(Point const& point1, Point const& point2): Shape("Rect"), point1(point1), point2(point2) {}

    Point const& getFirstPoint() const { return point1; }
    Point const& getSecondPoint() const { return point2; }

    double getSquare() const {
        return abs(point1.getX() - point2.getX()) * abs(point1.getY() - point2.getY());
    }

    std::string print() const {
        return getName() + " " +
            std::string("First point [") +
            std::to_string(point1.getX()) +
            ", " +
            std::to_string(point1.getY()) +
            "]; Second point[" +
            std::to_string(point2.getX()) +
            ", " +
            std::to_string(point2.getY()) +
            "]; Square: " + std::to_string(getSquare());
    }

private:
    Point point1, point2;
};

class Polyline: public Shape {
public:
    Polyline(): Shape("Polyline") {};

    Polyline(Polyline const& polyline): Shape("Polyline") {
        points = polyline.points;
    }

    Container<Point> const& getPoints() const {
        return points;
    }

    void addPoint(Point const& point) {
        points.append(point);
    }

    double getLength() const {
        if (points.getSize() < 2) return 0;

        double length = 0;

        ContainerIterator<Point> it(points);
        ContainerIterator<Point> it2(points);

        ++it2;

        while (it2) {
            Point& startPoint = *it;
            Point& endPoint = *it2;

            double dx = endPoint.getX() - startPoint.getX();
            double dy = endPoint.getY() - startPoint.getY();

            length += sqrt(dx * dx + dy * dy);

            ++it;
            ++it2;
        }

        return length;
    }

    std::string print() const {
        std::ostringstream s;
        s << getName();
        s << std::endl << "Points: " << std::endl;

        ContainerIterator<Point> it(points);

        while (it) {
            s << "    " << (*it).print() << std::endl;
            it++;
        }

        s << "Length: " << std::to_string(getLength());

        return s.str();
    }

private:
    Container<Point> points;
};


class Polygon: public Shape {
public:
    Polygon(): Shape("Polygon") {};

    Polygon(Polygon const& polygon): Shape("Polygon") {
        points = polygon.points;
    }

    Container<Point> const& getVerticies() const {
        return points;
    }

    void addVertice(Point const& point) {
        points.append(point);
    }

    double getPerimeter() const {
        if (points.getSize() < 2) return 0;

        double length = 0;

        ContainerIterator<Point> it(points);
        ContainerIterator<Point> it2(points);

        ++it2;

        while (it2) {
            Point& startPoint = *it;
            Point& endPoint = *it2;

            double dx = endPoint.getX() - startPoint.getX();
            double dy = endPoint.getY() - startPoint.getY();

            length += sqrt(dx * dx + dy * dy);

            ++it;
            ++it2;
        }

        Point const& firstPoint = points.getFirst();
        Point const& lastPoint = points.getLast();

        double dx = lastPoint.getX() - firstPoint.getX();
        double dy = lastPoint.getY() - firstPoint.getY();

        length += sqrt(dx * dx + dy * dy);

        return length;
    }

    std::string print() const {
        std::ostringstream s;
        s << getName();
        s << std::endl << "Verticies: " << std::endl;

        ContainerIterator<Point> it(points);

        while (it) {
            s << "    " << (*it).print() << std::endl;
            ++it;
        }

        s << "Length: " << std::to_string(getPerimeter());

        return s.str();
    }

private:
    Container<Point> points;
};

std::ostream& operator<<(std::ostream& os, Shape const& shape) {
    os << shape.print() << std::endl;
    return os;
}
# endif // SHAPES_HPP
