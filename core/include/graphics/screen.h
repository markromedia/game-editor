#ifndef __Flight__screen__
#define __Flight__screen__

#include <iostream>

class Screen {
private:
    float width, height;
    static Screen* _instance;
public:
    // init the screen width and height
    static void Init(int width, int height);
    
    static float Width();
    
    static float Height();
};


#endif /* defined(__Flight__screen__) */
