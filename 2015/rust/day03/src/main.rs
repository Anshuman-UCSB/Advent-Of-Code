use std::fs;
use std::time::Instant;
fn solve(data: String) -> (i32, i32){
	(0,0)
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