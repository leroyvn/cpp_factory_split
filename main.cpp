// https://adtmag.com/articles/2000/09/25/industrial-strength-pluggable-factories.aspx

#include <iostream>
#include <sstream>
#include <map>

using namespace std;

class Shape {
  public:
    virtual void do_something() = 0;
    static Shape *newShape(istream &);
};

class Circle : public Shape {
  public:
    explicit Circle(istream &params) {};
    void do_something() override { cout << "I am a Circle" << endl; }
};

Shape *Shape::newShape(istream &params) {
    string className;
    params >> className;
    if (className=="Circle")
        return new Circle(params);
    else
        return nullptr;
}

class ShapeMaker {
  public:
    ShapeMaker(string className);
    static Shape *newShape(istream &);
  protected:
    typedef map<string, ShapeMaker *> MakerMap;
    virtual Shape *makeShape(istream &) const = 0;
    static MakerMap registry;
};

Shape *ShapeMaker::newShape(istream &is) {
    string className;
    is >> className;
    ShapeMaker *maker = (*registry.find(className)).second;
    return maker->makeShape(is);
}

ShapeMaker::ShapeMaker(string className) {
    registry.insert(make_pair(className, this));
}

class CircleMaker : public ShapeMaker {
  public:
    virtual Shape *makeShape(istream &params) const {
        return new Circle(params);
    }

  private:
    CircleMaker() : ShapeMaker("Circle") {}
    static const CircleMaker registerThis;
};

int main() {
    stringstream s;
    s << "Circle";
    auto shape = ShapeMaker::newShape(s);
    shape->do_something();
    return 0;
}
