#pragma once
#include <vector>
#include <numeric>
#include <math.h>
#include <Gorgon/Graphics/Bitmap.h>
#include <Gorgon/Graphics/Color.h>

enum class EdgeDealing {
    ClosestPixel = 0,
    FixedColor,
    Cyclic,
    Mirror
};



std::vector<float> Gaussiankernel(const float sigma, bool normalization = true);
Gorgon::Graphics::Bitmap Convolution(const Gorgon::Graphics::Bitmap &bmp,
                                     const std::vector<float> &kernel, 
                                     EdgeDealing edgemethod = EdgeDealing::ClosestPixel,                 
                                     Gorgon::Graphics::RGBA color = Gorgon::Graphics::Color::White); 
template <class T_>
T_ KernelTotal(const std::vector<T_> &kernel) {
    T_ value  = 0;
    value = std::accumulate(kernel.begin(),kernel.end(), value);
    return value;
}
