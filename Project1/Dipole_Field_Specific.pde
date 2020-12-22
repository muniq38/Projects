int Size=4, Delta=4, Gap=4;
float dTheta=PI/180, Theta=0, R=210, dR=0.1, maxE=10;
float Msc=500, msc=-500, maxR=220, minR=210;
PVector o, Electron[] = new PVector[Size];
float Q[] = new float[Size], rRatio[] = new float[Size], V[][] = new float[200][200];

// PVector E[][] = new PVector[(int)height/(Size*Gap)][(int)width/(Size*Gap)];

float Cut(float N){ return min(255,max(0,N)); }

float rgb(float x, float m){
  x = min(Msc,max(x,msc));
  float X = 10+205*norm(x,msc,Msc);
  float r = -4.0 * abs(X - 255.0 * 3.0 / 4) + 255.0 * 3.0 / 2;
  float g = -4.0 * abs(X - 255.0 * 2.0 / 4) + 255.0 * 3.0 / 2;
  float b = -4.0 * abs(X - 255.0 * 1.0 / 4) + 255.0 * 3.0 / 2;
  if(m==2) return Cut(r);
  if(m==1) return Cut(g);
  return Cut(b);
}

void setup() {
  size(700, 700);  frameRate(30); smooth();
  background(0); strokeWeight(5.5);
  Q[0]=1; Q[1]=-1; Q[2]=1; Q[3]=-1; 
  rRatio[0]=1; rRatio[1]=0.1; rRatio[2]=1; rRatio[3]=0.1;
  for(float x=0; x<= width; x+=Delta) for(float y=height-50; y<=height; y+=Delta){
    float X = msc+(Msc-msc)*norm(x,0,width); 
    stroke(rgb(X,2), rgb(X,1), rgb(X,0)); point(x,y); // 0~768
  }
}

void draw(){
  Theta += dTheta; stroke(100); 
  rect(0,0,width,height-50);
  if(abs(R+dR)>maxR || abs(R+dR)<minR) dR *= -1; R += dR; 
  for(int i=0; i<Size; i++){ Electron[i] = new PVector(width/2+rRatio[i]*R*cos(i*2*PI/Size+Theta), height/2+rRatio[i]*R*sin(i*2*PI/Size+Theta)); 
    circle(Electron[i].x, Electron[i].y, 5); 
  }strokeWeight(5.5);
  for(int x=0; x<=width; x+=Delta){
    for(int y=0; y<=height-50; y+= Delta){ // Electric Potential part
      int X = x/Delta, Y = y/Delta; V[X][Y]=0;
      o = new PVector(x,y);
      for(int i=0; i<Size; i++){
        float D=o.dist(Electron[i]);
        V[X][Y] += 6000*Q[i]/D;
      }stroke(rgb(V[X][Y],2), rgb(V[X][Y],1), rgb(V[X][Y],0)); 
      //if(((V[X][Y]%10)+10)%10<2) stroke(0);
      point(x,y);
    }
  }strokeWeight(2); stroke(0); //for(int i=0; i<Size; i++) circle(Electron[i].x, Electron[i].y, 5);
  for(int x=0; x<=width; x+=Delta){
    for(int y=0; y<=height-50; y+= Delta){ // Electric Field part
      int X = x/Delta, Y = y/Delta; 
      o = new PVector(x,y);
      if(X>0 && Y>0 && (X%Gap)==0 && (Y%Gap)==0){
        float Ex = V[X-1][Y]-V[X][Y], Ey = V[X][Y-1]-V[X][Y];
        if(abs(Ex)>maxE) Ex=Ex*maxE/abs(Ex);
        if(abs(Ey)>maxE) Ey=Ey*maxE/abs(Ey);
        line((X-1)*Delta,(Y-1)*Delta,(X-1)*Delta+Ex*2,(Y-1)*Delta+Ey*2); 
      }
    }
  }strokeWeight(5);
}
