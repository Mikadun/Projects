class Control
{
  boolean ready;
  boolean input;
  int value;

  Control() { ready = false; input = false; value = 0; }

  boolean is_ready() { return ready; }

  void process_key( char key )
  {
  	if( key == DELETE )
  	{
  		input = false;
  		ready = false;
  		value = 0;
  	}
  	else if( !ready )
  	{
  		if( key == ENTER )
    	{
    		if( input && value != 0)
    		{
    			int max_value = 14;
    			int min_value = 5;

    			input = false;
    			ready = true;
    			if( value > max_value )
    				value = max_value;
    			if( value < min_value )
    				value = min_value;
    			
    			manager.launch_tests( value, 2 );
    			table.set_coef();
    			value = 0;
    		}
    		else
    			input = true;
    	}
    	else if( '0' <= key && key <= '9' )
    	{
    		value = value * 10 + ( (int) key - (int) '0' );
    	}
  	}
  	delay( 200 );
	}

}
