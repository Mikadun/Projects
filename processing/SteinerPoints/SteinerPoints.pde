void dline(PVector p1, PVector p2)
{
  line(p1.x, p1.y, p2.x, p2.y);
}

PVector vect(PVector p1, PVector p2)
{
  return new PVector(p2.x - p1.x, p2.y - p1.y);
}

PVector steiner_point(PVector A, PVector B, PVector C)
{
  float rotate_angle = 60;
  PVector X;
  
  if( (C.x - A.x) * (B.y - A.y) / (B.x - A.x) + A.y < C.y )
    rotate_angle *= -1;
    
  if(abs(degrees(vect( B, A ).heading())) < 90)
    X = PVector.add(B, vect(B, A).rotate(radians(rotate_angle)));
  else
    X = PVector.add(A, vect(A, B).rotate(radians(rotate_angle)));

  float l = 0.0; float r = 1.0;
  float eps = 0.001;
  float target_angle = 120.0;
  PVector _X = null;
  
  while( r - l > eps ) // bsearch
  {
    float mid = (r + l) * 0.5;
    _X = PVector.add(X, PVector.mult(vect(X, C), mid));
    float angle = degrees(PVector.angleBetween(vect(C, X), vect(B, _X)));
    if( angle > target_angle )
      r = mid;
    else
      l = mid;
  }
  
  return _X;
}

PVector[] points = new PVector[4];
int p_count = 0;
int max_count = 3;


void circles()
{
  float circle_size = 15;
  for(int i = 0; i < p_count; i++)
  {
    ellipse(points[i].x, points[i].y, circle_size, circle_size);
  }
}

void mousePressed()
{
  if(p_count < max_count)
  {
    points[p_count] = new PVector(mouseX, mouseY);
    p_count++;
  }
  else
  {
    p_count = 0;
    is_found = false;
  }
}

PVector _X = null;
PVector[][] lines = new PVector[6][2];
int max_line_count = 2 * max_count - 3;
boolean is_found = false;

void setup()
{
  size(400, 400);
}

void draw()
{
  background(51);
  fill(200);
  stroke(230);
  circles();
  if(p_count == max_count)
  {
    if(!is_found) // Check for angle > 120
    {
      _X = steiner_point(points[0], points[1], points[2]);
      lines[0][0] = _X; lines[1][0] = _X; 
      lines[0][1] = points[0]; lines[1][1] = points[1]; 
      lines[2][0] = _X; lines[2][1] = points[2];
      //PVector __X = steiner_point(_X, points[2], points[3]);
      //lines[2][0] = __X; lines[3][0] = __X; lines[4][0] = __X;
      //lines[2][1] = _X; lines[3][1] = points[2]; lines[4][1] = points[3];
      is_found = true;
    }
    for(int i = 0; i < max_line_count; i++)
      dline(lines[i][0], lines[i][1]);
  }
}