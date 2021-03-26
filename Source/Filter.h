#pragma once
#include <vector>
#include <numeric>
#include <math.h>
#include <Gorgon/Graphics/Bitmap.h>
#include <Gorgon/Geometry/Point.h>
#include <Gorgon/Graphics/Color.h>
#include "Kernel.h"

enum class EdgeDealing {
    ClosestPixel = 0,
    FixedColor,
    Cyclic,
    Mirror
};



std::vector<float> Gaussiankernel(const float sigma, bool normalization = true);
void DealingEdge(const EdgeDealing &method, int &current, int max, int min, bool isless = false);
void ApplyFilter(Gorgon::Graphics::Bitmap &bmp, Gorgon::Geometry::Point &coordinates, int channel, int value);
std::array<Gorgon::Byte,4> GetFixedColor(const Gorgon::Graphics::ColorMode &mode, const Gorgon::Graphics::RGBA &color);

Gorgon::Graphics::Bitmap Convolution(const Gorgon::Graphics::Bitmap &bmp,
                                     const Kernel &kernel, 
                                     EdgeDealing edgemethod = EdgeDealing::ClosestPixel,                 
                                     Gorgon::Graphics::RGBA color = Gorgon::Graphics::Color::White, 
                                     bool alphachanneldisable = false, bool normalization = false); 

Gorgon::Graphics::Bitmap GradientMagnitude(Gorgon::Graphics::Bitmap &x, Gorgon::Graphics::Bitmap &y);
