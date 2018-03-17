
class RadixSort extends Sort// Is ir necessary?
{
  RadixSort( int radix ) { this.radix = radix; }

  int radix;
  int size;

  public int[] sort( int[] container, int size )
  {
    if( size < 2 )
      return container;
    set_size( size );
    int[] temp_container = new int[ size ];
    int[] radix_count = new int[ radix ];
    int max_radix = get_max_radix( container );
    for( int i = 0; i < max_radix; i++ )
    {
      for( int j = 0; j < radix; j++ )
        radix_count[j] = 0;

      for( int j = 0; j < size; j++ )
        radix_count[ get_digit( container[j], i ) ]++;

      int temp, step = 0;
      for( int j = 0; j < radix; j++ )
      {
        temp = radix_count[j];
        radix_count[j] = step;
        step += temp;
      }

      for( int j = 0; j < size; j++ )
      {
        int index = get_digit( container[j], i );
        temp_container[ radix_count[ index ]++ ] = container[j];
      }

      for( int j = 0; j < size; j++ )
        container[j] = temp_container[j];
    }
    return container;  
  }

  private void set_size( int size )
  {
    this.size = size;
  }

  private int get_max_radix( int[] container )
  {
    int max_value = container[0];
    for( int i = 1; i < size; i++ ) 
    {
      max_value = max( max_value, container[i] );
    }
    int i = radix;
    int max_radix = 1;
    while( i <= max_value )
    {
      i *= radix;
      max_radix++;
    }
    return max_radix;    
  }

  private int get_digit( int element, int pos )
  {
    int denumerator = 1;
    for(int i = 0; i < pos; i++)
      denumerator *= radix;
    return (( element / denumerator ) % radix );
  }
}