uses Math;
const
    MAX_VALUE = 20000;
type
    TColorParams = record
        key: string;
        idxes: array of integer;
    end;
var
    n, i, j, m, minimum, key: integer;
    fin, fout: text;
    color: string;
    girlande: array of TColorParams;
    request: array [0..1] of integer;
    l, r, mid: integer;
 
procedure Swap(a, b: integer);
var
    temp: TColorParams;
begin
    temp := girlande[a];
    girlande[a] := girlande[b];
    girlande[b] := temp;
end;
 
procedure QuickSort(l, r: integer);
var
    di, i: integer;
begin
    if (l >= r) then exit;
    Swap(l, (l + r) div 2);
    di := l;
    for i := l + 1 to r do
        if girlande[i].key < girlande[l].key then
        begin
            di += 1;
            Swap(di, i);
        end;
    Swap(l, di);
    QuickSort(l, di - 1);
    QuickSort(di + 1, r);
end;
 
function FindColor(s: string):integer;
var
    i: integer;
begin
    for i := 0 to high(girlande) do
        if(girlande[i].key = s) then
            exit (i);
    exit (-1);
end;
 
function BFindColor(s: string): integer;
var
    mid, l, r: integer;
begin
    l := 0; r := length(girlande);
  if s = girlande[l].key then exit (0);
    while r - l > 1 do
    begin
    mid := (r + l) div 2;
        if s = girlande[mid].key then
            exit (mid);
        if s > girlande[mid].key then
            l := mid
        else
            r := mid;
    end;
    result := -1;
end;
 
procedure AddIdx(key, idx: integer);
begin
    setlength(girlande[key].idxes, length(girlande[key].idxes) + 1);
    girlande[key].idxes[high(girlande[key].idxes)] := idx;
end;
 
procedure AddColor(key: string; idx: integer);
begin
    setlength(girlande, length(girlande) + 1);
    girlande[high(girlande)].key := key; 
    AddIdx(high(girlande), idx);
end;
 
 
{function bsearch(l, r: integer):integer;
var
    mid: integer;
begin
    while(r - l > 1) do
    begin
        mid := (l + r) div 2;
        if(girlande[request[0]].idxes[j] > girlande[request[1]].idxes[mid]) then
            l := mid
        else
            r := mid;
    end;
    if r = length(girlande[request[1]].idxes) then
        result := abs(girlande[request[0]].idxes[j] - girlande[request[1]].idxes[l])
    else
        result := min(abs(girlande[request[1]].idxes[r] - girlande[request[0]].idxes[j]),
    abs(girlande[request[0]].idxes[j] - girlande[request[1]].idxes[l]));
end;}
 
 
begin
    assign(fin, 'input.txt'); assign(fout, 'output.txt');
    reset(fin); rewrite(fout);
    readln(fin, n);
    for i := 0 to n - 1 do
    begin
        readln(fin, color);
        key := FindColor(color);
        if(key = -1) then
            AddColor(color, i)
        else
            AddIdx(key, i);
    end;
  /////
 { for i := 0 to high(girlande) do begin
      write(girlande[i].key, ' ');
      for j := 0 to high(girlande[i].idxes) do
          write(girlande[i].idxes[j], ' ');
      writeln;
  end; }
  /////
    QuickSort(0, high(girlande));
    readln(fin, m);
    for i := 0 to m - 1 do
    begin
        for j := 0 to 1 do
        begin
        readln(fin, color);
        request[j] := BFindColor(color);
        end;
 
        if (request[0] = -1) or (request[1] = -1) then
        begin
            writeln(fout, -1);
            continue;
        end;
        minimum := MAX_VALUE;
        if (request[0] <> request[1]) then
        begin
            for j := 0 to high(girlande[request[0]].idxes) do
            begin
                l := 0;
                r := length(girlande[request[1]].idxes);
                while(r - l > 1) do
                begin
                    mid := (l + r) div 2;
                    if(girlande[request[0]].idxes[j] > girlande[request[1]].idxes[mid]) then
                        l := mid
                    else
                        r := mid;
                end;
                if r = length(girlande[request[1]].idxes) then
                    minimum := min(minimum, abs(girlande[request[0]].idxes[j] - girlande[request[1]].idxes[l]))
                else
                    minimum := min(minimum, min(abs(girlande[request[1]].idxes[r] - girlande[request[0]].idxes[j]),
                    abs(girlande[request[0]].idxes[j] - girlande[request[1]].idxes[l])));   
            end;
            writeln(fout, minimum - 1);
        end
        else
        begin
            for j := 1 to high(girlande[request[0]].idxes) do
                minimum := min(minimum, girlande[request[0]].idxes[j] - girlande[request[0]].idxes[j - 1]);
            if minimum = MAX_VALUE then
                writeln(fout, -2)
            else
                writeln(fout, minimum - 1);
        end;
    end;
    close(fin);
    close(fout);
 // readln;
end.
