#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Ibrahim Irshaid Sec 1

//ToDo: Search the performed tasks too, improve formatting the print at search, print responses when adding, searching .., checking before adding if id exists
//To Inquire: should we cover every edge case for ex; inputting a string instead of int, should we load the tasks at the beginning of the program, search unperformed or all

//Assuming The user first launches the Tasks File and only loads it one time
 typedef struct Tasks
 {
 int TaskID;
 char TaskName [100];
 char TaskDate [15];
 float TaskDuration;
 int isUnDone;// flag to tell which task in the unperformed list has been undone
 struct Tasks* Next;
 }Tasks;

 typedef struct TaskStack
 {
 int TaskID;
 char TaskName [100];
 char TaskDate [15];
 float TaskDuration;
 struct TaskStack* Next;
 }TaskStack;

int main()
{
    Tasks* unperformed = (Tasks*)malloc(sizeof(Tasks));
    unperformed->Next = NULL;

    TaskStack* performed = (struct TaskStack*)malloc(sizeof(TaskStack));
    performed->Next = NULL;

    Tasks* performedL = (Tasks*)malloc(sizeof(Tasks));
    performedL->Next = NULL;

    printf("Welcome to Task Management System\n\n");
    int op =0;

    while(op!=10)
    {
    displayMainMenu();
    scanf("%d",&op);

    switch( op )
{
case 1: loadTasks(unperformed);
    break;
case 2: addTask(unperformed);
    break;
case 3: DeleteTask(unperformed);
    break;
case 4: SearchTask(unperformed, performedL);
    break;
case 5: PrintList(unperformed);
    break;
case 6: performTask(unperformed, performed, performedL);
    break;
case 7: UndoTask(performed, unperformed, performedL);
    break;
case 8: PrintList(performedL);
    break;
case 9: GenReport(unperformed, performedL);
    break;
case 10: printf("\nExiting... GoodBye!");
    break;
default: printf( "No such Operation!\tPLease try again.\n\n" );
break;
}
    }
    return 0;
}

void displayMainMenu()
{

    printf("\nPlease Select an Operation <1-10>:\n");
    printf("1. Load Tasks File\n2. Add a New Task\n3. Delete a Task\n4. Search for a Task\n");
    printf("5. View Unperformed Tasks\n6. Perform a Task\n7. Undo Last Performed Task\n8. View Performed Tasks\n9. Generate Summary Report\n10. Exit\n\n");


}

void Insert(int id, char name[100], char date[15], float duration,int s, struct Tasks* L, struct Tasks* P){
     struct Tasks* temp;
     temp = (struct Tasks*)malloc(sizeof(struct
     Tasks));
     temp->TaskID = id;
     strcpy(temp->TaskName, name);
     strcpy(temp->TaskDate, date);
     temp->TaskDuration = duration;
     temp->isUnDone = s;
     temp->Next = P->Next;
     P->Next = temp;
 }
  int IsLast(struct Tasks* P, struct Tasks* L)
  {
      return P->Next == NULL;
  }
  int IsEmpty(struct Tasks* L)
  {
    return L->Next == NULL;
  }
  void PrintList(struct Tasks* L)
  {
     struct Tasks* P = L;
     if( IsEmpty(L))
     printf("Empty list\n");
     else
     do{
         P=P->Next;
         printf("ID: %d\tTask Name: %-30s\t Task Date: %-15s\t Task Duration: %.2f\n",P->TaskID, P->TaskName, P->TaskDate, P->TaskDuration);
     }while( !IsLast(P, L) );
     printf("\n");
 }
 struct Tasks* FindPrevious(int id, struct Tasks* L)
 {
     struct Tasks* P;
     P = L;
     while(P->Next != NULL)
     {
        if(P->Next->TaskID == id)
            return P;
        P = P->Next;
     }
     printf("Task with ID %d Does Not Exist!\n", id);
     return NULL;
 }

void loadTasks (Tasks* L)
{

    FILE* f = fopen("tasks.txt", "r");
    if (f == NULL)
    {
        printf("Error opening file tasks.txt\n");
        return;
    }
    printf("Task File Loaded:\n\n");
    char line[256];
    while (fgets(line, sizeof(line), f))
        {

                char* token = strtok(line, "#");
                int id = atoi(token);

                token = strtok(NULL, "#");

                char name[100];
                strcpy(name, token);

                token = strtok(NULL, "#");

                char date[15];
                strcpy(date, token);

                token = strtok(NULL, "#");

                float duration = atof(token);

                Tasks* P = L;
                while (!IsLast(P,L))
                P = P->Next;
                Insert(id, name, date, duration,0, L, P);


        }
     fclose(f);
     PrintList(L);
}

  void DelTask(int id, struct Tasks* L)// method to delete from task list passed the id parameter(used in perform/undo task functions)
 {
     struct Tasks* P;
     struct Tasks* temp;
     P = FindPrevious(id, L);
     if(P == NULL)
        printf("Could Not Be Deleted! Try Again");
     else if( !IsLast(P, L) )
        {
         temp = P->Next;
         P->Next = temp->Next;
         free(temp);
        }
 }

 struct Tasks* SearchByID(int id, struct Tasks* L)
 {
     struct Tasks* P ;
     P = L->Next;
     while(P != NULL)
     {
        if(P->TaskID == id)
            return P;

        P = P->Next;
     }
     return NULL;

 }

 struct Tasks* SearchByName ( struct Tasks* L)
 {
     char name[100];
     printf("Enter Task Name to Search:\n");
     scanf("%s", &name);
     //printf("%s\n", name);
     struct Tasks* P;
     P = L->Next;
     while(P != NULL)
     {
        if(strcmp(P->TaskName, name) == 0)
            return P;

        P = P->Next;

     }
     printf("Task\" %s \"Does Not Exist!\n", name);
     return NULL;
 }
  void addTask(struct Tasks* L)
 {
     int id;
     char name[100];
     char date[15];
     float dueration;

     printf("Please Enter The Task's ID:\n");
     scanf("%d",&id);

     if(SearchByID(id, L) != NULL)//to check if the task already exists
     {
         printf("Task with ID: %d already exist! Unable to add Task\n",id);
         return;
     }
         printf("Please Enter The Task's Name:\n");
         scanf("%s",&name);
         printf("Please Enter The Task's Date:\n");
         scanf("%s",&date);
         printf("Please Enter The Task's Duration:\n");
         scanf("%f",&dueration);

         Tasks* P = L;
         while (P->Next != NULL)
            P = P->Next;

         Insert(id, name, date,dueration,0, L, P);// new tasks has the isUndone flag = 0 by default
         printf("\nTask has been added successfully\n");
 }

 void DeleteTask(struct Tasks* L)
 {
     int id;
     struct Tasks* P;
     struct Tasks* temp;
     printf("Enter Task ID to Delete:\n");
     scanf("%d", &id);
     P = FindPrevious(id, L);
     if(P == NULL)
        printf("Could Not Be Deleted! Try Again\n");// does not search in the performed list since there is no sense in deleting it
     else if( !IsLast(P, L) )
        {
         temp = P->Next;
         P->Next = temp->Next;
         free(temp);
         printf("\nTask Has Been Deleted\n");
        }
 }

 void SearchTask(struct Tasks* L1, struct Tasks* L2)// searches the performed and unperformed lists both by either name or id
 {
     int method = 0;
     while(method != 1 || method != 2)
     {
        printf("To Search Task by ID Enter 1, To Search Task By Name Enter 2 or Enter 3 to Exit Search\n");
        scanf("%d", &method);

        if(method == 1)
        {
            int id;
            printf("Enter Task ID:\n");
            scanf("%d", &id);
            Tasks* P = SearchByID(id,L1);
            if(P != NULL)
            {
                printf("Task Found: Task ID: %d\tTask Name: %-30s\tTask Date: %-15s\tTask Duration: %.2f\tTask is Unperformed\n",P->TaskID, P->TaskName, P->TaskDate, P->TaskDuration);
                return;
            }
            P = SearchByID(id, L2);
            if (P == NULL)
            {
                printf("Task With ID %d Does Not Exist!\n", id);
                printf("Could not Find Task! Try Again\n");
            }
            else
              printf("Task Found: Task ID: %d\tTask Name: %-30s\tTask Date: %-15s\tTask Duration: %.2f\tTask is Performed\n",P->TaskID, P->TaskName, P->TaskDate, P->TaskDuration);
        }

        else if(method == 2)
        {
            Tasks* P = SearchByName(L1);
            if(P != NULL)
            {
                printf("Task Found: Task ID: %d\tTask Name: %-30s\tTask Date: %-15s\tTask Duration: %.2f\tTask is Unperformed\n",P->TaskID, P->TaskName, P->TaskDate, P->TaskDuration);
                return;
            }
            P = SearchByName(L2);
            if(P != NULL)
            {
                printf("Task Found: Task ID: %d\tTask Name: %-30s\tTask Date: %-15s\tTask Duration: %.2f\tTask is Performed\n",P->TaskID, P->TaskName, P->TaskDate, P->TaskDuration);
            }
            else
              printf("Could not Find Task! Try Again\n");
        }
         else if(method == 3)
            break;

        else
            printf("Invalid Input! Try Again\n");
     }
 }
 void Push(int id, char name[100], char date[15], float dueration, TaskStack* S )
 {

     TaskStack* temp;
     temp = ( TaskStack* )malloc( sizeof( struct TaskStack ) );
     if( temp == NULL)
     printf( "Out of space!");
     else
     {
         temp->TaskID = id;
         strcpy(temp->TaskName, name);
         strcpy(temp->TaskDate, date);
         temp->TaskDuration = dueration;
         temp->Next = S->Next;
         S->Next = temp;
     }
 }
 void performTask(struct Tasks* UnP, struct TaskStack* S, struct Tasks* Per)
 {
     char name[100];
     char date[15];
     int id;
     printf("Enter Task ID:\n");
     scanf("%d", &id);
     Tasks* temp = SearchByID(id, UnP);
     if(temp != NULL)
     {
         id = temp->TaskID;
         strcpy(name, temp->TaskName);
         strcpy(date, temp->TaskDate);
         float duration = temp->TaskDuration;

         DelTask(id, UnP);
         Push(id, name, date, duration, S);
         Tasks* P = Per;
         while (P->Next != NULL)
         P = P->Next;
         Insert(id, name,date,duration,0,Per, P );
         printf("Task has been performed successfully\n");
     }
     else
        printf("Could Not Perform Task");

 }
 int IsEmptyS( TaskStack* S )
 {
    return S->Next == NULL;
 }
 void UndoTask (struct TaskStack* S, struct Tasks* L, struct Tasks* Per)
 {
    TaskStack* first;
    if( IsEmpty( S ) )
        printf( "Empty stack");
    else
        {
            first = S->Next;
            Tasks* P= L;
            int id = first->TaskID;
            char name[100];
            char date [15];
            strcpy(name, first->TaskName);
            strcpy(date, first->TaskDate);
            float duration = first->TaskDuration;

            while (P->Next != NULL)
                P = P->Next;
            Insert(id, name, date, duration,1, L, P);// undone tasks has isUndone flag set to 1
            S->Next = S->Next->Next;
            free( first );
            DelTask(id, Per);
            printf("Task Undone\n");
        }
 }
 void GenReport(struct Tasks* L1, struct Tasks* L2)
 {
    FILE* f = fopen("Report.txt", "w");
    struct Tasks* P= L1;
    fprintf(f, "Unperformed Tasks:\n");
    if( IsEmpty(L1))
        printf("Empty list\n");
    else
        do
        {
            P=P->Next;
            fprintf(f, "ID: %d\tTask Name: %-30s\t Task Date: %-15s\t Task Duration: %.2f\n",P->TaskID, P->TaskName, P->TaskDate, P->TaskDuration);
        }while( !IsLast(P, L1) && P->Next->isUnDone == 0);

    fprintf(f, "\nUndone Tasks:\n");
    if( IsEmpty(L1))
        printf("Empty list\n");
    else
        do
        {
            P=P->Next;
            fprintf(f, "ID: %d\tTask Name: %-30s\t Task Date: %-15s\t Task Duration: %.2f\n",P->TaskID, P->TaskName, P->TaskDate, P->TaskDuration);
        }while( !IsLast(P, L1) && P->Next->isUnDone == 1);//to print undone tasks using the isUndone flag

    fprintf(f, "\nPerformed Tasks:\n");
    struct Tasks* Pe = L2;
    if( IsEmpty(L2))
        printf("Empty list\n");
    else
        do
        {
            Pe=Pe->Next;
            fprintf(f, "ID: %d\tTask Name: %-30s\t Task Date: %-15s\t Task Duration: %.2f\n",Pe->TaskID, Pe->TaskName, Pe->TaskDate, Pe->TaskDuration);
        }while( !IsLast(Pe, L2) );
     printf("\n");

     printf("Report Generated Successfully\n");

 }





