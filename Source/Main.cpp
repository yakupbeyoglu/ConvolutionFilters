#include <iostream>
#include <Gorgon/Graphics.h>
#include <Gorgon/Graphics/Bitmap.h>
#include "Filter.h"
#include "Kernel.h"
int main() {
std::cout<<"hello world"<<std::endl;
Kernel l({{1,2,3},{3,6,7},{2,3,4}});
auto l1 = Kernel::SobelFilter(Kernel::FilterAxis::X);
auto l11 = Kernel::SobelFilter(Kernel::FilterAxis::Y);
auto l2 = Kernel::EdgeDetection(3);
auto hpass = Kernel::HighPass(3);
Gorgon::Graphics::Bitmap bmp;
bmp.Import("hpasss.png");
/*Gorgon::Graphics::Bitmap Convolution(const Gorgon::Graphics::Bitmap &bmp,
                                     const Kernel &kernel, 
                                     EdgeDealing edgemethod,
                                     Gorgon::Graphics::RGBA fixedcolor, bool alphachanneldisable)*/
auto  z  = Convolution(bmp,hpass,EdgeDealing::FixedColor, Gorgon::Graphics::Color::White, false);
z.ExportPNG("yakup.png");
std::cout<<"Finish"<<std::endl;
return 0;

}
