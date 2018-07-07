import java.util.Random;
PImage car_sprite;
float line_size;

class Car
{
  private float speed;
  private PVector position;
  
  public Car( float speed, float x, float y )
  {
    this.speed = speed;
    position = new PVector( x, y );
  }
  
  public void draw()
  {
    image( car_sprite, 0.5 * car_sprite.width + position.x, 0.5 * car_sprite.height + position.y );
  }
  
  public void update()
  {
    position.x += speed;
    if( position.x > width )
      position.x = -car_sprite.width;
  }
  
  public void car_control()
  {
    switch( keyCode )
    {
      case( RIGHT ): speed += 0.5; break;
      case( LEFT ): speed -= 0.5; break;
    }
    if( speed > 10 )
      speed = 10;
    if( speed < 0 )
      speed = 0;
  }
  
  public boolean intersection( float x, float y )
  {
    return position.y < y && y < position.y + car_sprite.height;
  }
}

class Road
{
  private Car[] cars;
  private int lines;
  private int current_car;
  
  public Road( int lines, float ... input )
  {
    this.lines = lines;
    current_car = -1;
    cars = new Car[ lines ];
    for( int i = 0; i < lines; i++ )
    { 
      cars[i] = new Car( input[ 3 * i ], input[ 3 * i + 1 ], input [ 3 * i + 2 ] );
    }
  }
  
  public void draw()
  {
    for( int i = 0; i < lines; i++ )
    {
      int count = (int) ( width / lines );
      float len = 0.1 * count;
      if( i != 0 )
        for( int j = 0; j * len < width; j += 2 )
        {
          line( j * len, i * car_sprite.height, (j + 1) * len, i * car_sprite.height );
        }
      cars[i].draw();
    }
    line( 0, 0, width, 0 );
    line( 0, height - 0.05 * car_sprite.height, width, height - 0.05 * car_sprite.height );
  }
  
  public void update()
  {
    for( int i = 0; i < lines; i++ )
    {
      cars[i].update();
    }
  }
  
  public void car_control()
  {
    if( current_car != -1 )
      cars[ current_car ].car_control();
  }
  
  public void choose_car( float x, float y )
  {
    for( int i = 0; i < lines; i++ )
    {
      if( cars[i].intersection( x, y ) )
      {
        current_car = i;
        return;
      }
    }
    current_car = -1;
  }
  
}

Road road;

void setup()
{
  int lines = 10;
  
  size(700, 400);
  car_sprite = loadImage( "car.png" );
  imageMode( CENTER );
  car_sprite.resize( 0, (int) (height / lines) );
  
  float[] input = new float[ 3 * lines ];
  Random rand = new Random();
  for( int i = 0; i < lines; i++ )
  {
    input[3 * i] = rand.nextInt(100) * 0.1;
    input[3 * i + 1] = 0;
    input[3 * i + 2] = i * car_sprite.height;
  }
  
  road = new Road( lines, input );
  stroke( 255 );
  strokeWeight( 0.05 * car_sprite.height );
  strokeCap( SQUARE );
}

void draw()
{
  background( 78 );
  road.update();
  road.draw();
}

void keyPressed()
{
  road.car_control();
}

void mousePressed()
{
  road.choose_car( mouseX, mouseY );
}