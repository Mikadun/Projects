def vector( start, end ):
	return [ end[0] - start[0], end[1] - start[1] ]

def vector_work( v1, v2 ):
	return v1[0] * v2[1] - v1[1] * v2[0]

def is_convex( points ):
	sign = vector_work( vector( points[1], points[0] ), vector( points[1], points[2] ) ) > 0

	for i in range( 1, len( points ) - 2 ):
		v1 = vector( points[i + 1], points[i] )
		v2 = vector( points[i + 1], points[i + 2] )
		if vector_work( v1, v2 ) > 0 != sign:
			return False

	return True

def area( points ):
	result = 0
	for i in range( 1, len( points ) - 1 ):
		v1 = vector( points[i], points[0] )
		v2 = vector( points[i], points[i + 1] ) 
		result += 0.5 * abs( vector_work( v1, v2 ) )
	return result

n = int( input() )
p = [ [ int( i ) for i in input().split() ] for _ in range( n ) ]
# p = [ [6, 0], [3, 5.19], [-3, 5.19], [-6, 0], [-3, -5.19], [3, -5.19] ]

# A = 93

if is_convex( p ):
	print( area( p ) )
else:
	print( "Not convex" )