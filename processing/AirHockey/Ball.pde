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
  
  Ball(float _x, float _y, float _r){
    x = _x;
    y = _y;
    r = _r;
  }
  
  void show(){ // Drawing ball
    noStroke();
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
    speed *= losing_speed;
    if(speed < stop_speed)
      speed = 0;
  }
  
  void check_collision(){ // Check for walls
    if(x < r || x > width - r)
      v.x *= -1;
    if(y < r || y > height - r)
      v.y *= -1;
  }
  
  boolean intersect(float _x, float _y, float _r){ // Check for intersection of tw
    return dist(x, y, _x, _y) < r + _r;
  }
}
