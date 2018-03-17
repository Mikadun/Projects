
Manager manager = new Manager(new RadixSort(10), new MergeSort());

int
	sort_amount,
	test_amount,
	digit;
int[][] times;

Table table = new Table();

void setup()
{
	size(500, 500);
	table.draw_table();
	manager.launch_tests(12, 2);
	table.set_coef();
}

void draw()
{
	table.draw_table();
	table.draw_diagram();
	table.check_mouse(mouseX, mouseY);
	//noLoop();
}
