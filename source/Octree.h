#ifndef OCTREE_H
#define OCTREE_H
//#include <bits/stdc++.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

#define G 100     //G granularidad

struct Point {
    double x,y,z;
    Point () {
        x = 0;
        y = 0;
        z = 0;
    }
    Point (double _x, double _y, double _z) {
        x = _x;
        y = _y;
        z = _z;
    }
    Point operator-(Point a) {
        Point rpta;
        rpta.x = x - a.x; rpta.y = y - a.y; rpta.z = z - a.z;
        return rpta;
    }
    double disEu (Point a) {
        return sqrt(pow(x - a.x, 2) + pow(y - a.y, 2) + pow(z - a.z, 2));
    }

    double max_cord () {
        double max = abs(x);
        if (abs(y) > max) { max = abs(y); }
        if (abs(z) > max) { max = abs(z); }
        return max;
    }
};

Point getMinPoint(Point* _points, int _nPoints ) {
    Point minPoint = _points[0];
    for (int i = 1; i < _nPoints; i++) {
        if( _points[i].x < minPoint.x )
            minPoint.x = _points[i].x;
        if( _points[i].y < minPoint.y )
            minPoint.y = _points[i].y;
        if( _points[i].z < minPoint.z )
            minPoint.z = _points[i].z;
    }
    return minPoint;
}

Point getMaxPoint(Point* _points, int _nPoints ) {
    Point maxPoint = _points[0];
    for (int i = 1; i < _nPoints; i++) {
        if( _points[i].x > maxPoint.x )
            maxPoint.x = _points[i].x;
        if( _points[i].y > maxPoint.y )
            maxPoint.y = _points[i].y;
        if( _points[i].z > maxPoint.z )
            maxPoint.z = _points[i].z;
    }
    return maxPoint;
}

class Octree {
private:
    Octree* children[8];
    Point *points;

    int nPoints;

    Point leftBottom;
    double h;
    bool isLeaf; //si es hoja

public:
    Octree() { 
        for (int i = 0; i < 8; i++) {
            children[i] = nullptr;
        }
        points = new Point[G];
        this->nPoints = 0;
        cout << "Octree created!\n";
    }

    // TDD: Test Driven Development
    // Ingresar el primer punto
    // Ingresar n puntos hasta antes que explote
    // Ingresar el punto k para que explote
    void explote () {
        for (int i = 0; i < G; i++) {
            insertTypeOctree(points[i]);
        }
    }
    void insert(const Point &point ) {
        if (isLeaf && nPoints + 1 == G) {
            explote();
            this->nPoints = 0;
            this->isLeaf = false;
        }
        if( isLeaf && nPoints == 0 ){
            points[nPoints++] = point;
            this->nPoints++;
            h = 0;
            leftBottom = point;
        }
        else if( isLeaf && nPoints < G ) {
            points[nPoints++] = point;
            this->nPoints++;
            Point minPoint = getMinPoint(points, nPoints);
            Point maxPoint = getMaxPoint(points, nPoints);
            h = (minPoint-maxPoint).max_cord();
            cout << "h -> " << h << endl;
            leftBottom = minPoint;

        }
        else {      //Buscar region que pertenece e insertarlo
            insertTypeOctree(point);
        }
    }

    void insertTypeOctree(const Point &_point) {
        double midX = leftBottom.x + h/2;
        double midY = leftBottom.y + h/2;
        double midZ = leftBottom.z + h/2;

        if( _point.x < midX ) {
            if( _point.y < midY ) {
                if( _point.z < midZ ) {
                    if (children[0] == nullptr){
                        children[0] = new Octree;
                    }
                    children[0]->insert(_point);
                }
                else {
                    if (children[1] == nullptr){
                        children[1] = new Octree;
                    }
                    children[1]->insert(_point);
                }
            }
            else {
                if( _point.z < midZ ) {
                    if (children[2] == nullptr){
                        children[2] = new Octree;
                    }
                    children[2]->insert(_point);
                }
                else {
                    if (children[3] == nullptr){
                        children[3] = new Octree;
                    }
                    children[3]->insert(_point);
                }
            }
        }
        else {
            if( _point.y < midY ) {
                if( _point.z < midZ ) {
                    if (children[4] == nullptr){
                        children[4] = new Octree;
                    }
                    children[4]->insert(_point);
                }
                else {
                    if (children[5] == nullptr){
                        children[5] = new Octree;
                    }
                    children[5]->insert(_point);
                }
            }
            else {
                if( _point.z < midZ ) {
                    if (children[6] == nullptr){
                        children[6] = new Octree;
                    }
                    children[6]->insert(_point);
                }
                else {
                    if (children[7] == nullptr){
                        children[7] = new Octree;
                    }
                    children[7]->insert(_point);
                }
            }

        }
    }

    //caso básico: hoja
    //caso no es hoja
    /*bool exist(const Point &point) {
        if( isLeaf ){
            for (int i = 0; i < nPoints; i++)
            {
                if( point[i] == point )
                    return true;   
            }
            return false;
        } else {
            double midX = leftBottom.x + h/2;
            double midY = leftBottom.y + h/2;
            double midZ = leftBottom.z + h/2;
            if( point.x < midX ) {
                if( point.y < midY ) {
                    if( point.z < midZ ) {
                        return children[0].exist(point);
                    }
                    else {
                    }
                }
                else {

                }
            }
            else {

            }
        }
    }

   Point closestPoint(const Point &point) {
    if( isLeaf ){
        double dist = distancia( point, points[0]);
        Point closest = point[0];
        for (int i = 1; i < nPoints; i++)
        {
            double distTmp = distancia( point, points[i]);
            if( distTmp < dist ) {
                dist = distTmp;
                closest = point[i];
            }
        }
        return closestt;
    } else {
        ..
    }
   }*/


};

#endif