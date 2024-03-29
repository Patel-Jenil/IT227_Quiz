#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
// Jenil_Patel_202101074
// Query using linked list(i used double linked list) 
// Declaring global variables here...
int totalQuery = 0;
typedef struct query Query;
struct query **array = NULL;

// Function Declarations
void queryDetails(const Query*);
void showQueries();
Query* getDetails();
void addQuery();
void runQuery(int );
void completeQuery(int );
void deleteQuery(int );
void freeList();
void updateElapsedTime();
void removeAllCompletedQueries();

struct query {
    int query_id;
    char *query_text;
    time_t start_time;
    uint64_t time_elapsed;
    int query_status; // submitted=1 , running=2, finish=3
};

void queryDetails(const Query* prog) {
    if (!prog)
        return;
    printf("\n* Query-ID:%d\t\tStatus: ", prog->query_id);
    if (prog->query_status == 1) {
        printf("Submitted.\n");
    } else if (prog->query_status == 2) {
        printf("Running.\n");
    } else {        
        printf("Completed.\n");
    }
    printf("  Query Text: %s", prog->query_text);
    printf("  Start-Time: %s",ctime(&(prog->start_time)));
    printf("  Elapsed-Time: ");
    if (prog->time_elapsed > 59) {
        printf("%lu min %lu sec\n", (unsigned long)prog->time_elapsed/60 , (unsigned long) prog->time_elapsed%60 );
    } else {
        printf("%lu sec\n", prog->time_elapsed);
    }
}

void showQueries() {
    if (!array) {
        printf("\nNo Queries at the moment.\n");
        return;
    }
    printf("\nQuery List:\n");
    updateElapsedTime();
    for (int i=0; i<totalQuery; ++i) {
        queryDetails(array[i]);
    }
}

Query* getDetails() {
    Query* prog = (Query *) malloc(sizeof(Query));
    ++totalQuery;
    prog->query_id = totalQuery;
    prog->query_text = (char *) malloc(512) ;
    printf("Enter Query text: ");
    fgets(prog->query_text, 512 , stdin);
    prog->start_time = time(NULL);
    prog->time_elapsed = 0;
    prog->query_status = 1;
    return prog;
}

void addQuery() {
    Query* newQuery = getDetails();
    array = (Query** )realloc(array ,(sizeof(Query*) * totalQuery));
    array[totalQuery - 1] = newQuery;
    printf("\nQuery added.\n");
}

void runQuery(int id) {
    if (id <=0 || id > totalQuery) {
        printf("\nInvalid QID.\n");
        return;
    }
    if ( !array ){
        printf("\nQuery List is Empty.\n");
    }
    if (array[id - 1]->query_status == 2) {
        printf("\nQuery is already running with Text:\n%s", array[id - 1]->query_text);
    } else {
        array[id - 1]->query_status=2;
        array[id - 1]->start_time = time(NULL);
        printf("\nQuery is now running with Text:\n%s", array[id - 1]->query_text);
    }
}

void completeQuery(int id) {
    if (id <=0 || id > totalQuery) {
        printf("\nInvalid QID.\n");
        return;
    }
    if ( !array ){
        printf("\nQuery List is Empty.\n");
    }
    updateElapsedTime();
    if (array[id - 1]->query_status == 3) {
        printf("\nQuery is already completed with Text:\n%s", array[id - 1]->query_text);
    } else {
        array[id - 1]->query_status=3;
        printf("\nQuery is now completed with Text:\n%s", array[id - 1]->query_text);
    }
}

void deleteQuery(int i) {
    int curr_id = array[i]->query_id;
    for (int j = i+1; j < totalQuery; ++j) {
        array[j]->query_id = curr_id++;
    }
    for (int j = i; j < totalQuery-1; ++j) {
        *array[j] = *array[j+1];
    }
    free(array[totalQuery - 1]);
    --totalQuery;
    array = (Query** )realloc(array ,(sizeof(Query*) * totalQuery));
}

void updateElapsedTime() {
    if (!array)
        return;
    uint64_t current_time = time(NULL);
    for (int i = 0; i < totalQuery; ++i )
        if (array[i]->query_status == 2)
            array[i]->time_elapsed = current_time - array[i]->start_time;
}

void removeAllCompletedQueries() {
    if (!array) {
        printf("\nNo Programs at the moment.\n");
        return;
    }
    int isIT = 0;
    for (int i=0; i< totalQuery; ) {
        if (array[i]->query_status == 3) {
            deleteQuery(i);
            isIT++;
        } else {
            ++i;
        }
    }
    if (isIT) {
        printf("\n%d completed Quer%s removed.\n", isIT, isIT==1?"y":"ies");
    } else {
        printf("\nNo completed Queries at the moment.\n");
    }
}

void freeList() {
    for (int i=0; i<totalQuery; ++i) {
        array[i] = (Query*) realloc(array[i] , 0);
    }
    array = (Query**) realloc(array, 0);
    printf("\n***Memory Freed***\n");
}
int main() {

    char choice;
    int id;
    while (1) {
        printf("\n============================================\n");
        showQueries();
        printf("\n============================================\n");
        printf("\n1. Add new Query.\n");
        printf("2. Run a Query.\n");
        printf("3. Complete a Query.\n");
        printf("4. Update time-elapsed for running Queries.\n");
        printf("5. Remove all completed Queries.\n");
        printf("0. Exit.\n");
        printf("Choice: ");
        scanf("%c", &choice);
        fflush(stdin);
        switch(choice) {
        case '1':
            getchar();
            addQuery();
            break;
        case '2':
            printf("Enter I'd of the Query: ");
            scanf ("%d",&id);
            runQuery(id);
            getchar();
            break;
        case '3':
            printf("Enter I'd of the Query: ");
            scanf ("%d",&id);
            completeQuery(id);
            getchar();
            break;
        case '4':
            if (!array){
                printf("\nNo Queries at the moment.\n");
            } else {
                printf("\n***Updated Elapsed Time for running Queries***\n");
                updateElapsedTime();
            }
            getchar();
            break;
        case '5':
            removeAllCompletedQueries();
            getchar();
            break;
        case '0':
            printf("\nAdios Amigo\n");
            freeList();
            getchar();
            getchar();
            return 0;
        default:
            printf("Invalid choice!\n");
            getchar();
        }
        getchar();
    }
    return 0;
}