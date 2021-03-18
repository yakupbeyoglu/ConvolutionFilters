#include <iostream>
#include <Gorgon/Graphics.h>
#include <Gorgon/Graphics/Bitmap.h>
#include "Filter.h"
int main() {
std::cout<<"hello world"<<std::endl;
Gorgon::Graphics::Bitmap bmp;
bmp.Import("test.png");
auto gkernelx = Gaussiankernel(2, true);

auto nbmp = Convolution(bmp, gkernelx);
return 0;

}
