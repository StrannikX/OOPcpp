# include <iostream>
# include "Container.hpp"
# include "Shapes.hpp"
# include "ShapeFactory.hpp"

int main() {
    ShapeFactory factory;

    std::cout << Shape::getCount() << std::endl;

    Container<Shape*> cnt;
    for (int i = 0; i < 30; ++i) {
        cnt.append(factory.getRandShape());
    }

    std::cout << Shape::getCount() << std::endl;

    ContainerIterator<Shape*> it(cnt);

    while (it) {
        std::cout << **it << std::endl;
        it++;
    }

    it.reset(cnt);

    while (it) {
        delete *it;
        it++;
    }

    cnt.clear();
    std::cout << Shape::getCount() << std::endl;
}
