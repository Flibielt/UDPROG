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
  var eredmeny = 0; //hányat kapott el
  var ido = 0; //mennyi maradéknak kell lennie, amikor lejár az idõ
  var elkapasi_ido = 100;
  var elkapta = 0; //mikor kapta el az utolsó labdát
  //a labda színezéséhez kell
  var elet = 3;
  var pont = 'Pont: ';
  var elet_str = " Life: ";
  var szin = 2; //mennyivel szorozzuk meg a labda színezésénél
   
function draw() { 
  if(elet != 0){
 background(100);
 
 //Élet
 textAlign(LEFT);
 elet_str = "Élet: "
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
 fill(0); // a betûk így feketék maradnak
 
 //Ha lenyomva tartjuk a gombot, akkor 2-szeres sebesség
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

  //Csökken az elkapási idõ
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
   ido = frameCount % elkapasi_ido - 1; //maradékos osztás az elkapási idõvel
   // -1, mert amúgy rögtön lejárna az idõ
   if(ido == -1){
     //a -1 kivételkezelése
    ido = elkapasi_ido + ido; 
   }
   //így mindig elkapási idõnyi mp lesz 
   eredmeny += 1;
   elkapta = frameCount; //az idõ amikor elkapta
   kajax = int(random(50,width-50));
   kajay = int(random(50,height-50));
 }

  if(frameCount % elkapasi_ido == ido){ //maradékos osztás
  //mennyi ideje van a játékosnak, hogy elkapja a labdát
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




//A speciális karakterek
function keyPressed() { 
  //irányítás nyilakkal
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
 //beszorulás estén középre teszi a kört
 if(keyCode === 32){ //szóköz
  x = width * 0.5;
  y = height * 0.5;
 }
}


//Az átlagos karakterek
function keyTyped(){
  //irányítás wasd-vel
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