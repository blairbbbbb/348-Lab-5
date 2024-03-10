all: problemOne #problemTwo

# Compile programone
problemOne: problemOne.c
	gcc problemOne.c -o problemOne

# Compile programtwo
#problemTwo: problemTwo.c
#	cc -o problemTwo.c -o problemTwo

# Clean build files
clean:
	rm -f problemOne problemTwo