// Initialization
int sort_count = 2;
int test_count = 18; // No more than 18 for my laptop
int digit = 2;
Sort[] sort_algs = { new RadixSort(10), new MergeSort() };
String[] alg_names = { "Radix", "Merge" };

int[][] times = new int[ sort_count ][ test_count ];
// Main test function
void sort_test( int count, int size, int number_size )
{
  int[][] container = new int[ sort_count ][ size ];
  for( int i = 0; i < size; i++ )
  {
    container[0][i] = (int) ( Math.random() * number_size );
    container[1][i] = container[0][i] + 1; // Idk how java works with containers  
  }

  for( int i = 0; i < sort_count; i++ )
  {
    times[i][ count ] = (int) sort_algs[i].time_test( container[i], size );
  }
}

String get_time( int time )
{
  return Float.toString(( float ) time / 1000 ) + "s";
}

Table table = new Table();

void setup()
{
  size(500, 500);
  background(51);
  stroke(255);
  textSize(24);
  stroke(#E6E6FA);
  for( int i = 0; i < test_count; i++ )
    sort_test( i, (int) Math.pow(digit, i) * 100, 1000 );
  for( int i = 0; i < sort_count; i++ )
  {
    int sum = 0;
    for( int j = 0; j < test_count; j++ ){
      System.out.printf("%s ", get_time(times[i][j]));
      sum += (int) times[i][j];
    }
    System.out.printf("Total %s\n", get_time(sum));
  }

  table.set_coef();
}

void draw()
{
  table.draw_table();
  table.draw_diagram();
  noLoop();
}