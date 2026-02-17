# Ford-Johnson-sort
Merge Sort using Ford-Johnson algorithm and Jacobsthal numbers to set the insertation sequence - in C++

45 8 65 20 366 98 1 74 21 47 12 88 9

make pairs:
45 8	65 20	366 98	1 74	21 47	12 88	9

sort pairs:
8 45	20 65	98 366	1 74	21 47	12 88	9

sort highs:
8 45	21 47	20 65	1 74	12 88	98 366	9

split high and low:
45	47	65	74	88	366			low + pending : 8	21	20	1	12	98	9

pending[0] = 8 -> insert =	8	45	47	65	74	88	366
low + pending = 21	20	1	12	98	9
				[0] [1] [2] [3] [4] [5]

jacobsthalSequence = [1, 3, 5, 11, 21, ...]
pending size = 6
createInsertionSequence = [0, 2, 1, 4, 3, 5]

insert pending[insertionSequence(0)] (21) in -> [8 45 47 65 74 88 366]
begin = 8 / end = 366 / mid = 65
21 > 65 ? NO
begin = 8 / end = 65 / mid = 45
21 > 45 ? NO
begin = 8 / end = 45 / mid = 8
21 > 8 ? YES
begin = mid(8) -> begin++ = 45
begin(45) == end(45) -> break and return begin.
insert before pos(45) -> [8 21 45 47 65 74 88 366]

insert pending[insertionSequence(2)] (1) in -> [8 21 45 47 65 74 88 366]
begin = 8 / end = 366 / mid = 65
1 > 65 ? NO
begin = 8 / end = 65 / mid = 45
1 > 45 ? NO
begin = 8 / end = 45 / mid = 21
1 > 21 ? NO
begin = 8 / end = 21 / mid = 8
1 > 8 ? NO
begin = 8 / end = 8 / mid = 8
begin(8) == end(8) -> break and return begin.
insert before pos(8) -> [1 8 21 45 47 65 74 88 366]

insert pending[insertionSequence(1)] (20) in -> [1 8 21 45 47 65 74 88 366]
begin = 1 / end = 366 / mid = 47
20 > 47 ? NO
begin = 1 / end = 47 / mid = 21
20 > 21 ? NO
begin = 1 / end = 21 / mid = 8
20 > 8 ? YES
begin = mid(8) -> begin++ = 21
begin(21) == end(21) -> break and return begin.
insert before pos(21) -> [1 8 20 21 45 47 65 74 88 366]

In Jacobsthal Sequence you need to firstly insert the last index bc his high is higher than the previous index because high's list is sorted.
high list = [45	47 	65	74	88	366]
low  list = [8	21	20	1	12	98]
Jacobsthal:	 1  	3			5

1- insert 8 -> I'm sure 8 < 45 so I started binarySearch with end = 45
2- insert 20 -> I'm sure 20 < 65 when 21 < 47 --> 65 > 47 so it's more sure to insert his low.
3- insert 21 -> I'm sure 21 < 47 so I started binarySearch with end = 47
That's how I save comparisons
