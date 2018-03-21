using System;

class MaxHeap
{
  public int size;
  public int[] heap;
  
  public MaxHeap( int[] container )
  {
    this.size = container.Length;
    heap = container;
    for( int i = this.size / 2; i >= 0; i-- )
      siftDown( i );
  }
  
  void swap( int a, int b )
  {
    int temp = heap[a];
    heap[a] = heap[b];
    heap[b] = temp;
  }
  
  void siftDown( int index, int _size )
  {
    int l = 2 * index + 1;
    int r = 2 * index + 2;
    int maxChild = l;
    
    if( l < _size )
    {
      if( r < _size )
      {
        maxChild = heap[r] > heap[l] ? r : l;
      }
      
      if( heap[index] <= heap[maxChild] )
      {
        swap( index, maxChild );
        siftDown( maxChild, _size );
      }
    }
  }
  
  void siftDown( int index )
  {
    siftDown( index, this.size );
  }
  
  public void heapSort()
  {
    int _size = this.size;
    for( int i = 0; i < this.size - 1; i++ )
    {
      swap( 0, _size - 1 );
      siftDown( 0, --_size );
    }
  }
}

class MainClass {
  public static void Main (string[] args) {
    int[] container = new int[] {1, 9, 2, 6, 7, 3, 4, 0, 5, 8};
    MaxHeap heap = new MaxHeap( container );
    heap.heapSort();
    for( int i = 0; i < heap.size; i++ )
      Console.WriteLine( heap.heap[i] );
  }
}
