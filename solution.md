##Solutions Write Up for Anmol Agarwal
## Part 1: Building C source with Makefile (2pt)

part1: driver1.c memsets.c 
	$(CC) -c $^
	$(CC) driver1.o memsets.o -o $@

This solution compiles driver1.c and memsets.c files into object files
Then, the second line takes the object files and links to an output executable file named part1

## Part 2: Creating a static library (2pt)

part2: driver1.c memsets.c
	$(CC) -c $^
	ar -crs libmemsets.a memsets.o
	$(CC) driver1.o libmemsets.a -o $@
	./$@

This compiles the driver1.c and memsets.c files into object files
Then ar is used to create an archive file from the memsets.o object file
Then, the driver1.o object file is linked to the part2 executable file using the static library file libmemsets.a

## Part 3: Creating a dynamic library (3pt)

part3: driver1.c memsets.c
	$(CC) -c $^
	$(CC) -shared -o libmemsets.so memsets.o
	$(CC) -o $@ $< -L. -l memsets
	export LD_LIBRARY_PATH=".";./$@	

This solution compiles the driver1.c and memsets.c into object files
Then, the second line creates a shared library libmemsets.so using the -shared
option
The third line links the shared library into the part3 executable file using the -L. option which specifies to look into the current directory and the -l option specifies to look at the shared library called memsets. Note, that -l uses the library name instead of the filename.
I also exported the LD_LIBRARY_PATH to be the current directory so that when part3 is run, it looks at the current directory to find the shared library file

## Part 4: Dynamically load a library (3pt)
I modified driver4.c source file to make changes and used dlopen to open the libmemsets.so library. I referred to the dlopen man page to find out how to open the library.

  handle = dlopen("./libmemsets.so", RTLD_LAZY);

I also used the dlsym function to create the various mem functions.The line below indicates how I used dlsym.

  _memset1 = (void* (*) (void*, char, size_t)) dlsym(handle, "memset1");

I used dlsym for each of the memfunctions as shown above and then replaced the replace_me part with the respective mem function. I also modified the Makefile as shown below. 

part4: driver4.c part3
	$(CC) $< -ldl -o $@
	./$@

This is compiling driver4.c and then uses ldl to link the file to the part4 executable file. ldl is the library designation for the linker to find and link the file. I also run part4 to see the output. 

## Part 5: Library interposing with LD_PRELOAD (bonus 5pt)
For part5, I first created my own memset() function in memset1.c file. This new memset() function has a string that will be printed out each time it is called: "You've been hacked!". This function has the same name and arguments as the old memset function, so I can use LD_PRELOAD to use this new function instead.
I then did the following commands in my makefile to run my new memset function with the part3 executable.

	$(CC) -c ./memset1.c
	$(CC) -shared -o memset1.so memset1.o
	export LD_LIBRARY_PATH="."; LD_PRELOAD=./memset1.so ./$<

I first compile my memset1.c file and then create a shared library called memset1.so with the memset1 object file. Then, I export the LD_LIBRARY_PATH to be the current directory again so that the current directory is used and use LD_PRELOAD to run the new memset1 shared library with the part3 executable. When I run the command make part5, I see the console output the string "You've been hacked!" several times, which indicates my new memset function is being used and LD_PRELOAD worked. 
