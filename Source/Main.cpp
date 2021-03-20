#include <iostream>
#include <Gorgon/Graphics.h>
#include <Gorgon/Graphics/Bitmap.h>
#include "Filter.h"
#include "Kernel.h"
int main() {
std::cout<<"hello world"<<std::endl;
Gorgon::Graphics::Bitmap bmp;
Kernel l({{1,2,3},{3,6,7}});
std::cout<<"Finish"<<std::endl;
return 0;

}
