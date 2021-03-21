#include "Filter.h"
 

void ApplyFilter(Gorgon::Graphics::Bitmap &bmp, Gorgon::Geometry::Point &coordinates, int channel, int value) 
{
    bmp(coordinates, channel) = value;
    
}

void DealingEdge(const EdgeDealing &method, int &current, int max, int min, bool isless = false) {
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

Gorgon::Graphics::RGBA GetFixedColor(const Gorgon::Graphics::ColorMode &mode, const Gorgon::Graphics::RGBA &color) {
    Gorgon::Graphics::RGBA ncolor;
    
    switch(mode){
        case Gorgon::Graphics::ColorMode::Alpha:
            ncolor.A = color.A;
            break;
        case Gorgon::Graphics::ColorMode::Grayscale_Alpha:
            ncolor.R = color.Luminance();
            ncolor.A = color.A;
            break;
        case Gorgon::Graphics::ColorMode::Grayscale:
            ncolor.R = color.Luminance();
            break;
        case Gorgon::Graphics::ColorMode::RGB:
            ncolor.R = color.R;
            ncolor.G = color.G;
            ncolor.B = color.B;
            break;
        case Gorgon::Graphics::ColorMode::BGR:
            ncolor.B = color.R;
            ncolor.G = color.G;
            ncolor.R = color.B;
            break;
        case Gorgon::Graphics::ColorMode::RGBA:
            ncolor.R = color.R;
            ncolor.G = color.G;
            ncolor.B = color.B;
            ncolor.A = color.A;
            break;
        case Gorgon::Graphics::ColorMode::BGRA:
            ncolor.B = color.R;
            ncolor.G = color.G;
            ncolor.R = color.B;
            ncolor.A = color.A;
            break;
        default:
            ;
    }
    
    return ncolor;
    
}
Gorgon::Graphics::Bitmap Convolution(const Gorgon::Graphics::Bitmap &bmp,
                                     const Kernel &kernel, 
                                     EdgeDealing edgemethod,
                                     Gorgon::Graphics::RGBA fixedcolor, bool alphachanneldisable)
{
    Gorgon::Graphics::Bitmap nbmp;
    Gorgon::Graphics::RGBA nfixed  = GetFixedColor(bmp.GetMode(), fixedcolor);
    nbmp.Resize(bmp.GetSize());
     if(bmp.IsEmpty())
        return nbmp;
     
    // find number of avaliable channel
    int numberofchannel = bmp.GetChannelsPerPixel();
    // check which is alpha if not have it will -1
    int alphaindex = bmp.HasAlpha() ? bmp.GetAlphaIndex() : -1;
    
    Gorgon::Geometry::Point maxbounds = { bmp.GetWidth() -1 , bmp.GetHeight() - 1};
    Gorgon::Geometry::Point minbounds = {0, 0};
    
    
    
    
    
    for(int y = 0; y < bmp.GetHeight(); y++) {
        for(int x = 0; x < bmp.GetWidth(); x++) {
            std::vector<float> calculatedvalue(numberofchannel,0.0);

            for(int kernely = -kernel.GetHeight() / 2; kernely < kernel.GetHeight() / 2; kernely++) {
                for(int kernelx = -kernel.GetWidth() / 2; kernelx < kernel.GetWidth() / 2; kernelx++) {
                    Gorgon::Geometry::Point current = {x + kernelx, y + kernely};
                    bool isedge;
                    if(current.X  > maxbounds.X) {
                       DealingEdge(edgemethod, current.X, maxbounds.X, minbounds.X);
                        isedge = true;
                    }
                    else if(current.X < minbounds.X) {
                        DealingEdge(edgemethod, current.X, maxbounds.X, minbounds.X, true);
                        isedge = true;
                    }
                    if(current.Y > maxbounds.Y) {
                        DealingEdge(edgemethod, current.Y, maxbounds.Y, minbounds.Y);
                        isedge = true;
                    }
                    
                    else if(current.Y < minbounds.Y) {
                        DealingEdge(edgemethod, current.Y, maxbounds.Y, minbounds.Y, true);
                        isedge = true;
                    }
                      
                    auto kernelvalue = kernel.GetValue((kernely + kernel.GetHeight()/2) * kernel.GetWidth() + (kernelx + kernel.GetWidth()/2));
                    
                    // calculate for each channel
                    if(edgemethod == EdgeDealing::FixedColor && isedge)
                        
                        
                    if(edgemethod == EdgeDealing::FixedColor && isedge) {
                            calculatedvalue[0] = nfixed.R * kernelvalue;
                            calculatedvalue[1] = nfixed.G * kernelvalue;
                            calculatedvalue[2]= nfixed.B * kernelvalue;
                    }
                    else {
                        for(unsigned int  channel = 0; channel < numberofchannel; channel++) {
                            calculatedvalue[channel] += bmp.Get(current, channel)* kernelvalue;
                            
                        }
                    }
                }
                        
            }
            
            for(unsigned int channel = 0; channel < numberofchannel; channel++) {
                if(channel == alphaindex && !alphachanneldisable)
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

        
        
        
        
    
    
    
    
    
    

 
    
    


 /*
 Gorgon::Graphics::Bitmap	bmp2 = bmp.Duplicate();
            bmp2.Grayscale();
            auto kerneltotal = KernelTotal(kernel);
            Gorgon::Geometry::Point max = { bmp.GetWidth()-1,bmp.GetHeight()-1};
            Gorgon::Geometry::Point min = { 0,0 };

                for (int y = 0; y < bmp2.GetHeight(); y++) {
                    for (int x = 0; x < bmp2.GetWidth(); x++) {
                        Gorgon::Geometry::Point current = { x,y };
                        double sum = 0;
                        bool status = false;
                        for (auto location : kernel) {
                            auto calculatedlocation = current + location.Get();
                    
                            if (calculatedlocation.X > max.X)
                                calculatedlocation.X = max.X;
                            else if (calculatedlocation.X < min.X)
                                calculatedlocation.X = min.X;
                            if (calculatedlocation.Y > max.Y)
                                calculatedlocation.Y = max.Y;
                            else if (calculatedlocation.Y < min.Y)
                                calculatedlocation.Y = min.Y;

                            sum += bmp2.Get(calculatedlocation)*location.Getvalue();
                        }
                        sum /= kerneltotal ? kerneltotal : 1;
                    
                        bmp2(current) = sum;
                    }
                }
                bmp2.ExportBMP("newclamping.PNG");
            return bmp2;
*/
