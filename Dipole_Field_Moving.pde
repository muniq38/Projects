int Size=6, Delta=4, Gap=4;
float dTheta=PI/180, Theta=0, R=210, dR=0.1, maxE=10, Fd=2;
float Msc=500, msc=-500, maxR=220, minR=210;
PVector o, Electron[] = new PVector[Size], Speed[] = new PVector[Size], Force[] = new PVector[Size];
float Q[] = new float[Size], V[][] = new float[200][200];
boolean Fix[] = new boolean[Size];

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
  Q[0]=2; Q[1]=-2; Q[2]=2; Q[3]=-2; Q[4]=1; Q[5]=-1;
  //for(int i=0; i<Size; i++) Fix[i]=true;
  for(int i=0; i<Size; i++){ 
    Electron[i] = new PVector(random(0,width),random(0,height)); 
    Speed[i] = new PVector(random(-5,5),random(-5,5));
    Force[i] = new PVector(0,0);
  }for(float x=0; x<= width; x+=Delta) for(float y=height-50; y<=height; y+=Delta){
    float X = msc+(Msc-msc)*norm(x,0,width); 
    stroke(rgb(X,2), rgb(X,1), rgb(X,0)); point(x,y); // 0~768
  }
}

void draw(){
  Theta += dTheta; stroke(100); 
  rect(0,0,width,height-50);
  if(abs(R+dR)>maxR || abs(R+dR)<minR) dR *= -1; R += dR; 
  for(int i=0; i<Size; i++){ 
    if(Fix[i]) continue;
    if(Electron[i].x+Speed[i].x > width || Electron[i].x+Speed[i].x<0) Speed[i].x=0;
    if(Electron[i].y+Speed[i].y > height-50 || Electron[i].y+Speed[i].y<0) Speed[i].y=0;
    Electron[i].add(Speed[i]); 
    Speed[i].add(Force[i]);
    Force[i].set(0,0);
  }strokeWeight(5.5);
  for(int i=0; i<Size; i++){
    for(int j=0; j<Size; j++){
      if(i==j) continue;
      float D=Electron[i].dist(Electron[j]);
      Force[i].add(500*Q[i]*Q[j]*(Electron[i].x-Electron[j].x)/(D*D*D), 500*Q[i]*Q[j]*(Electron[i].y-Electron[j].y)/(D*D*D)); // mass = 6000/500 = 12
    }if(keyPressed){
        if(key=='a') Force[i].x -= Fd*Q[i]; 
        if(key=='w') Force[i].y -= Fd*Q[i]; 
        if(key=='d') Force[i].x += Fd*Q[i]; 
        if(key=='s') Force[i].y += Fd*Q[i]; 
      }
  }for(int x=0; x<=width; x+=Delta){
    for(int y=0; y<=height-50; y+= Delta){ // Electric Potential part
      int X = x/Delta, Y = y/Delta; V[X][Y]=0;
      if(keyPressed){
        if(key=='a') V[X][Y] += Fd*(X-75); 
        if(key=='w') V[X][Y] += Fd*(Y-75); 
        if(key=='d') V[X][Y] -= Fd*(X-75);
        if(key=='s') V[X][Y] -= Fd*(Y-75); 
      }o = new PVector(x,y);
      for(int i=0; i<Size; i++){
        float D=o.dist(Electron[i]);
        V[X][Y] += 6000*Q[i]/D;
      }stroke(rgb(V[X][Y],2), rgb(V[X][Y],1), rgb(V[X][Y],0)); 
      if(abs(V[X][Y])<2) stroke(0);
      point(x,y);
    }
  }strokeWeight(2); stroke(0); //for(int i=0; i<Size; i++) circle(Electron[i].x, Electron[i].y, 5);
  /*for(int x=0; x<=width; x+=Delta){
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
  }*/strokeWeight(5);
}
