#include "geometry.h"
#include<cstddef>
#include<cmath>

PointArray::PointArray() {
    size = 0;
    points = new Point[0]; // Permite borrar mas tarde
}
PointArray::PointArray( const Point ptsToCopy[], const int toCopySize){
    size = toCopySize;
    points = new Point[toCopySize];
    for(int i = 0; i < toCopySize; ++i) {
        points[i] = ptsToCopy[i];
    }
 }

PointArray::PointArray( const PointArray &other) {
// Cualquier c�digo en la clase PointArray tiene acceso a
    // variables privadas como tama�o y puntos
    size = other.size;
    points = new Point[size];
    for (int i=0; i<size; i++) {
        points[i] = other.points[i];
    }
 }

PointArray::~PointArray() {
    delete [] points;
 }

void PointArray::resize( int newSize) {
    Point *pts = new Point[newSize];
    int minSize = (newSize > size ? size : newSize);
    for (int i = 0; i < minSize; i++)
        pts[i] = points[i];
    delete [] points;
    size = newSize;
    points = pts;
 }

void PointArray::clear() {
    resize(0);
 }


void PointArray::push_back( const Point &p) {
    resize(size + 1);
    points[size -1] = p;
    // Tambi�n podr�a usar solo insertar (size, p);
 }

void PointArray::insert( const int pos, const Point &p) {
    resize(size + 1);
    for (int i= size -1; i>pos; i--) {
        points[i] = points[i -1];
    }
    points[pos] = p;
}

void PointArray::remove( const int pos) {
    if(pos >= 0 && pos < size) { // pos < size implica q size > 0
        // Desplazar todo hacia la izquierda
        for(int i = pos; i < size -2; i++) {
            points[i] = points[i + 1];
        }
        resize(size -1);
        }
 }

Point *PointArray::get( const int pos) {
    return pos >= 0 && pos < size ? points + pos : NULL;
 }

const Point *PointArray::get( const int pos) const {
    return pos >= 0 && pos < size ? points + pos : NULL;
 }

//5.|.2
int Polygon::numPolygons = 0;//he cambiado el n ..

Polygon::Polygon( const PointArray &pa) :
    points(pa) {
     ++numPolygons;
}

Polygon::Polygon( const Point pointArr[], const int numPoints) :
     points(pointArr, numPoints) {
        ++numPolygons;
}

//5.2.2
Point constructorPoints[4];

Point *updateConstructorPoints( const Point &p1, const Point &p2, const Point &p3, const Point &p4 = Point(0,0)) {
    constructorPoints[0] = p1;
    constructorPoints[1] = p2;
    constructorPoints[2] = p3;
    constructorPoints[3] = p4;
    return constructorPoints;
}

Rectangle::Rectangle( const Point &ll, const Point &ur) :
     Polygon(updateConstructorPoints(ll, Point(ll.getX(), ur.getY() ), ur, Point(ur.getX(), ll.getY() )), 4) {}

Rectangle::Rectangle( const int llx, const int lly, const int urx, const int ury):
     Polygon(updateConstructorPoints(Point(llx, lly), Point(llx, ury), Point(urx, ury), Point(urx, lly)), 4) {}

double Rectangle::area() const {
    int length = points.get(1) ->getY() -points.get(0) ->getY();
    int width = points.get(2) ->getX() -points.get(1) ->getX();
    return std::abs(( double )length * width);
}

//5.4
Triangle::Triangle( const Point &a, const Point &b, const Point &c): Polygon(updateConstructorPoints(a, b, c), 3) {}
double Triangle::area() const {
    int dx01 = points.get(0) ->getX() -points.get(1) ->getX(),
        dx12 = points.get(1) ->getX() -points.get(2) ->getX(),
        dx20 = points.get(2) ->getX() -points.get(0) ->getX();
    int dy01 = points.get(0) ->getY() -points.get(1) ->getY(),
        dy12 = points.get(1) ->getY() -points.get(2) ->getY(),
        dy20 = points.get(2) ->getY() -points.get(0) ->getY();
    double a = std::sqrt(dx01*dx01 + dy01*dy01),
        b = std::sqrt(dx12*dx12 + dy12*dy12),
        c = std::sqrt(dx20*dx20 + dy20*dy20);

    double s=(a +b+c) /2;

    return std::sqrt( s * (s-a) * (s-b) * (s-c) );
 }
