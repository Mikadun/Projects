class Table
{
	int cell_size, border, grid_size, grid_pix_size;
	float time_coef;
	Table()
	{
		cell_size 		= 25;
		border    		= 2 * cell_size;
		grid_pix_size		= 400;
		grid_size 		= grid_pix_size / cell_size;
		time_coef 		= 10;
	}

	PVector grid_to_pix( int x, int y )
	{
		return new PVector( x * time_coef + border, width - border - y * cell_size );
	}

	int grid_to_pix( int x, boolean ordinate )
	{
		return ordinate ? width - border - x * cell_size : border + x * cell_size;
	}

	void grid_line( int x1, int y1, int x2, int y2 )
	{
		line( grid_to_pix( x1, false ), grid_to_pix( y1, true ), 
			  	grid_to_pix( x2, false ), grid_to_pix( y2, true ));
	}

	void grid_circle( int x1, int y1, int r )
	{
		ellipse( grid_to_pix( x1, false ), grid_to_pix( y1, true ), r, r );
	}

	void set_coef()
	{
		float maximum = 0.00001;
		for( int i = 0; i < sort_amount; i++ )
			for( int j = 0; j < test_amount; j++ )
				maximum = max( maximum, times[i][j] );
		time_coef = (float) grid_pix_size / maximum;
	}

	void draw_table()
	{
		background(51);

		stroke(90);
		for( int i = 0; i <= grid_size; i++ )
		{
			grid_line( 0, i, grid_size, i );
			grid_line( i, 0, i, grid_size );
		}

		fill(51);
		for( int i = 0; i <= grid_size; i++ )
			for( int j = 0; j <= grid_size; j++ )
				grid_circle( i, j, 5 );
	}  

	void draw_diagram()
	{
		System.out.printf("Coef is %f\n", time_coef);
		fill(255);
		stroke(255);
		for( int i = 0; i < sort_amount; i++ )
		{
			float prev_x = grid_to_pix(0, false), prev_y = grid_to_pix(0, true);

			for( int j = 0; j < test_amount; j++ )
			{
				PVector p = grid_to_pix( times[i][j], j );
				ellipse( p.x, p.y, 10, 10 );
				line( p.x, p.y, prev_x, prev_y );
				prev_x = p.x; prev_y = p.y;
			}
			fill(#A2A3FF);
			stroke(#A2A3FF);
		}
	}
}
