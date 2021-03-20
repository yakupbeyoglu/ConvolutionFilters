#include "Filter.h"
 
/* 
std::vector<float> Gaussiankernel (const float sigma, bool normalization) {
    std::vector<float> kernel;
    int n = 2 * sigma + 1;
    float normalizationvalue = (2 * 3.14 * sigma * sigma);
    
    for(int x = -n/2; x<= n/2; x++) {
        float value = std::exp((-1*  (x * x)) / (2 * sigma * sigma));
        value /= normalizationvalue;
        kernel.push_back(value);
    }
    if(normalization) {
        auto total = KernelTotal(kernel);
        for(auto &value : kernel){
                value /= total;
        }
    }
    return kernel;
}*/

Gorgon::Graphics::Bitmap Convolution(const Gorgon::Graphics::Bitmap &bmp,
                                     const Kernel &kernel, 
                                     EdgeDealing edgemethod,
                                     Gorgon::Graphics::RGBA color)
{
    Gorgon::Graphics::Bitmap nbmp;
    
    
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
