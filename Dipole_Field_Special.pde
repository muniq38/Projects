int Size=0, Delta=4, Gap=4;
float maxE=10, Fd=2, curQ=1, dQ=0.2, VGap=10, curXS=0, curYS=0, dS=1, k=6000, M=6;
float Msc=500, msc=-500, maxR=220, minR=210;
PVector o, Electron[] = new PVector[100], Speed[] = new PVector[100], Acc[] = new PVector[100];
float Q[] = new float[100], V[][] = new float[200][200];
boolean Fix[] = new boolean[100], Eqp=false, Fdon=false;
boolean Click=false, FPress=false, EPress=false, Backsp=false;

float Cut(float N){ return min(255,max(0,N)); }

float rgb(float x, float m){
  x = min(Msc,max(x,msc));
  float X = 25+205*norm(x,msc,Msc);
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
  for(int i=0; i<100; i++){ Q[i]=0; Speed[i] = new PVector(0,0); Acc[i] = new PVector(0,0); Electron[i] = new PVector(0,0); }
  for(float x=0; x<= width; x+=Delta) for(float y=height-50; y<=height; y+=Delta){
    float X = msc+(Msc-msc)*norm(x,0,width); 
    stroke(rgb(X,2), rgb(X,1), rgb(X,0)); point(x,y); // 0~768
  }textSize(30); 
}

void draw(){
  fill(255); rect(0,0,width,height-50); 
  for(int i=0; i<Size; i++){ // Move Part
    if(Fix[i]) continue;
    if(Electron[i].x+Speed[i].x > width || Electron[i].x+Speed[i].x<0) Speed[i].x=0;
    if(Electron[i].y+Speed[i].y > height-50 || Electron[i].y+Speed[i].y < 0) Speed[i].y=0; //!!!!
    Electron[i].add(Speed[i]); 
    Speed[i].add(Acc[i]);
    Acc[i].set(0,0);
  }strokeWeight(5.5);
  for(int i=0; i<Size; i++){
    for(int j=0; j<Size; j++){
      if(i==j) continue;
      float D=Electron[i].dist(Electron[j]);
      Acc[i].add(k*Q[i]*Q[j]*(Electron[i].x-Electron[j].x)/(D*D*D*M), k*Q[i]*Q[j]*(Electron[i].y-Electron[j].y)/(D*D*D*M)); 
    }if(keyPressed){
        if(key=='a') Acc[i].x -= Fd*Q[i]; 
        if(key=='w') Acc[i].y -= Fd*Q[i]; 
        if(key=='d') Acc[i].x += Fd*Q[i]; 
        if(key=='s') Acc[i].y += Fd*Q[i]; 
      }
  }for(int x=0; x<=width; x+=Delta){
    for(int y=0; y<=height-50; y+= Delta){ // Electric Potential part, Make Scalar Field
      int X = x/Delta, Y = y/Delta; V[X][Y]=0;
      if(keyPressed){
        if(key=='a') V[X][Y] += Fd*(X-75); 
        if(key=='w') V[X][Y] += Fd*(Y-75); 
        if(key=='d') V[X][Y] -= Fd*(X-75);
        if(key=='s') V[X][Y] -= Fd*(Y-75); 
      }o = new PVector(x,y);
      for(int i=0; i<Size; i++){
        float D=o.dist(Electron[i]);
        V[X][Y] += k*Q[i]/D;
      }stroke(rgb(V[X][Y],2), rgb(V[X][Y],1), rgb(V[X][Y],0)); 
      if(Eqp && abs(V[X][Y]%VGap)<2) stroke(0); // Equipotential Surface
      point(x,y);
    }
  }stroke(100); 
  for(int x=0; x<=width; x+=Delta){
    if(!Fdon) break;
    for(int y=0; y<=height-50; y+= Delta){ // Vector Field part, Used Gradient of E.P.
      int X = x/Delta, Y = y/Delta; 
      o = new PVector(x,y);
      if(X>0 && Y>0 && (X%Gap)==0 && (Y%Gap)==0){
        float Ex = V[X-1][Y]-V[X][Y], Ey = V[X][Y-1]-V[X][Y];
        float Scale = sqrt(Ex*Ex+Ey*Ey);
        if(Ex*Ex+Ey*Ey>maxE*maxE){ Ex*=maxE/Scale; Ey*=maxE/Scale; } // Turn on this
        //if(abs(Ex)>maxE) Ex=Ex*maxE/abs(Ex); // or these
        //if(abs(Ey)>maxE) Ey=Ey*maxE/abs(Ey); //
        strokeWeight(3); point((X-1)*Delta, (Y-1)*Delta);
        strokeWeight(2); line((X-1)*Delta,(Y-1)*Delta,(X-1)*Delta+Ex*2,(Y-1)*Delta+Ey*2); 
      }
    }
  }strokeWeight(5); stroke(0);
  if(!keyPressed){ FPress=false; EPress=false; Backsp=false; }
  if(keyPressed){
    if(keyCode==UP) curQ += dQ;
    if(keyCode==DOWN) curQ -= dQ;
    if(key=='z') curXS -= dS; if(key=='x') curXS += dS;
    if(key=='c') curYS -= dS; if(key=='v') curYS += dS;
    if(key==BACKSPACE && !Backsp){ Size=max(0,Size-1); Backsp=true; }
    if(key=='e' && !EPress){ Eqp = !Eqp; EPress=true; }
    if(key=='f' && !FPress){ Fdon = !Fdon; FPress=true; }
  }fill(0); text(curQ, 10, 40); text(curXS, 10, 630); text(curYS, 120, 630); 
  if(!mousePressed) Click=false;
  if(mousePressed && !Click){ // Add particles
    Q[Size]=curQ; Speed[Size].set(curXS,curYS);
    Electron[Size] = new PVector(mouseX, mouseY);
    Acc[Size] = new PVector(0,0); Fix[Size] = false;
    if(mouseButton==RIGHT) Fix[Size]=true;  
    Size++; Click=true;
  }
}
