var
  graph: array of array of integer;
  v1, v2, n, m, i, s: integer;
  fin, fout: text;
procedure BFS(v: integer);
var
  l, r, i, depth: integer;
  deck, dist: array of integer;
  visited: array of boolean;
begin
  l := -1; r := 0;
  setlength(visited, n);
  setlength(deck, n);
  setlength(dist, n);
  deck[r] := v;
  visited[v] := true;
  while(l < r) do
  begin
    l += 1;
    //depth += 1;
    v := deck[l];
    For i := 0 to high(graph[v]) do
      if {(graph[v][j] <> 0) and }(not visited[graph[v][i]]) then
      begin
        r += 1;
        deck[r] := graph[v][i];
        //dist[graph[v][i]] := depth;
        visited[graph[v][i]] := true;
      end;
  end;
  if (r = n - 1) then
    for i := 0 to r do
      write(fout, deck[i] + 1, ' ')
    else
      writeln(fout, '-1');
end;
 
begin
  assign(fin, 'input.txt');
  assign(fout, 'output.txt');
  reset(fin);
  rewrite(fout);
  readln(fin, n, m, s);
  setlength(graph, n);
  for i := 0 to m - 1 do
  begin
    readln(fin, v1, v2);
    v1 -= 1; v2 -= 1;
    setlength(graph[v1], length(graph[v1]) + 1);
    setlength(graph[v2], length(graph[v2]) + 1);
    graph[v1][high(graph[v1])] := v2;
    graph[v2][high(graph[v2])] := v1;
  end;
  BFS(s - 1);
  close(fin);
  close(fout);
end.
