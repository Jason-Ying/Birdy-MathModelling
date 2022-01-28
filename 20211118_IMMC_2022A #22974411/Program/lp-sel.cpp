#include<bits/stdc++.h>
#define N 2000
using namespace std;
double lpx[48]={-1,0,0,0,0,0,0,0,0,0,25,25,25,25,25,25,25,25,25,25,25,60,60,106,106,106,106,106,106,106,113,113,113,113,113,127,127,137,196,196,196,240,240,240,240,240,240,245},lpy[48]={
-1,12,57,102,148,193,242,360,383,397,27,53,96,122,138,151,180,208,357,398,360,55,105,111,114,154,194,236,320,436,72,273,303,362,390,57,130,254,91,160,234,40,138,192,274,308,371,425
},MIDX=121,MIDY=216;
double dis(double x,double y,double xx,double yy){return sqrt((x-xx)*(x-xx)+(y-yy)*(y-yy));}
int t=1942,n=8,id[N][N],MAX,MAXI;
double MAXX=1,sum;
int main(){
	freopen("lp-sel-8.out","r",stdin);
//	freopen("lp-sel.out","w",stdout);
	for(int i=1;i<=t;i++){
		sum=0;
		for(int j=1;j<=n;j++)cin>>id[i][j];
		for(int j=1;j<=n;j++)sum+=dis(lpx[id[i][j]],lpy[id[i][j]],MIDX,MIDY);
		if(sum>=MAX)MAX=sum,MAXI=i;
		cout<<i<<": "<<sum<<endl;
	}
	cout<<MAXI<<": "<<MAX<<endl;
	for(int i=1;i<=n;i++)
		cout<<lpx[id[MAXI][i]]<<" "<<lpy[id[MAXI][i]]<<endl;
	return 0;
}
