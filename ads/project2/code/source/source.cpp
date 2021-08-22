#include <bits/stdc++.h>
#define N 1005
#define M 10050
using namespace std;

int E, V, mx; //E is the number of edges, V is the number of vertices

int tipa[M], tipb[M], mp[M], invmp[M], val[N], tot; //Variable used for relabeling.

int p[N], mark[N], ans1; //Variables used to calculate the answer
int sum, cv, cd, ins[N], vis[N], F[105][105], o[N], tp, ans2;
bitset<105> b[105][105], curb, msk, hm; 

/*
Key for vertex sorting.
*/
bool cmp(int p1, int p2) {
	return val[p1] < val[p2];
}

/*
The structure Edge is used to store edges, where b represents 
adjacent vertices and n represents the next edge. h[] is the label 
that stores the first edge of each vertex.
*/
int h[N], cnt;
struct Edge{int b,n;}e[M];
inline void link(int a, int b) {
	e[++cnt] = (Edge){b,h[a]}, h[a] = cnt;
}

/*
The functions enc() and dec() are an encoder and a decoder to 
relabel vertices.
*/
inline int enc(int t) {
	!mp[t] ? mp[t] = ++tot : 0;
	invmp[ mp[t] ] = t;
	return mp[t];
}

inline int dec(int t) {
	return invmp[t];
}

/*
The main process of this program is DFS (), which is a depth 
first search process.
*/

void dfs(int dep, int cx) {

	//If the recursion reaches the boundary, that is, all the 
	//points have been taken, the answer is updated and returned.
	if (dep == 0) {
		F[cv][cd] = sum;
		b[cv][cd] = curb;
		if (cd > ans1 || (cd == ans1 && sum < ans2)) {
			ans1 = cd;
			ans2 = sum;
			hm = curb;
		}
		return ;
	}

	//There's nothing to expand
	if (cx == 0) return ;	
	
	//Enumerate a vertex and consider adding it to the answer.
	for (int i=cx;i>=(dep==cd ? cx : 1);i--) {
		int u = p[i];
		
		//If this point can be added to the answer, consider adding 
		//it to the answer. Mark the point next to it and mark it in 
		//BitSet.
		if (!vis[u]) {
			vis[u] = 1;
			ins[u] = 1;
			for (int j=h[u];j;j=e[j].n) {
				vis[ e[j].b ]++;
				if (vis[ e[j].b ]) msk[ e[j].b ] = 1;
			}
			sum += val[u]; //Weight h of the currently selected independent set
			curb[u] = 1; //A BitSet is used to mark which points are in the answer.
			msk[u] = 1; //A BitSet is used to mark which points cannot be added to the independent set.

			//Using inequality and evaluation function to judge whether the answer may be better. 
			//Keep going if possible, otherwise stop the search.
			if (sum + F[i-1][dep-1] < F[cv][cd]) {
				if ((msk & b[i-1][dep-1]).count() == 0) {
					F[cv][cd] = sum + F[i-1][dep-1];
					b[cv][cd] = curb | b[i-1][dep-1];
					
					//Update the answer if there is a legal situation.
					if (cd > ans1 || (cd == ans1 && F[cv][cd] < ans2)) {
						ans1 = cd;
						ans2 = F[cv][cd];
						hm = b[cv][cd];
					}
				} else{
					dfs(dep-1, i-1);
				}
				
			}
			
			//Backtracking in depth first search. Remove all previous marks.
			sum -= val[u]; //Weight h of the currently selected independent set
			for (int j=h[u];j;j=e[j].n) {
				vis[ e[j].b ]--; 
				if (!vis[ e[j].b ]) msk[ e[j].b ] = 0;
			}
			vis[u] = 0;
			msk[u] = 0;//A BitSet is used to mark which points cannot be added to the independent set.
			ins[u] = 0;
			curb[u] = 0;//A BitSet is used to mark which points are in the answer.
		}
	}
	return ;
}

int main() {
/*
The following part of the code is used to read in all the input data, 
relabel the input data and complete various initialization operations.
*/
	scanf("%d%d",&E,&V);
	for (int i=1;i<=E;i++) 
		scanf("%d%d",&tipa[i],&tipb[i]);
	
	for (int i=1;i<=V;i++) {
		int x, y;
		scanf("%d%d",&x,&y);
		val[ enc(x) ] = y;
		mx += y;
	}

	srand(mx);
	
	for (int i=1;i<=E;i++)
		if (mp[ tipa[i] ] && mp[ tipb[i] ]) {
			int u = enc(tipa[i]), v = enc(tipb[i]);
			link(u, v);
			link(v, u);
		}
	
//--------------------------------------------------------------	
/*
This part of the code is used to calculate the answer
*/
	for (int i=1;i<=V;i++) p[i] = i;
	if (rand()&1) sort(p+1, p+V+1, cmp);

	memset(F, 127/3, sizeof(F));
	for (int i=0;i<=V;i++) F[i][0] = 0; 
	ans2 = 1<<29;
	for (int i=1;i<=V;i++) 
		for (int j=ans1+1;j>=1;j--) {
			cv = i;
			cd = j;
			//It will not cost much to get the same independent set from fewer points. 
			//Use this to update the initial value.
			if (F[cv-1][cd] < F[cv][cd]) {
				F[cv][cd] = F[cv-1][cd];
				b[cv][cd] = b[cv-1][cd];
			}
			
			//Taking a smaller independent set from the same point set will not cost more. 
			//Use this to update the initial value.
			if (F[cv][cd+1] < F[cv][cd]) {
				F[cv][cd] = F[cv][cd+1];
				b[cv][cd] = b[cv][cd+1];
			}
			
			dfs(cd, cv);
		} 

//-----------------------------------------------------------
/*
This code is used to sort, decode and output the answers.
*/
	cout << ans1 << endl;

	for (int i=1;i<=V;i++) if (hm[i]) o[++tp] = dec(i);
	sort(o+1, o+ans1+1);
	for (int i=1;i<=ans1;i++) printf("%03d%c", o[i], i==ans1?'\n':' ');
	cout << ans2 << endl;
	
	return 0;
}