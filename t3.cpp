# include <iostream>
# include <bits/stdc++.h>

using namespace std;

int insCost=4;
int delCost=4;

int modCost(char a, char b)
{
	if(a==b)
		return 0;
	else
		return 3;
}


// typedef struct list{
// 	int x;
// 	int y;
// }list;

// list *P;
// k=0;
long int cost=0;

string reverseString(string a)
{
	int i,len;
	len=a.length();
	for(i=0;i<len/2;i++)
		swap(a[i],a[len-i-1]);
	return a;
}




long int OPT(long int n,long int m,string a,string b,long int**A,int signal)
{
	int alpha;
	alpha=modCost(a[n-1],b[m-1]);
	if(signal==1)
		m=1;
	return(min(alpha+A[n-1][m-1],min(delCost+A[n-1][m],insCost+A[n][m-1])));
}

// long int revOPT(long int n,long int m,string a,string b,long int **A)
// {
// 	int alpha;
// 	if(a[n]==b[m])
// 		alpha=0;
// 	else
// 		alpha=2;
// 	return(min(alpha+A[n+1][1],min(delta+A[n+1][0],delta+A[n][1])));
// }


pair<string,string> Alignment(string a, string b)
{
	string ansA,ansB;
	long int **A;
	long int n,i,j,m;
	n=a.length();
	m=b.length();
	A=(long int **)malloc((n+1)*sizeof(long int*));
	for(i=0;i<=n;i++)
		A[i]=(long int*)malloc((m+1)*sizeof(long int));
	for(i=0;i<n+1;i++)
		A[i][0]=i*delCost;
	for(i=0;i<m+1;i++)
		A[0][i]=i*insCost;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m;j++)
		{
			A[i][j]=OPT(i,j,a,b,A,0);
		}
	}
	i=n;
	j=m;
	cost=cost+A[i][j];
	
	while(true)
	{
		if((i==0)||(j==0))
			break;

		if((i>=0)&&(j>=0)&&(A[i][j]==modCost(a[i-1],b[j-1])+A[i-1][j-1]))
		{
			ansA.push_back(a[i-1]);
			ansB.push_back(b[j-1]);
			i--;
			j--;
		}

		else if((i-1>=0)&&(j>=0)&&(A[i][j]=delCost+A[i-1][j]))
		{
			ansA.push_back(a[i-1]);
			ansB.push_back('-');
			i--;
		}	

		else if((i >= 0) && (j-1 >= 0) && (A[i][j]=insCost+A[i][j-1]))
		{
			ansA.push_back('-');
			ansB.push_back(b[j-1]);
			j--;
		//	cout <<"in ti"<<endl;
		}
	}


	if(i!=0)
	{
		while(i)
		{
			ansA.push_back(a[i-1]);
			ansB.push_back('-');
			i--;
		}
	}

	else
	{
		while(j)
		{
			ansA.push_back('-');
			ansB.push_back(b[j-1]);
			j--;
		}
	}
	reverse(ansA.begin(),ansA.end());
	reverse(ansB.begin(),ansB.end());

	return make_pair(ansA,ansB);
}

long int** spaceEfficientAlignment(string a, string b)
{
	long int **B;
	long int n,i,j,m;
	n=a.length();
	m=b.length();
	B=(long int **)malloc((n+1)*sizeof(long int*));
	for(i=0;i<=n;i++)
		B[i]=(long int*)malloc((2)*sizeof(long int));
	for(i=0;i<n+1;i++)
		B[i][0]=i*delCost;
	for(j=1;j<=m;j++)
	{
		B[0][1]=j*insCost;
		for(i=1;i<=n;i++)
		{
			B[i][1]=OPT(i,j,a,b,B,1);
		}
		//cout<<"forward"<<endl;
		for(i=0;i<=n;i++)
			cout << B[i][0] << " "<< B[i][1]<<endl;
		cout << endl;

		for(i=0;i<=n;i++)
			B[i][0]=B[i][1];
	}
	return B;
}


// long int** revSpaceEfficientAlignment(string a, string b)
// {
// 	long int **B;
// 	long int n,i,j,m;
// 	n=a.length();
// 	m=b.length();
// 	B=(long int **)malloc((n+1)*sizeof(long int*));
// 	for(i=0;i<=n;i++)
// 		B[i]=(long int*)malloc((2)*sizeof(long int));
// 	for(i=n;i>=0;i--)
// 		B[i][1]=(n-i)*delta;
	
// 	cout <<"backward initialisation"<<endl;

// 	for(i=0;i<=n;i++)
// 		cout << B[i][0] << " "<< B[i][1]<<endl;

// 	cout << endl;

// 	cout << m << endl;


// 	for(j=m-1;j>=0;j--)
// 	{
// 		B[n][0]=(m-j)*delta;
// 		for(i=n-1;i>=0;i--)
// 		{
// 			B[i][0]=revOPT(i,j,a,b,B);
// 		}

// 		cout <<"backward"<<endl;

// 		for(i=0;i<=n;i++)
// 			cout << B[i][0] << " "<< B[i][1]<<endl;

// 		cout << endl;

// 		for(i=0;i<=n;i++)
// 			B[i][1]=B[i][0];
// 	}
// 	return B;
// }

pair<string , string> divideAndConquer(string a, string b)
{
	long int min,q,n,m,i,c,ntemp,mtemp;
	string alg1,alg2;
	long int **B;
	long int **B1;
	n=a.length();
	m=b.length();
	//P=new list[m+n];
	if(n==0)
	{
		for(i=0;i<m;i++)
		{
			alg1.push_back('-');
			alg2.push_back(b[i]);
			cost=cost+insCost;
		}
	}

	else if(m==0)
	{
		for(i=0;i<n;i++)
		{
			alg1.push_back(a[i]);
			alg2.push_back('-');
			cost=cost+delCost;
		}
	}

	else if ((m==1)||(n==1))
	{
		pair<string,string> t = Alignment(a,b);
		alg1=t.first;
		alg2=t.second;
	}
	else
	{
		B=spaceEfficientAlignment(a,b.substr(0,m/2));
		B1=spaceEfficientAlignment(reverseString(a),reverseString(b.substr(m/2,m-(m/2))));
		for(i=0;i<n+1;i++)
		{
			if(i==0)
				min=B[i][1]+B1[n-i][1];
			
			if(B[i][1]+B1[n-i][1]<min)
			{
				min=B[i][1]+B1[n-i][1];
				q=i;
			}
		}
		cout<<"q = "<<q<<endl;
		pair<string,string> t = divideAndConquer(a.substr(0,q),b.substr(0,m/2));
		alg1=t.first;
		alg2=t.second;
		cout<<"s1 = "<< alg1 <<"   s2 = "<< alg2<<endl;
		t=divideAndConquer(a.substr(q,n-q),b.substr(m/2,m-(m/2)));
		alg1=alg1+t.first;
		alg2=alg2+t.second;
		cout<<"s1 = "<< alg1 <<"   s2 = "<< alg2<<endl;
			
	}
	return make_pair(alg1,alg2);
	
}	

int main()
{
	string a,b;
	ifstream f1 ("input1.txt");
	ifstream f2 ("input2.txt");
	getline(f1,a);
	getline(f2,b);
	cout<< a <<" "<<b<<endl;
	pair<string,string> t=divideAndConquer(a,b);
	cout<<"Alignment for 1st string - "<< t.first << endl;
	cout<<"Alignment for 2nd string - "<< t.second << endl;
	cout<<"cost = "<<cost << endl;
	return 0;

}


 