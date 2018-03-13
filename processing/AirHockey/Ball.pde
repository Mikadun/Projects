class Ball {
  float x, y, r;
  PVector v;
  float speed;
  Ball(float _x, float _y, float _r, PVector _v, float _speed){
    x = _x;
    y = _y;
    r = _r;
    v = _v;
    speed = _speed;
  }
  
  void show(){ // Drawing ball
    //noStroke();
    fill(255);
    ellipse(x, y, 2*r, 2*r);
  }
  
  void update(){ // Updating coords with vector
    x += v.x * speed;
    y += v.y * speed;
    update_speed();
    check_collision();
  }
  
  void update_speed(){ // Updating speed
    float losing_speed = 0.984;
    float stop_speed = 0.1;
    float max_speed = 10;
    if(speed > max_speed)
      speed = max_speed;
    speed *= losing_speed;
    if(speed < stop_speed)
      speed = 0;
  }
  
  void check_collision(){ // Check for walls
    if(x < r || x > width - r){
      v.x *= -1; // Reverse direction by x
      if(x < r) // Dont let balls to go out of walls c:
        x = r;
      else
        x = width - r;
    }
    if(y < r || y > height - r){
      v.y *= -1; // Reverse direction by y
      if(y < r)
        y = r;
      else
        y = height - r;
    }
  }
}
