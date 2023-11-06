// Aliya Goncalves Almeida & Maya Elysse

void printString(char *);
void printChar(char);
void readString(char *);
void readSector(char *, int);
void handleInterrupt21(int, int, int, int);

main()
{

/* Step 1
	char * s = "Hello World";
	printString(s);
*/


/* Step 2
	char line[80];
	printString("Enter a line: ");
	readString(line);
	printString(line);
*/


/* Step 3
	char buffer[512];
	readSector(buffer, 30);
	printString(buffer);
*/


/* Step 4
	makeInterrupt21();
	interrupt(0x21,0,"Enter a line: ",0,0);
	interrupt(0x21, 1, line, 0, 0);
*/


//Step 5

	char line[80];
	makeInterrupt21();
	interrupt(0x21,1,line,0,0);
	interrupt(0x21,0,line,0,0);


	while(1){}
}

void printChar(char chars)
{
		interrupt(0x10, 0xe*256+chars,0,0,0);
}

void printString(char* chars)
{
	char al = '\n';
	while(*chars != '\0'){

		al = *chars;
		interrupt(0x10, 0xe * 256 + al, 0, 0, 0);
		chars++;
	}
}

void readString(char* str)
{
	int i =0;
	int length = 80;
	int enterKey = 0xd;
	int lineFeed = 0xa;
	int endString = 0x0;
	int backSpace = 0x8;

	while(i != length)
	{
		str[i] = interrupt(0x16,0,0,0);
		printChar(str[i]);

		if(str[i] == enterKey){
			str[i+1] = lineFeed;
			printChar(lineFeed);
			str[i+2] = endString;
			break;
		}

		else if(str[i] == backSpace){
			if(i > 0){

				printChar(' ');
				printChar(backSpace);
				i--;
			}
		}

		else{
			i++;
		}
	}
}


void readSector(char * buffer, int sector)
{
	int ax = 2*256+1;
	int cx = 0*256+sector+1;
	int dx = 0*256+0x80;

	interrupt(0x13, ax, buffer, cx, dx);
}

void handleInterrupt21(int ax, int bx, int cx, int dx)
{
/*
Step 4
	if(ax == 0){
		printString("Hello World");
	}

	else if(ax > 1){
		readString(bx);
*/


//Step 5
	if(ax == 0){
		printString(bx);
	}

	else if(ax == 1){
		readString(bx);
	}

	else if(ax == 2){
		readSector(bx, cx);
	}

	else if(ax > 3){
		printString("An error occured when ax is greather than 2");
	}
}
