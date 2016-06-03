#include "PowerSetString.h"

/* creates a node for a singularly linked list and appends itself to the top of the stack */
void push(Node **head_node, const char* cstring, const int cstring_length, const int last_index) {
	Node* temp_node = malloc(sizeof(Node));
	assert(temp_node != 0);

	temp_node->S = malloc(sizeof(char)*cstring_length); 
	assert(temp_node->S != 0); 
	strncpy(temp_node->S,cstring,cstring_length);

	temp_node->length = cstring_length;
	temp_node->last_index = last_index;
	temp_node->next = *head_node;               // Next is really the previously pushed node
	*head_node =temp_node;
} 

/* removes the top of the stack and returns it */
Node* pop(Node **head_node) {
		Node *temp_node = *head_node; // grab the current head
		*head_node = temp_node->next; // remove head from stack	
		return temp_node;	
}

size_t djb2Hash(char* str) {
	size_t hash = 5381;
	int c;
	while ((c=*str++)) {
		hash = ((hash << 5) + hash) ^ c;
	}
	return hash;
}

// Creates memory space for a hash map of character & their frequency values within the base string
HashMap* hashMapCreate(size_t size)
{
    HashMap* m;

    m = malloc(sizeof(HashMap));
    assert(m != 0);

    m->size = size;
    m->map = calloc(m->size, sizeof(Node*));
    assert(m->map != 0);

    return m;
}

void destroyStack(Node *stack) {
	Node *item;
	while(stack!=NULL) {
		item=pop(&stack);
		free(item->S);
		free(item);		
	}
}

// Frees memory used for a hash map
void hashMapDestroy(HashMap* m)
{
    int i;
    for(i=0; i < m->size; i++) {
    	if(m->map[i]) {
    		destroyStack(m->map[i]);
    	}
    }
    free(m->map);
    free(m);
}

// inserts a new entry into the hash map structure
void hashMapInsert(HashMap* m, Node* n)
{
    size_t h;
    Node* item;
    h = djb2Hash(n->S) % m->size;
    item = m->map[h];
    if (item==0) {
		push(&m->map[h], n->S, n->length, 0);
	} else {
		while(item != 0) {
			if(strncmp(item->S,n->S,n->length) == 0) {
				printf("\t\t%s\n", "Duplicate detected!");
				return;   // Duplicate are not added again to the chain
			}
			item = item->next;
		}
		printf("\t\t\t%s\n", "Collison detected!");
		push(&m->map[h], n->S, n->length,0);
	} 
}

void printPset(Node *stack, HashMap* m) {
	int count=0;
	Node *item=stack;	
	printf("\tP(S)={\n%d)\t\t{} :\n",count++);
	while(item != NULL) {
		size_t h = djb2Hash(item->S) % m->size;
		printf("%d)\t\t{", count++);         //Lists the number of the subset within the power set
		if(m->map[h]) {
			printf("%s} : %zu %s\n",item->S, h, m->map[h]->S);  //currently just gets first item on the chain...
		} else {
			printf("%s} not found, hash value %zu is empty! \n",item->S, h);
		}
		item=item->next;
	}
	printf("\t};\n");					
}

void calculatePowerSet(char *str, int str_length) {
	int i;
	Node *temp_stack = NULL;
	// this stack will be populated and used to replace the need for recursive calls
	for(i=0;i<str_length;i++) { 
		push(&temp_stack, &str[i], 1, i);
	}
	printf("\t\t%s\n", "let's a go");
	Node* item=NULL;
	while(temp_stack!=NULL) {
		item=pop(&temp_stack);
		printf("%s\n",item->S);
		printf("length: %d\n", item->length);
		push(&saved_stack, item->S, item->length, 0);    // consider removing saved_map and saved_stack from this function
		hashMapInsert(saved_map, saved_stack);
		printf("%s\n",saved_stack->S);
		printf("saved length: %lu\n", strlen(saved_stack->S));
		printf("stated length: %d\n", saved_stack->length);

		for(i=item->last_index; i<str_length-1; i++){                         //iterates last item through the size of the subset
			printf("\t tick: %d\n",i);
			push(&temp_stack, item->S, item->length+1, i+1);
			strncat(temp_stack->S,&str[i+1],1);
			printf("\t next char: %c\n",str[i+1]);
			printf("\t %s\n",temp_stack->S);
			printf("\t length: %d\n",temp_stack->length);
		}
		free(item->S);
		free(item);
		printf("\t tock : %s\n",item->S);		
	}
	printPset(temp_stack, saved_map);
	printf("%s\n","DONE");
}

int main(int argc, char **argv) {
	if (argc!=2) {
		printf("%s\n", "Only taking one thing at a time for now dummy");
        return 0;
	}

	int c, i, count, proceed=1, buffer_length = 20, str_length = strlen(argv[1]);
	size_t h;
	Node* item;
	saved_map = hashMapCreate((1 << (str_length+1)));
	sortStr(argv[1],str_length);
	calculatePowerSet(argv[1],str_length);

	printPset(saved_stack,saved_map);

	char* user_str = malloc(sizeof(char) * buffer_length);
	assert(user_str);

	while(1) {
		printf("%s\n", "Enter str to see it exists in the power set: ");
		while(1) {
			c = getchar();
			if (c==EOF || c=='\n') {
				proceed=0;
				break;
			}
			if (!isTokenizer(c)) {
				ungetc(c, stdin);
				break;
			}
		}
		if(proceed==0) {
			break;
		}
		i=0;
		while(1) {
			c = getchar();
			if(isTokenizer(c) || c==EOF) {
				user_str[i] = 0;       //terminating 0
				break;
			}
			user_str[i]=c;
			if (i == buffer_length - 1) { // buffer is full
				buffer_length = buffer_length + buffer_length;
				user_str = realloc(user_str, sizeof(char)*buffer_length);
				assert(user_str);
			}
			i++;
		}
		count=0;
		sortStr(user_str,i);
		h = djb2Hash(user_str) % saved_map->size;
		if (saved_map->map[h]) {
			printf("%s\n", "Hash hit! Checking entries...");
			item = saved_map->map[h];
			while(item) {
				printf("Entry #%d : %s",count, item->S);
				if(strncmp(item->S, user_str, item->length)!= 0) {
					printf(" -> %s\n", "not a match...");
				} else {
					printf(" -> %s\n", "match found!");
				}
				count++;
				item=item->next;			
			}
		} else {
			printf("%s\n", "Hash miss, this str could not be found...");
		}
		memset(user_str,0,buffer_length);
	}
	free(user_str);
	destroyStack(saved_stack);
	hashMapDestroy(saved_map);
	return 0;
}

