#include <iostream>
#include <Gorgon/Graphics.h>
#include <Gorgon/Graphics/Bitmap.h>
#include "Filter.h"
#include "Kernel.h"
int main() {
std::cout<<"hello world"<<std::endl;
Kernel l({{1,2,3},{3,6,7},{2,3,4}});

auto hpass = Kernel::HighPass(3);
Gorgon::Graphics::Bitmap bmp;
 std::cout<<"import";
bmp.Import("lenna.png");
auto sobelybmp = Convolution(bmp, hpass, EdgeDealing::ClosestPixel, Gorgon::Graphics::Color::White, false);
sobelybmp.ExportPNG("output.png");
  std::cout<<"Finish"<<std::endl;
return 0;

}
