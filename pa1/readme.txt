Bhavin Soni
RUID: 171002303

__DESIGN and IMPLEMENTATION__
	Calc takes in four arguments:
		- Operator: +, -, and * 
			***(NOTE: when using multiplication do '\*' as an input)****
			***(EXAMPLE: ./calc \* d3 d2 b)****
		
		- Operand 1: String representing a number with base of either d, b, o, x
		- Operand 2: String representing a number with base of either d, b, o, x
		- Output Base: After computation - converts answer to output base (d, b,o,x)

Calc adds, subtracts, or multiplies the operands and then outputs the answer in the desired base. The arguments can be up to 64 bits and anything less than that is filled with leading 0s or 1s depending if the answer is negative or positive. 

Calc checks for the right operands and the whether the inputs fits in 64 bits. Then anything above that will show as an error. string_to_base_64b will convert the string input to any of the bases(d, b, o, x). The function calc will take the operands and do the necessary overflow check and then convert the first and second operands to the necessary base as inputted and then computes the operation given as an input. Then the program takes the two converted operands and then computes the outputs to the desired base using the string_to_base_64b.

**Calc will output leading 1s and 0s to fit 64 bits.**


	Format takes in 2 arguments:
		-Binary input string of 32 bits
		-Output Type : Determines how input should be interpreted as, either float or int.
FORMAT DOES NOT DO 64 Bit - only 32.
Format uses PROFESSOR BRIAN'S code for the function floatToASCII to implement the decimals and the scientific notation. The program also recreated intToDecASCII to complement Professor Brian's code. This function is used to convert the integer to decimal ASCII string by using mod 10 and dividing by 10 to reverse it and be placed in an array. Depending on the output type is int or float, the int is first converted from binary to an integer using binToInt. Then it uses the intToDecASCII function which helps convert the integer to a decimal ascii string. Float is done by being converted to an integer using binToInt and then it memory is copied to the float variable flo. This value flo is converted to a float ASCII string using the Professor's function floatToASCII. 

__CHALLENGES__

	- Trying to fit everything to 64 bits for Calc and Format
	- I couldn't figure out 64 with Format  
	- Trying to piece together how the code should work and function.
	- All the base conversions and calculations took longer than expected.
	- Figuring out how pointers worked. 

__RUN TIME__
	Both programs run in linear time - O(n). All functions written do not take more time or space than O(n). 