# include <iostream>

using namespace std;

int delta=1;
int **A;

int OPT(int n, int m,string a,string b)
{
	int alpha;
	if(a[n-1]==b[m-1])
		alpha=0;
	else
		alpha=2;
	return(min(alpha+A[n-1][0],min(delta+A[n-1][1],delta+A[n][0])));
}

int spaceEfficientAlignment(string a, string b)
{
	
	int n,i,j,m;
	n=a.length();
	m=b.length();
	A=(int **)malloc((n+1)*sizeof(int*));
	for(i=0;i<=n;i++)
		A[i]=(int*)malloc((2)*sizeof(int));
	for(i=0;i<n+1;i++)
		A[i][0]=i*delta;
	for(j=1;j<=m;j++)
	{
		A[0][1]=j*delta;
		for(i=1;i<=n;i++)
		{
			A[i][1]=OPT(i,j,a,b);
		}
		for(i=0;i<=n;i++)
		{
			cout<<A[i][0]<<" "<<A[i][1]<<endl;
		}
		cout<<endl<<endl;
		for(i=0;i<=n;i++)
			A[i][0]=A[i][1];
	}
	// for(i=0;i<=n;i++)
	// {
	// 	for(j=0;j<=m;j++)
	// 	{
	// 		cout << A[i][j] << " ";
	// 	}
	// 	cout << endl;
	// }
	return A[n][1];
}


int main()
{
	string a,b;
	cin >> a >> b;
	cout<<spaceEfficientAlignment(a,b)<<endl;
	return 0;
}