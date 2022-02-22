#include<bits/stdc++.h>
#include<windows.h>
#include<sstream>
#define TRCNT 1000
#define PRMCNT 4
using namespace std;
double lambda;
double p,maxf,f,S,step,plant_den,minrng;
struct prm{
	double start,end,val;
	double maxval;
}param[PRMCNT];
struct tre{
	double birth;
	double x,y;
	double sigmaN(double t){
		return 50*lambda/t*(p/(t+p)+log(t+p)-log(p)-1);	
	};
	bool inDst(){
		return x>=param[0].val && x<=param[2].val && y>=param[1].val && y<=param[3].val;
	}
}tree[TRCNT];
void cls(string s){
	string scrInit = "Harvest Plan Decision System\nBy MCM/ICM Team 2226737\n=========================================\n";
	system("cls");
	cout<<scrInit<<s<<endl;
	Sleep(500);
}
int main(){
	freopen("tree.dat","r",stdin);
//	freopen("tree.out","w",stdout);
	
	cls("Reading parameters(lambda, p)...");
	cin>>lambda>>p;
	
	cls("Reading scanning range and step:");
	cin>>param[0].start>>param[0].end>>param[1].start>>param[1].end>>step>>minrng;
	param[2].start=param[0].start,param[2].end=param[0].end;
	param[3].start=param[1].start,param[3].end=param[1].end;
	
	int tmp;
	cin>>tmp;
	plant_den=tmp/(param[1].end-param[1].start)/(param[0].end-param[0].end); 
	for(int i=0;i<tmp;i++)cin>>tree[i].birth>>tree[i].x>>tree[i].y;
	
	cls("Calculating...");
//	param[0].val=199,param[1].val=149,param[2].val=221,param[3].val=171;
	for(param[0].val=param[0].start;param[0].val<param[0].end;param[0].val+=step){
		for(param[1].val=param[1].start;param[1].val<param[1].end;param[1].val+=step){
			for(param[2].val=param[0].val+step+minrng;param[2].val<param[2].end;param[2].val+=step){
				for(param[3].val=param[1].val+step+minrng;param[3].val<param[3].end;param[3].val+=step){
					f=0;
					int cnt=0;
					for(int i=0;i<tmp;i++){
						if(tree[i].inDst()){
							cnt++; 
							f+=pow(tree[i].sigmaN(-tree[i].birth)-tree[i].sigmaN(1),2);
						}
					}
					f=sqrt(f/cnt);
					if(f>maxf){
						maxf=f;
						for(int j=0;j<PRMCNT;j++)param[j].maxval=param[j].val;
					}
				}
			}
		}
	}
	
	cout<<maxf<<endl;
	cout<<"Finished.\nOptimal Harvest Area:"<<endl;
	cout<<"x: From "<<param[0].maxval<<" to "<<param[2].maxval<<endl;
	cout<<"y: From "<<param[1].maxval<<" to "<<param[3].maxval<<endl;
	cout<<"Thanks for using."<<endl;
	cout<<"Quitting..."<<endl;
	Sleep(1000);
	system("pause");
	return 0;
}
