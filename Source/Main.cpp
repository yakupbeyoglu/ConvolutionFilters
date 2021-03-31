#include <iostream>
#include <Gorgon/Graphics.h>
#include <Gorgon/Graphics/Bitmap.h>
#include "Filter.h"
#include "Kernel.h"
int main() {
std::cout<<"hello world"<<std::endl;
Kernel l({{1,2,3},{3,6,7},{2,3,4}});

auto hpass = Kernel::LowPass(5);
auto edge = Kernel::EdgeDetection(5);
auto sobelx = Kernel::SobelFilter(Kernel::FilterAxis::X);
auto sobely = Kernel::SobelFilter(Kernel::FilterAxis::Y);
//  Gorgon::Graphics::Bitmap bmp1;
//  bmp1.Import("testgaussian.png");
//  auto xfilter = Convolution(bmp1, hpass, ::EdgeDealing::ClosestPixel, Gorgon::Graphics::Color::White, false, false);
// 
// xfilter.ExportPNG("magnitud.png");

return 0;
}
