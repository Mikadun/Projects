uses Math;
var
    distances: array of integer;
    d: array of array of integer;
    i, j, l, N, M: integer;
    fin, fout: text;
begin
    assign(fin, 'input.txt');
    assign(fout, 'output.txt');
    reset(fin); rewrite(fout);
    read(fin, N, M);
    setlength(distances, N);
    setlength(d, N, N);
    for i := 1 to M do
        d[0][i] := MAXINT;
    for i := 0 to N - 1 do
        read(fin, distances[i]);
    for i := 1 to N - 1 do
        for j := 0 to M do begin
            d[i][j] := MAXINT;
            for l := 0 to min(i - 1, j) do
                d[i][j] := min(d[i][j], max(d[i - l - 1][j - l], distances[i] - distances[i - l - 1]));
        end;
    write(fout, d[N - 1][M]);
    close(fin); close(fout);
end.
