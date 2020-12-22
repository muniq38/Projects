
#include <bits/stdc++.h>
#define WIDTH 2184
#define HEIGHT 1920
#define HEADER 54
using namespace std;
typedef unsigned char uc;
typedef pair<int,int> pint;
struct RGB{
	uc r; uc g; uc b;
	RGB(){
		r=0; g=0; b=0;
	}RGB(uc A, uc B, uc C){
		r=C; g=B; b=A;
	}bool Eq(RGB A){
		if(-100 < r-A.r && r-A.r < 100)
		if(-100 < g-A.g && g-A.g < 100)
		if(-100 < b-A.b && b-A.b < 100) return true;
		return false;
	}void Cp(RGB A){
		r=A.r; g=A.g; b=A.b;
	}
};

RGB Board[HEIGHT+2][WIDTH+2];
RGB white = RGB(255,255,255);
RGB black = RGB(0,0,0);
queue<pint> Q; 
int Graph[1000][1000]; // Num < 400
vector< pair<int,int> > Edge;
map<string,int> EvS; // Eval Storage
int Vis[HEIGHT+2][WIDTH+2]={};
int BPix=15, Num=0, K, p=800, iter=0, Cut=7;
int ITER=500, x, y, keep=5; // Pixel of black border of map
int Add[8][2] = {{-1,0},{1,0},{0,-1},{0,1},{-1,1},{-1,-1},{1,-1},{1,1}};

void BFS(RGB Color){
	pint T = Q.front(); Q.pop();
	int X = T.first, Y = T.second, a, b;
	for(int i=0; i<8; i++){
		a = Add[i][0]; b = Add[i][1];
		if(!Vis[X+a][Y+b]){
			if(!Board[X+a][Y+b].Eq(black)){
				Q.push({X+a,Y+b}); Vis[X+a][Y+b]=Num; Board[X+a][Y+b].Cp(Color);
			}else if(0<X+a*BPix && X+a*BPix<=HEIGHT && 0<Y+b*BPix && Y+b*BPix<=WIDTH)
			if(Vis[X+a*BPix][Y+b*BPix]){
				Graph[Vis[X+a*BPix][Y+b*BPix]][Vis[X][Y]]++; // was =1, but change to ++
				Graph[Vis[X][Y]][Vis[X+a*BPix][Y+b*BPix]]++; // if Graph value <30, then touching vertex
			} 
		}
	}
}

int Eval(string& a){ // Eval : O(Num^2)  
	int Cnt=0; 
	for(int i=1; i<=Num; i++) for(int j=i+1; j<=Num; j++){
		if(Graph[i][j] && a[i]==a[j]) Cnt++;
	}return Cnt;
}

bool Comp(string& a, string& b){
	return EvS[a]<EvS[b]; // EvS에 유전자가 들어있을 것이라 장담함 
} 

void Mutate(string &a){ // Mutate : O(EK)
	if(rand()%100==1) for(int i=1; i<=Num; i++) a[i]='A'+rand()%K;
	for(int i=0; i<Edge.size(); i++){
		int x = Edge[i].first, y = Edge[i].second;
		if(a[x]==a[y]){ // Nothing happens if a is perfect
			vector<int> OK(K,1); // 
			for(int k=1; k<=Num; k++) if(Graph[k][y]) OK[a[k]-'A']=0;
			for(int k=0; k<K; k++) if(OK[k]) a[y]='A'+k;
			if(a[x]!=a[y]) continue;
			OK = vector<int>(K,1); 
			for(int k=1; k<=Num; k++) if(Graph[x][k]) OK[a[k]-'A']=0;
			for(int k=0; k<K; k++) if(OK[k]) a[x]='A'+k;
			if(a[x]==a[y]) a[y]='A'+rand()%K; 
		}
	}//I made ch[i] of last iteration to Mutate and give one more chance.
}

string Crossover(string &a, string& b){
	string ans; ans.resize(Num+1);
	int ind=rand()%Num+1; // heuristic #1
	ans.replace(1,ind,a.substr(1,ind));
	ans.replace(ind+1,Num,b.substr(ind+1,Num));
	Mutate(ans); return ans;
}

int main(){
	FILE *F1 = fopen("start.bmp", "rb");
	FILE *F2 = fopen("end.bmp", "wb");
	int i, j; srand(time(NULL));
	for(i=0; i<HEADER; i++) putc(getc(F1),F2); // scan part
	for(i=1; i<=HEIGHT; i++) for(j=1; j<=WIDTH; j++)
	Board[i][j] = RGB(getc(F1),getc(F1),getc(F1));
	RGB Color[6];
	for(i=0; i<6; i++) Color[i]=RGB(rand()%256,rand()%256,rand()%256);
	
	for(i=1; i<=HEIGHT; i++) for(j=1; j<=WIDTH; j++){ // BFS processing part
		if(!Board[i][j].Eq(black) && !Vis[i][j]){	
			//printf("%d %d %d\n", Num, i, j);
			Num++; Q.push({i,j}); Vis[i][j]=Num; 
			Board[i][j]=RGB(100+rand()%156,100+rand()%156,100+rand()%156);
			while(!Q.empty()) BFS(Board[i][j]);
		}
	}
	
	for(i=0; i<=Num; i++){ // Cutting Vertex Met in Graph Matrix part
		Graph[i][i]=0;
		for(j=i+1; j<=Num; j++) if(Graph[i][j]<Cut){ Graph[i][j]=0; Graph[j][i]=0; }
	}for(i=1; i<=Num; i++) for(j=i+1; j<=Num; j++) 
	if(Graph[i][j]) Edge.push_back({i,j}); 
	
	printf("V = %d, E = %d, p = %d, r = 1%%\n", Num, Edge.size(), p); 
	printf("K색 칠하기 : "); scanf("%d", &K); 
	vector<string> chromo(p), temp(p);
	string Ans; Ans.resize(Num+1); 
	vector<int> proba; // testing the best probability..
	for(i=0; i<p; i++) for(j=0; j<100-i; j++) proba.push_back(i); // this was best, 1000/(i+1), (100-i)*(100-i)
	//if good chs are emphasized too much, the program can fall into local minimum
	for(i=0; i<p; i++){
		chromo[i].resize(Num+1);
		for(j=1; j<=Num; j++) chromo[i][j]='A'+rand()%K;
	}sort(chromo.begin(), chromo.end(), Comp);
	do{
		for(i=0; i<keep; i++) temp[i].replace(0,Num+1,chromo[i]); // keeping the best solution
		for(i=keep; i<p; i++){
			x = rand()%proba.size(); x = proba[x];
			y = rand()%proba.size(); y = proba[y];
			temp[i].replace(0,Num+1,Crossover(chromo[x],chromo[y]));
		}for(i=0; i<p; i++) EvS[temp[i]]=Eval(temp[i]);
		sort(temp.begin(), temp.end(), Comp);
		for(i=0; i<p; i++){ swap(chromo[i],temp[i]); EvS.erase(chromo[i]); }
		iter++; printf("%d %d\n", iter, Eval(chromo[0]));
	}while(Eval(chromo[0]) && iter<ITER);
	for(i=p-1; i>=0; i--) cout << chromo[i] << " " << Eval(chromo[i]) << endl;
	Ans.replace(0,Num+1,chromo[0]);
	cout << endl << "Total iteration : " << iter << endl; 
	
	for(i=1; i<=HEIGHT; i++) for(j=1; j<=WIDTH; j++){ // print part
		int num = Vis[i][j]; 
		if(num<=0 || num>Num){ 
			putc(black.b,F2); putc(black.g,F2); putc(black.r,F2); 
			continue; 
		}
		/*putc(Board[i][j].b,F2);
		putc(Board[i][j].g,F2);
		putc(Board[i][j].r,F2); // */
		int cr = (int)Ans[num]-'A';
		putc(Color[cr].b,F2);
		putc(Color[cr].g,F2);
		putc(Color[cr].r,F2); // */
	}
	return 0;
}

