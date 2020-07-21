#include<stdbool.h>
#include<stdio.h>

#define MAX 1000 //maximum number of expected lists. 
#define No_Of_Nodes 1000

extern bool used[No_Of_Nodes];
extern int prev_point;
extern int no_of_lists;
extern int free_head;
extern int total_free;

//Struct used for maintaining list heads only.
//max no of lists allowed
struct head_size{
    int head;
    int size;
};
typedef struct head_size LIST;

LIST createList(int arr[],int ele,LIST heads[],int tails[],int nos);
void insertElement(int arr[],int n,LIST heads[],int tails[]);
void list_sort(int arr[],int n,LIST heads[],int tails[]);
void delete_node(int arr[],int n,LIST heads[],int tails[]);
void printall(int arr[],LIST heads[],int tails[]);
void printallfree(int arr[]);
void defrag(int arr[],LIST heads[],int tails[]);
void list_sort_min(int arr[],int n,LIST heads[],int tails[]);
