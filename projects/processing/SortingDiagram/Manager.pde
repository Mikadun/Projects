class Sort // Just parent for creating array of childs
{
	int[] sort( int[] container, int size ) { return null; };
}

int[] sizes;

class Manager
{
	Sort[] sort_algs;
	Manager( Sort ... _sort_algs )
	{
		sort_amount = _sort_algs.length;
		sort_algs = new Sort[ sort_amount ];
		for( int i = 0; i < sort_amount; i++ )
			sort_algs[i] = _sort_algs[i];
	}

	int get_time( Sort sort_alg, int[] container, int size )
	{
		long start_time = System.currentTimeMillis();
		container = sort_alg.sort( container, size );
		long finish_time = System.currentTimeMillis();
		return (int)(finish_time - start_time);
	}

	void launch_tests( int _test_amount, int _digit )
	{
		test_amount 		 		 = _test_amount;
		digit 							 = _digit;
		int minimal_value		 = 1000;
		int max_number_value = 1000;
		times 							 = new int[sort_amount][test_amount];
		sizes 							 = new int[test_amount];
		
		for( int i = 0; i < test_amount; i++ )
		{
			int size = (int) Math.pow(digit, i) * minimal_value;
			sizes[i] = size;
			int[][] container = new int[ sort_amount ][ size ];
			
			for( int k = 0; k < sort_amount; k++ )
			{
				for( int j = 0; j < size; j++ )
				{
					container[k][j] = (int) ( Math.random() * max_number_value );
					container[k][j] = container[k][j] + 1;
				}
				times[k][i] = get_time( sort_algs[k], container[k], size );
			}
		}
	}
}
