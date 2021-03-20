#pragma once
#include <vector>
#include <Gorgon/Geometry/Size.h>
#include <initializer_list>
#include <Gorgon/Types.h>
#include <assert.h>

class Kernel {
public:

    Kernel();
    Kernel(const std::initializer_list<std::initializer_list<Gorgon::Float>> &tkernel) {
        *this = tkernel;
    }
        // copy constructor
    Kernel(const Kernel &ckernel) {
     kernel = ckernel.kernel;   
     size = ckernel.size;
    }

    Kernel &operator = (const Kernel &other) {
        kernel = other.kernel;
        size = other.size;
        return *this;
    }
    
    Kernel &operator = (const std::initializer_list<std::initializer_list<Gorgon::Float>> & initlist) {
        
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
    std::vector<Gorgon::Float> kernel;
    
};
