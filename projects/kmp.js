
let s = 'aabaabaaaabaabaaab';
//let s = 'aab'

let prefix_function = function( str )
{
	let p = new Array( str.length );
	p[0] = 0;

	for( let i = 1; i < str.length; i++ )
	{
		j = p[i - 1];
		while( j > 0 && str[i] != str[j] )
			j = p[j - 1];

		if( str[i] == str[j] )
			j++;

		p[i] = j;
		
	}
	return p;
}

let KMP = function( str, substr )
{
	let p = prefix_function( substr + '#' + str );
	let result = new Array();

	for( let i = substr.length + 1; i < p.length; i++ )
	{
		if( p[i] == substr.length )
		{
			result.push( i - 2 * substr.length );
		}
	}

	return result;
}

console.log( KMP( s, "aabaa" ) );
