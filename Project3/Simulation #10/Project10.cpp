#include <stdio.h>
#include <bits/stdc++.h>
#define PI 3.141592
using namespace std;
typedef unsigned char byte;

struct WAV
{
  byte ChunkID[4];      //"RIFF"
  byte ChunkSize[4];    //*
  byte Format[4];       //"WAVE"
  byte Subchunk1ID[4];  //"fmt "
  byte Subchunk1Size[4];//*
  byte AudioFormat[2];  //*, 1:pcm(pulse code modulation)
  byte NumChannels[2];  //*
  byte SampleRate[4];   //*
  byte ByteRate[4];     //*
  byte BlockAlign[2];   //*
  byte BitsPerSample[2];//*
  byte Subchunk2ID[4];  //"data"
  byte Subchunk2Size[4];//*
};

struct WAVt
{
  byte ChunkID[4];    //"RIFF"
  int ChunkSize;      //*
  byte Format[4];     //"WAVE"
  byte Subchunk1ID[4];//"fmt "
  int Subchunk1Size;  //*
  short AudioFormat;  //*, 1:pcm(pulse code modulation)
  short NumChannels;  //*
  int SampleRate;     //*
  int ByteRate;       //*
  short BlockAlign;   //*
  short BitsPerSample;//*
  byte Subchunk2ID[4];//"data"
  int Subchunk2Size;  //*
};

//little endian read
int ler(byte x[], int n)
{
  int t=0, s=4-n;
  for(int i=0; i<n; i++)
    t |= (x[i]<<((i+s)*8));
  return t>>(s*8);
}

//헤더 데이터 읽어 오기
WAVt readheader(WAV x)
{
  WAVt t;
  for(int i=0; i<4; i++) t.ChunkID[i]=x.ChunkID[i];
  t.ChunkSize=ler(x.ChunkSize, 4);
  for(int i=0; i<4; i++) t.Format[i]=x.Format[i];
  for(int i=0; i<4; i++) t.Subchunk1ID[i]=x.Subchunk1ID[i];
  t.Subchunk1Size=ler(x.Subchunk1Size, 4);
  t.AudioFormat=ler(x.AudioFormat, 2);
  t.NumChannels=ler(x.NumChannels, 2);
  t.SampleRate=ler(x.SampleRate, 4);
  t.ByteRate=ler(x.ByteRate, 4);
  t.BlockAlign=ler(x.BlockAlign, 2);
  t.BitsPerSample=ler(x.BitsPerSample, 2);
  for(int i=0; i<4; i++) t.Subchunk2ID[i]=x.Subchunk2ID[i];
  t.Subchunk2Size=ler(x.Subchunk2Size, 4);
  return t;
}

//little endian write
void lew(byte *x, int t, int n)
{
  for(int i=0; i<n; i++, t>>=8)
    x[i] = t&0xFF;
}

WAV writeheader(WAVt x)
{
  WAV t;
  for(int i=0; i<4; i++) t.ChunkID[i]=x.ChunkID[i];
  lew(t.ChunkSize, x.ChunkSize, 4);
  for(int i=0; i<4; i++) t.Format[i]=x.Format[i];
  for(int i=0; i<4; i++) t.Subchunk1ID[i]=x.Subchunk1ID[i];
  lew(t.Subchunk1Size, x.Subchunk1Size, 4);
  lew(t.AudioFormat, x.AudioFormat, 2);
  lew(t.NumChannels, x.NumChannels, 2);
  lew(t.SampleRate, x.SampleRate, 4);
  lew(t.ByteRate, x.ByteRate, 4);
  lew(t.BlockAlign, x.BlockAlign, 2);
  lew(t.BitsPerSample, x.BitsPerSample, 2);
  for(int i=0; i<4; i++) t.Subchunk2ID[i]=x.Subchunk2ID[i];
  lew(t.Subchunk2Size, x.Subchunk2Size, 4);
  return t;
}

int pcm[44100000][4]; //데이터 저장용 배열, 최대1000초

const int width=200, height=200, micx=100, micy=115, F=523;
double alpha=0.00002, c=340, t=(double)1/44100, h=0.02, Amp=3;
double Pixel[width+3][height+3];
double nPixel[width+3][height+3];
double mPixel[width+3][height+3];
int Wall[width+3][height+3];
double Laplacian(int i, int j, bool useold){
	double Dv;
	if(useold) Dv=mPixel[i-1][j]+mPixel[i+1][j]+mPixel[i][j-1]+mPixel[i][j+1]-4*mPixel[i][j];
	else Dv=Pixel[i-1][j]+Pixel[i+1][j]+Pixel[i][j-1]+Pixel[i][j+1]-4*Pixel[i][j];
	return Dv/(h*h); 
}

int main()
{
  FILE *fp1=fopen("Last Part.wav","rb");
  FILE *fp2=fopen("hello.wav","wb");
  //FILE *fp3=fopen("Chul.txt","r");
  //FILE *fp4=fopen("hello.txt","w");
  WAV head; WAVt headt;
  fread(&head, sizeof(head), 1, fp1);  //헤더 읽기
  headt=readheader(head);              //헤더 데이터를 값으로 변환
    
  //파일 크기나 속성을 바꾸고 싶다면 여기서 처리!!
  head=writeheader(headt);             //헤더에 저장될 값을 헤더용 데이터로 변환
  fwrite(&head, sizeof(head), 1, fp2); //헤더 기록 

  //사운드 데이터 읽어들이기 
  int n=(headt.Subchunk2Size)/headt.BlockAlign; //샘플링 데이터 블록 개수 계산
  printf("%d\n", n);
  int ch=headt.NumChannels;             //채널 개수
  int size=headt.BlockAlign/ch;        //한 채널당 블록 크기(바이트) 계산
  byte buffer[4];                               //데이터를 읽어들일 임시 버퍼
  
  //사운드 데이터 읽어 R에 저장하기 
  int R[n];
  for(int i=0; i<n; i++)
  {
  	for(int j=0; j<ch; j++) 
	fread(buffer, size, 1, fp1);
    R[i]=ler(buffer, size);
    //fprintf(fp4,"%d\n", R[i]); // fp4 : for processing simulation
  }
  
  char Rdy;
  printf("are you ready?");
  scanf("%c", &Rdy); if(Rdy=='n') return 0;
  
  // Initializing FDTD
  memset(Pixel,0,sizeof(Pixel));
  memset(Pixel,0,sizeof(nPixel));
  memset(Pixel,0,sizeof(mPixel));
  memset(Pixel,0,sizeof(mPixel));
  
  for(int iter=0; iter<n; iter++){
  	// making sound here
	Pixel[100][85]=Amp*R[iter]; // Amp : Volume up
  	if(!(iter%100)) printf("%d\n", iter); // check progress
	for(int i=1; i<=width; i++) for(int j=1; j<=height; j++){
	  nPixel[i][j] = 2*Pixel[i][j]+(c*c*t*t+c*alpha*t)*Laplacian(i,j,false);
	  nPixel[i][j] -= mPixel[i][j]+c*alpha*t*Laplacian(i,j,true);
	  // add any wall effect after here
	  int S = (int)(5*sin(2*PI*i/10));
	  Wall[i][j]=0;
	  if(iter>2*n/3 && 100+S-3<j && j<100+S+3) Wall[i][j]=2; 
	  else if(iter>n/3 && j<103 && j>97) Wall[i][j]=2;
	}
	for(int i=1; i<=width; i++) for(int j=1; j<=height; j++){
  	  mPixel[i][j] = Pixel[i][j]; Pixel[i][j] = nPixel[i][j];
  	  // absorb wave, reduce reflection
	  if(i==1) Pixel[i][j]=Pixel[i+1][j];
  	  if(j==1) Pixel[i][j]=Pixel[i][j+1];
  	  if(i==width) Pixel[i][j]=Pixel[i-1][j];
  	  if(j==height) Pixel[i][j]=Pixel[i][j-1]; 
  	  if(Wall[i][j]==2) Pixel[i][j] *= 0.98; // Transmission Rate 
  	  if(Wall[i][j]==3) Pixel[i][j] = 0; // Full Reflection
	}
	pcm[iter][0]=pcm[iter][1]=Pixel[micx][micy];
  }
  
  //사운드 데이터 파일에 쓰기 
  for(int i=0; i<n; i++) for(int j=0; j<ch; j++)
  {
    lew(buffer, pcm[i][j], size);
    fwrite(buffer, size, 1, fp2);
  }return 0;
}


