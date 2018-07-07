Ball ball;
int w = 400, h = 400;
Player player;
boolean game_over = false;
float [][]g = {{w * 0.4, h * 0.95, w * 0.6, h}, {w * 0.4, 0, w * 0.6, h * 0.05}};
void setup() {
  size(400, 400);
  ball = new Ball(width / 2, height / 2, 15, new PVector(0, 0), 0);
  player = new Player(width / 2, height - 20, 15);
  noCursor();
  strokeWeight(2);
}

boolean check_gates(Ball b){
  boolean res = false;
  for(int i = 0; i < 2; i++)
    res |= (b.x > g[i][0] && b.x < g[i][2] && b.y > g[i][1] && b.y < g[i][3]);
  return res;
}

void show_board() {
  background(51);
  fill(255);
  noStroke();
  rect(g[1][0], g[1][1], g[1][2] - g[1][0], g[1][3] - g[1][1]);
  rect(g[0][0], g[0][1], g[0][2] - g[0][0], g[0][3] - g[0][1]);
  stroke(255);
  line(0, height / 2, width, height / 2);
  stroke(51);
}

void draw() {
  show_board();
  player.update(mouseX, mouseY, ball);
  player.show();
  if(!game_over)
    ball.update();
  ball.show();
  game_over = check_gates(ball);
}
