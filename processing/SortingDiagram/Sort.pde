class Sort
{
  int[] sort( int[] container, int size ) { return null; }
  long time_test( int[] container, int size )
  {
    long start_time = System.currentTimeMillis();
    container = sort( container, size );
    long finish_time = System.currentTimeMillis();
    return (int)(finish_time - start_time);
  }
}