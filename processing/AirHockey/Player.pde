
class Player {
  float x, y, r, px, py, speed;
  Player(float _x, float _y, float _r) {
    x = _x;
    y = _y;
    r = _r;
    px = _x;
    py = _y;
  }

  void show() {
    noStroke();
    fill(255);
    float d = 2 * r;
    ellipse(x, y, d, d);
    fill(51);
    ellipse(x, y, 0.8*d, 0.8*d);
    fill(255);
    ellipse(x, y, 0.6*d, 0.6*d);
  }

  void update(float _x, float _y) {
    x = _x;
    y = _y;
    update_speed();
  }

  void update_speed() {
    speed = dist(px, py, x, y);
    px = x;
    py = y;
  }
  
  boolean intersect(float _x, float _y, float _r) { // Check for intersection
    return dist(x, y, _x, _y) < r + _r;
  }
  
  void impact(Ball b){  
    b.v.x = map(b.x - x, -b.r, b.r, -1, 1);
    b.v.y = map(b.y - y, -b.r, b.r, -1, 1);
    b.speed = map(speed, 0, 2*width, 0.2, width);
  }
}
