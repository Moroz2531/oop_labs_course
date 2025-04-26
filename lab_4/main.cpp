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

    tPoint rect_p1(&field, 20, 40);
    tPoint rect_p2(&field, 10, 30);

    tPoint circ_p1(&field, 30, 50);
    tPoint circ_p2(&field, 40, 60);

    tPoint el_p1(&field, 20, 25);
    tPoint el_p2(&field, 36, 42);
    tPoint el_p3(&field, 40, 50);

    Line l1;
    Line l2(ln_p1, ln_p2);

    l2.setLength();
    cout
        << "Отрезок. Длина отрезка: " << l2.getLength() << endl
        << endl;

    Square sq1;
    Square sq2(sq_p1, sq_p2);

    sq2.setPer();
    sq2.setSquare();

    cout << "Квадрат. Его площадь: " << sq2.getSquare() << endl;
    cout << "Квадрат. Его периметр: " << sq2.getPer() << endl
         << endl;

    Rectangle rect1;
    Rectangle rect2(rect_p1, rect_p2);

    rect2.setPer();
    rect2.setSquare();

    cout << "Прямоугольник. Его площадь: " << rect2.getSquare() << endl;
    cout << "Прямоугольник. Его периметр: " << rect2.getPer() << endl;

    Circle circle1;
    Circle circle2(circ_p1, circ_p2);

    Ellipse el1;
    Ellipse el2(el_p1, el_p2, el_p3);

    tPoint p[6] = {{&field, 10, 15}, {&field, 17, 40}, {&field, 11, 36}, {&field, 4, 13}, {&field, 8, 5}, {&field, 54, 21}};

    Rectangle *rect = new Rectangle[3]{{p[0], p[1]}, {p[2], p[3]}, {p[4], p[5]}};

    for (int i = 0; i < 3; i++)
    {
        rect[i].setPer();
        rect[i].setSquare();
    }

    for (int i = 0; i < 3; i++)
    {
        cout << endl
             << i + 1 << " прямоугольник. Площадь: " << rect[i].getSquare() << ". Периметр: " << rect[i].getPer() << endl;
    }

    delete[] rect;

    return 0;
}
