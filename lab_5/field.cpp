#include <iostream>
#include <time.h>
#include <math.h>
#include <cmath>

#include "field.hpp"

static int getrand(int min, int max)
{
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
};

// tPoint

tPoint::tPoint() : x{0}, y{0}, color{WHITE}, field{nullptr}
{
}

tPoint::tPoint(Field *field, double x, double y, int c) : x{x}, y{y}, color{c}, field{field}
{
}

tPoint::tPoint(tPoint &tp) : x{tp.x}, y{tp.y}, color{tp.color}, field{tp.field}
{
}

void tPoint::setData(Field *field, double x, double y, int color)
{
    this->field = field;
    if (checkField())
        return;
    if (x < 0 || y < 0 || color < 0)
        return;
    if (x > field->cols || y > field->rows)
        return;

    setCoords(x, y);
    this->color = color;
};

void tPoint::setData(tPoint &p)
{
    x = p.x;
    y = p.y;
    color = p.color;
    if (field != nullptr)
        field = p.field;
}

int tPoint::control(const int send)
{
    if (checkField())
        return 1;
    if (send == UP && y > 0)
    {
        up();
        return 0;
    }
    if (send == DOWN && y < field->rows)
    {
        down();
        return 0;
    }
    if (send == LEFT && x > 0)
    {
        left();
        return 0;
    }
    if (send == RIGHT && x < field->cols)
    {
        right();
        return 0;
    }
    return 1;
};

int tPoint::randControl()
{
    if (control(getrand(UP, RIGHT + 1)))
        return 1;
    return 0;
};

void tPoint::setCoords(double x, double y)
{
    this->x = x;
    this->y = y;
}

void tPoint::getCoords(double &x, double &y) const
{
    x = this->x;
    y = this->y;
}

double tPoint::getFieldRows()
{
    if (field != nullptr)
        return field->rows;
    return 0;
}

double tPoint::getFieldCols()
{
    if (field != nullptr)
        return field->cols;
    return 0;
}

double tPoint::getX()
{
    return x;
};

double tPoint::getY()
{
    return y;
};

double tPoint::getColor()
{
    return color;
}

int tPoint::checkField()
{
    if (field == nullptr)
        return 1;
    return 0;
}

void tPoint::up()
{
    y--;
};

void tPoint::down()
{
    y++;
};

void tPoint::left()
{
    x--;
};

void tPoint::right()
{
    x++;
};

// Figure

int Figure::rotatePoint(float angle, tPoint &p)
{
    float radians = angle * M_PI / 180.0f;

    double x = center->getX() + (p.getX() - center->getX()) * cos(radians) - (p.getY() - center->getY()) * sin(radians);
    double y = center->getY() + (p.getX() - center->getX()) * sin(radians) + (p.getY() - center->getY()) * cos(radians);

    p.setCoords(x, y);

    return 0;
}

// Line

int Line::countCreate{0};
int Line::countExist{0};

Line::Line()
{
    increaseCount();
}

Line::Line(tPoint &p1, tPoint &p2)
{
    setCoords(p1, p2);
    increaseCount();
}

Line::~Line()
{
    delete p1;
    delete p2;
    countExist--;
}

void Line::increaseCount()
{
    countCreate++;
    countExist++;
}

void Line::setCoords(tPoint &p1, tPoint &p2)
{
    if (this->p1 == nullptr)
        this->p1 = new tPoint();
    if (this->p2 == nullptr)
        this->p2 = new tPoint();
    this->p1->setData(p1);
    this->p2->setData(p2);
    setCenter();
}

void Line::setCenter()
{
    double x = (p1->getX() + p2->getX()) / 2;
    double y = (p1->getY() + p2->getY()) / 2;

    center = new tPoint(*p1);
    center->setCoords(x, y);
}

void Line::getCoords(tPoint &p1, tPoint &p2)
{
    p1 = *this->p1;
    p2 = *this->p2;
}

void Line::setLength()
{
    length = sqrt(pow(p1->getX() - p2->getX(), 2.0) + pow(p1->getY() - p2->getY(), 2.0));
}

double Line::getLength()
{
    return length;
}

int Line::control(int send)
{
    tPoint p1{*this->p1}, p2{*this->p2}, center{*this->center};

    if (p1.control(send) || p2.control(send) || center.control(send))
        return 1;
    if (canMovePoint(p1) || canMovePoint(p2))
        return 1;

    this->center->setData(center);
    this->p1->setData(p1);
    this->p2->setData(p2);

    return 0;
}

int Line::rotate(float angle)
{
    tPoint p1{*this->p1}, p2{*this->p2};

    if (rotatePoint(angle, p1) || rotatePoint(angle, p2))
        return 1;
    if (canMovePoint(p1) || canMovePoint(p2))
        return 1;
    this->p1->setData(p1);
    this->p2->setData(p2);
    this->angle = angle;

    return 0;
}

int Line::canMovePoint(tPoint &p)
{
    double x = p.getX();
    double y = p.getY();

    if (x < 0 || x >= center->getFieldCols() || y < 0 || y >= center->getFieldRows())
        return 1;
    return 0;
}

int Line::getCountCreate()
{
    return countCreate;
}

int Line::getCountExist()
{
    return countExist;
}

// Square

int Square::countCreate{0};
int Square::countExist{0};

Square::Square()
{
    increaseCount();
}

Square::Square(tPoint &p1, tPoint &p2)
{
    setCoords(p1, p2);
    increaseCount();
}

Square::~Square()
{
    countExist--;
}

void Square::increaseCount()
{
    countCreate++;
    countExist++;
}

void Square::setSquare()
{
    sq = pow(setSide(), 2.0);
}

void Square::setPer()
{
    per = setSide() * 4;
}

int Square::control(const int send)
{
    tPoint center(*this->center);

    center.control(send);
    if (canMove())
        return 1;
    return Line::control(send);
}

int Square::canMove()
{
    double side = setSide() / 2;
    double x = center->getX(), y = center->getY();

    return !(x - side >= 0 && x + side < center->getFieldCols() && y - side >= 0 && y + side < center->getFieldRows());
}

int Square::rotate(float angle)
{
    tPoint p1(*this->p1), p2(*this->p2);

    if (Line::rotate(angle))
        return 1;
    if (!canMove())
        return 1;

    this->p1->setCoords(p1.getX(), p1.getY());
    this->p2->setCoords(p2.getX(), p2.getY());

    return 0;
}

double Square::getSquare()
{
    return sq;
}

double Square::getPer()
{
    return per;
}

double Square::setSide()
{
    setLength();
    return (length / sqrt(2));
}

int Square::getCountCreate()
{
    return countCreate;
}

int Square::getCountExist()
{
    return countExist;
}

// Rectangle

int Rectangle::countCreate{0};
int Rectangle::countExist{0};

Rectangle::Rectangle()
{
    increaseCount();
}

Rectangle::Rectangle(tPoint &p1, tPoint &p2)
{
    setCoords(p1, p2);
    increaseCount();
}

Rectangle::~Rectangle()
{
    countExist--;
}

void Rectangle::increaseCount()
{
    countCreate++;
    countExist++;
}

void Rectangle::setSquare()
{
    setSides();
    sq = a * b;
}

void Rectangle::setPer()
{
    setSides();
    per = a * 2 + b * 2;
}

void Rectangle::setSides()
{
    a = abs(p1->getX() - p2->getX());
    b = abs(p1->getY() - p2->getY());
}

int Rectangle::canMove()
{
    setSides();
    double x = center->getX(), y = center->getY();

    return !(x - a / 2 >= 0 && x + a / 2 < center->getFieldCols() && y - b / 2 >= 0 && y + b / 2 < center->getFieldRows());
}

int Rectangle::getCountCreate()
{
    return countCreate;
}

int Rectangle::getCountExist()
{
    return countExist;
}

// Circle

int Circle::countCreate{0};
int Circle::countExist{0};

Circle::Circle()
{
    center = new tPoint;
    radius = new tPoint;
    increaseCount();
}

Circle::Circle(tPoint &center, tPoint &radius)
{
    this->center = new tPoint(center);
    this->radius = new tPoint(radius);
    increaseCount();
}

Circle::~Circle()
{
    delete radius;
    countExist--;
}

void Circle::setData(tPoint &center, tPoint &radius)
{
    this->center->setData(center);
    this->radius->setData(radius);
}

void Circle::getData(tPoint &center, tPoint &radius)
{
    center = *this->center;
    radius = *this->radius;
}

void Circle::setPer()
{
    per = 2 * M_PI * getLength(radius);
}

double Circle::getPer()
{
    return per;
}

double Circle::getLength(tPoint *p)
{
    return sqrt(pow(center->getX() - p->getX(), 2.0) + pow(center->getY() - p->getY(), 2.0));
}

int Circle::control(int send)
{
    tPoint radius{*this->radius};

    radius.control(send);

    if (canMove())
        return 1;
    this->center->control(send);
    this->radius->setData(radius);
    return 0;
}

int Circle::rotate(float angle)
{
    rotatePoint(angle, *radius);
    this->angle = angle;
    return 0;
}

int Circle::canMove()
{
    double rad = getLength(radius);

    double x = center->getX(), y = center->getY();

    return !(x - rad >= 0 && x + rad < center->getFieldCols() && y - rad >= 0 && y + rad < center->getFieldRows());
}

void Circle::increaseCount()
{
    countCreate++;
    countExist++;
}

// Ellipse

int Ellipse::countCreate{0};
int Ellipse::countExist{0};

Ellipse::Ellipse() : Circle()
{
    width = new tPoint;
    increaseCount();
}

Ellipse::Ellipse(tPoint &center, tPoint &height, tPoint &width) : Circle(center, height)
{
    this->width = new tPoint(width);
    increaseCount();
}

Ellipse::~Ellipse()
{
    delete width;
    countExist--;
}

void Ellipse::setData(tPoint &center, tPoint &height, tPoint &width)
{
    Circle::setData(center, height);
    this->width->setData(width);
}

void Ellipse::getData(tPoint &center, tPoint &height, tPoint &width)
{
    Circle::getData(center, height);
    width = *this->width;
}

int Ellipse::control(int send)
{
    tPoint height{*radius}, width{*this->width};

    height.control(send);
    width.control(send);

    if (canMove())
        return 1;
    center->control(send);
    radius->setData(height);
    this->width->setData(width);

    return 0;
}

int Ellipse::rotate(float angle)
{
    rotatePoint(angle, *radius);
    rotatePoint(angle, *this->width);

    if (canMove())
    {
        rotatePoint(this->angle, *radius);
        rotatePoint(this->angle, *this->width);
        return 1;
    }
    this->angle = angle;
    return 0;
}

int Ellipse::canMove()
{
    if (Circle::canMove())
        return 1;
    double rad = getLength(width);

    double x = center->getX(), y = center->getY();

    return !(x - rad >= 0 && x + rad < center->getFieldCols() && y - rad >= 0 && y + rad < center->getFieldRows());
}

void Ellipse::setPer()
{
    double a, b;

    getAxes(a, b);
    per = 2 * M_PI * sqrt((a * a + b * b) / 2);
}

void Ellipse::getAxes(double &a, double &b)
{
    a = getLength(radius);
    b = getLength(width);
}

void Ellipse::increaseCount()
{
    countCreate++;
    countExist++;
}
