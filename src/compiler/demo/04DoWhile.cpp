int main()
{
	int a = 10, sum = 0;
	do
	{
		sum = sum + a;
		a--;
	} while (a > 0);
	cout << sum; //sum = 10+9+8+...+1 = 55
}