// C8_04_PointerAssignment.cpp
int d = 1;
const int e = 2;
int* u = &d;    // OK -- d not const
// int* v = &e; // Illegal  -- e const
int* w = (int*)&e;  // legal but bad practice

int main() {}