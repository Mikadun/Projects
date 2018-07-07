"use strict"
var fs = require('fs');
var input = fs.readFileSync("input.txt", "utf8");
input = input.split(/\s+\n/g)
 
var stack = [];
var values_stack = [];
var answer = "";
 
var set_variable = function(index, value){
    if (stack.lastIndexOf(value) == -1){
        values_stack[index] = value;
    } else {
        set_variable(index, values_stack[stack.lastIndexOf(value)]);
    }
}
 
for (let i = 0; i < input.length; i++){
    if (input[i] == '{'){
        stack.push('{');
        values_stack.push('{');
    } else if (input[i] == '}'){
        while (stack.pop() != '{'){
            values_stack.pop();
        }
    } else if (input[i].substr(0,3) === "int"){
        let value = input[i].split(" ");
        stack.push(value[1]);
        values_stack.push(0);
    } else if(input[i].substr(0,5) == 'print'){
        let value = input[i].split(" ");
        answer += values_stack[stack.lastIndexOf(value[1])]+'\n';
    } else if (input[i].split("=").length === 2){
        let value = input[i].split("=");
        let index = stack.lastIndexOf(value[0]);
        set_variable(index, value[1]);
    }
}
fs.writeFileSync("output.txt", answer);
