#include <bits/stdc++.h>
using namespace std;
int main()
{
	srand(time(0));

	char s[100];
	int N[8] = {10, 100,500, 1000,3000, 5000,7000,10000}; //N of each testing file
	for (int cases = 0; cases < 8; cases++)
	{
		sprintf(s,"mkdir test%d",cases); 
		system(s);                               //create these folders
		sprintf(s, "test%d/data.in",cases);     
		freopen(s, "w", stdout);                //Redirect the standard output stream to the data.in file.
		int n = N[cases];
		int m=n/10+rand()%(n-n/10);           //We limit the range of m from n/10 to n.
		cout<<n<<' '<<m<<endl;
		for(int i=0;i<n;i++)
		{
			int a,b;
			a=1+rand()%(m-1);                //We limit the range of a from 1 to m, since the rectangles can be dropped
			b=1+rand()%(m*2);				 //We limit the range of a from 1 to m*2
			cout<<a<<' '<<b<<endl;
		}
		fclose(stdout);
		sprintf(s, "test%d/Readme.txt",cases);
		freopen(s, "w", stdout);
		cout<<"This testing file is generated randomly.\n"<<"n="<<n<<"   m="<<m<<"\n";
		fclose(stdout);
		
	}
	
	return 0;
}