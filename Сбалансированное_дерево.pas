const
    HashSize = 1000000;
type
    PList = ^TList;
    TList = record
        Value: integer;
        Next: PList;
    end;
var
    i, n: integer;
    Hash: array [0..HashSize - 1] of PList;
    fin, fout: text;
 
procedure Add(Value: integer);
var
    Handle, Temp: PList;
begin
    Handle := Hash[Value mod HashSize];
    while Handle^.Next <> nil do begin
        Handle := Handle^.Next;
        if Handle^.Value = Value then exit;
    end;
    New(Temp);
    Temp^.Value := Value;
    Temp^.Next := nil;
    Handle^.Next := Temp;
end;
 
procedure Remove(Value: integer);
var
    Handle, Temp: PList;
begin
    Handle := Hash[Value mod HashSize];
    while Handle^.Next <> nil do begin
        If Handle^.Next^.Value = Value then begin
            Temp := Handle^.Next;
            Handle^.Next := Temp^.Next;
            Dispose(Temp);
            exit;
        end;
        Handle := Handle^.Next;
    end;
end;
 
begin
    assign(fin, 'input.txt');
    assign(fout, 'output.txt');
    reset(fin); rewrite(fout);
    for i := 0 to HashSize - 1 do
        New(Hash[i]);
    repeat
        read(fin, n);
        if n > 0 then Add(n)
        else if n < 0 then Remove(-n);
    until n = 0;
 
    for i := 0 to HashSize - 1 do
        while Hash[i]^.Next <> nil do begin
            Hash[i] := Hash[i]^.Next;
            write(fout, Hash[i]^.Value,' ');
        end;
    close(fin); close(fout);
end.
