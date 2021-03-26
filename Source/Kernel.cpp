#include "Kernel.h"

Kernel::Kernel(const std::initializer_list<std::initializer_list<Gorgon::Float>> &tkernel) {
    *this = tkernel;
}

Kernel::Kernel(const Kernel &ckernel) {
    kernel = ckernel.kernel;   
    size = ckernel.size;
}

Kernel  &Kernel::operator = (const Kernel &other) {
    kernel = other.kernel;
    size = other.size;
    return *this;
}

Kernel &Kernel::operator = (const std::initializer_list<std::initializer_list<Gorgon::Float>> & initlist) {
  
    int maxlistsize = initlist.begin()->size();
    
    for(auto &list : initlist) {            
        if(list.size()  > maxlistsize)
            maxlistsize = list.size();
    }
            
    for(auto &list : initlist) {
        // if size is not equal break in debug
        assert(list.size() == maxlistsize);
        kernel.insert(kernel.end(), list.begin(), list.end());
                
        if(list.size() < maxlistsize)
            kernel.insert(kernel.end(), maxlistsize - list.size(), 0);
    }        
        
    size.Height = initlist.size();
    size.Width = maxlistsize;
    return *this;
}

void Kernel::SetWidth(int width) {
    size.Width = width;
}

void Kernel::SetHeight(int height) {
    size.Height = height;
}

void Kernel::SetSize(Gorgon::Geometry::Size tsize) {
    size = tsize;
}

void Kernel::SetSize(int width, int height) {
    size = {width, height};
}

int Kernel::GetWidth() const {
    return size.Width;
}

int Kernel::GetHeight() const {
    return size.Height;
}
    
Gorgon::Geometry::Size Kernel::GetSize() const {
    return size;
}

Gorgon::Float Kernel::GetKernelTotal() const {
    float total = std::accumulate(kernel.begin(),kernel.end(), 0.0f);
    return total;
}

Gorgon::Float Kernel::GetValue(int index) const {
    return kernel.at(index);
}


Kernel Kernel::SobelFilter(const Kernel::FilterAxis &axis) {
    Kernel nkernel;
    
    switch (axis){
        case FilterAxis::X :
            nkernel = {{1, 0, -1}, {2, 0, -2}, {1, 0, -1}};
            break;
        case FilterAxis::Y :
            nkernel = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};
            break;
    }
    
    return nkernel;
}


Kernel Kernel::Sharpen() {
    Kernel nkernel;
    nkernel = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
    return nkernel;
}  

Kernel Kernel::HorizontalLineDetection() {
    Kernel nkernel;
    nkernel = {{-1, -1, -1}, {2, 2, 2}, {-1, -1, -1}};
    return nkernel;
}

Kernel Kernel::LowPass(int kernelsize) {
    Kernel nkernel;
    nkernel.SetSize({kernelsize, kernelsize});
    nkernel.CreateBoxKernel((double)1/(kernelsize * kernelsize), (double)1 / (kernelsize * kernelsize));
    return nkernel;
    
    
}

Kernel Kernel::HighPass(int kernelsize) {
    Kernel nkernel;
    nkernel.SetSize({kernelsize, kernelsize});
    nkernel.CreateBoxKernel(kernelsize * kernelsize, -1);
    return nkernel;
}

Kernel Kernel::EdgeDetection(int kernelsize) {
    Kernel nkernel;
    nkernel.SetSize({kernelsize, kernelsize});
    nkernel.CreateBoxKernel(kernelsize * kernelsize -1, -1);
    return nkernel;
    
}

Kernel Kernel::GaussianKernel(const float sigma, FilterAxis axis) {
    Kernel nkernel;
    int size = 2 * sigma + 1;
    
    if(axis == FilterAxis::Y)
        nkernel.SetSize({1,size});
    else
        nkernel.SetSize({size, 1});

        
    float base1 = 2 * sigma * sigma;
    float base2 = 2 * 3.14 * sigma * sigma;
    for(int x = 0; x < size; x++) {
        auto value =  (std::exp( -1 * x * x) / base1) / base2;
        nkernel.kernel.push_back(value);
    }
            
    return nkernel;
}

void Kernel::CreateBoxKernel(float centervalue, float others) {
    int centerindex = size.Height / 2;
    
    for(int y = 0; y < size.Height; y++) {
        for(int x= 0; x< size.Width; x++) {
            if(x == centerindex && y == centerindex)
                kernel.push_back(centervalue);
            else
                kernel.push_back(others);
        } 
       
    }
 }
    

    
