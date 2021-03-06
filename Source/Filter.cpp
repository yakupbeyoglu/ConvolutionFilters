#include "Filter.h"
#include <array>

void ApplyFilter(Gorgon::Graphics::Bitmap &bmp, Gorgon::Geometry::Point &coordinates, int channel, int value) 
{
    bmp(coordinates, channel) = value;
    
}

void DealingEdge(const EdgeDealing &method, int &current, int max, int min, bool isless) {
    int value = isless ? min : max;
    
    switch(method) {
        case EdgeDealing::ClosestPixel:
            current = value;
            break;
        case EdgeDealing::Cyclic:
            current = max - current;
            break;
        case EdgeDealing::Mirror:
            if(current < 0)
                current = std::abs(current);
            break;
        case EdgeDealing::FixedColor:
        default :
            current = value;
            break;
    }
    
}

std::array<Gorgon::Byte,4> GetFixedColor(const Gorgon::Graphics::ColorMode &mode, const Gorgon::Graphics::RGBA &color) {
    
    switch(mode){
        case Gorgon::Graphics::ColorMode::Alpha:
            return {color.A};
            break;
        case Gorgon::Graphics::ColorMode::Grayscale_Alpha:
            return {color.Luminance(), color.A};
            break;
        case Gorgon::Graphics::ColorMode::Grayscale:
            return {color.Luminance()};
            break;
        case Gorgon::Graphics::ColorMode::RGB:
            return {color.R, color.G, color.B};
            break;
        case Gorgon::Graphics::ColorMode::BGR:
            return {color.B, color.G, color.R};
            break;
        case Gorgon::Graphics::ColorMode::RGBA:
            return {color.R, color.G, color.B, color.A};
            break;
        case Gorgon::Graphics::ColorMode::BGRA:
            return {color.B, color.G, color.R, color.A};
            break;
        default:
            return {};
            
    }
        
}
Gorgon::Graphics::Bitmap Convolution(const Gorgon::Graphics::Bitmap &bmp,
                                     const Kernel &kernel, 
                                     EdgeDealing edgemethod,
                                     Gorgon::Graphics::RGBA fixedcolor, bool alphachanneldisable, bool normalization)
{
    
    Gorgon::Graphics::Bitmap nbmp = bmp.Duplicate();
    
    if(bmp.IsEmpty())
        return nbmp;
    
    std::array<Gorgon::Byte, 4 > fixedcolorarray;
    if(edgemethod == EdgeDealing::FixedColor)
        fixedcolorarray  = GetFixedColor(bmp.GetMode(), fixedcolor);
    
    // find number of avaliable channel
    int numberofchannel = bmp.GetChannelsPerPixel();
    // check which is alpha if not have it will -1
    int alphaindex = bmp.HasAlpha() ? bmp.GetAlphaIndex() : -1;
    
    Gorgon::Geometry::Point maxbounds = { bmp.GetWidth() -1 , bmp.GetHeight() - 1};
    Gorgon::Geometry::Point minbounds = {0, 0};
    
    for(int y = 0; y < nbmp.GetHeight(); y++) {
        for(int x = 0; x < nbmp.GetWidth(); x++) {
            std::vector<float> calculatedvalue(numberofchannel, 0.0);
            
            for(int kernely = -kernel.GetHeight() / 2; kernely <= (kernel.GetHeight() - 1) / 2; kernely++) {
                for(int kernelx = -kernel.GetWidth() / 2; kernelx <= (kernel.GetWidth() - 1) / 2; kernelx++) {
                    Gorgon::Geometry::Point current =  {x + kernelx, y + kernely};
                    bool isedge = false;
                    auto kernelvalue = kernel.GetValue((kernely + kernel.GetHeight() / 2) * kernel.GetWidth() + (kernelx + kernel.GetWidth() / 2));
                    if(normalization)
                        kernelvalue/= kernel.GetKernelTotal();
                    
                    if((current.X > maxbounds.X || current.X < minbounds.X ||
                        current.Y > maxbounds.Y || current.Y < minbounds.Y) &&
                        edgemethod == EdgeDealing::FixedColor)
                        isedge = true;
                    
                    else {
                        
                        if(current.X  > maxbounds.X) 
                            DealingEdge(edgemethod, current.X, maxbounds.X, minbounds.X);
                        
                        else if(current.X < minbounds.X) 
                            DealingEdge(edgemethod, current.X, maxbounds.X, minbounds.X, true);
                        
                        if(current.Y > maxbounds.Y) 
                            DealingEdge(edgemethod, current.Y, maxbounds.Y, minbounds.Y);
                        
                        else if(current.Y < minbounds.Y) 
                            DealingEdge(edgemethod, current.Y, maxbounds.Y, minbounds.Y, true);
                        
                    }
                    
                    if(isedge) {
                        for(int i = 0; i < numberofchannel; i++)
                            calculatedvalue[i] = fixedcolorarray[i] * kernelvalue;
                    }
                    
                    else {
                        for(unsigned int  channel = 0; channel < numberofchannel; channel++) {
                            calculatedvalue[channel] += bmp.Get(current, channel) * kernelvalue;
                        }
                    }
                }
                
            }
            
            for(unsigned int channel = 0; channel < numberofchannel; channel++) {
                if(channel == alphaindex && alphachanneldisable)
                    continue;
                
                // if is edge detection should be cycle it 
                if(calculatedvalue.at(channel) < 0)
                    calculatedvalue.at(channel) = 0;
                
                else if(calculatedvalue.at(channel) > 255)
                    calculatedvalue.at(channel) = 255;
                
                nbmp(x, y, channel) = calculatedvalue.at(channel);
                
                
            }
        }
    }
    
    return nbmp;  
    
}

Gorgon::Graphics::Bitmap GradientMagnitude(Gorgon::Graphics::Bitmap &x, Gorgon::Graphics::Bitmap &y) {
    Gorgon::Graphics::Bitmap s = x.Duplicate();
    int numberofchannel = x.GetChannelsPerPixel();
    for (int j = 0; j < s.GetHeight(); j++) {
        for (int i = 0; i < s.GetWidth(); i++) {
            for (int nc = 0; nc < numberofchannel; nc++) {
                float value = std::sqrt(std::pow(x(i, j, nc), 2) + std::pow(y(i, j, nc), 2));
                if (value > 255)
                    value = 255;
                else if (value < 0)
                    value = 0;
                s(i, j, nc) = value;

            }
        }

    }
    return s;
}


