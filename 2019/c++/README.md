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