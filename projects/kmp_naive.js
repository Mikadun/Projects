
let s = 'aabaabaaaabaabaaab';
//let s = 'aab'

let prefix_function = function( str )
{
  let p = new Array( str.length );

  for( let i = 0; i < str.length; i++ )
  {
    p[i] = 0;
    for( let j = 0; j <= i; j++ )
    {
      let k = 0;
      while( k < j && str[k] == str[i - j + k + 1] )
      {
        k++;
      }

      if( k == j && p[i] < k )
        p[i] = k;
    }
    
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
