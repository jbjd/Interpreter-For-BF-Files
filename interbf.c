#include <stdio.h>

int cellIndex = 0;
char cells[30000];

void readFile(char *fileStr, long index){

	while(fileStr[index] != 0){
		//printf("%d ", index);
		switch (fileStr[index]){
			case '>':
				++cellIndex;
				break;
			case '<':
				--cellIndex;
				break;
			case '+':
				++cells[cellIndex];
				break;
			case '-':
				--cells[cellIndex];
				break;
			case '.':
				putc(cells[cellIndex], stdout);
				break;
			case ',':
				cells[cellIndex] = getc(stdin);
				break;
			case '[':
				if(cells[cellIndex] == 0){
					int evenBrackets = 1;
					while(evenBrackets != 0){
						++index;
						if(fileStr[index] == 0){
							// error, no closing ]
							return;
						}
						if(fileStr[index] == '['){
							++evenBrackets;
						}else if(fileStr[index] == ']'){
							--evenBrackets;
						}
					}
					break;
				}
				readFile(fileStr, index+1);
				--index;
				break;
			case ']':
				return;
			default:
				break;
		}
		++index;
	}
}

int main(int argc, char *argv[])
{
	if(argc<2) return 1;

	FILE *f = fopen(argv[1], "r");
	if(!f){
		fclose(f);
		return 1;
	}

	fseek(f, 0L, SEEK_END);
	long fsize = ftell(f),
	i = 0;
	char fileStr[fsize+1];
	fseek(f, 0L, SEEK_SET);
	char ch = fgetc(f);
	while(!feof(f)){
		switch (ch){
			case '+':
			case '-':
			case ']':
			case '[':
			case '.':
			case ',':
			case '>':
			case '<':
				fileStr[i] = ch;
				++i;
				break;
			default:
				break;
		}
		ch = fgetc(f);
	}
	fileStr[i] = 0;

	readFile(fileStr, 0);

	fclose(f);
	return 0;
}
