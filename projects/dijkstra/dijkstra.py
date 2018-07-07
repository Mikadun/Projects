fin = open('input.txt', 'r')
stream = fin.read().split('\n')
test_count = int( stream.pop(0) )
INF = 1000000
u, v = [ int(i) for i in input().split() ]


def dijkstra( g, n, start, end ):
	if ( start >= n ) or ( end >= n ):
		print( 'Out of range' )
		return
	parents = [ 0 for i in range(n) ]
	d = [ INF for i in range(n) ]
	d[start] = 0
	used = [ False for i in range(n) ]

	for _ in range(n):
		min_idx = -1
		for i in range( n ):
			if ( ( min_idx == -1 ) or ( d[i] < d[min_idx] ) ) and not used[i]:
				min_idx = i

		if min_idx == -1: #if no one found
			break

		used[min_idx] = True;

		for i in range( n ):
			if ( g[min_idx][i] != INF ) and ( d[i] > d[min_idx] + g[min_idx][i] ):
				d[i] = d[min_idx] + g[min_idx][i]
				parents[i] = min_idx

	if( d[end] == INF ):
		print( 'No way' )
		return

	# restore shortest path from start to end
	path = []
	while end != start :
		path.append( end + 1 )
		end = parents[end]
	path.append( start + 1 )

	print( ' '.join([str(i) for i in path[::-1]]))


for count in range( test_count ):
	print( 'Test', count + 1, '\n' )
	size = int( stream.pop( 0 ) )
	graph = [ [ int(i) for i in stream.pop(0).split() ] for j in range(size) ]
	for i in graph:
		print( ' '.join([str(j) for j in i]) )
	print()
	for i in range(size):
		for j in range(size):
			if ( graph[i][j] == 0 ) and ( i != j ):
				graph[i][j] = INF
	dijkstra( graph, size, u - 1, v - 1 )
	print()
