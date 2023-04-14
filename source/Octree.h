#ifndef OCTREE_H
#define OCTREE_H
//#include <bits/stdc++.h>

using namespace std;

class Point {
    double x,y,z;
    Point () {
        x = 0;
        y = 0;
        z = 0;
    }
};

class Octree {
private:
   Octree* children[8];
   Point *points;

   int K; //G granularidad
   int nPoints;

   Point leftBottom;
   int h;
   bool isLeaf; //si es hoja

public:
   Octree(int K) { 
    this->K = K;
    this->nPoints = 0;
    points = new Point[K];
   }
   // TDD: Test Driven Development
   // Ingresar el primer punto
   // Ingresar n puntos hasta antes que explote
   // Ingresar el punto k para que explote
   void insert(const Point &point ) {
    if( isLeaf && nPoints == 0 ){
        points[nPoints++] = point;
        h = 0;
        leftBottom = point;
    else if( isLeaf && nPoints < K ) {
        points[nPoints++] = point;
        Point minPoint = getMinPoint(points, nPoints);
        Point maxPoint = getMaxPoint(points, nPoints);
        h = abs(max(minPoint-maxPoint));
        leftBottom = minPoint;
    }
    else {
        // buscar region que pertenece e insertarlo
        insertTypeOctree(point);
    }
   }

   void insertTypeOctree(const Point &point) {
    double midX = leftBottom.x + h/2;
    double midY = leftBottom.y + h/2;
    double midZ = leftBottom.z + h/2;

    if( point.x < midX ) {
        if( point.y < midY ) {
            if( point.z < midZ ) {
                children[0].insert(point);
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

  //caso básico: hoja
  //caso no es hoja
   bool exist(const Point &point) {
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
   }


};

Point getMinPoint(Points *points, int nPoints ) {
    Point minPoint = points[0];
    for (int i = 1; i < nPoints; i++) {
        if( points[i].x < minPoint.x )
            minPoint.x = points[i].x;
        if( points[i].y < minPoint.y )
            minPoint.y = points[i].y;
        if( points[i].z < minPoint.z )
            minPoint.z = points[i].z;
    }
    return minPoint;
}

#endif
