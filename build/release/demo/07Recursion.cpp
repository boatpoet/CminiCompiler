int max(int a)
{
	if (a > 5)
	{
		a--;
		a = max(a);
	}
	else
	{
		a = 10;
	}
	return a;
}

int main() 
{
	int a;
	a=30;
	a = max(30); //a=10
	cout(8) << a; //Output = 12
	return 0;
}


