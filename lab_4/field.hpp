#pragma once

enum
{
    WHITE = 1,
    RED = 2,
    GREEN = 3,
    BLUE = 4,

    UP = 1,
    DOWN = 2,
    LEFT = 3,
    RIGHT = 4,
};

// Field

struct Field
{
    double rows{0}, cols{0};
};

// tPoint

class tPoint
{
protected:
    double x{0}, y{0};
    int color{WHITE};

    Field *field{nullptr};

public:
    tPoint();
    tPoint(Field *field, double x, double y, int c = WHITE);
    tPoint(tPoint &tp);

    void setData(Field *field, double x, double y, int color = WHITE);
    void setData(tPoint &p);
    void setCoords(double x, double y);
    void getCoords(double &x, double &y) const;

    int control(const int send);
    int randControl();

    double getFieldRows();
    double getFieldCols();
    double getX();
    double getY();
    double getColor();

private:
    void up();
    void down();
    void left();
    void right();

    int checkField();
};

// Figure

class Figure
{
protected:
    tPoint *center{nullptr};
    float angle{0}; // в градусах

public:
    Figure();
    Figure(tPoint &p);
    ~Figure();

    float getAngle();

protected:
    int rotatePoint(float radians, tPoint &p, tPoint &center);
};

// Line

class Line : public Figure
{
protected:
    double length{0.0};
    tPoint *p1{nullptr}, *p2{nullptr};

public:
    Line();
    Line(tPoint &p1, tPoint &p2);
    ~Line();

    void setCoords(tPoint &p1, tPoint &p2);
    void getPoints(tPoint &p1, tPoint &p2);
    void setLength();
    void control(const int send);

    int rotate(float angle);

    double getLength();

protected:
    void returnValue(tPoint *p, const int send);
    void setCenter();
};

// Square

class Square : public Line
{
protected:
    double sq{0.0}, per{0.0};

public:
    Square();
    Square(tPoint &p1, tPoint &p2);

    void setSquare();
    void setPer();
    void control(const int send);
    void rotate(float angle);

    double getSquare();
    double getPer();

private:
    bool canMove(tPoint &p);
    double setSide();
};

// Rectangle

class Rectangle : public Square
{
private:
    double a{0.0}, b{0.0};

public:
    Rectangle();
    Rectangle(tPoint &p1, tPoint &p2);

    void setSquare();
    void setPer();

private:
    bool canMove(tPoint &p);
    void setSides();
};

// Circle

class Circle : public Figure
{
protected:
    tPoint *radius{nullptr};

public:
    Circle();
    Circle(tPoint &p1, tPoint &p2);
    ~Circle();

    void setData(tPoint &center, tPoint &radius);
    void getData(tPoint &center, tPoint &radius);
};

// Ellipse

class Ellipse : public Circle
{
private:
    tPoint *width{nullptr};

public:
    Ellipse();
    Ellipse(tPoint &p1, tPoint &p2, tPoint &p3);
    ~Ellipse();

    void setData(tPoint &center, tPoint &height, tPoint &width);
    void getData(tPoint &center, tPoint &height, tPoint &width);
};
