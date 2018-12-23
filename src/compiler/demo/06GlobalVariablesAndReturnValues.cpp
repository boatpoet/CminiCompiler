int qj = 5;
int max(int i)
{
	qj += i;
	return i;
}
int main()
{
	int k;
	qj = 3;
	k = max(5); //k = i = 5; qj = qj + i = 3 + 5 = 8
	cout << k; //5
	cout << qj; //8
}