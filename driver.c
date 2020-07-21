#include<stdio.h>
#include"linked_array.h"

bool used[No_Of_Nodes];
int prev_point;
int no_of_lists=0;
int free_head=0;
int total_free=No_Of_Nodes;

int main(int argc, int argv[]){
    LIST heads[MAX];//stores the heads of all the lists.
    int tails[MAX];
    int option =-1;
    int arr[No_Of_Nodes*3];
    int j=0;
    int i;
    int k=1;
    for(i=1;i<((No_Of_Nodes*3)-3);i=i+3){
        arr[i-1] = k;
        arr[i]= i+2;
        arr[i+1]=-1;
        used[j]=false;
        j++;
        k++;
    }
    arr[i-1]=k;
    arr[i+1]=-1;
    arr[i]=-1;
    used[No_Of_Nodes-1]=false;
    printf("Program in starting.....");

    while(option!=0){
        printf("Select an option:\n 1. Create a new list \n 2. Insert a new element in a given list in sorted order\n 3. Delete an element from a given list\n 4. Count total elements excluding free list\n 5. Count total elements of a list\n 6. Display all lists\n 7. Display free list\n 8. Perform defragmentation\n 9. Press 0 to exit: \n");
        scanf("%d",&option);//reading from user
        if(option == 1){
            int count=0;
            for(int i=0;i<No_Of_Nodes;i++){
                if(used[i])
                    count ++;
            }
            if(no_of_lists==MAX || count == No_Of_Nodes){
                printf("FAILURE: MEMORY NOT AVAILABLE\n");
                continue;
            }
            int ele;
            no_of_lists++;
            printf("The sequence number of newly created list is: %d\n",no_of_lists);
            printf("Enter Key element: ");
            scanf("%d",&ele);
            heads[no_of_lists-1]=createList(arr,ele,heads,tails,no_of_lists);
            printf("SUCCESS\n");
            tails[no_of_lists-1]=heads[no_of_lists-1].head;
        }
        else if(option == 2){
            int n;
            printf("Enter list number in which to add: ");
            scanf("%d",&n);
            insertElement(arr,n-1,heads,tails);
        }
        else if(option == 3){
            int n;
            printf("Enter list number from which to delete: ");
            scanf("%d",&n);
            delete_node(arr,n-1,heads,tails);
        }
        else if(option == 4){
            int count=0;
            for(int i=0;i<No_Of_Nodes;i++){
                if(used[i])
                    count ++;
            }
            printf("Total number of nodes in all the lists are: %d\n",count);
        }
        else if(option == 5){
            int n;
            printf("Enter list number: ");
            scanf("%d",&n);
            printf("The total number of nodes in list '%d' is: %d\n",n,heads[n-1].size);
        }
        else if(option == 6){
            printall(arr,heads,tails);
        }
        else if(option == 7){
            printallfree(arr);
        }
        else if(option == 8){
            defrag(arr,heads,tails);
        }
    }

    printf("'0' selected.... EXITING\n");
}

