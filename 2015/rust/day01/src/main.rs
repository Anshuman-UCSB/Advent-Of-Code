use std::fs;
use std::time::Instant;
fn solve(data: String) -> (i32, u32){
	let mut level:i32 = 0;
	let mut p2:u32 = 0;
	for (i,c) in data.chars().enumerate(){
		level += if c=='(' {1} else {-1};
		if p2==0 && level==-1 {
			p2 = (i+1) as u32;
		}
	}
	(level, p2)
}

fn main() {
	let data = fs::read_to_string("input").expect("Input not found.");
	let t0 = Instant::now();
	let resp = solve(data);
	let t1 = Instant::now();
	println!("{}", getus(t0, t1));
	println!("Part 1: {:?}", resp.0);
	println!("Part 2: {:?}", resp.1);
}
#[allow(dead_code)]
pub fn getus(start: Instant, end: Instant) -> String {
	let t = end-start;
	format!("{} μs",t.as_micros())
}
