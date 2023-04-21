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
  double x_max, y_max, z_max;
  double x_min, y_min, z_min;
  pre_pro(x_min, y_min, z_min, x_max, y_max, z_max);
  
  Point min_p(x_min, y_min, z_min);   //Creamos el octre con los maximos y menores puntos posibles hallados
  Point max_p(x_max, y_max, z_max);   //para que todos los puntos se encuentren dentro del mismo
  Octree my_oct;
  my_oct.insert(min_p);
  my_oct.insert(max_p);

  fstream newfile;
  newfile.open("../dama_octal.txt",ios::in); //open a file to perform read operation using file object
  string line;
  stringstream linestream;

  double x, y, z;
  int i = 0;
  while (getline(newfile, line))
  {
      stringstream linestream;
      linestream << line;
      linestream >> x >> y >> z;
      Point _pp(x,y,z);
      my_oct.insert(_pp);
      i++;
  }
  newfile.close();

  fstream newfile1;
  newfile1.open("../cubes.txt",ios::out);  // open a file to perform write operation using file object
  my_oct.write_LeftBottom(newfile1);
  newfile1.close();

  cout << "Done\n";

  return 0;
}