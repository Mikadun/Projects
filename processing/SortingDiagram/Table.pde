class Table
{
	int cell_size, border, grid_size, grid_pix_size;
	float time_coef;
	Table()
	{
		cell_size 		= 25;
		border    		= 2 * cell_size;
		grid_pix_size	= 400;
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

	int r = 10;

	void draw_diagram()
	{
		textSize(20);
		stroke(255);			fill(255);			text("Radix", 0.20 * width, 1.2 * cell_size);
		stroke(#A2A3FF);	fill(#A2A3FF);	text("Merge", 0.65 * width, 1.2 * cell_size);
		//System.out.printf( "Coef is %f\n", time_coef );
		fill(255);
		stroke(255);
		for( int i = 0; i < sort_amount; i++ )
		{
			float prev_x = grid_to_pix( 0, false ), 
						prev_y = grid_to_pix( 0, true );

			for( int j = 0; j < test_amount; j++ )
			{
				PVector p = grid_to_pix( times[i][j], j );
				ellipse( p.x, p.y, r, r );
				line( p.x, p.y, prev_x, prev_y );
				prev_x = p.x; prev_y = p.y;
			}
			fill(#A2A3FF);
			stroke(#A2A3FF);
		}

		stroke(255);
		textSize(12);
		for( int i = 0; i < test_amount; i++ )
		{
			String thousands = "";
			int size = sizes[i];
			while( size / 1000 > 0 )
			{
				thousands += "M";
				size /= 1000;
			}
			text( Integer.toString( size ) + thousands, 10, grid_to_pix( i, true ));
		}
	}

	void check_mouse( int x, int y )
	{
		for( int i = 0; i < sort_amount; i++ )
		{
			for( int j = 0; j < test_amount; j++ )
			{
				PVector p = grid_to_pix( times[i][j], j );
				if( abs( p.x - x ) <= r && abs( p.y - y ) <= r )
				{
					stroke(51);
					fill(i == 1 ? #A2A3FF : 255);
					ellipse( p.x, p.y, 1.5 * r, 1.5 * r );
					text( int_to_sec( times[i][j] ), p.x + r, p.y - r);
					return;
				}
			}
		}
	}

	String int_to_sec( int time )
	{
		return Float.toString(( float ) time / 1000 ) + "s";
	}
}
