#include <iostream>
#include <Gorgon/Graphics.h>
#include <Gorgon/Graphics/Bitmap.h>
#include "Filter.h"
#include "Kernel.h"
int main() {
std::cout<<"hello world"<<std::endl;
Kernel l({{1,2,3},{3,6,7},{2,3,4}});

auto hpass = Kernel::HighPass(3);
auto edge = Kernel::EdgeDetection(4);
auto sobelx = Kernel::SobelFilter(Kernel::FilterAxis::X);
auto sobely = Kernel::SobelFilter(Kernel::FilterAxis::Y);
// Gorgon::Graphics::Bitmap bmp1;
// bmp1.Import("testimage.jpg");
// bmp1.Grayscale();
// 
// auto xfilter = Convolution(bmp1, sobelx, ::EdgeDealing::ClosestPixel, Gorgon::Graphics::Color::White, false, false);
// auto yfilter = Convolution(bmp1, sobely, ::EdgeDealing::ClosestPixel, Gorgon::Graphics::Color::White, false, false);
// xfilter.ExportPNG("x.png");
// yfilter.ExportPNG("y.png");
// auto gradient = GradientMagnitude(xfilter, yfilter);
// 
// gradient.ExportPNG("magnituderesult.png");

return 0;
}
