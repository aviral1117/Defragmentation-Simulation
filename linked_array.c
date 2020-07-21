#include "linked_array.h"

LIST createList(int arr[],int ele,LIST heads[],int tails[],int nos){
    LIST a1;
    tails[nos-1] = free_head;
    //printf("In create list with free_head as %d;;;;\n",free_head);
    a1.head=free_head;
    arr[free_head]=ele;
    prev_point = arr[free_head+1];
    arr[free_head+1]=-1;
    arr[free_head+2]=-1;
    used[free_head/3]=true;
    free_head=prev_point;
    a1.size=1;
    total_free--;
    //printf("helllo");
    return a1;
}

void insertElement(int arr[],int n,LIST heads[],int tails[]){
    int i,ele;
    if(n+1 > no_of_lists){
        printf("FAILURE: The entered list number is not valid\n");
        return;
    }
    for(i=0;i<No_Of_Nodes;i++){
        if(used[i]==false){
            break;
        }
    }
    if(i==No_Of_Nodes){
        printf("FAILURE : MEMORY NOT AVAILABLE\n");
        return;
    }

    printf("Enter key value for the node to be added: ");
    scanf("%d",&ele); 

    arr[tails[n]+1]=free_head;
    arr[free_head]=ele;
    prev_point = arr[free_head+1];
    arr[free_head+1]= -1;
    arr[free_head+2]= tails[n];
    tails[n]=free_head;
    heads[n].size++;
    used[free_head/3]=true;
    free_head = prev_point;
    list_sort(arr,n,heads,tails);
    total_free--;
    printf("SUCCESS\n");
}

void list_sort(int arr[],int n,LIST heads[],int tails[]){
    //heads[n] stores the index of the starting node of list and tail stores the index of the last element of the list.
    for(int i=heads[n].head;i!=-1;i=arr[i+1]){
        for(int j=i;j!=-1;j=arr[j+1]){
            if(arr[i]>arr[j]){
                int temp = arr[j];
                arr[j]=arr[i];
                arr[i]=temp;
            }
        }
    }
}

void delete_node(int arr[],int n,LIST heads[],int tails[]){
    int m=-1;
    int ele;
    if(n+1 > no_of_lists){
        printf("FAILURE: The entered list number is not valid/ The list does not exist.\n");
        return;
    }
    printf("Enter key value for the node to be deleted: ");
    scanf("%d",&ele);
    for(int i=heads[n].head;i!=-1;i=arr[i+1]){
        if(arr[i]==ele){
            m=i;
            break;
        }
    }
    if(m==-1){
        printf("FAILURE : ELEMENT NOT THERE/LIST EMPTY\n");
        return; 
    }
    else if(m==heads[n].head){
        heads[n].head = arr[m+1];
        arr[arr[m+1]+2]=-1;
        prev_point = free_head;
        free_head = m;
        arr[m] = (m/3) + 1;
        arr[m+1] = prev_point;
        heads[n].size--;
        total_free++; 
    }
    else if(m==tails[n]){
        //printf("%d\t",tails[n]);
        tails[n] = arr[m+2];
        arr[arr[m+2]+1] = -1; 
        prev_point = free_head;
        free_head = m;
        arr[m] = (m/3) + 1;
        arr[m+1] = prev_point;
        heads[n].size--;
        total_free++;
    }
    else{
        //printf("Here\n");
        arr[arr[m+1]+2] = arr[m+2];
        arr[arr[m+2]+1] = arr[m+1];
        prev_point = free_head;
        free_head = m;
        arr[m] = (m/3) + 1;
        arr[m+1] = prev_point;
        heads[n].size--; 
        total_free++;
    }
    used[m/3]=false;
    printf("SUCCESS\n");
}

void printall(int arr[],LIST heads[],int tails[]){
    if(no_of_lists==0){printf("No lists exists; Please insert a list to view");return;}
    for(int j=0;j<no_of_lists;j++){
        printf("\nThe elements of list %d are:\n",j+1);
        printf("Key  next  prev:\n");
        for(int i=heads[j].head;i!=-1;i=arr[i+1]){
            printf("%d   ",arr[i]);
            if(arr[i+1] == -1)
                printf("NIL  ");
            else
                printf("%d  ",arr[i+1]);
            if(arr[i+2] == -1)
                printf("NIL\n");
            else
                printf("%d\n",arr[i+2]);
        }
    }
}

void printallfree(int arr[]){
    int m = free_head;
    int c=0;
    printf("The Elements of free list are:\n");
    printf("[");
    while(m!=-1){
        printf("%d, ",m);
        m=arr[m+1];
        c++;
        if(c==total_free-1)
            break;
    }
    if(m!=-1)
        printf("%d",m);
    printf("]\n\n");
}

void defrag(int arr[],LIST heads[],int tails[]){
    //printf("inside defrag\n");
    int filled = No_Of_Nodes-total_free;
    LIST local_head[1];
    int local_tails[1];
    local_head[0].head = free_head;
    int temp = free_head;
    int prev;
    while(1){
        if(temp==-1){
            local_tails[0] = prev;
            break;
        }
        prev = temp;
        temp = arr[temp+1];
    }
    list_sort_min(arr,0,local_head,local_tails);
    int checker = filled * 3;//from this index freeall should print.
    if(checker >= No_Of_Nodes*3)
    {
        printf("SUCCESS\n");
        return;
    }
    for(int i=0;i<no_of_lists;i++){
        if(heads[i].head >= checker){
            used[heads[i].head/3] = false;
            prev_point = arr[free_head+1];
            arr[free_head]=arr[heads[i].head];
            arr[free_head+1] = arr[heads[i].head + 1];
            arr[free_head+2]=-1;
            used[free_head/3]=true;
            temp = free_head;
            free_head = heads[i].head;
            arr[free_head + 1] = prev_point;
            arr[free_head] = (free_head/3) + 1;
            heads[i].head=temp;
            local_head[0].head = free_head;
            temp = free_head;
            list_sort_min(arr,0,local_head,local_tails);
        }
    }
    //printf("i am here\n");
    if(free_head == checker){
        printf("SUCCESS\n");
    }
    else{
        int i=checker;
        while(free_head!=checker){
            if(used[i/3]){
                //printf("Inside while if\n");
                used[i/3] = false;
                prev_point = arr[free_head+1];
                arr[free_head] = arr[i];
                arr[free_head+1] = arr[i+1];
                arr[free_head+2] = arr[i+2];
                int previous_node = arr[i+2];
                arr[previous_node+1] = free_head; 
                used[free_head/3] = true;
                free_head = i;
                arr[free_head + 1] = prev_point;
                arr[free_head] = (free_head/3) + 1;
                local_head[0].head = free_head;
                list_sort_min(arr,0,local_head,local_tails);
            }
            else{
                i=i+3;
                continue;
            }
        }
        printf("SUCCESS\n");
    }
}

void list_sort_min(int arr[],int n,LIST heads[],int tails[]){
    //printf("helllo in list sort min\n");
    int min = arr[heads[n].head];
    for(int i=heads[n].head;i!=-1;i=arr[i+1]){
        if(arr[i]<min)
            min = arr[i];
    }
    if(min == arr[heads[n].head])
        return;
    prev_point = (min-1)*3;
    arr[free_head+2] = arr[free_head+1];
    arr[free_head+1] = arr[prev_point+1];
    arr[prev_point+1] = free_head;
    arr[prev_point+2] = -1;
    free_head = prev_point;
    //printf("Exiting\n");
}