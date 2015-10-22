# Project 2 Notes
## Example 1
```
This is the Job and Execution provided to us
Job	: A B C D
AT	: 0 2 5 9
CT	: 7 4 1 2
```

### Various Methods
```
First Come First Serve (FCFS) / First In First Out (FIFO)
Job:	A	B	C	D
Time:	0-7	7-11	11-12	12-14

Shortest Job Next (SJN)
Job:	A	C	B	D
Time:	0-7	7-8	8-12	12-14

Shortest Remaining Time (SRT)
Job:	A	B	C	B	A	D	A
Time:	0-2	2-5	5-6	6-7	7-9	9-11	11-14

Round Robin (RR)
In this example we give the Round Robin's
Queue:	A	BA	ACB	CBDA	BDA	DA	A
Job:	A	B	A	C	B	D	A
Time:	0-3	3-6	6-9	9-10	10-11	11-13	13-14
```
### Data Structures
```
Queue
	- FCFS
	- RR
Priority Queue
	- SJN
	- SRT
```
