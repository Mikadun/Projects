
// Initialization
Manager manager = new Manager(new RadixSort(10), new MergeSort());

// Global variables
int
	sort_amount,
	test_amount,
	digit;
int[][] times;

// Graphic class
Table table = new Table();

void setup()
{
	size(500, 500);
	// First value is amount of 
	table.draw_table();
	manager.launch_tests(12, 2);
	table.set_coef();
}

void draw()
{
	table.draw_table();
	table.draw_diagram();
	noLoop();
}
