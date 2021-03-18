#include <iostream>
#include <Gorgon/Graphics.h>
#include <Gorgon/Graphics/Bitmap.h>
#include "Filter.h"
int main() {
std::cout<<"hello world"<<std::endl;
Gorgon::Graphics::Bitmap bmp;
bmp.Import("Test3.png");
auto gkernelx = Gaussiankernel(2, true);

auto nbmp = Convolution(bmp, gkernelx);
std::cout<<"Finish"<<std::endl;
return 0;

}
