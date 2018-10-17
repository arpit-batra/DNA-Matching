/*
    S1' = GCCCTAGCG
    S2' = GCGC-AATG*/


#include <bits/stdc++.h>
using namespace std;

	//cost associated
	int cost = 0;

	//insertion cost
	inline int insC() {
		return 4;
	}

	//deletion cost
	inline int delC() {
		return 4;
	}

	//modification cost
	inline int modC(char fr, char to) {
		if(fr == to)
			return 0;
		return 3;
	}

	//reversing the string
	string rever(string s) {
		int k = s.length();

		for(int i = 0; i < k/2; i++)
			swap(s[i], s[k-i-1]);
		return s;
	}

	//minimizing the sum of shortest paths, calculating next starting point
	int minimize(vector<int> ve1, vector<int> ve2, int le) {
		int sum, xmid = 0;
		
		for(int i = 0; i <= le; i++) {
			if(i == 0)
				sum = ve1[i] + ve2[le-i];

			if(sum > ve1[i] + ve2[le-i]) {
				sum = ve1[i] + ve2[le-i];
				xmid = i;
			}

		}
		return xmid;
	}

	pair<string, string> stringOne(string s1, string s2) {

		//building of array for case string length one of any of the string
		string sa, sb;
		int m1 = 0;

		int m = s1.length();
		int n = s2.length();

		vector<vector<int> > fone(s1.length()+5, vector<int>(2));

		for(int i = 0; i <= m; i++)
			fone[i][0] = i*delC();

		for(int j = 0; j <= n; j++)
			fone[0][j] = j*insC();

		for(int i = 1; i <= m; i++) {
			int j;
			for(j = 1; j <= n; j++) {
				fone[i][j] = min(modC(s1[i-1], s2[j-1]) + fone[i-1][j-1], min(delC() + fone[i-1][j], insC() + fone[i][j-1]));
			}
		}

		int i = m, j = n;
		cost += fone[i][j];

		//backtracking in case the length is one of string
		while(true) {

			if(i == 0 || j == 0)
				break;

			if(i >= 0 && j >= 0 && fone[i][j] == modC(s1[i-1], s2[j-1]) + fone[i-1][j-1]) {
				sa.push_back(s1[i-1]);
				sb.push_back(s2[j-1]);
				i--; j--;
			}

			else if((i-1) >= 0 && j >= 0 && fone[i][j] == delC() + fone[i-1][j]) {
				sa.push_back(s1[i-1]);
				sb.push_back('-');
				i-=1;
			}

			else if(i >= 0 && (j-1) >= 0 && insC() + fone[i][j-1]){
				sa.push_back('-');
				sb.push_back(s2[j-1]);
				j-=1;
				//cout<<"in it"<<endl;
			}
		}

		//continue backtracking
		if(i != 0) {
			while(i) {
				sa.push_back(s1[i-1]);
				sb.push_back('-');
				i--;
			}
		}

		else {
			while(j) {
				sa.push_back('-');
				sb.push_back(s2[j-1]);
				j--;
			}
		}	

		//strings obtained are reversed alignment
		reverse(sa.begin(), sa.end());
		reverse(sb.begin(), sb.end());

		return make_pair(sa, sb);

	}

	//getting the cost associated with alignment
	vector<int> SpaceEfficientAlignment(string s1, string s2) {
		
		//space efficient version
		int m = s1.length();
		int n = s2.length();
		
		vector<vector<int> > array2d(m+5, vector<int>(2));

		//base conditions
		for(int i = 0; i <= m; i++)
			array2d[i][0] = i*(delC());

		for(int j = 1; j <= n; j++) {

			array2d[0][1] = j*(insC());

			for(int i = 1; i <= m; i++) {
				array2d[i][1] = min(modC(s1[i-1], s2[j-1]) + array2d[i-1][0], min(delC() + array2d[i-1][1], insC() + array2d[i][0]));
			}
			for(int i=0;i<=m;i++)
				cout << array2d[i][0] << " "<< array2d[i][1]<<endl;
			cout << endl;
			for(int i = 0; i <= m; i++)
				array2d[i][0] = array2d[i][1];
		}

		//returning the last column
		vector<int> vec(m+1);
		for(int i = 0; i <= m; i++) {
			vec[i] = array2d[i][1];
		}

		return vec;
	}

	pair<string, string> GainAlignment(string s1, string s2) {

		string te1, te2;
		int l1 = s1.length();
		int l2 = s2.length();

		//trivial cases
		if(l1 == 0) {
			for(int i = 0; i < l2; i++) {
				te1.push_back('-');
				te2.push_back(s2[i]);
				cost += insC();
			}
		}

		else if(l2 == 0) {
			for(int i = 0; i < l1; i++) {
				te1.push_back(s1[i]);
				te2.push_back('-');
				cost += delC();
			}
		}

		else if(l1 == 1 || l2 == 1) {
			pair<string, string> temp = stringOne(s1, s2);
			te1 = temp.first;
			te2 = temp.second;
		}

		//main divide and conquer
		else {
			int ymid = l2/2;

			vector<int> ScoreL = SpaceEfficientAlignment(s1, s2.substr(0, ymid));
			vector<int> ScoreR = SpaceEfficientAlignment(rever(s1), rever(s2.substr(ymid, l2-ymid)));

			int xmid = minimize(ScoreL, ScoreR, l1);

			cout << " q = "<<xmid<<endl;

			pair<string, string> temp = GainAlignment(s1.substr(0, xmid), s2.substr(0, ymid));
			te1 = temp.first; te2 = temp.second;
			cout<<"s1 = "<< te1 <<"   s2 = "<< te2<<endl;
			temp = GainAlignment(s1.substr(xmid, l1-xmid), s2.substr(ymid, l2-ymid));
			te1 += temp.first; te2 += temp.second;
			cout<<"s1 = "<< te1 <<"   s2 = "<< te2<<endl;
		}

		return make_pair(te1, te2);
	}


int main() {
	string s1, s2;
	cin >> s1 >> s2;
	pair<string, string> temp = GainAlignment(s1, s2);
	cout << temp.first << "\n";
	cout << temp.second << "\n";
	cout << "cost = " << cost << "\n";
}