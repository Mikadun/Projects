
class Points
{
  private int count;
  private PVector[] points;
  
  private int MAX_POINTS = 100;
  private float P_SIZE = 6;
  
  private PVector center;
  private float r;
  
  public Points()
  {
    count = 0;
    points = new PVector[MAX_POINTS];
    r = -1;
  }
  
  public void endDrawing()
  {
    if( MAX_POINTS == count )
    {
      MAX_POINTS = 100;
      count = 0;
    }
    else
    {
      MAX_POINTS = count;
      findCircle();
    }
    
  }
  
  public void addPoint( float x, float y )
  {
    if( count < MAX_POINTS )
    {
      points[ count ] = new PVector( x, y );
      count++;
    }
  }
  
  public void draw()
  {
    fill( 78 );
    stroke( 255 );
    if( count == MAX_POINTS )
    {
      ellipse( center.x, center.y, 2 * r, 2 * r );
    }
    
    fill( 51 );
    stroke( 200 );
    for( int i = 0; i < count; i++ )
    {
      ellipse( points[i].x, points[i].y, P_SIZE, P_SIZE );
    }
     
  }
  
  private void findCircle()
  {
    float distance = count * ( width + height );
    center = new PVector( 0, 0 );
    for( int i = 0; i < (int) width; i++ )
    {
      for( int j = 0; j < (int) height; j++ )
      {
        float current_distance = 0;
        float max_distance = 0;
        
        for( int k = 0; k < count; k++ )
        {
          float d = dist( (float) i, (float) j, points[k].x, points[k].y );
          current_distance += d;
          max_distance = max( d, max_distance );
        }
        
        if( max_distance < distance )
        {
          distance = max_distance;
          r = max_distance;
          center.x = (float) i;
          center.y = (float) j;
        }

      }
    }
  }
  
}

Points points = new Points();

void mousePressed()
{
  if( mouseButton == LEFT )
    points.addPoint( mouseX, mouseY );
  if( mouseButton == RIGHT )
    points.endDrawing();
}

void setup()
{
  size( 400, 400 );
  stroke( 255 );
}

void draw()
{
  background( 51 );
  points.draw();
}