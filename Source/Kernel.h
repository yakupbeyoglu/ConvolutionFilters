#pragma once
#include <vector>
#include <Gorgon/Geometry/Size.h>
#include <initializer_list>
#include <Gorgon/Types.h>
#include <assert.h>
#include <numeric>

class Kernel {
public:
    enum class FilterAxis {
        X,
        Y
    };
    
    Kernel() {}
    
    Kernel(const std::initializer_list<std::initializer_list<Gorgon::Float>> &tkernel);
    
    // copy constructor
    Kernel(const Kernel &ckernel);

    Kernel &operator = (const Kernel &other);
    
    Kernel &operator = (const std::initializer_list<std::initializer_list<Gorgon::Float>> & initlist);
    
    void SetWidth(int width);
    
    void SetHeight(int height);
    
    void SetSize(Gorgon::Geometry::Size tsize);
    
    int GetWidth()const;
    
    int GetHeight()const;
    
    Gorgon::Float GetKernelTotal() const;
    
    Gorgon::Float GetValue(int index) const;
    
    
    Gorgon::Geometry::Size GetSize() const;
    
    // Below include the Prepeared Filters as constructor
    static Kernel SobelFilter(const Kernel::FilterAxis &axis);
    
    static Kernel Sharpen();
    
    static Kernel HorizontalLineDetection();
    
    static Kernel LowPass(int kernelsize);
    
    static Kernel HighPass(int kernelsize);
    
    static Kernel EdgeDetection(int kernelsize);
    
    static Kernel GaussianKernel(const float sigma);
    
private :
    // use to create box kernel for default filters!
    void CreateBoxKernel(float centervalue, float others);
    
    Gorgon::Geometry::Size size;
    std::vector<Gorgon::Float> kernel;
    
};
