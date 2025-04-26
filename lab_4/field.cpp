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

Figure::Figure()
{
    center = new tPoint;
}

Figure::Figure(tPoint &p)
{
    center = new tPoint(p);
}

Figure::~Figure()
{
    delete center;
}

int Figure::rotatePoint(float radians, tPoint &p, tPoint &center)
{
    double x = center.getX() + (p.getX() - center.getX()) * cos(radians) - (p.getY() - center.getY()) * sin(radians);
    double y = center.getY() + (p.getX() - center.getX()) * sin(radians) + (p.getY() - center.getY()) * cos(radians);

    if (x < 0 || x >= p.getFieldCols() || y < 0 || y >= p.getFieldRows())
        return 1;
    p.setCoords(x, y);
    return 0;
}

float Figure::getAngle()
{
    return angle;
}

// Line

Line::Line() : Figure()
{
    p1 = new tPoint();
    p2 = new tPoint();
}

Line::Line(tPoint &p1, tPoint &p2)
{
    Figure();
    this->p1 = new tPoint(p1);
    this->p2 = new tPoint(p2);
    setCenter();
}

Line::~Line()
{
    delete p1;
    delete p2;
}

void Line::setCoords(tPoint &p1, tPoint &p2)
{
    this->p1->setData(p1);
    this->p2->setData(p2);
    setCenter();
}

void Line::setCenter()
{
    double x = (p1->getX() + p2->getX()) / 2;
    double y = (p1->getY() + p2->getY()) / 2;
    center->setCoords(x, y);
}

void Line::getPoints(tPoint &p1, tPoint &p2)
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

void Line::control(const int send)
{
    double x1, y1, x2, y2, x3, y3;

    center->getCoords(x1, y1);
    p1->getCoords(x2, y2);
    p2->getCoords(x3, y3);

    if (center->control(send))
        return;
    if (p1->control(send))
    {
        returnValue(center, send);
    }
    if (p2->control(send))
    {
        returnValue(center, send);
        returnValue(p1, send);
    }
}

int Line::rotate(float angle)
{
    float new_radians = angle * M_PI / 180.0f;
    float old_radians = this->angle * M_PI / 180.0f;

    if (p1 != nullptr)
        if (rotatePoint(new_radians, *p1, *center))
            return 1;
    if (p2 != nullptr)
        if (rotatePoint(new_radians, *p2, *center))
        {
            rotatePoint(old_radians, *p1, *center);
            return 1;
        }
    this->angle = angle;
    return 0;
}

void Line::returnValue(tPoint *p, const int send)
{
    switch (send)
    {
    case UP:
        p->control(DOWN);
        break;
    case DOWN:
        p->control(UP);
        break;
    case LEFT:
        p->control(RIGHT);
        break;
    case RIGHT:
        p->control(LEFT);
    };
}

// Square

Square::Square() : Line()
{
}

Square::Square(tPoint &p1, tPoint &p2) : Line(p1, p2)
{
}

void Square::setSquare()
{
    sq = pow(setSide(), 2.0);
}

void Square::setPer()
{
    per = setSide() * 4;
}

void Square::control(const int send)
{
    tPoint NewCenter(*center);

    NewCenter.control(send);
    if (NewCenter.control(send) && canMove(NewCenter))
        center->setCoords(NewCenter.getX(), NewCenter.getY());
}

bool Square::canMove(tPoint &p)
{
    double side = setSide(), halfS = side / 2;

    double x = p.getX(), y = p.getY();

    return (x - halfS >= 0 && x + halfS < p.getFieldCols() && y - halfS >= 0 && y + halfS < p.getFieldRows());
}

void Square::rotate(float angle)
{
    tPoint p1(*this->p1), p2(*this->p2);

    if (Line::rotate(angle))
        return;
    if (!canMove(*center))
    {
        this->p1->setCoords(p1.getX(), p1.getY());
        this->p2->setCoords(p2.getX(), p2.getY());
    }
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

// Rectangle

Rectangle::Rectangle() : Square()
{
}

Rectangle::Rectangle(tPoint &p1, tPoint &p2) : Square(p1, p2)
{
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

bool Rectangle::canMove(tPoint &p)
{
    setSides();

    double halfWidth = a / 2, halfHeight = b / 2;

    double x = p.getX(), y = p.getY();

    return (x - halfWidth >= 0 && x + halfWidth < p.getFieldCols() && y - halfHeight >= 0 && y + halfHeight < p.getFieldRows());
}

// Circle

Circle::Circle()
{
    radius = new tPoint;
}

Circle::Circle(tPoint &p1, tPoint &p2)
{
    center->setData(p1);
    radius = new tPoint(p2);
}

Circle::~Circle()
{
    delete radius;
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

// Ellipse

Ellipse::Ellipse()
{
    width = new tPoint;
}

Ellipse::Ellipse(tPoint &p1, tPoint &p2, tPoint &p3) : Circle(p1, p2)
{
    width = new tPoint(p3);
}

Ellipse::~Ellipse()
{
    delete width;
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
