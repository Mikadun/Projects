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

string calculate( float a, float b, char op )
{
	switch( op )
	{
		case '+': return to_string(a + b);
		case '-': return to_string(a - b);
		case '*': return to_string(a * b);
		case '/': return to_string(a / b); // Dividing by zero
	}
}

stack<char> operations;
stack<string> values;

bool is_last_digit = false;

void push_digit( char c )
{
	string value(1, c);
	if( is_last_digit )
	{
		// Increase last digit and delete him
		value = values.top() + value;
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
		string b = values.top(); values.pop();
		string a = values.top(); values.pop();
		char op = operations.top(); operations.pop();

		// Insert new value
		values.push( calculate( strtof( a.c_str(), NULL ), strtof( b.c_str(), NULL ), op ) );
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
	if( isdigit(c) || c == '.' )
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
	string expression = "1.25*4-(3*8/2-4)";
	expression = '(' + expression + ')';
	for( int i = 0; i < expression.length(); i++ )
	{
		process_char( expression[i] );
	}
	cout << strtof( ( values.top() ).c_str(), NULL );
}
