"use strict"
var fs = require('fs');
var input = fs.readFileSync('input.txt', 'utf-8');
input = input.split(/\s+/g);
var n = input[0];
var columns = new Array(n);
for(let i = 0; i < n; i++) columns[i] = +input[i + 1] + 1;
var max = Math.max.apply(null, columns);

var answer = '';
var append = function (str){
	answer += str;
};

for(let i = 0; i < n; i++) append('......');
append('.\n');
for(let i = 0; i < max; i++){
	append('.');
	for(let j = 0; j < n; j++){
		if(columns[j] == max - i)
			append('+---+');
		else if(columns[j] < max - i)
			append('.....');
		else
			append('|###|');
		append('.');
	}
	append('\n');
}
append('-');
for(let i = 0; i < n; i++) append('+---+-');
fs.writeFileSync('output.txt', answer);
