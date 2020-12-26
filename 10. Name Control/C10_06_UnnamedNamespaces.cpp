// C10_06_UnnamedNamespaces.cpp
namespace{
    class Arm { };
    class Leg { };
    class Head { };
    class Robot{
        Arm arm[4];
        Leg leg[16];
        Head head[3];
    } xanthan;
    int i, j, k;
}

int main() {}