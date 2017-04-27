# ifndef SHAPE_FACTORY_HPP
# define SHAPE_FACTORY_HPP

# include "Shapes.hpp"
# include <cstdlib>

class ShapeFactory {
public:
    ShapeFactory() {
        srand(time(NULL));
    }

    Shape* getRandShape() {
        switch (rand() % 5) {
            case 0: return getPoint();
            case 1: return getCircle();
            case 2: return getRect();
            case 3: return getPolyline();
            default: return getPolygon();
        }
    }

    Point * getPoint() {
        return new Point(1.0 * rand() / 1000000, 1.0 * rand() / 1000000);
    }

    Circle * getCircle() {
        return new Circle(
            Point(1.0 * rand() / 1000000, 1.0 * rand() / 1000000),
            1.0 * rand() / 1000000);
    }

    Rect * getRect() {
        return new Rect(
            Point(1.0 * rand() / 1000000, 1.0 * rand() / 1000000),
            Point(1.0 * rand() / 1000000, 1.0 * rand() / 1000000));
    }

    Polyline * getPolyline() {
        int n = rand() % 30;
        Polyline * p = new Polyline();
        for (int i = 0; i < n; ++i) {
            p->addPoint(Point(1.0 * rand() / 1000000, 1.0 * rand() / 1000000));
        }
        return p;
    }

    Polygon * getPolygon() {
        int n = rand() % 30;
        Polygon * p = new Polygon();
        for (int i = 0; i < n; ++i) {
            p->addVertice(Point(1.0 * rand() / 1000000, 1.0 * rand() / 1000000));
        }
        return p;
    }
};

#endif // SHAPE_FACTORY_HPP
