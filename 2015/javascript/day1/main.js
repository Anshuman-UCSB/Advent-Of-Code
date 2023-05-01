const fs = require('fs');
const data = fs.readFileSync('input', 'utf8');
let level = 0;
let p2 = false;
for(let i in data){
	level += data[i]=='('?1:-1;
	p2 = p2 || (level == -1 ? i+1:false)
}
console.log("Part 1:",level)
console.log("Part 2:",p2)