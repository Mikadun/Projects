
Manager manager = new Manager(new RadixSort(10), new MergeSort());
Control control = new Control();

int
	sort_amount,
	test_amount,
	digit,
	input = 0;
int[][] times;

boolean is_ready = false, is_input = false;

Table table = new Table();

void setup()
{
	size(500, 500);
	table.draw_table();
}

void draw()
{
	table.draw_table();
	if( control.is_ready() )
	{
		table.draw_diagram();
		table.check_mouse( mouseX, mouseY );
	}

	if( keyPressed )
		control.process_key( key );
}
