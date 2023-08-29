## Anshuman Dash's Advent of Code Repo
To me Advent of Code is the single best way to practice/learn/get better at coding, and so I decided to create one repository for my years.

Each year/language I have a goal in mind

2019: Relearn c++

2018: Learn c++20

2017: Use c++20 and optimize for speed

2016: Use pypy and practice pythonic solutions

2015: Use pypy and work on an AoC library

2020: Speed code in python

2019: Work on library and speed code in Python

2021: Leaderboard spot (Python) and total <1s in c++!

2022: Refresh on coding (Python)

2020: Refresh coding again, but also do it with a friend (Python)

To get millisecond-time,

```
#!/bin/bash
ts=$(date +%s%N) ; $@ ; tt=$((($(date +%s%N) - $ts)/1000000)) ; echo "Time taken: $tt milliseconds"
```

add above to 
```
/usr/local/bin
```
and run
```
chmod +x /usr/local/bin/millisecond-time
```
