//Name: Brooke Alviar NETID: bca27
#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h> 
#define DIE(msg)    exit (fprintf (stderr, "%s\n", msg)) // Print error message unless COND is true
#define ORDIE(cond,msg)     if (cond) ; else DIE(msg)
#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0]) 
#define CHAR_SIZE (26) 
#define CHAR_TO_INDEX(c) ((int)c - (int)'a') 
  
struct Trie
{ 
    char* isWord;
    int count;
    struct Trie* character[CHAR_SIZE];
}; 

struct Trie* getNewTrieNode()
{ 
    struct Trie* node = (struct Trie*)malloc(sizeof(struct Trie)); 
    node->count = 0;
    node->isWord = NULL;
	for (int i = 0; i < CHAR_SIZE; i++) {
		node->character[i] = NULL;
	}
    return node; 
} 

// If not present, inserts key into trie 
// If the key is prefix of trie node, just marks leaf node 
void insert(struct Trie *head, char *str) 
{ 
    struct Trie* curr = head;
    int n = strlen(str);
    for (int i = 0; i < n; i++) {
    	int index = CHAR_TO_INDEX(str[i]);

    	if (curr->character[index] == NULL)
    		curr->character[index] = getNewTrieNode();

    	curr = curr->character[index];
    } 
    curr->isWord = strdup(str);
} 

// int check(struct Trie* currnode)
// {
// 	if (currnode == NULL) {
// 		return 0;
// 	}
// 	if (currnode->isWord == NULL) {
// 		return 1;
// 		printf("incomplete word\n");
// 	}
// 	if (currnode->isWord != NULL) {
// 		currnode->count = currnode->count + 1;
// 		printf("INCREMENT %s\n", currnode->isWord);
// 	}
// 	return 1;
// }

void printWords(struct Trie *node, int cflag) 
{
	if (node == NULL) {
		return;
	}
	if (node->count > 0 && node->isWord != NULL && cflag == 0) {
		printf("%s: %i\n", node->isWord, node->count);
	}
	if (node->count == 0 && node->isWord != NULL && cflag == 1) {
		printf("%s\n", node->isWord);
	}
	for (int i = 0; i < 26; i++) {    
                if (node->character[i]!= NULL) {   
                    printWords(node->character[i], cflag);
            }   
    }           
}

void searchWord(struct Trie *currnode, char *board, int i, int j, bool visited[], int nrows, int ncols, int tflag) 
{ 
	char boggle[nrows][ncols];
		for (int m = 0; m < (nrows); m++) {
			for (int n = 0; n < (ncols); n++) {
				boggle[m][n] = board[m * ncols + n];
			}
		}

    if (currnode != NULL) {

    	if (currnode->isWord != NULL && visited[i * ncols + j] == false) {
    		currnode->count = currnode->count + 1;
    	}

	    if (visited[i * ncols + j] == false) 
	    { 
	        
	    	if (tflag == 1) {
		    	visited[i * ncols + j] = true;
		    }

	        for (int K = 0; K < CHAR_SIZE; K++) 
	        { 
	            if (currnode->character[K] != NULL) 
	            { 	
	                // current character 
	                char ch = K + (char)'a'; 

	                if (i < (nrows - 1) && j < (ncols - 1)) {
		                if (boggle[i+1][j+1] == ch || boggle[i+1][j+1] == '_') {	
		                    searchWord(currnode->character[K],board,i+1,j+1,visited,nrows,ncols,tflag); 
		                }
		            }
		            if (j < (ncols - 1)) {
		                if (boggle[i][j+1] == ch || boggle[i][j+1] == '_') {
		                    searchWord(currnode->character[K],board,i, j+1,visited,nrows,ncols,tflag); 
		                }
		            }
		            if (i > 0 && j < (ncols - 1)) {
		                if (boggle[i-1][j+1] == ch || boggle[i-1][j+1] == '_') {
		                    searchWord(currnode->character[K],board,i-1, j+1,visited,nrows,ncols,tflag); 
		                }
		            }
		            if (i < (nrows - 1)) {
		                if (boggle[i+1][j] == ch || boggle[i+1][j] == '_') {
		                    searchWord(currnode->character[K],board,i+1, j,visited,nrows,ncols,tflag);
		                }
		            }
	                if (i < (nrows - 1) && j > 0) {
		                if (boggle[i+1][j-1] == ch || boggle[i+1][j-1] == '_') {
		                    searchWord(currnode->character[K],board,i+1, j-1,visited,nrows,ncols,tflag); 
		                }
		            }
		            if (j > 0) {
		                if (boggle[i][j-1] == ch || boggle[i][j-1] == '_') {
		                    searchWord(currnode->character[K],board,i,j-1,visited,nrows,ncols,tflag); 
		                }
		            }
		            if (i > 0 && j > 0) {
	               		if (boggle[i-1][j-1] == ch || boggle[i-1][j-1] == '_') {
		                    searchWord(currnode->character[K],board,i-1, j-1,visited,nrows,ncols,tflag); 
		                }
		            }
		            if (i > 0) {
		                if (boggle[i-1][j] == ch || boggle[i-1][j] == '_') {
		                    searchWord(currnode->character[K],board,i-1, j,visited,nrows,ncols,tflag); 
		                }
		            }
	       
	            } 
	        }
	    	visited[i * ncols + j] = false; 
	    } 
	}
}

void findWords(char *board, struct Trie* root, int nrows, int ncols, int cflag, int tflag) 
{ 
    bool visited[nrows * ncols];     // Mark all characters as not visited 
    memset(visited,false,sizeof(visited)); 
  
    struct Trie *pChild = root; 

    char boggle[nrows][ncols];

	for (int m = 0; m < (nrows); m++) { 
		for (int n = 0; n < (ncols); n++) {
			boggle[m][n] = board[m * ncols + n];
		}
	}
    // traverse all matrix elements 
    for (int i = 0 ; i < nrows; i++)  { 
        for (int j = 0 ; j < ncols ; j++) { 
            // we start searching for word in dictionary if we found a character which is child of Trie root 
            if (pChild->character[CHAR_TO_INDEX(boggle[i][j])] != NULL ) 
            { 
                searchWord(pChild->character[CHAR_TO_INDEX(boggle[i][j])], 
                           board, i, j, visited, nrows, ncols, tflag);
            }
            else {
            	for (int q = 0; q < CHAR_SIZE; q++) {
    				if (pChild->character[q] != NULL && (boggle[i][j] == '_')) {
    					 searchWord(pChild->character[q], 
                           board, i, j, visited, nrows, ncols, tflag);
    				}
    			}
        	}
    	} 
    }

    printWords(root, cflag);
}
//separate print function
int main(int argc, char *argv[])
{
	struct Trie *head = getNewTrieNode(); int start = 1; int notinsert = 0;
	int nrows = 0; int ncols = 0; char *board = NULL; int cflag = 0; int tflag = 0; int traysize = 0;

	if (argc != 4 && argc != 5 && argc != 6) {
			fprintf(stderr, "%s", "Invalid input 1\n");
			exit(0);
	}

	if (argc == 5) {
		start = 2;
		if (argv[1][0] == '-') {
			if (argv[1][1] == 'c') 
				cflag = 1;
			else if (argv[1][1] == 't') 
				tflag = 1;
			else {
				fprintf(stderr, "%s", "Invalid input\n"); exit(0);
			}
		}
		else {
			fprintf(stderr, "%s", "Invalid input\n"); exit(0);
		}
	}

	if (argc == 6) {
		start = 3;
		if (argv[1][0] == '-') {
			if (argv[1][1] == 'c') 
				cflag = 1;
			else {
				fprintf(stderr, "%s", "Invalid input\n"); exit(0);
			}
		}
		if (argv[2][0] == '-') {
			if (argv[2][1] == 't') 
				tflag = 1;
			else {
				fprintf(stderr, "%s", "Invalid input\n"); exit(0);
			}
		}
		else {
			fprintf(stderr, "%s", "Invalid input\n"); exit(0);
		}
	}

	if (!isdigit(argv[start][0]) || !isdigit(argv[start + 1][0])) { //checking h and w
		fprintf(stderr, "%s", "Invalid input\n"); exit(0);
	}
	for (int j = 0; j<strlen(argv[start + 2]); j++) {
		if (!isalpha(argv[start + 2][j]) && ((argv[start + 2][j]) != '_')) { //alphabet char or blank
			fprintf(stderr, "%s", "Invalid input 3\n"); exit(0);
		}
	}

	nrows = atoi(argv[start]); ncols = atoi(argv[start + 1]); board = argv[start + 2]; 
	//once there are assignments

	traysize = nrows*ncols;
	if ((strlen(board) != traysize)) {
		fprintf(stderr, "%s", "Invalid input\n"); exit(0);
	}

	for (int b = 0; b<strlen(board); b++) {
		if (isalpha(board[b]) && isupper(board[b])) {
			board[b] = tolower(board[b]);
		}
	}
	//ARG PARSING DONE ABOVE

	char *line = NULL;  size_t len = 0;

	while (getline(&line, &len, stdin) != -1) { //remove newline char? how will dict be formatted? //how to ignore '-'? I know how to find it but not how to ignore
		int len = strlen(line);		
		if(line[len-1] == '\n') { //removing the newline char
		   line[len-1] = 0;
		}

		for (int q = 0; q<strlen(line); q++) { //makinng sure chars are alphabetic;
			if (!isalpha(line[q])) {
				notinsert = 1;
			}
		}

		for (int j = 0; j<strlen(line); j++) { //making all chars lowercase;
			if (!islower(line[j])) {
				line[j] = tolower(line[j]);
			}
		}
		if (notinsert == 0) {
			insert(head, line); 
		}
		notinsert = 0;
	} 
	findWords(board, head, nrows, ncols, cflag, tflag);

exit(0);
}
