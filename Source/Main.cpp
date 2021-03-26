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
auto gaussianX = Kernel::GaussianKernel(3, Kernel::FilterAxis::X);
auto gaussianY = Kernel::GaussianKernel(3, Kernel::FilterAxis::Y);
// Gorgon::Graphics::Bitmap bmp;
// bmp.Import("eye.png");
// auto outx = Convolution(bmp, gaussianX, EdgeDealing::ClosestPixel, Gorgon::Graphics::Color::White, false, true);
// auto outy = Convolution(outx, gaussianY, EdgeDealing::ClosestPixel, Gorgon::Graphics::Color::White, false, true);

// outy.ExportPNG("testgaussian.png");

return 0;
}
