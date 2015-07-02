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
	Prob5_5D();
	getchar();
	return 0;
}