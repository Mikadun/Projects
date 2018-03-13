Ball ball;
Player player;
void setup() {
  size(400, 400);
  ball = new Ball(width / 2 - 10, height / 2 + 30, 15, new PVector(0, 0), 0);
  player = new Player(width / 2, height - 20, 15);
  noCursor();
}

void draw() {
  background(51);
  player.update(mouseX, mouseY);
  player.show();
  if (player.intersect(ball.x, ball.y, ball.r))
    player.impact(ball);
  ball.update();
  ball.show();
}
