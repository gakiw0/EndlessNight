#ifndef AUTOSCROLLER_HPP 
#define AUTOSCROLLER_HPP

#include <allegro5/allegro.h>

class AutoScroller {
public:
    AutoScroller(const char* imagePath, float speed);
    ~AutoScroller();

    void Update(float deltaTime);
    void Draw();
    void SetZoom(float zoomFactor); 

private:
    ALLEGRO_BITMAP* image;
    float offsetX;
    float speed;
    int width, height;
    float zoom; // New zoom factor member
};

#endif // AUTOSCROLLER_HPP