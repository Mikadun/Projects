let substr_search = function(str, substr) {
  let result = [];
  let dlen = str.length - substr.length;

  for (let i = 0; i < dlen; i++) {
    found = true;
    for (let j = 0; j < substr.length; j++) {
      if (str[i + j] != substr[j]) {
        found = false;
        break;
      }
    }

    if (found) {
      result.push(i);
    }
  }

  return result;

}

let s = 'aabaabaaaabaabaaab';
let substr = 'aabaa';
let arr = substr_search(s, substr);
console.log(arr.length, arr);
