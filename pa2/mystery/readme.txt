Bhavin Soni
bbs39
171002303

__MYSTERY__

The mystery program takes in an integer n and prints out the nth Fibonacci number.

In order to figure out how the mystery program worked I had to read the given assembly code. This was the biggest challenge because I had to go line by line and try to figure out what each line exactly did and which registers were being used. Finding what "num" was frustrating since it did not make sense at first. However, after searching online and researching about assembly code I figured out that arrays were being used as a global variable, hence "num" being an array. Then the function "add" was practically a given since it was pretty easy to figure out that the function just adds two integers together. Then the function "compute_fib" was also easy to figure out that it was computing Fibonacci. The function also called upon "add" and "compute_fib" so I realized that it was using a recursive call. The hardest part was trying to figure out how the if statements and loops were being used within the main function and the "compute_fib" function since I found it weirdly coded. I programmed mystery to the best of my ability and it still computed the correct Fibonacci values and so hopefully I read the assembly code properly. 


Comparing Optimized vs Unoptimized Mystery

After doing a side by side comparison, I saw that optimized code tries to keep the variable values in registers as long as possible. In the unoptimized code the variables are are always stored in memory which affects the speed of the program. Therefore, in optimized code the variables are not consistently being used repeatedly and so it makes it more efficient when debugging and compiling. Optimized code also uses "testl" multiple times, which I found to be the 'and' instruction and checks if the resulting compilation is less than, greater than, or is equal to 0. It then jumps to the code based on the result. However, "test" does not store the result making it more efficient in time and comparisons. Therefore in general, it is safe to say that the optimize code minimizes the amount of registers and repetitiveness of variables.
