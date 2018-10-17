# include <stdio.h>
# include <stdlib.h>
# include <string.h>

//using namespace std;

int delta=1;
int **A;

int OPT(int n, int m,string a,string b)
{
	int alpha,ans;
	if(a[n-1]==b[m-1])
		alpha=0;
	else
		alpha=2;
	return(min(alpha+A[n-1][m-1],min(delta+A[n-1][m],delta+A[n][m-1])));
}

int Alignment(string a, string b)
{
	
	int n,i,j,m,flag=0;
	n=a.length();
	m=b.length();
	A=(int **)malloc((n+1)*sizeof(int*));
	for(i=0;i<=n;i++)
		A[i]=(int*)malloc((m+1)*sizeof(int));
	for(i=0;i<n+1;i++)
		A[i][0]=i*delta;
	for(i=0;i<m+1;i++)
		A[0][i]=i*delta;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m;j++)
		{
			A[i][j]=OPT(i,j,a,b);
		}
	}
	for(i=0;i<=n;i++)
	{
		for(j=0;j<=m;j++)
		{
			cout << A[i][j] << " ";
		}
		cout << endl;
	}
	return A[n][m];
}


int main()
{
	string a,b;
	cin >> a >> b;
	cout<<Alignment(a,b)<<endl;
	return 0;
}