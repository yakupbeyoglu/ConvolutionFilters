#pragma once
#include <vector>
#include <Gorgon/Geometry/Size.h>
#include <initializer_list>

template <class T_>
class Kernel {
public:
    Kernel(const std::initializer_list<T_> &kernel, 
        const Gorgon::Geometry::Size &size): kernel(kernel), size(size) {
        
    }
    
    Kernel(const std::initializer_list<std::initializer_list<T_>> &tkernel) {
        const auto &listwidth = tkernel.begin();
        size.Height = tkernel.size();
        size.Width = listwidth->size();
        for(auto element : tkernel){
            for(auto el:element){
                kernel.push_back(el);
                
            }
            
        }
        
    }
    
    Kernel & operator = (const std::initializer_list<std::initializer_list<T_>> & initlist){
            Kernel nkernel;
            for(auto element : initlist){
            for(auto el:element){
                nkernel.push_back(el);
                
            }
            
        }
        return nkernel;
    }
    // copy constructor
    Kernel(const Kernel &ckernel) {
     kernel = ckernel.kernel;   
     size = ckernel.size;
    }

    Kernel &operator = (const Kernel &other) {
        kernel = other.kernel;
        size = other.size;
    }
    
    void SetWidth(int width) {
        size.Width = width;
    }
    
    void SetHeight(int height) {
        size.Height = height;
    }
    
    void SetSize(Gorgon::Geometry::Size tsize) {
        size = tsize;
    }
    
    int GetWidth()const {
        
        return size.Width;
        
    }
    int GetHeight()const {
        return size.Height;
    }
    
    Gorgon::Geometry::Size GetSize()const {
        return size;
    }
    
private :
    Gorgon::Geometry::Size size;
    std::vector<T_> kernel;
    
};
