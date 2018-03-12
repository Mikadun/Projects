class Star {
  float x, y, z;
  Star() {
    x = random(-width, width);
    y = random(-height, height);
    z = random(width);
  }
  
  void show(){
    fill(255);
    noStroke();
    float star_size = map(z, 0, width, 8, 0.5);
    
    float delta_x = map(x / z, 0, 1, 0, width);
    float delta_y = map(y / z, 0, 1, 0, width);
    ellipse(delta_x, delta_y, star_size, star_size);
  }
  
  void update(){
    z -= 10;
    if(z < 1)
      z = width;
  }
}
