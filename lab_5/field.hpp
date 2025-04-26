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
    float angle{0};

public:
    virtual ~Figure() { delete center; };

    float getAngle() { return angle; };

    virtual void setPer() = 0;
    virtual double getPer() = 0;

    virtual int control(int send) = 0;
    virtual int rotate(float angle) = 0;

protected:
    int rotatePoint(float angle, tPoint &p);
};

// Line

class Line : public Figure
{
protected:
    double length{0.0};
    tPoint *p1{nullptr}, *p2{nullptr};

    static int countCreate;
    static int countExist;

public:
    Line();
    Line(tPoint &p1, tPoint &p2);
    ~Line();

    void setCoords(tPoint &p1, tPoint &p2);
    void getCoords(tPoint &p1, tPoint &p2);

    static int getCountCreate();
    static int getCountExist();

    void setLength();
    double getLength();

    virtual int control(int send);
    virtual int rotate(float angle);

protected:
    void setCenter();
    int canMovePoint(tPoint &p);

    static void increaseCount();

    virtual void setPer() {};
    virtual double getPer() { return 0; };
};

// Square

class Square : public Line
{
protected:
    double sq{0.0}, per{0.0};

    static int countCreate;
    static int countExist;

public:
    Square();
    Square(tPoint &p1, tPoint &p2);
    ~Square();

    virtual void setSquare();
    virtual void setPer();

    static int getCountCreate();
    static int getCountExist();

    virtual int control(int send) override final;
    virtual int rotate(float angle) override final;

    double getSquare();
    virtual double getPer() final;

protected:
    static void increaseCount();
    virtual int canMove();

private:
    double setSide();
};

// Rectangle

class Rectangle : public Square
{
private:
    double a{0.0}, b{0.0};

    static int countCreate;
    static int countExist;

public:
    Rectangle();
    Rectangle(tPoint &p1, tPoint &p2);
    ~Rectangle();

    static int getCountCreate();
    static int getCountExist();

    virtual void setSquare() override final;
    virtual void setPer() override final;

private:
    static void increaseCount();
    virtual int canMove() override final;
    void setSides();
};

// Circle

class Circle : public Figure
{
protected:
    tPoint *radius{nullptr};
    double per{0.0};

    static int countCreate;
    static int countExist;

public:
    Circle();
    Circle(tPoint &center, tPoint &radius);
    ~Circle();

    void setData(tPoint &center, tPoint &radius);
    void getData(tPoint &center, tPoint &radius);

    virtual double getPer() final;

    virtual int control(int send);
    virtual int rotate(float angle);

    virtual void setPer();

protected:
    static void increaseCount();
    int canMove();
    double getLength(tPoint *p); // возвращает длину между центром и точкой
};

// Ellipse

class Ellipse : public Circle
{
private:
    tPoint *width{nullptr};

    static int countCreate;
    static int countExist;

public:
    Ellipse();
    Ellipse(tPoint &center, tPoint &height, tPoint &width);
    ~Ellipse();

    void setData(tPoint &center, tPoint &height, tPoint &width);
    void getData(tPoint &center, tPoint &height, tPoint &width);

    virtual int control(int send) override final;
    virtual int rotate(float angle) override final;

    virtual void setPer() override final;

private:
    static void increaseCount();
    int canMove();
    void getAxes(double &a, double &b);
};
