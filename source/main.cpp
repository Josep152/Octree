/*#include <vtkActor.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPoints.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkVertexGlyphFilter.h>

#include <sstream>
#include <iostream>


int main(int argc, char* argv[]) {
  std::cout << "Hola VTK" << std::endl;
  std::cout << "Hi VTK" << std::endl;
  std::cout << "Halo VTK " << std::endl;
}*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Octree.h"

using namespace std;

int main() {
  fstream newfile;
  newfile.open("../dama_octal.txt",ios::in); //open a file to perform read operation using file object
  string line;
  int i = 0;
  double x_max, y_max, z_max;
  double x_min, y_min, z_min;
  stringstream linestream;
  linestream << line;
  linestream >> x_max >> y_max >> z_max;
  x_min = x_max;
  y_min = y_max;
  z_min = z_max;
  
  while (getline(newfile, line))
  {
    double x, y, z;
    stringstream linestream;
    linestream << line;
    linestream >> x >> y >> z;
    if( x > x_max )
        x_max = x;
    if( y > y_max )
        y_max = y;
    if( z > z_max )
        z_max = z;
    if( x < x_min )
        x_min = x;
    if( y < y_min )
        y_min = y;
    if( z < z_min )
        z_min = z;
    i++; 
  }
  //Creamos el octre con los maximos y menores puntos posibles hallados, para que todos los puntos se encuentren dentro del mismo
  Point min_p(x_min, y_min, z_min);
  Point max_p(x_max, y_max, z_max); 
  Octree my_oct;
  my_oct.insert(min_p);
  my_oct.insert(max_p);
  newfile.close();
  return 0;
}