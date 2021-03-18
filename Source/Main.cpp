#include <iostream>
#include <Gorgon/Graphics.h>
#include <Gorgon/Graphics/Bitmap.h>
#include "Filter.h"
#include "Kernel.h"
int main() {
std::cout<<"hello world"<<std::endl;
Gorgon::Graphics::Bitmap bmp;
Kernel<int>k({1,3,4},{3,5});
Kernel<int>l({{1,2,3},{3,4,6,7,8,9}});
std::cout<<"Finish"<<std::endl;
return 0;

}
