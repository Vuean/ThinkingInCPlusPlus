// C05: C5_08_Handle.h
// Handle classes
#ifndef C5_08_HANDLE_H
#define C5_08_HANDLE_H
class Handle
{
    struct Cheshire;    // class declaration only
    Cheshire* smile;
public:
    void initialize();
    void cleanup();
    int read();
    void change(int);
};

#endif // C5_08_HANDLE_H