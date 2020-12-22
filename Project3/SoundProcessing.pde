BufferedReader in;
PrintWriter out;
int ch=2, n=0, iteration=0, sigsize=0;
float alpha=0.00002, c=340, t=0.0000227, h=0.015, F=523;
PVector mic = new PVector(100,150);

float Pixel[][] = new float[1000/5+3][1000/5+3];
float nPixel[][] = new float[1000/5+3][1000/5+3];
float mPixel[][] = new float[1000/5+3][1000/5+3];
int Wall[][] = new int[1000/5+3][1000/5+3];
float signal[] = new float[44100*10];
float Laplacian(int i, int j, boolean useold){
  float Dv;
  if(useold) Dv=mPixel[i-1][j]+mPixel[i+1][j]+mPixel[i][j-1]+mPixel[i][j+1]-4*mPixel[i][j];
  else Dv=Pixel[i-1][j]+Pixel[i+1][j]+Pixel[i][j-1]+Pixel[i][j+1]-4*Pixel[i][j];
  return Dv/(h*h); 
}

void setup(){
  size(1000,1000); // 5*5 pixel = 1.5cm * 1.5cm
  frameRate(1000);
  /*in = createReader("hello.txt");
  String line; 
  try{
    while((line=in.readLine())!=null){
      signal[sigsize] = int(line); sigsize++;
    }
  }catch(IOException e){ e.printStackTrace(); }
  //out = createWriter("Chul.txt");*/
  for(int i=1; i<=200; i++) for(int j=1; j<=200; j++){
    //if(625<=(i-100)*(i-100)+(j-100)*(j-100) && (i-100)*(i-100)+(j-100)*(j-100)<=900) Wall[i][j]=3;
  }
}


void draw(){
  smooth(); iteration++;
  if(iteration<50){
    Pixel[100][50]=2000*sin(2*PI*F*iteration/(11025)); //5*signal[iteration];
    //Pixel[100][50]=2000*sin(3*PI*F*iteration/(11025));
  }
  for(int i=1; 5*i<=width; i++) for(int j=1; 5*j<height; j++){
     //if(Wall[i][j]==1) c=200; else c=340;
     nPixel[i][j] = 2*Pixel[i][j]+(c*c*t*t+c*alpha*t)*Laplacian(i,j,false);
     nPixel[i][j] -= mPixel[i][j] + c*alpha*t*Laplacian(i,j,true);
     // WAll effect here
     int K=2*i+j, L=2*i-j; 
    if(j==50 && (i<95 || 105<i)) Wall[i][j]=3;
    if(50<j && j<150 && ((228<K&&K<232) || (168<L&&L<172))) Wall[i][j]=3;
  }for(int i=1; 5*i<=width; i++) for(int j=1; 5*j<=height; j++){
     mPixel[i][j] = Pixel[i][j]; Pixel[i][j] = nPixel[i][j];  
     if(i==1){ Pixel[i][j]=Pixel[i+1][j]; }
     if(j==1){ Pixel[i][j]=Pixel[i][j+1]; }
     if(i==200){ Pixel[i][j]=Pixel[i-1][j]; }
     if(j==200){ Pixel[i][j]=Pixel[i][j-1]; } 
     if(Wall[i][j]==2) Pixel[i][j] *= 0.93; // Transmission Ratio
     if(Wall[i][j]==3) Pixel[i][j] = 0;
     if(Pixel[i][j]<0) stroke(abs(Pixel[i][j]),0,0); 
     else stroke(0,0,Pixel[i][j]); 
     strokeWeight(5); 
     if(Wall[i][j]>0) stroke(200); else strokeWeight(7); 
     point(5*i,5*j);
  }//int Result = round(Pixel[(int)mic.x][(int)mic.y]);
  //out.println((Result)+" "+(Result)); //println(iteration);
  stroke(200); point(mic.x*5,mic.y*5);
  //line(500,500,0,500); line(500,500,500,0);
  //noFill(); strokeWeight(2); circle(500,500,60*5); circle(500,500,50*5);
}
