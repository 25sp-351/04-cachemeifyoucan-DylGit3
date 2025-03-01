Test 1 - No output remainder and second input's spacing is off:
Input
45
5,10 
10, 25
20, 50
30, 70

Output
{
'input_length' : 45
'value' : 110
'remainder' : 0
'cuts' : [
{ 'length' : 20, 'count' : 2,
'piece_value' : 50, 'value' : 100}
{ 'length' : 5, 'count' : 1,
'piece_value' : 10, 'value' : 10}
] }

-----------------------------------
Test 2 - Length that is too large but is best value:
Input
50
6, 12
8, 15
10, 20
20, 45
1000, 70

Output
{
'input_length' : 50
'value' : 110
'remainder' : 0
'cuts' : [
{ 'length' : 20, 'count' : 2,
'piece_value' : 45, 'value' : 90}
{ 'length' : 10, 'count' : 1,
'piece_value' : 20, 'value' : 20}
] }

-----------------------------------
Test 3 - Remainder expected:
Input
17
5, 10
8, 15
10, 20

Output
{
'input_length' : 17
'value' : 30
'remainder' : 2
'cuts' : [
{ 'length' : 10, 'count' : 1,
'piece_value' : 20, 'value' : 20}
{ 'length' : 5, 'count' : 1,
'piece_value' : 10, 'value' : 10}
] }

-----------------------------------
Test 4 - Initial length is smaller than any piece:
Input
4
5, 10
7, 15
8, 20
10, 30

Output
{
'input_length' : 4
'value' : 0
'remainder' : 4
'cuts' : [

] }

-----------------------------------
Test 5 - 0 initial rod length:
Input
0
5, 10
10, 18
15, 25

Ouput
Invalid input. Please enter a positive integer.

-----------------------------------
Test 6 - 0 piece lengths:
Input
10

Ouput
Unable to read valid piece values from file, input.txt.

-----------------------------------
Test 7 - String input only:
Input
abc
5, 10
10, 18
15, 25


Ouput
Invalid input. Please enter an integer larger than 0.

-----------------------------------
Test 8 - Negative input:
Input
-1
5, 10
10, 18
15, 25

Ouput
Invalid input. Please enter an integer larger than 0.

-----------------------------------
Test 9 - Integer rod length with string after:
Input
45a
5,10
10, 25
20, 50
30, 70

Ouput
{
'input_length' : 45
'value' : 110
'remainder' : 0
'cuts' : [
{ 'length' : 5, 'count' : 1,
'piece_value' : 10, 'value' : 10},
{ 'length' : 10, 'count' : 4,
'piece_value' : 25, 'value' : 100}
] }

-----------------------------------
Test 10 - Integer rod length with string before:
a45
5,10
10, 25
20, 50
30, 70

Output
Invalid input. Please enter an integer larger than 0.

-----------------------------------
Test 11 - Invalid value inputs:
Input
50
5,10 
10, 25
20, 50
0, 1
1, 0
abc, 10
10, abc
1, 
,
, 10
30, 70

Output
Skipping invalid line: 0, 1
Skipping invalid line: 1, 0
Skipping invalid line: abc, 10
Skipping invalid line: 10, abc
Skipping invalid line: 1, 
Skipping invalid line: ,
Skipping invalid line: , 10
{
'input_length' : 50
'value' : 125
'remainder' : 0
'cuts' : [
{ 'length' : 10, 'count' : 5,
'piece_value' : 25, 'value' : 125}
] }

-----------------------------------
Test 12 - One piece:
Input
4
5, 10
7, 15
8, 20
10, 30

Output
{
'input_length' : 4
'value' : 0
'remainder' : 4
'cuts' : [

] }