
let search_substr = function(s, substr) {

	let offset = {};
	for (let i = 0; i < substr.length - 1; i++) {
		offset[substr[i]] = substr.length - i - 1;
	}
	if (!offset[substr[substr.length - 1]])
		offset[substr[substr.length - 1]] = substr.length;

	let result = [];
	let i = 0;
	let j = substr.length - 1;
	while (i < s.length - substr.length) {
		if (s[i + j] == substr[j])
			if (j == 0) {
				result.push(i);
				i++;
				j = substr.length - 1;
			} else
				j--;
		else
			i += offset[s[i + j]] || substr.length;
	}

	return result;
}

let s = 'aabaabaaaabaabaaab';
let substr = 'aabaa';

console.log(search_substr(s, substr));
