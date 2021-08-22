#include <bits/stdc++.h>
using namespace std;
int main()
{
	srand(time(0));

	char s[100];
	int N[5] = {573, 5031, 10707, 50307, 99999};
	int M[5] = {10, 100,1000,1000,1000};
	int Maxi[5] = {100,1000,10000,100000,100000};
	for (int cases = 0; cases < 5; cases++)
	{
		sprintf(s,"mkdir test%d",cases);
		system(s);
		sprintf(s, "test%d/data.in",cases);
		freopen(s, "w", stdout);
		int n = N[cases];
		int m = rand()%M[cases];
		while(m<=M[cases]/10)	m = rand()%M[cases];
		cout<<n<<' '<<m<<endl;
		for(int i=0;i<n;i++)
		{
			int ni=rand()%Maxi[cases]+1;
			cout<<ni;
			if(i==n)	cout<<endl;
			else cout<<' ';
		}
		fclose(stdout);
		sprintf(s, "test%d/Readme.txt",cases);
		freopen(s, "w", stdout);
		cout<<"This testing file is generated randomly.\n"<<"n="<<n<<"   m="<<m<<"\n";
		fclose(stdout);
		
	}
	
	return 0;
}