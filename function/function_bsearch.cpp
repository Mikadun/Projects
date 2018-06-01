#include <iostream>
#include <cmath>
#define F( x ) get_function_value( x )

using namespace std;

class function
{
	int degree;
	float *coef;
	const float eps = 0.000001;

public:
	void set( int degree, float *coef )
	{
		this->degree = degree;
		this->coef = new float[ degree + 1 ];
		for( int i = 0; i <= degree; i++ )
			this->coef[ i ] = coef[ i ];
	}

	float get_function_value( float x )
	{
		float result = 0;
		for( int i = 0; i <= degree; i++ )
			result += coef[i] * pow( x, degree - i );

		return result;
	}

	float get_variable_value_bsearch( float value, float l, float r )
	{
		float sign = derivative( 1 );

		while( r - l > eps )
		{
			float mid = ( l + r ) / 2;

			if( cmp( get_function_value( mid ), value, sign ) )
				r = mid;
			else
				l = mid;
		}

		return l;
	}

	float get_variable_value_chord( float value, float l, float r )
	{
		float x1 = l;
		float x2 = r;

		while( fabs( r - l ) > eps )
		{
			l = r - ( r - l ) * F( r ) / ( F( r ) - F( l ) );
			r = l + ( l - r ) * F( l ) / ( F( l ) - F( r ) );
		}

		return r;
	}

	float derivative( float x )
	{
		float result = 0;
		for( int i = 0; i <= degree - 1; i++ )
			result += coef[i] * ( degree - i ) * pow( x, degree - i - 1 );

		return result;
	}

	bool cmp( float a, float b, float sign )
	{
		return sign >= 0 ? a > b : a < b;
	}

};

function f;

int main()
{
	int degree;
	cin >> degree;
	float coef[ degree + 1 ];

	for( int i = 0; i < degree + 1; i++ )
		cin >> coef[ i ];

	f.set( degree, coef );

	float y = 0, l, r;
	cin >> l >> r;

	cout << f.get_variable_value_bsearch( y, l, r ) << endl;
	cout << f.get_variable_value_chord( y, l, r ) << endl;
}