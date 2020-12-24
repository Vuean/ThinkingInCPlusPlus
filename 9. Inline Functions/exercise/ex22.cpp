inline int f(int a, int b) __attribute__((always_inline));

inline int f(int a, int b) {
	return a + b;
}

int main() 
{
	f(2, 3);
}