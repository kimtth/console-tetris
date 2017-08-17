#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char ** split_comma(char* text) {

	char partial;
	char buff[100];

	int i = 0;
	int j = 0;
	int k = 0;

	//for return,
	//this need to set in the heap. malloc set data in the heap, so it will keep in memory before calling free()
	//char **list without malloc will be remove memory after end of function call, because it record in stack area.
	char **list = malloc(10 * sizeof(char*));

	for (int i = 0; i < 10; i++) {
		list[i] = strdup("");
	}

	//char *buff = (char *) malloc(sizeof(char) * 20); size of heap cannot fixed without realloc.
	//when you want to add element dynamically, it need to using char buff[100].
	//so buff can be modified and add one char to buff.

	//printf("%d\n", sizeof(list) / sizeof(char*)); //why retrn 1 ??
	while (text[i] != '\0') {
		partial = text[i];

		if (partial == ',') {
			buff[k] = '\0'; //for blocking weird char end of string.

			//add to list
			char* tmp = strdup(buff);

			/* strdup(buff) is posix standard. this is same as below.
			 int bufflen = strlen(buff) + 1;
			 char *tmp = (char*)malloc(bufflen * sizeof(char));
			 strcpy(tmp, buff);
			*/

			list[j] = tmp;

			//initialize buffer
			for (int idx = 0; idx < k; idx++) {
				buff[idx] = '\0';
			}

			k = 0;
			j++;
		} else {
			buff[k] = partial;

			k++;
		}
		i++;
	}

	//last element
	//add to list
	char* tmp = strdup(buff);
	list[j] = tmp;

	return list;
}

int main_x() {
	char **list = split_comma("1111,2,333,4455");

	printf("main\n");
	for (int i = 0; i < 10; i++) {
		printf("%i ", i);
		printf("%s\n", list[i]);
	}

	free(list);

	return 0;
}
