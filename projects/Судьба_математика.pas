const
    MAX = 1000000;
type
    TCondition = record
        l, r, op: integer;
    end;
var
    line: string;
    fin, fout: text;
    Conditions: array of TCondition;
    Number: array [1..6] of integer;
    i, j, count: integer;
 
function ToCond(l: string): TCondition;
var
    operand: string;
begin
    result.l := ord(l[1]) - ord('0');
    result.r := ord(l[length(l)]) - ord('0');
    operand :=  copy(l, 2, length(l) - 2);
    case(operand) of
        '=':  result.op := 1;
        '>':  result.op := 2;
        '<':  result.op := 3;
        '<>': result.op := 4;
        '>=': result.op := 5;
        '<=': result.op := 6;
    end;
end;
 
function IsRight: boolean;
begin
    case Conditions[j].op of
        1: result := Number[Conditions[j].l] =   Number[Conditions[j].r];
        2: result := Number[Conditions[j].l] >   Number[Conditions[j].r];
        3: result := Number[Conditions[j].l] <   Number[Conditions[j].r];
        4: result := Number[Conditions[j].l] <>  Number[Conditions[j].r];
        5: result := Number[Conditions[j].l] >=  Number[Conditions[j].r];
        6: result := Number[Conditions[j].l] <=  Number[Conditions[j].r];
    end;
end;
procedure Increment;
var
    k: integer;
begin
    k := 6;
    Number[k] += 1;
    while(Number[k] = 10) do
    begin
        Number[k] := 0;
        k -= 1;
        Number[k] += 1;
    end;
 
end;
 
begin
    assign(fin, 'input.txt'); assign(fout, 'output.txt');
    reset(fin);
    rewrite(fout);
  count := 0;
    while(not EOF(fin)) do
    begin
        readln(fin, line);
        setlength(Conditions, length(Conditions) + 1);
        Conditions[high(Conditions)] := ToCond(line);
    end;
    for i := 0 to MAX - 1 do
    begin
        count += 1;
        for j := 0 to high(Conditions) do
            if not IsRight then
            begin
                count -= 1;
                break;
            end;
        Increment;
    end;
    writeln(fout, count);
    close(fin); close(fout);
end.
