int max(int a)
{
	if (a > 5)
	{
		a--;
		a = max(a);
	}
	else
	{
		a = 0;
	}
	return a;
}
int main() {
	int a;
	a = max(50000);
	cout << a;
	return 0;
}
