#include <iostream>
#include <iomanip>
#include <time.h>

#include "field.hpp"

using std::cin, std::cout, std::endl;

enum
{
    ROWS = 100,
    COLS = 100,
};

int main()
{
    Field field = {ROWS, COLS};

    tPoint ln_p1(&field, 50, 51);
    tPoint ln_p2(&field, 48, 49);

    tPoint sq_p1(&field, 50, 55);
    tPoint sq_p2(&field, 45, 50);

    tPoint rect_p1(&field, 50, 55);
    tPoint rect_p2(&field, 10, 30);

    tPoint circ_p1(&field, 30, 50);
    tPoint circ_p2(&field, 40, 60);

    tPoint el_p1(&field, 50, 55);
    tPoint el_p2(&field, 55, 69);
    tPoint el_p3(&field, 50, 60);

    Line l1;
    Line *l2 = new Line(ln_p1, ln_p2);

    Square sq1;
    Square *sq2 = new Square(sq_p1, sq_p2);

    Rectangle rect1;
    Rectangle *rect2 = new Rectangle(rect_p1, rect_p2);

    Circle circle1;
    Circle *circle2 = new Circle(circ_p1, circ_p2);

    Ellipse el1;
    Ellipse *el2 = new Ellipse(el_p1, el_p2, el_p3);

    cout << "Прямоугольник. Количество созданных объектов: " << Rectangle::getCountCreate() << ". Количество существующих объектов: " << Rectangle::getCountExist() << endl;

    Rectangle *rect3 = rect2;
    rect3->setPer();

    cout << "Прямоугольник. Количество созданных объектов: " << Rectangle::getCountCreate() << ". Количество существующих объектов: " << Rectangle::getCountExist() << endl;

    Rectangle *rect4 = new Rectangle();

    cout << "Прямоугольник. Количество созданных объектов: " << Rectangle::getCountCreate() << ". Количество существующих объектов: " << Rectangle::getCountExist() << endl;

    Figure **arr = new Figure *[4]{sq2, rect2, circle2, el2};

    cout << "Прямоугольник. Количество созданных объектов: " << Rectangle::getCountCreate() << ". Количество существующих объектов: " << Rectangle::getCountExist() << endl;

    for (int i = 0; i < 4; i++)
    {
        arr[i]->setPer();
        cout << "Периметр " << i + 1 << " фигуры: " << arr[i]->getPer() << endl;
    }

    delete[] arr;

    cout << "Прямоугольник. Количество созданных объектов: " << Rectangle::getCountCreate() << ". Количество существующих объектов: " << Rectangle::getCountExist() << endl;

    delete l2;
    delete sq2;
    delete rect2;
    delete rect4;
    delete circle2;
    delete el2;

    cout << "Прямоугольник. Количество созданных объектов: " << Rectangle::getCountCreate() << ". Количество существующих объектов: " << Rectangle::getCountExist() << endl;

    return 0;
}
