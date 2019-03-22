function setup() {
  createCanvas(600, 600); //width - height
  ellipseMode(RADIUS);
  frameRate(30);
}

  var deltax = 10;
  var deltay = 10;
  var x = 100;
  var y = 200;
  var r = 50;

  var kajax = 300;
  var kajay = 500;
  var kajar = 10;
  var eredmeny = 0; //h�nyat kapott el
  var ido = 0; //mennyi marad�knak kell lennie, amikor lej�r az id�
  var elkapasi_ido = 100;
  var elkapta = 0; //mikor kapta el az utols� labd�t
  //a labda sz�nez�s�hez kell
  var elet = 3;
  var pont = 'Pont: ';
  var elet_str = " Life: ";
  var szin = 2; //mennyivel szorozzuk meg a labda sz�nez�s�n�l
   
function draw() { 
  if(elet != 0){
 background(100);
 
 //�let
 textAlign(LEFT);
 elet_str = "�let: "
 elet_str += elet;
 text(elet_str,0,15);
 //Pont
 pont = 'Pont: ';
 textAlign(RIGHT);
 pont += eredmeny;
 text(pont,width-5,15);
 
 fill(255);
 ellipse(x,y,r,r);
 fill(255, 255 - (frameCount % elkapta) * szin, 255 - (frameCount % elkapta) * szin);
 ellipse(kajax,kajay,kajar,kajar);
 fill(0); // a bet�k �gy feket�k maradnak
 
 //Ha lenyomva tartjuk a gombot, akkor 2-szeres sebess�g
 if(keyIsDown(LEFT_ARROW) || keyIsDown(RIGHT_ARROW) || keyIsDown(65) || keyIsDown(68) ){ //65: a, 68: d
   x += 2 * deltax;
 }
 else{
  x += deltax 
 }
 if(keyIsDown(UP_ARROW) || keyIsDown(DOWN_ARROW) || keyIsDown(83) || keyIsDown(87) ){ //83: s, 85: w
   y += 2 * deltay;
 }
 else{
   y += deltay;
 }

  //Cs�kken az elkap�si id�
  if(frameCount % (elkapasi_ido * 3) == 0 && elkapasi_ido > 40){
   elkapasi_ido -= 10; 
   szin += 1;
  }

 if(x+r >= width || x-r <= 0){
   deltax *= -1;
 }
 
 if(y+r >= height || y-r <= 0){
    deltay *= -1;
 }
  

 if((kajax-x)*(kajax-x)+(kajay-y)*(kajay-y)-r*r<0){
   ido = frameCount % elkapasi_ido - 1; //marad�kos oszt�s az elkap�si id�vel
   // -1, mert am�gy r�gt�n lej�rna az id�
   if(ido == -1){
     //a -1 kiv�telkezel�se
    ido = elkapasi_ido + ido; 
   }
   //�gy mindig elkap�si id�nyi mp lesz 
   eredmeny += 1;
   elkapta = frameCount; //az id� amikor elkapta
   kajax = int(random(50,width-50));
   kajay = int(random(50,height-50));
 }

  if(frameCount % elkapasi_ido == ido){ //marad�kos oszt�s
  //mennyi ideje van a j�t�kosnak, hogy elkapja a labd�t
   elet -= 1;
   elkapta = frameCount;
   kajax = int(random(20,width-20));
   kajay = int(random(20,height-20));
  }
  }
  
  
  else{
    //GAME OVER
   background(100);
   textAlign(CENTER);
   text('GAME OVER',width / 2, height / 2); 
   
   pont = "Pont: ";
   pont += eredmeny;
   textAlign(CENTER);
   text(pont,width/2,height/2+20);
  }
}




//A speci�lis karakterek
function keyPressed() { 
  //ir�ny�t�s nyilakkal
 if(keyCode === LEFT_ARROW){
  deltax = abs(deltax)*(-1); 
 }
 if(keyCode === RIGHT_ARROW){
  deltax = abs(deltax); 
 }
 
 if(keyCode === UP_ARROW){
  deltay = abs(deltay)*(-1);
 } 
 if(keyCode === DOWN_ARROW){
  deltay = abs(deltay);
 } 
 //beszorul�s est�n k�z�pre teszi a k�rt
 if(keyCode === 32){ //sz�k�z
  x = width * 0.5;
  y = height * 0.5;
 }
}


//Az �tlagos karakterek
function keyTyped(){
  //ir�ny�t�s wasd-vel
  if(key === 'a'){
    deltax = abs(deltax)*(-1);
  }
  if(key === 'd'){
  deltax = abs(deltax); 
 }
 if(key === 'w'){
  deltay = abs(deltay)*(-1);
 } 
 if(key === 's'){
  deltay = abs(deltay);
 } 
}