#include "Filter.h"
 
 
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
}

Gorgon::Graphics::Bitmap Convolution(const Gorgon::Graphics::Bitmap &bmp,
                                     const std::vector<float> &kernel, 
                                     EdgeDealing edgemethod,
                                     Gorgon::Graphics::RGBA color)
{
    
    Gorgon::Graphics::Bitmap nbmp = bmp.Duplicate();
    nbmp.Grayscale();
    nbmp.ExportPNG("gs.png");
    float kerneltotal = KernelTotal(kernel);
  for(int y = 0; y < bmp.GetHeight(); y++) {
        for (int x = 0; x < bmp.GetWidth(); x++) {
         Gorgon::Geometry::Point current = {x, y};   
         float sum = 0.0;
         int kernelsize = kernel.size();
         Gorgon::Geometry::Point  maxbmpsize= {nbmp.GetWidth()-1, nbmp.GetHeight()-1};
         Gorgon::Geometry::Point  minbmpsize = {0, 0};
         for (int ky = - kernelsize / 2; ky < kernelsize/2; ky++) {
             int kxi = 0;
                for(int kx = -kernelsize/2 ; kx < kernelsize/2; kx++) {
                      auto calculatedlocation = current + Gorgon::Geometry::Point(kx,ky);
                      // y*size + x
                    if(calculatedlocation.X > maxbmpsize.X)
                        calculatedlocation.X = maxbmpsize.X;
                    else if (calculatedlocation.X < minbmpsize.X)
                        calculatedlocation.X = minbmpsize.X;
                    if(calculatedlocation.Y > maxbmpsize.Y)
                        calculatedlocation.Y = maxbmpsize.Y;
                    else if(calculatedlocation.Y < minbmpsize.Y)
                        calculatedlocation.Y = minbmpsize.Y;
                    sum += bmp.Get(calculatedlocation) * kernel.at(kxi);
                    kxi++;
                }
                
               // sum /= kerneltotal ? kerneltotal : 1;
                nbmp(current) = sum;
             
         }
         nbmp.ExportBMP("result.png");
            
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
