#include<bits/stdc++.h>
#define S 6
#define R 33+1
#define C 10
#define PSG 189
#define PSGALL 100000
using namespace std;
int cnt=0;
int seat[S][R][C];
struct aisle{
	int psg;
}ail[R];
int cnt_C[S]={3,-1,3};
struct passenger{
	int st_S,st_R,st_C,stat;//0 waiting 1 walking 2 baggage 3 entering 4 in seat 5 quitting 6 quitting(returning) 7+ wait 100 waitend
}pass[PSGALL];
bool isBlocked(int a,int r){
	for(int i=0;i<cnt_C[a];i++)
		if(pass[seat[a][r][i]].stat==5)return true;
	return false;
}
bool checkDone(){
	for(int i=0;i<R;i++)
		if(ail[i].psg!=-1) return false;
	return true;
}
int genRand(int start,int end){
	return (rand()%(end-start+1))+start;
}
int ocp_it=1000;
void ocp(int r,int t){
	ail[r].psg=ocp_it;
	pass[ail[r].psg].stat=100-t;
	ocp_it++;
}
void add_ocp(){
	for(int i=0;i<R;i++){
		if(pass[ail[i].psg].stat>=7)pass[ail[i].psg].stat++;
		if(pass[ail[i].psg].stat>=100){
			pass[ail[i].psg].stat=0;
			ail[i].psg=-1;
		}
	}
}
void printStat(){
	for(int i=0;i<PSG;i++)cout<<pass[i].stat<<" ";
	cout<<endl;
}
void printAil(){
	for(int i=0;i<R;i++)cout<<ail[i].psg<<" ";
	cout<<endl;
}
void printAilStat(){
	for(int i=0;i<R;i++)cout<<pass[ail[i].psg].stat<<" ";
	cout<<endl;
}
void init(){
	for(int i=0;i<R;i++)ail[i].psg=-1;
	for(int i=0;i<S;i++)
		for(int j=0;j<R;j++)
			for(int k=0;k<C;k++)
				seat[i][j][k]=-1;
}
int main(){
	freopen("in.in","r",stdin);
	freopen("out.out","w",stdout);
	for(int T=0;T<50;T++){
		for(int i=0;i<189;i++){
			cin>>pass[i].st_S>>pass[i].st_R>>pass[i].st_C;
			pass[i].st_S--,pass[i].st_R--,pass[i].st_C--;
		}
		int insert_it=0;
		init();
		cnt=0;
		while(!checkDone()||!cnt){
			pass[-1].stat=0;
			add_ocp();
			cnt++;
			if(insert_it<=188&&ail[0].psg==-1&&cnt%1==0){ // insertPassenger
				ail[0].psg=insert_it;
				pass[ail[0].psg].stat=1;
				insert_it++;
			}
			for(int i=0;i<R;i++){ // restoreClearBlock
				if(ail[i].psg!=-1&&(pass[ail[i].psg].stat==5||pass[ail[i].psg].stat==3)&&!isBlocked(pass[ail[i].psg].st_S,pass[ail[i].psg].st_R)){
					if(pass[ail[i].psg].stat==5&&i!=pass[ail[i].psg].st_R)ocp(pass[ail[i].psg].st_R,2);
					seat[pass[ail[i].psg].st_S][pass[ail[i].psg].st_R][pass[ail[i].psg].st_C]=ail[i].psg;
					pass[ail[i].psg].stat=4;
					ail[i].psg=-1;
				} 
			}
			for(int i=0;i<R;i++){ // baggage -> entering -> clearBlock
				int row=pass[ail[i].psg].st_R,column=pass[ail[i].psg].st_C,section=pass[ail[i].psg].st_S;
				if(ail[i].psg!=-1&&(pass[ail[i].psg].stat==2||pass[ail[i].psg].stat==3)){
					pass[ail[i].psg].stat=3;
					if(section==0){
						bool flag=true;
						for(int j=cnt_C[0]-1;j>=max(0,column+1);j--){
							if(seat[section][row][j]==-1)continue;
							flag=false;
							if(j==cnt_C[0]-1){
								if(ail[row+1].psg==-1&&ail[row-1].psg==-1){
									if(genRand(0,1)==0){
										pass[seat[0][row][j]].stat=5;
										ail[row-1].psg=seat[0][row][j];
										seat[0][row][j]=-1;
									}
									if(genRand(0,1)==1){
										pass[seat[0][row][j]].stat=5;
										ail[row+1].psg=seat[0][row][j];
										seat[0][row][j]=-1;
									}
								}
								else if(ail[row+1].psg==-1){
									pass[seat[0][row][j]].stat=5;
									ail[row+1].psg=seat[0][row][j];
									seat[0][row][j]=-1;
								}
								else if(ail[row-1].psg==-1){
									pass[seat[0][row][j]].stat=5;
									ail[row-1].psg=seat[0][row][j];
									seat[0][row][j]=-1;
								}
								else if(ail[i].psg!=-1&&pass[ail[row-1].psg].stat==5&&pass[ail[row-1].psg].st_R==row&&ail[row-2].psg==-1){
									pass[seat[0][row][j]].stat=5;
									ail[row-2].psg=ail[row-1].psg;
									ail[row-1].psg=-1;
									ail[row-1].psg=seat[0][row][j];
									seat[0][row][j]=-1;
									
								}
								else if(ail[i].psg!=-1&&pass[ail[row+1].psg].stat==5&&pass[ail[row+1].psg].st_R==row&&ail[row+2].psg==-1){
									pass[seat[0][row][j]].stat=5;
									ail[row+2].psg=ail[row+1].psg;
									ail[row+1].psg=-1;
									ail[row+1].psg=seat[0][row][j];
									seat[0][row][j]=-1;
								}
							}
							else if(seat[0][row][j+1]==-1){
								pass[seat[0][row][j]].stat=5;
								seat[0][row][j+1]=seat[0][row][j];
								seat[0][row][j]=-1;
							}
						}
						if(flag){
							seat[section][row][column]=ail[i].psg;
							pass[ail[i].psg].stat=4;
							ail[i].psg=-1;
						}
					}
					else if(section==2){
						bool flag=true;
						for(int j=0;j<=min(cnt_C[2]-1,column-1);j++){
							if(seat[section][row][j]==-1)continue;
							flag=false;
							if(j==0){
								if(ail[row+1].psg==-1&&ail[row-1].psg==-1){
									if(genRand(0,1)==0){
										pass[seat[2][row][j]].stat=5;
										ail[row-1].psg=seat[2][row][j];
										seat[2][row][j]=-1;
									}
									if(genRand(0,1)==1){
										pass[seat[2][row][j]].stat=5;
										ail[row+1].psg=seat[2][row][j];
										seat[2][row][j]=-1;
									}
								}
								else if(ail[row+1].psg==-1){
									pass[seat[2][row][j]].stat=5;
									ail[row+1].psg=seat[2][row][j];
									seat[2][row][j]=-1;
								}
								else if(ail[row-1].psg==-1){
									pass[seat[2][row][j]].stat=5;
									ail[row-1].psg=seat[2][row][j];
									seat[2][row][j]=-1;
								}
								else if(ail[row-1].psg!=-1&&pass[ail[row-1].psg].stat==5&&pass[ail[row-1].psg].st_R==row&&ail[row-2].psg==-1){
									pass[seat[2][row][j]].stat=5;
									ail[row-2].psg=ail[row-1].psg;
									ail[row-1].psg=-1;
									ail[row-1].psg=seat[2][row][j];
									seat[2][row][j]=-1;
									
								}
								else if(ail[row-1].psg!=-1&&pass[ail[row+1].psg].stat==5&&pass[ail[row+1].psg].st_R==row&&ail[row+2].psg==-1){
									pass[seat[2][row][j]].stat=5;
									ail[row+2].psg=ail[row+1].psg;
									ail[row+1].psg=-1;
									ail[row+1].psg=seat[1][row][j];
									seat[2][row][j]=-1;
								}
							}
							else if(seat[2][row][j+1]==-1){
								pass[seat[2][row][j]].stat=5;
								seat[2][row][j+1]=seat[2][row][j];
								seat[2][row][j]=-1;
							}
						}
						if(flag){
							seat[section][row][column]=ail[i].psg;
							pass[ail[i].psg].stat=4;
							ail[i].psg=-1;
						}
					}
				}
			}
			for(int i=R-1;i>=0;i--){ // walking -> baggage/move
				if(ail[i].psg!=-1&&pass[ail[i].psg].stat==1){
					if(i==pass[ail[i].psg].st_R){
						if(genRand(1,10)<=4) pass[ail[i].psg].stat=2;
						else pass[ail[i].psg].stat=3; // no baggage
					}
					else if(ail[i+1].psg==-1) ail[i+1].psg=ail[i].psg,ail[i].psg=-1;
				}
			}
		}
		cout<<cnt<<endl;
	}
	return 0;
}
