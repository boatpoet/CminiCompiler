int main()
{
	int a = 10,sum = 0;
	while (a > 0)
	{
		sum = sum + a;
		a--;
	}
	cout << sum; //sum = 10+9+8+...+1 = 55
}