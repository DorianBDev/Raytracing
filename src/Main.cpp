//#define SDL_DISABLE_ANALYZE_MACROS
//#include <SDL.h>
#include "Utils/Matrix.h"

#include <iostream>

int main()
{
    Matrix a(3, 3, {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}});
    a.print();

    //double norm = Matrix::getNorm(a);
    //std::cout << "norme = " << norm << std::endl;

    //Matrix d = Matrix::normalize(a);
    //d.printMatrix();

    return 0;
}