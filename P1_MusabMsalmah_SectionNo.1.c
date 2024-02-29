#include <stdio.h>
#include <stdlib.h>

typedef struct bus * Bus;
typedef struct passenger * pass;
int flag = 0;


struct bus{           //struct to the bus
    int bus_num;
    char date[15];
    char dep_time[10];
    char from[15];
    char to[15];
    int price;
    int capacity;
    pass nextL;
};

struct passenger{       // struct to the passenger
    int id;
    char date[15];
    char travelTime[10];
    char from[15];
    char to[15];
    pass next;
};

int NOL(char fileName[20]){       //function to get number of lines from file
    FILE *f;
    int count = 0;
    f = fopen(fileName,"r");
    char c = getc(f);             //get the characters from the file
    if(c == EOF)                  //if the file empty return zero else return the number of lines
        count = 0;
    else
        count = 1;

    for (c = getc(f); c != EOF; c = getc(f)){ //get all the characters from the file and when the char == new line the counter will increse by one
        if (c == '\n')
            count++;
    }
    fclose(f);
    return count;
}

void insertPass(pass head,pass node){        //function to insert passengers to the linked list
    if(head == NULL){
        printf("There was not linked list");
    }
    else{
    pass temp = head;
    while(head != NULL && temp->next != NULL) //the inseartion
        temp = temp->next;

    temp->next = node;
    node->next = NULL;
    }
}

void readBUS(Bus b[]){                        //function to read bus file
    FILE *f;
    f = fopen("busses.txt","r");
    char *token;
    char line[200];
    int j=0;
    while(fgets(line,sizeof(line),f)){     //get the lines line by line

        int i=0;
        token = strtok(line,"#");  //cut the line to words in all #
        char take[7][20];
        while(token != NULL){
            strcpy(take[i],token);     //put the tokens in array
            token = strtok(NULL,"#");
            i++;
            }
            b[j] = (Bus) malloc(sizeof(struct bus));               //linked list declerations
            b[j]->nextL = (pass) malloc(sizeof(struct passenger));
            b[j]->nextL->next = NULL;

            int num = atoi(take[0]);     //put the items in the linked list
            b[j]->bus_num = num;
            strcpy(b[j]->date,take[1]);
            strcpy(b[j]->dep_time,take[2]);
            strcpy(b[j]->from,take[3]);
            strcpy(b[j]->to,take[4]);
            int price = atoi(take[5]);
            b[j]->price = price;
            int capacity = atoi(take[6]);
            b[j]->capacity = capacity;
            j++;
    }

    fclose(f);
    printf("The bus file was readen.\n");
    printf("**********************************************************************************************************************\n");
}

void readSTU(pass Pass[]){               //function to read the passengers file like the bus file
    FILE *f;
    f = fopen("passengers.txt","r");
    char *token;
    char line[200];
    int j=0;
    while(fgets(line,sizeof(line),f)){
        int i = 0;
        token = strtok(line,"#");
        char take[5][20];
        while(token != NULL){
            strcpy(take[i],token);
            token = strtok(NULL,"#");
            i++;
            }
            Pass[j] = (pass) malloc(sizeof(struct passenger));
            Pass[j]->next = NULL;

            int id = atoi(take[0]);
            Pass[j]->id = id;
            strcpy(Pass[j]->date,take[1]);
            strcpy(Pass[j]->travelTime,take[2]);
            strcpy(Pass[j]->from,take[3]);
            int  q,k=0;
            for(q=0;take[4][q];q++)                                  //remove spaces from the ends
            {
                take[4][q]=take[4][q+k];
                if(take[4][q]==' '|| take[4][q]=='\t' || take[4][q+1] =='\n')
                    {
                        k++;
                        i--;
                    }
    }
            strcpy(Pass[j]->to,take[4]);
            j++;
    }
            fclose(f);
            printf("-The bus passengers file was readen.\n");
            printf("**********************************************************************************************************************\n");
}

void Assign(Bus buss[],pass pas[],pass wait,int CountBus){ //function to assign passengers to the buses
    int CountPass = NOL("passengers.txt");
    int counter = 0;
    for(int i=0 ; i<CountPass ; i++){
        int k=1;
        for(int j=0 ; j<CountBus ; j++){
           if(strcmp(pas[i]->date,buss[j]->date) == 0 && strcmp(pas[i]->travelTime,buss[j]->dep_time) == 0 && strcmp(pas[i]->from,buss[j]->from) == 0 && strcmp(pas[i]->to,buss[j]->to) == 0 && buss[j]->capacity > 0){
            printf("-passenger with id: %d to buss number: %d\n\n",pas[i]->id,buss[j]->bus_num); //the if is to check if the passenger can added to the busses
            pass temp = buss[j]->nextL; //get the head of the linked list of the passengers that added the the bus

            insertPass(temp,pas[i]);

            buss[j]->capacity = buss[j]->capacity - 1; //put the capacity -1 bucouse there is a passenger added to the bus
            break;

            }

            if(k == CountBus){                                 //if we check all the busses and can not add to bus then we add to in matched
                    printf("-passenger with id: %d to waiting list\n\n",pas[i]->id);
                insertPass(wait,pas[i]);
                counter++;
            }
            k++;
            }
    }
    printf("**********************************************************************************************************************\n");

}

void print_busses_information(Bus bus[],pass wait,int CountBus){ //function to print the buss information with its passengers
    int size = CountBus;
    size = size-flag;                //to reduce the the number of busses that we print it if we delete any busses
    for(int i=0 ; i<size ; i++){
        Bus tempBus = bus[i];
        pass tempPas = tempBus->nextL;
        printf("-->Buss number: %d ,date: %s ,departure time: %s ,form: %s ,to: %s ,price: %d ,capacity: %d ,The passengers:- \n",tempBus->bus_num,tempBus->date,tempBus->dep_time,tempBus->from,tempBus->to,tempBus->price,tempBus->capacity);
        if(tempPas->next == NULL){
            printf("No passengers in this bus\n\n");
        }
        while(tempPas != NULL && tempPas->next != NULL){
            tempPas = tempPas->next;
             printf("-The id: %d ,the date: %s ,the travel time: %s ,from: %s ,to: %s .\n",tempPas->id,tempPas->date,tempPas->travelTime,tempPas->from,tempPas->to);
        }
        printf("\n");
    }
    printf("**********************************************************************************************************************\n");
}

void print_unMatched(pass wait){      //function to print the unmatched

    pass temp = wait;
    printf("The Unmatched passengers information:-\n");
    while(wait != NULL && temp->next != NULL){
        temp = temp->next;
        char copy[20];
        char date1[20];

        printf("-The id: %d ,the date: %s ,the travel time: %s ,from: %s ,to: %s.\n",temp->id,temp->date,temp->travelTime,temp->from,temp->to);

    }
    printf("\n");
    printf("**********************************************************************************************************************\n");
}

void add_pass(Bus buss[],pass wait,int CountBus){             //function to add passengerto the bus
            int id,date,travel_time;
            char from[20],to[20],travel_time_hours[5],travel_time_minites[5],dateDay[15],dateMounth[15],dateYear[15]; //ask the user to enter the informations
            printf("Enter the id:\n");
            scanf("%d",&id);
            for(int i=0 ; i<CountBus+1 ; i++){   //check if the id is exist or not
                pass temp;
                if(i == CountBus){
                    temp = wait;
                }
                else
                    temp = buss[i]->nextL;

                while(temp->next != NULL){           //to make the id of all passengers deffrent
                    if(temp->next->id == id){
                        printf("This id exist, Enter a new one: ");
                        scanf("%d",&id);
                    }
                    else{
                        temp = temp->next;

                }
                }
            }
            printf("Date of travinling:-\n");
            printf("Day: ");
            scanf("%s",dateDay);
            printf("Mounth: ");
            scanf("%s",dateMounth);
            printf("Year: ");
            scanf("%s",dateYear);
            strcat(dateDay,dateMounth);
            strcat(dateDay,dateYear);
            printf("Travilling time:-\n");
            printf("In hours: ");
            scanf("%s",travel_time_hours);
            printf("In minites: ");
            getchar();
            gets(travel_time_minites);
            printf("%s",travel_time_minites);
            strcat(travel_time_hours,":");
            strcat(travel_time_hours,travel_time_minites);
            printf("The diriction:-\n");
            printf("from: ");
            getchar();
            gets(from);
            printf("to: ");
            getchar();
            gets(to);

            //printf("%s\n",travel_time_hours);

            pass pas = (pass) malloc(sizeof(struct passenger)); //put the information to the node of linked list
            pas->next = NULL;
            pas->id = id;
            strcpy(pas->date,dateDay);
            strcpy(pas->travelTime,travel_time_hours);
            strcpy(pas->from,from);
            strcpy(pas->to,to);

            int k = 1;                     //check if the passenger can add to a bus
        for(int j=0 ; j<CountBus ; j++){
            char temp[15];
            strcat(temp,buss[j]->dep_time);
            strcat(temp,pas->to);
          //  printf("%d %d %d %d %d\n",strcmp(pas->date,buss[j]->date) == 0,strcmp(pas->travelTime,buss[j]->dep_time) == 0,strcmp(pas->from,buss[j]->from) == 0,strcmp(pas->to,buss[j]->to) == 0, buss[j]->capacity > 0);
           if(strcmp(pas->date,buss[j]->date) == 0  && strcmp(pas->travelTime,buss[j]->dep_time) == 0 && strcmp(pas->from,buss[j]->from) == 0 && strcmp(pas->to,buss[j]->to) == 0 && buss[j]->capacity > 0){
            printf("Add passenger with id: %d to buss number: %d.\n",pas->id,buss[j]->bus_num);
            pass temp = buss[j]->nextL;

            insertPass(temp,pas);

            buss[j]->capacity = buss[j]->capacity - 1;
            break;
            }
            printf("hello\n");
                k++;
                printf("%d\n",k);
            if(k == CountBus){
                    printf("Add passengers with id: %d to Unmatched passengers.\n",pas->id);
                    insertPass(wait,pas);
            }
            }
            printf("**********************************************************************************************************************\n");
}

void Delete_passenger(Bus bus[],pass wait,int CountBus){  //function to delete a passenger from a bus

    printf("Enter the id of the passenger: ");
    int id;
    scanf("%d",&id);
    printf("Enter the number of the bus: ");
    int num;
    scanf("%d",&num);
    int k = 0;
    for(int i=0 ; i<CountBus ; i++){   //find the bus with number num
            printf("%d\n",bus[i]->bus_num == num);
        if(bus[i]->bus_num == num){
            pass temp = bus[i]->nextL;
            while(temp!=NULL && temp->next != NULL && temp->next->id != id)  //find the node before the node we want to delete it
                temp = temp->next;

            if(temp->next == NULL){
                printf("-->There was no passenger with id: %d in bus number: %d.\n",id,num);
            }
            else{                              //delete the passenger
                 pass tempWait = wait;
                 while(tempWait->next != NULL)
                    tempWait = tempWait->next;

                 tempWait->next = temp->next;

                 temp->next = temp->next->next;
                 free(temp->next);
            }

            break;
        }
        k++;
        if(k == CountBus){ //if the bus number did not found
            printf("-->There was no bus with this number.\n");
        }

    }
    printf("**********************************************************************************************************************\n");

}

void delete_bus_number(Bus bus[],pass wait,int CountBus){  //function to delete a bus
    int num;
    printf("Enter the number of bus: ");
    scanf("%d",&num);
    int k = 0;
    for(int i=0 ; i<CountBus ; i++){ //find the bus with number num
        if(bus[i]->bus_num == num){
          pass temp = wait;
          while(temp != NULL && temp->next != NULL)
            temp = temp->next;
          temp->next = bus[i]->nextL->next; //add all passengers in this bus to the unmatched linked list

          free(bus[i]->nextL);
          for(int j=i ; j<CountBus-1 ; j++){  //delete the bus from the array of busses
            bus[j] = bus[j+1];
          }
          flag++; //in print function, print the passengers that did not removed
            break;
        }

        k++;
        if(k == CountBus){    //if there was not a bus
            printf("-->There was no bus with this number.\n");
        }
    }
    printf("**********************************************************************************************************************\n");
}

int main()
{
    printf("**********************************************************************************************************************\n");
    int CountBus = NOL("busses.txt");                   //count the number of busses
    pass wait = (pass) malloc(sizeof(struct passenger)); //make a ynmatched linked list
    wait->next = NULL;
    int countPas = NOL("passengers.txt");         //count the number of passengers
    Bus buss[CountBus];                   //array of busses
    pass pas[countPas];                     //array of passengers

    int counter = 0;

    printf("The menu:-\n1. Load the bus information.\n\n2. Load the passenger information file.\n\n3. Assign passengers.\n\n4. Print a specific bus information along with its passengers information.\n\n5. Print unmatched passengers.\n\n6. Add new passenger.\n\n7. Delete passenger.\n\n8. Delete bus number.\n\n9. Exit.\nEmter your choice:  ");
    int choice;
    scanf("%d",&choice);
    while(counter == 0){
    if(choice != 1){                        //declare the choices
        printf("You must enter number 1: ");
        scanf("%d",&choice);
    }
    else
        counter++;
    }
    while(choice != 9){ //switch statment to do the choice
    switch(choice){
        case 1:
            readBUS(buss);
            break;
        case 2:
            readSTU(pas);
            break;
        case 3:
            Assign(buss,pas,wait,CountBus);
            break;
        case 4:
            print_busses_information(buss,wait,CountBus);
            break;
        case 5:
            print_unMatched(wait);
            break;
        case 6:
            add_pass(buss,wait,CountBus);
            break;
        case 7:
            Delete_passenger(buss,wait,CountBus);
            break;
        case 8:
            delete_bus_number(buss,wait,CountBus);
            break;

  }
  printf("**********************************************************************************************************************\n");
    printf("The menu:-\n1. Load the bus information.\n\n2. Load the passenger information file.\n\n3. Assign passengers.\n\n4. Print a specific bus information along with its passengers information.\n\n5. Print unmatched passengers.\n\n6. Add new passenger.\n\n7. Delete passenger.\n\n8. Delete bus number.\n\n9. Exit.\nEmter your choice:  ");
    scanf("%d",&choice);
    if(counter == 1){
    if(choice != 2){
        printf("You must enter number 2: ");
        scanf("%d",&choice);
    }
    }
    else if(counter == 2){                   //declare the choices
    if(choice != 3){
        printf("You must enter number 3: ");
        scanf("%d",&choice);
    }
    }
    else if(counter >= 3){
    if(choice < 4 || choice > 9){
        printf("You must enter number between 4 to 9: ");
        scanf("%d",&choice);
    }
    }
    counter++;
    }

    return 0;
}
