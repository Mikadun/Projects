#include <iostream>
#include <string>

using namespace std;

typedef int t_element;
const int radix = 10;

int get_max_radix(t_element *container, int size){
	t_element max_value = container[0];
	for(int i = 1; i < size; i++){
		max_value = max(max_value, container[i]);
	}
	int i = radix;
	int max_radix = 1;
	while(i <= max_value){
		i *= radix;
		max_radix++;
	}
	return max_radix;
}

t_element get_digit(t_element element, int pos){
	int denumerator = 1;
	for(int i = 0; i < pos; i++)
		denumerator *= radix;
	return ((element / denumerator) % radix);
}

t_element* radix_sort(t_element *container, int size){
	if(size < 2)
		return container;
	t_element temp_container[size];
	int radix_count[radix];
	int max_radix = get_max_radix(container, size);
	for(int i = 0; i < max_radix; i++){
		for(int j = 0; j < radix; j++)
			radix_count[j] = 0;
		for(int j = 0; j < size; j++){
			radix_count[get_digit(container[j], i)]++;
		}
		int temp, step = 0; 
		for(int j = 0; j < radix; j++){
			temp = radix_count[j];
			radix_count[j] = step;
			step += temp;
		}
		for(int j = 0; j < size; j++){
			int index = get_digit(container[j], i);
			temp_container[radix_count[index]++] = container[j];
		}
		for(int j = 0; j < size; j++)
			cout << temp_container[j] << " ";
		cout << endl;
		for(int j = 0; j < size; j++)
			container[j] = temp_container[j];
	}
	return container;
	
}

int main(){
	t_element arr[] = {312, 25, 1, 84, 6566, 656, 12, 7, 88, 901, 10000, 312};
	cout << get_max_radix(arr, 12) << endl;
	cout << get_digit(12345, 10) << endl;
	radix_sort(arr, 12);
	
	return 0;
}
