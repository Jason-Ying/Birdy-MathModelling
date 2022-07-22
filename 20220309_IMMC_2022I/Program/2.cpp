#include<bits/stdc++.h>

#define A 9
#define R 14+1 
#define C 10

#define PSG 95
#define PSGALL 100000

#define TESTS 50

#define FREQ 1
#define STEP 5
#define BAG 0.9

#define FIGTEST 1
#define FIGTIME1 20
#define FIGTIME2 40
#define FIGTIME3 80
#define FIGTIME4 160
#define FIGTIME5 300
#define FIGMODE false

using namespace std;

// =========
// variables
// =========

// ========== general ==========
struct passenger{
	bool hasBag;
	int st_A,st_R,st_C,stat;
	// 0 waiting 1 walking 2 baggage 3 entering 4 in seat 5 quitting 6 quitting(returning)
	// 7+ wait 100 waitend
	// -10 walking -9 taking bag -8 in seat
}pass[PSGALL];

int seat[A][R][C];
int ail[A][R];

// ========== boarding ==========
int insert_it,cnt[TESTS];
double avg,stdevp;
int cnt_C[A]={3,1,6,1,6,1,6,1,3};

// ========== disembarking ==========
int cnt_dis[TESTS];
double avg_dis,stdevp_dis;

// =========
// functions
// =========

// ========== general ==========
// random
int genRand(int start,int end){
	return (rand()%(end-start+1))+start;
}

// debug
void printStat(){
	for(int i=0;i<PSG;i++)cout<<pass[i].stat<<" ";
	cout<<endl;
}
void printAil(){
	for(int a=1;a<A;a+=2)
		for(int i=0;i<R;i++)
			cout<<ail[a][i]<<" ";
	cout<<endl;
}
void printSeatAil(){
	cout<<"==========\n";
	for(int a=0;a<A;a++){
		if(a%2==0){
			for(int c=0;c<cnt_C[a];c++){
				cout<<"seat ";
				for(int r=0;r<R;r++)
					cout<<seat[a][r][c]<<" ";
				cout<<endl;
			}
		}
		else{
			cout<<"aisle ";
			for(int r=0;r<R;r++)
				cout<<ail[a][r]<<" ";
		}
	}
	cout<<"\n==========\n";
}
void printAilStat(){
	for(int a=1;a<A;a+=2)
		for(int i=0;i<R;i++)
			cout<<pass[ail[a][i]].stat<<" ";
	cout<<endl;
}

// ========== boarding ==========
// check
bool isBlocked(int a,int r){
	for(int i=0;i<cnt_C[a];i++)
		if(pass[seat[a][r][i]].stat==5)return true;
	return false;
}
bool checkDone(){
	for(int i=1;i<A;i+=2)
		for(int j=0;j<R;j++)
			if(ail[i][j]!=-1) return false;
	return true;
}

// ocp for easy getback
int ocp_it=1000;
void ocp(int a,int r,int t){
	ail[a][r]=ocp_it;
	pass[ail[a][r]].stat=100-t;
	ocp_it++;
}
void add_ocp(){
	for(int a=1;a<A;a+=2){
		for(int i=0;i<R;i++){
			if(pass[ail[a][i]].stat>=7)pass[ail[a][i]].stat++;
			if(pass[ail[a][i]].stat>=100){
				pass[ail[a][i]].stat=0;
				ail[a][i]=-1;
			}
		}
	}
}

// init
void init(){
	insert_it=0;
	ocp_it=1000;
	memset(ail,-1,sizeof(ail));
	memset(seat,-1,sizeof(seat));
}

// ========== disembarking ==========
void init_dis(){
	memset(ail,-1,sizeof(ail));
	for(int a=0;a<A;a+=2)
		for(int r=0;r<R;r++)
			for(int c=0;c<cnt_C[a];c++)
				if(pass[seat[a][r][c]].stat==4) pass[seat[a][r][c]].stat=-8;
}

int main(){
	freopen("in2.in","r",stdin);
	
	// ========================================
	//                boarding
	// ========================================
	
	for(int T=0;T<TESTS;T++){
		for(int i=0;i<PSG;i++){
			cin>>pass[i].st_A>>pass[i].st_R>>pass[i].st_C;
			pass[i].st_A--,pass[i].st_R--,pass[i].st_C--;
		}
		init();
		while(!checkDone()||!cnt[T]){
//			if(T==1)printSeatAil();
			pass[-1].stat=0;
			add_ocp();
			cnt[T]++;
			if(insert_it<PSG&&(cnt[T]%FREQ==1||FREQ==1)){ // insert passengers
				if((pass[insert_it].st_C>=cnt_C[pass[insert_it].st_A]/2&&pass[insert_it].st_A!=A-1)||pass[insert_it].st_A==0){ // from left aisle
					if(ail[pass[insert_it].st_A+1][0]==-1){
						ail[pass[insert_it].st_A+1][0]=insert_it;
						pass[ail[pass[insert_it].st_A+1][0]].stat=1;
						insert_it++;
					}
				}
				else{ // from right aisle
					if(ail[pass[insert_it].st_A-1][0]==-1){
						ail[pass[insert_it].st_A-1][0]=insert_it;
						pass[ail[pass[insert_it].st_A-1][0]].stat=1;
						insert_it++;
					}
				}
			}
			for(int a=1;a<A;a+=2){
				for(int i=0;i<R;i++){ // restoreClearBlock
					if(ail[a][i]!=-1&&(pass[ail[a][i]].stat==5||pass[ail[a][i]].stat==3)&&!isBlocked(pass[ail[a][i]].st_A,pass[ail[a][i]].st_R)){
						if(pass[ail[a][i]].stat==5&&i!=pass[ail[a][i]].st_R&&ail[a][pass[ail[a][i]].st_R]==-1)ocp(a,pass[ail[a][i]].st_R,2);
						seat[pass[ail[a][i]].st_A][pass[ail[a][i]].st_R][pass[ail[a][i]].st_C]=ail[a][i];
						pass[ail[a][i]].stat=4;
						ail[a][i]=-1;
					} 
				}
				for(int i=0;i<R;i++){ // baggage -> entering -> clearBlock
					int row=pass[ail[a][i]].st_R,column=pass[ail[a][i]].st_C,area=pass[ail[a][i]].st_A;
					if(ail[a][i]!=-1&&(pass[ail[a][i]].stat==2||pass[ail[a][i]].stat==3)){
						pass[ail[a][i]].stat=3;
						if(area<a){ // to right
							bool flag=true;
							for(int j=cnt_C[area]-1;j>=max(0,column+1);j--){
								if(seat[area][row][j]==-1)continue;
								flag=false;
								if(j==cnt_C[area]-1){
									if(ail[a][row+1]==-1&&ail[a][row-1]==-1){
										if(genRand(0,1)==0){
											pass[seat[area][row][j]].stat=5;
											ail[a][row-1]=seat[0][row][j];
											seat[area][row][j]=-1;
										}
										if(genRand(0,1)==1){
											pass[seat[area][row][j]].stat=5;
											ail[a][row+1]=seat[area][row][j];
											seat[area][row][j]=-1;
										}
									}
									else if(ail[a][row+1]==-1){
										pass[seat[area][row][j]].stat=5;
										ail[a][row+1]=seat[area][row][j];
										seat[area][row][j]=-1;
									}
									else if(ail[a][row-1]==-1){
										pass[seat[area][row][j]].stat=5;
										ail[a][row-1]=seat[area][row][j];
										seat[area][row][j]=-1;
									}
									else if(row-2>=0&&ail[a][i]!=-1&&pass[ail[a][i]].stat==3&&pass[ail[a][row-1]].stat==5&&pass[ail[a][row-1]].st_R==row&&ail[a][row-2]==-1){
										pass[seat[area][row][j]].stat=5;
										ail[a][row-2]=ail[a][row-1];
										ail[a][row-1]=seat[area][row][j];
										seat[area][row][j]=-1;
										
									}
									else if(row+2<=R&&ail[a][i]!=-1&&pass[ail[a][i]].stat==3&&pass[ail[a][row+1]].stat==5&&pass[ail[a][row+1]].st_R==row&&ail[a][row+2]==-1){
										pass[seat[area][row][j]].stat=5;
										ail[a][row+2]=ail[a][row+1];
										ail[a][row+1]=seat[area][row][j];
										seat[area][row][j]=-1;
									}
								}
								else if(seat[area][row][j+1]==-1){
									pass[seat[area][row][j]].stat=5;
									seat[area][row][j+1]=seat[area][row][j];
									seat[area][row][j]=-1;
								}
							}
							if(flag){
								seat[area][row][column]=ail[a][i];
								pass[ail[a][i]].stat=4;
								ail[a][i]=-1;
							}
						}
						else{ // to left
							bool flag=true;
							for(int j=0;j<=min(cnt_C[area]-1,column-1);j++){
								if(seat[area][row][j]==-1)continue;
								flag=false;
								if(j==0){
									if(ail[a][row+1]==-1&&ail[a][row-1]==-1){
										if(genRand(0,1)==0){
											pass[seat[area][row][j]].stat=5;
											ail[a][row-1]=seat[area][row][j];
											seat[area][row][j]=-1;
										}
										if(genRand(0,1)==1){
											pass[seat[area][row][j]].stat=5;
											ail[a][row+1]=seat[area][row][j];
											seat[area][row][j]=-1;
										}
									}
									else if(ail[a][row+1]==-1){
										pass[seat[area][row][j]].stat=5;
										ail[a][row+1]=seat[area][row][j];
										seat[area][row][j]=-1;
									}
									else if(ail[a][row-1]==-1){
										pass[seat[area][row][j]].stat=5;
										ail[a][row-1]=seat[area][row][j];
										seat[area][row][j]=-1;
									}
									else if(ail[a][row-1]!=-1&&pass[ail[a][row-1]].stat==5&&pass[ail[a][row-1]].st_R==row&&ail[a][row-2]==-1){
										pass[seat[area][row][j]].stat=5;
										ail[a][row-2]=ail[a][row-1];
										ail[a][row-1]=-1;
										ail[a][row-1]=seat[area][row][j];
										seat[area][row][j]=-1;
										
									}
									else if(ail[a][row-1]!=-1&&pass[ail[a][row+1]].stat==5&&pass[ail[a][row+1]].st_R==row&&ail[a][row+2]==-1){
										pass[seat[area][row][j]].stat=5;
										ail[a][row+2]=ail[a][row+1];
										ail[a][row+1]=-1;
										ail[a][row+1]=seat[1][row][j];
										seat[area][row][j]=-1;
									}
								}
								else if(seat[2][row][j+1]==-1){
									pass[seat[area][row][j]].stat=5;
									seat[area][row][j-1]=seat[area][row][j];
									seat[area][row][j]=-1;
								}
							}
							if(flag){
								seat[area][row][column]=ail[a][i];
								pass[ail[a][i]].stat=4;
								ail[a][i]=-1;
							}
						}
					}
				}
				for(int i=R-1;i>=0;i--){ // walking -> baggage/move
					if(ail[a][i]!=-1&&pass[ail[a][i]].stat==1){
						if(i==pass[ail[a][i]].st_R){
							if(genRand(1,10)<=BAG*10) pass[ail[a][i]].stat=2,pass[ail[a][i]].hasBag=true;
							else pass[ail[a][i]].stat=3; // no baggage
						}
						else if(ail[a][i+1]==-1) ail[a][i+1]=ail[a][i],ail[a][i]=-1;
					}
				}
			}
			// ===== FIG OUTPUT =====
			if(FIGMODE&&T==FIGTEST&&(cnt[T]==FIGTIME1||cnt[T]==FIGTIME2||cnt[T]==FIGTIME3||cnt[T]==FIGTIME4||cnt[T]==FIGTIME5)){
				for(int i=0;i<PSG;i++){
					bool flagg=true;
					for(int r=0;r<R;r++){
						if(!flagg)break;
						for(int a=0;a<A;a++){
							if(!flagg)break;
							for(int c=0;c<cnt_C[a];c++){
								if(!flagg)break;
								if(ail[a][r]==i){
									cout<<"aisle 2 "<<r+1<<" "<<pass[ail[a][r]].stat<<endl;
									flagg=false;
								}
								else if(seat[a][r][c]==i){
									cout<<"seat "<<a+1<<" "<<r+1<<" "<<c+1<<" "<<pass[seat[a][r][c]].stat<<endl;
									flagg=false;
								}
							}
						}
					}
					if(flagg)cout<<"none"<<endl;
				}
				cout<<endl;
			}
			//===== FIG OUTPUT END =====
		}
//		cout<<cnt[T]<<endl;
		avg+=cnt[T]*STEP;
		
		// ========================================
		//             disembarking               
		// ========================================
		
		init_dis();
		while(!checkDone()||!cnt_dis[T]){
			cnt_dis[T]++;
			for(int a=1;a<A;a+=2) ail[a][0]=-1;
			for(int a=1;a<A;a+=2){
				for(int r=0;r<R;r++){
					if(pass[ail[a][r]].stat==-10&&ail[a][r-1]==-1) ail[a][r-1]=ail[a][r],ail[a][r]=-1;
					if(pass[ail[a][r]].stat==-9) pass[ail[a][r]].stat=-10;
				}
			}
			for(int a=1;a<A;a+=2){
				for(int r=0;r<R;r++){
					if(ail[a][r]!=-1)continue;
					
					int tmpL=0,tmpR=0;
					for(tmpL=0;tmpL<cnt_C[a+1];tmpL++)
						if(seat[a+1][r][tmpL]!=-1)break;
					for(tmpR=cnt_C[a-1]-1;tmpR>=0;tmpR--)
						if(seat[a-1][r][tmpR]!=-1)break;
						
					if(tmpL<cnt_C[a-1]-1-tmpR){
						if(pass[seat[a+1][r][tmpL]].hasBag) pass[seat[a+1][r][tmpL]].stat=-9;
						else pass[seat[a+1][r][tmpL]].stat=-10;
						ail[a][r]=seat[a+1][r][tmpL];
						seat[a+1][r][tmpL]=-1;
					}
					else{
						if(pass[seat[a-1][r][tmpR]].hasBag) pass[seat[a-1][r][tmpR]].stat=-9;
						else pass[seat[a-1][r][tmpR]].stat=-10;
						ail[a][r]=seat[a-1][r][tmpR];
						seat[a-1][r][tmpR]=-1;
					}
				}
			}
		}
//		cout<<cnt_dis[T]<<endl;
		avg_dis+=cnt_dis[T]*STEP;
	}
	
	// boarding results
	avg/=TESTS;
	cout<<"avg: "<<avg<<endl;
	for(int t=0;t<TESTS;t++) stdevp+=(cnt[t]*STEP-avg)*(cnt[t]*STEP-avg);
	stdevp/=TESTS; 
	cout<<"stdevp: "<<sqrt(stdevp)<<endl;
	
	// disembarking results
	avg_dis/=TESTS;
	cout<<"dis-avg: "<<avg_dis<<endl;
	for(int t=0;t<TESTS;t++) stdevp_dis+=(cnt_dis[t]*STEP-avg_dis)*(cnt_dis[t]*STEP-avg_dis);
	stdevp_dis/=TESTS;
	cout<<"dis-stdevp: "<<sqrt(stdevp_dis)<<endl;
	
	return 0;
}
