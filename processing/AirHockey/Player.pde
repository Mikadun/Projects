
class Player extends Ball {
  float px;
  float py;
  Player(float _x, float _y, float _r){
    super(_x, _y, _r);
    px = _x;
    py = _y;
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
