Bhavin Soni
bbs39
171002303

___FORMULA___

DESIGN & IMPLEMENTATION:
	The program formula prints the expanded form of (1+x)^n in which n is a non-negative integer. The program is called by: formula <power> in which <power> is n. The implementation of formula took in 3 main functions: main function of formula, Factorial(n), and nCr(n, r). 

	The main function of formula checks for valid arguments and then uses a for loop to print out the final expanded form of (1+x)^n in the form of: (1 + x)^n = 1 + nC1*x + nC2*x^2+ ... + nCr*x^r + ... + nCn*x^n
If -h is passed as argument it prints out a simple message demonstrating how the user can implement the function. 
The main function also calls upon the function nCr in order to get the coefficients of the expanded formula. 
When an OVERFLOW error is detected the output is (1+x)^n = 1 (n is the power inputted ) to exhibit that an OVERFLOW has occurred. This happens when the result of factorial is greater than what can be held by integer. 

	Factorial(n) was created using recursion. The recursive call was used to multiply n by Factorial(n-1) which makes the function efficient.

	nCr(n,r) is the formula:
n!/r!(n-r)!
nCr called upon the factorial function multiple times in order to generate the result. This result as previously stated was used as the coefficient for the expanded polynomial. I first created a nCr.c file with the Factorial and nCr calculations and then compiled into Assembly. 


CHALLENGES:
	The challenges I faced were not that big or difficult. I had figure out how to get microseconds for the Time Required and that took some time researching. I also did not find an easier way of outputting the OVERFLOW error without having the (1+x)^n =1 being printed out but that was small and did the best I could in explaining the error message. Another challenge was determining when the threshold of integer range was too big. 


RUNNING TIME & SPACE ANALYSIS:
	The program takes O(n) time and space. Formula takes O(n) time to run since it takes a single input and goes through a for loop to print out the expanded polynomial. Factorial(n) also takes O(n) time to run since it is recursively taking the current number and multiply it by one minus that number. nCr(n, r) also takes O(n) time to run since it calls upon Factorial multiple times. This shows that all three functions have a linear time and also allocates a linear amount of space. 
