int stars_count = 1000;
Star[] stars = new Star[stars_count];

void setup(){
  size(400, 400);
  for(int i = 0; i < stars_count; i++){
    stars[i] = new Star();
  }
}

void draw(){
  background(0);
  translate(width / 2, height / 2);
  for(int i = 0; i < stars_count; i++){
    stars[i].update();
    stars[i].show();
  }
}
