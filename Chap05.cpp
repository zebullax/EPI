#include <iostream>
using namespace std;

int AddTwoIntegersBitwiseOper(int a,int b)
{
	int carry = 0;
	int bit_position = 0;
	int bit_value = 0;
	int result=0;

	while (a || b)
	{
		bit_value = carry ^ (a & 1) ^ (b & 1);
		carry = ((a & 1) & (b & 1)) | (carry &  ((a & 1) | (b & 1)));
		result |= (bit_value << bit_position);
		bit_position++;
		a >>= 1; b >>= 1;
	}
	if (carry)
	{
		result |= (carry << bit_position);
	}
	return result;
}
unsigned Add(unsigned a, unsigned b) {
	unsigned sum = 0, carryin = 0, k = 1, temp_a = a, temp_b = b;
	while (temp_a || temp_b) {
		unsigned ak = a & k, bk = b & k;
		unsigned carryout = (ak & bk) | (ak & carryin) | (bk & carryin);
		sum |= (ak ^ bk ^ carryin);
		carryin = carryout << 1, k <<= 1, temp_a >>= 1, temp_b >>= 1;
	}
	return sum | carryin;
}

unsigned Divide(unsigned x, unsigned y) {
	unsigned result = 0;
	int power = 32;
	unsigned long long y_power = static_cast <unsigned long long >(y) << power;
	while (x >= y) {
		while (y_power > x) {
			y_power >>= 1;
			--power;
		}
		result += 1U << power;
		x -= y_power;
	}
	return result;
}

void Prob5_5D()
{
	int x = 7;
	int y = 5;
	int sum = 0;
	for (int i = 0; i < y; ++i)
	{
		sum = AddTwoIntegersBitwiseOper(sum, x);
	}
	cout << sum << endl;
}
int main(int argc, char** argv)
{
	Divide(11, 2);
	getchar();
	return 0;
}