Bhavin Soni 
RUID: 171002303
NetID: bbs39

_______________
___Y86 EMUL____


__DESIGN & IMPLEMENTATION__

	The program is essentially a large switch case that goes through each of the cases which are hex addresses to specific opcodes and instructions. When entered '-h' as an argument, the program will print out an usage message on how the emulator works. 

The program checks the arguments and then starts by cycling through the directives (.size, .text, .long, .byte, and .string). These directives help setup the initial read of the file and then allocate the necessary memory for the emulator to start. Then in the .text directive, the emulator gets the individual hex addresses for the switch case and to start the program counter. This goes through the switch case and then goes directly to the specific instruction while keeping count of the program counter. In the case of a halt or invalid instruction an error message will be printed out. 

__Challenges__
	- Figuring out how everything worked -- had to reread the instructions a few times
	- Trying to find how the memory and registers were being set
	- Making the ints
	- The pointers and addresses as well as type casting was difficult at times to figure out 


Extra Credit: myprog.y86
	- Edited a little bit of prog1.y86 to output my little own message. Somehow I got it to minimize my terminal window every time I run it. I dont know if that happens to you on your computer but I found that pretty cool too. 


