uses
    Math;
const
        INF = MaxInt;
type
    TPoint = record
        x, y, angle: double;
    end;
var
    i, j, idx, n: integer;
    points, Stack: array of TPoint;
        Minim, GMinim: double;
        DeletedP: TPoint;
 
procedure Push(P: TPoint);
begin
     setlength(Stack, length(Stack) + 1);
     Stack[high(Stack)] := P;
end;
 
procedure Pop();
begin
  setlength(Stack, length(Stack) - 1);
end;
 
procedure swap_points(var a, b: TPoint);
var
        temp: TPoint;
begin
    temp := a;
    a := b;
    b := temp;
end;
 
function Rotate(A, B, C: TPoint): double;
begin
  Result := (B.x - A.x) * (C.y - B.y) - (B.y - A.y) * (C.x - B.x);
end;
 
function Large(C: TPoint): double;
begin
  Result := sqrt(sqr(C.x) + sqr(C.y));
end;
 
function GetAngle(i: integer): double;
var
        A, B: TPoint;
begin
        with A do begin
                x := Stack[i].x - Stack[i-1].x;
                y := Stack[i].y - Stack[i-1].y;
        end;
        with B do begin
                x := Stack[i+1].x - Stack[i].x;
                y := Stack[i+1].y - Stack[i].y;
        end;
        //Result := 180 - (180 * arccos((A.x*B.x + A.y*B.y) / (Large(A) * Large(B))) / Pi);
        Result := arccos((A.x*B.x + A.y*B.y) / (Large(A) * Large(B)));
        if Result > 3.13 then Result := 0;
end;
 
procedure qSort(l, r: integer);
var i, j: integer;
    w: TPoint;
    q: double;
begin
  i := l;
  j := r;
  q := points[(l+r) div 2].angle;
  repeat
    while (points[i].angle < q) do i += 1;
    while (q < points[j].angle) do j -= 1;
    if (i <= j) then
    begin
      w := points[i];
      points[i] := points[j];
      points[j] := w;
      i += 1;
      j -= 1;
    end;
  until (i > j);
  if (l < j) then qSort(l,j);
  if (i < r) then qSort(i,r);
end;
 
begin
    assign(input, 'input.txt');
    assign(output, 'output.txt');
    reset(input); rewrite(output);
    readln(n);
    setlength(points, n + 1);
    for i := 0 to n - 1 do
        read(points[i].x, points[i].y);
    for i := 1 to n - 1 do
        if points[idx].y >= points[i].y then
            if (points[idx].x > points[i].x) or (points[idx].y > points[i].y) then
                idx := i;
    swap_points(points[0], points[idx]);
        for i := 1 to n - 1 do begin
        points[i].angle := arctan2(points[i].y - points[0].y, points[i].x - points[0].x);
    end;
        qSort(1, n - 1);
        for j := 0 to N-1 do begin
                DeletedP := points[N - j];
                points[N - j].angle := INF;
                Push(points[0]); Push(points[1]);
                for i := 2 to N-1 do begin
                        if points[i].angle = INF then continue;
                        while Rotate(Stack[high(Stack)-1], Stack[high(Stack)], points[i]) < 0 do
                              Pop();
                        Push(points[i]);
                end;
                Push(points[0]); Push(Stack[1]);
                Minim:= 360;
                for i := 1 to high(stack) - 1 do begin
                        Minim := min(minim, GetAngle(i));
                end;
                GMinim := max(GMinim, Minim);
                points[N - j] := DeletedP;
                setlength(Stack, 0);
        end;
        write(GMinim:0:2);
end.
