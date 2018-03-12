#include <iostream>
#include <string>

// For rand function in tests
#include <stdlib.h>

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
    //cout << "We are going to create temporary array" << endl;
	t_element temp_container[size];
	//cout << "But u will not see this string, sadly" << endl;
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
			container[j] = temp_container[j];
	}
	return container;

}

void print_container(t_element *container, int size){
    for(int i = 0; i < size; i++){
        cout << container[i] << " ";
        if((i + 1) % 10 == 0)
            cout << endl;
    }
    cout << endl;
}

int main(){
	const int test_size = 100;
	const int test_digit_size = 1000;
	t_element *arr = new t_element[test_size];
	for(int i = 0; i < test_size; i++)
		arr[i] = rand() % (test_digit_size - test_digit_size / radix) + test_digit_size / radix;
    print_container(arr, test_size);
	radix_sort(arr, test_size);
	print_container(arr, test_size);
	return 0;
}
