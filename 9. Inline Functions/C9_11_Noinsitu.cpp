// C9_11_Noinsitu.cpp
// Removing in situ functions

class Rectangle
{
    int width, height;
public:
    Rectangle(int w = 0, int h = 0);
    int getWidth() const;
    void setWidth(int w);
    int getHeight() const;
    void setHeight(int h);
};

inline Rectangle::Rectangle(int w, int h)
    : width(w), height(h) {}

inline int Rectangle::getWidth() const { return width; }

inline void Rectangle::setWidth(int w) { width = w; }

inline int Rectangle::getHeight() const { return height; }

inline void Rectangle::setHeight(int h) { height = h;}

int main()
{
    Rectangle r(19, 47);
    int iHeight = r.getHeight();
    r.setHeight(r.getWidth());
    r.setWidth(iHeight);
}