
class Player extends Ball {
  float px;
  float py;
  Player(float _x, float _y, float _r){
    super(_x, _y, _r);
    px = _x;
    py = _y;
  }
  
  void show(){
    noStroke();
    fill(255);
    float d = 2 * r;
    ellipse(x, y, d, d);
    fill(51);
    ellipse(x, y, 0.8*d, 0.8*d);
    fill(255);
    ellipse(x, y, 0.6*d, 0.6*d);
  }
  
  void update(float _x, float _y){
    x = _x;
    y = _y;
    update_speed();
  }
  
  void update_speed(){
    speed = dist(px, py, x, y);
    px = x;
    py = y;
  }
}
