Ball ball;
Player player;
void setup(){
  size(400, 400);
  ball = new Ball(width / 2 - 10, height / 2 + 30, 15, new PVector(0, 0), 0);
  player = new Player(width / 2, height - 20, 15);
  noCursor();
}

/*
void mousePressed(){
  if(ball.intersect(mouseX, mouseY, 0)){
    ball.v.x = map(ball.x - mouseX, -ball.r, ball.r, -1, 1);
    ball.v.y = map(ball.y - mouseY, -ball.r, ball.r, -1, 1);
    ball.speed = 10;
  }
}
*/

void draw(){
  background(51);
  player.update(mouseX, mouseY);
  player.show();
  if(player.intersect(ball.x, ball.y, ball.r)){
    ball.v.x = map(ball.x - player.x, -ball.r, ball.r, -1, 1);
    ball.v.y = map(ball.y - player.y, -ball.r, ball.r, -1, 1);
    ball.speed = map(player.speed, 0, 2*width, 0.2, width);
  }
  ball.update();
  ball.show();
}
