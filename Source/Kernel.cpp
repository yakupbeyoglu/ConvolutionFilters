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

int Kernel::GetWidth() const {
    return size.Width;
}

int Kernel::GetHeight() const {
    return size.Height;
}
    
Gorgon::Float Kernel::GetKernelTotal() const {
    float total = std::accumulate(kernel.begin(),kernel.end(), 0.0f);
    return total;
}

Gorgon::Float Kernel::GetValue(int index) const {
    return kernel.at(index);
}

Gorgon::Geometry::Size Kernel::GetSize() const {
    return size;
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
    

    
