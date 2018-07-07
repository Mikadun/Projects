class MergeSort extends Sort
{
  void merge_sort( int[] container, int l, int r )
  {
    if( l < r )
    {  
      int mid = ( l + r ) / 2;
      merge_sort(  container, l, mid );
      merge_sort(  container, mid + 1, r );
      merge( container, l, mid, r );
    }
  }

  void merge( int[] container, int l, int mid, int r )
  {
    int l_size = mid - l + 1;
    int r_size = r - mid;
    int[] l_container = new int[ l_size ];
    int[] r_container = new int[ r_size ];
    System.arraycopy(container, l, l_container, 0, l_size);
    System.arraycopy(container, mid + 1, r_container, 0, r_size);
    int i = 0, j = 0, index = l;

    while( i < l_size && j < r_size )
    {
      if( l_container[i] <= r_container[j] )
        container[ index++ ] = l_container[ i++ ];
      else
        container[ index++ ] = r_container[ j++ ];
    }

    while( i < l_size )
      container[ index++ ] = l_container[ i++ ];

    while( j < r_size )
      container[ index++ ] = r_container[ j++ ];
  }

  int[] sort( int[] container, int size )
  {
    merge_sort( container, 0, size - 1 );
    return container;
  }
}