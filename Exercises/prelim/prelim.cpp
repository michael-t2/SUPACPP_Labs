
# include <iostream>
# include <math.h>

float mag_2d(float x, float y);

int main ()
{
    float x = 3.4;
    float y = 7.5;

    float mag = mag_2d(x,y);
    // float mag = sqrt(x*x + y*y)

    std::cout << mag << std::endl;

    return 0;
}


float mag_2d (float x, float y){

    return sqrt(x*x + y*y);
}