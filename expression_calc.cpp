#include <iostream>
#include <stack>
#include <string>

using namespace std;

int get_priority( char op )
{
	switch( op )
	{
		case '(': return 3;
		case '*': return 1;
		case '/': return 1;
		case '+': return 2;
		case '-': return 2;
		case ')': return 3;
	}
}

float calculate( float a, float b, char op )
{
	switch( op )
	{
		case '+': return a + b;
		case '-': return a - b;
		case '*': return a * b;
		case '/': return a / b; // Dividing by zero
	}
}

stack<char> operations;
stack<float> values;

bool is_last_digit = false;

void push_digit( char c )
{
	float value = c - '0';
	if( is_last_digit )
	{
		// Increase last digit and delete him
		value += values.top() * 10;
		values.pop();
	}
	is_last_digit = true;
	// Add new element to stack
	values.push( value );
}

void push_op( char c )
{
	is_last_digit = false;
	
	while( !operations.empty() && c != '(' && get_priority( c ) >= get_priority( operations.top() )) 
		// Also check for ()
	{
		// Calculate last two values with last op and delete them
		float b = values.top(); values.pop();
		float a = values.top(); values.pop();
		char op = operations.top(); operations.pop();

		// Insert new value
		values.push( calculate( a, b, op ) );
		if( !operations.empty() && operations.top() == '(' && c == ')' )
		{
			operations.pop();
			return;
		}
	}
	// Add new op
	operations.push( c );

}

void process_char( char c )
{
	if( isdigit(c) )
	{
		// add to values
		push_digit( c );
	}
	else
	{
		// add to op
		push_op( c );
	}
}

int main()
{
	// Read string and cycle it's chars with func prcocess_char
	string expression = "1-1+2+3/(4-1)*2+1";
	expression = '(' + expression + ')';
	for( int i = 0; i < expression.length(); i++ )
	{
		process_char( expression[i] );
	}
	cout << values.top();
}
