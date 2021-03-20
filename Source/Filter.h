#pragma once
#include <vector>
#include <numeric>
#include <math.h>
#include <Gorgon/Graphics/Bitmap.h>
#include <Gorgon/Graphics/Color.h>
#include "Kernel.h"

enum class EdgeDealing {
    ClosestPixel = 0,
    FixedColor,
    Cyclic,
    Mirror
};



std::vector<float> Gaussiankernel(const float sigma, bool normalization = true);
Gorgon::Graphics::Bitmap Convolution(const Gorgon::Graphics::Bitmap &bmp,
                                     const Kernel &kernel, 
                                     EdgeDealing edgemethod = EdgeDealing::ClosestPixel,                 
                                     Gorgon::Graphics::RGBA color = Gorgon::Graphics::Color::White); 
