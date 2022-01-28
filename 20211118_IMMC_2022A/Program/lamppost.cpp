#include<bits/stdc++.h>
#define N 1234
#define M 1234
#define C 8
#define D_MAX 100
#define C_MAX 150
using namespace std;
int n,m,sum,cover[M],i[C],MAX=0;
double MAXX[C];//cover0=none,cover1=1,cover2=2
double cr[N],crr[N];
bool flg;
struct Lamp{int x,y;}lp[N];
struct Road{
	int x,y;
	double car;
}rd[M];
double dis(double x,double y,double xx,double yy){return sqrt((x-xx)*(x-xx)+(y-yy)*(y-yy));}
void solve(){
	flg=0;
	for(int j=1;j<=m;j++){
		int coversum=0;
		memset(cover,0,sizeof(cover));
		for(int k=1;k<=C;k++)
			if(dis(lp[i[k]].x,lp[i[k]].y,rd[j].x,rd[j].y)<=D_MAX)cover[k]++,coversum++;
		if(!coversum){
			flg=1;
			return;
		}
		for(int k=1;k<=C;k++)
			if(cover[k])cr[k]+=rd[j].car/coversum;
	}
}
void solve2(){
	for(int j=1;j<=C;j++){
		if(cr[j]<=C_MAX)crr[j]=1;
		else crr[j]=C_MAX/cr[j];
	}
	double crrr=0;
	for(int j=1;j<=C;j++)crrr+=crr[j]*crr[j];
	crrr=sqrt(crrr/C);
	for(int j=1;j<=C;j++)cout<<i[j]<<" ";
	cout<<endl<<crrr<<endl;
	if(crrr>=MAX){
		MAX=crrr;
		for(int j=1;j<=C;j++)MAXX[j]=i[j];
	}
	memset(crr,0,sizeof(crr));
	memset(cr,0,sizeof(cr));
}
int main(){
	freopen("lamppost.in","r",stdin);
	freopen("lamppost.out","w",stdout);
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>lp[i].x>>lp[i].y;
	for(int i=1;i<=m;i++)cin>>rd[i].x>>rd[i].y>>rd[i].car;
	for(i[1]=1;i[1]<=n;i[1]++){
		for(i[2]=i[1]+1;i[2]<=n;i[2]++){
			for(i[3]=i[2]+1;i[3]<=n;i[3]++){
				for(i[4]=i[3]+1;i[4]<=n;i[4]++){
					for(i[5]=i[4]+1;i[5]<=n;i[5]++){
						for(i[6]=i[5]+1;i[6]<=n;i[6]++){
							for(i[7]=i[6]+1;i[7]<=n;i[7]++){
								for(i[8]=i[7]+1;i[8]<=n;i[8]++){
//									for(i[9]=i[8]+1;i[9]<=n;i[9]++){
										solve();
										if(flg)continue;
										solve2();
//									}
								}
							}
						}
					}
				}
			}
		}
	}
	return 0;
}
