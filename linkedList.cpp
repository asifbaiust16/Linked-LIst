#include<bits/stdc++.h>
using namespace std;

#define CHAIN_LENGTH 53
#define M 128

struct symbol_info{
    char *name;
    char *classtype;
    struct symbol_info *next;
} *block[CHAIN_LENGTH];

int cHash(char* name){
    int idx = 0;
    for(int i = 0; name[i]; ++i){
        idx = idx + name[i];
    }
    return (idx % CHAIN_LENGTH);
}
void cInsert(char* name, char* classtype){
    int pos = cHash(name);

    if( block[pos] == NULL ){
        block[pos] = new symbol_info();
        block[pos]->name = name;
        block[pos]->classtype = classtype;
        block[pos]->next = NULL;
    }
    else{
        symbol_info* newNode = new symbol_info();
        newNode->name = name;
        newNode->classtype = classtype;

        symbol_info* nextNode = block[pos];
        block[pos] = newNode;
        newNode->next = nextNode;
    }
}
bool cSearch(char* name, char* classtype){

    int pos = cHash(name);

    symbol_info* temp = block[pos];

    while( temp != NULL ){
        if( !strcmp( temp->name, name ) && !strcmp( temp->classtype, classtype ) ){
            return true;
        }
        temp = temp->next;
    }

    return false;
}

void cDelete(char* name, char* classtype){
    int pos = cHash(name);

    symbol_info* temp = block[pos];
    if(temp == NULL) return;

    if( temp->next == NULL && !strcmp( temp->name, name ) && !strcmp( temp->classtype, classtype ) ){
        block[pos] = NULL;
    }

    else if( !strcmp( temp->name, name ) && !strcmp( temp->classtype, classtype ) ){
        block[pos] = temp->next;
    }
    else{

        while( temp->next != NULL ){
                if ( !strcmp( temp->next->name, name ) && !strcmp( temp->next->classtype, classtype ) ){
                    printf("FOUND IT %s : %s\n", temp->name, temp->classtype );
                    break;
                }
            temp = temp->next;
        }

      if( temp != NULL ){
            symbol_info* found = temp->next;
            temp->next = found->next;
            delete(found);
        }
   }
}
int showMenu(){
    cout << "Menu:\n";
    cout << "=====\n";

    string message = "Enter 1 to insert(name, class type)\n"

                     "Enter 2 to search(name, class type)\n"
                     "Enter 3 to delete(name, class type)\n";

  cout << message << "\n";
  cout << "User Choice: ";
    int choice;
    scanf("%d", &choice);


    return choice;
}


int main(){




    int choice = showMenu();
    while( 1 ){

        char *name = new char[M];
        char *classtype = new char[M];


        switch(choice){
        case 1:
            {
                cout << "Insert Selected:\n";
                scanf("%s%s", name, classtype);

                // Omit the comma character
                int pos = strlen(name) - 1;
                if( name[ pos ] == ',' ){
                    name[ pos ] = '\0';
                }

                printf("%s %s\n", name, classtype);
                printf("%d\n", cHash(name) );
                cInsert(name, classtype);
            }
            break;

        case 2:
            {
                cout << "Search Selected:\n";

                scanf("%s%s", name, classtype);
                int pos = strlen(name) - 1;
                if( name[ pos ] == ',' ){
                    name[ pos ] = '\0';
                }

                printf("%s %s\n", name, classtype);
                printf("%d\n", cHash(name) );

                if( cSearch(name, classtype) ){
                    printf("FOUND\n");
                }else{
                    printf("NOT FOUND\n");
                }
            }
            break;
        case 3:
            {
                cout << "Delete Selected:\n";
                scanf("%s%s", name, classtype);
                int pos = strlen(name) - 1;
                if( name[ pos ] == ',' ){
                    name[ pos ] = '\0';
                }

                printf("%s %s\n", name, classtype);
                printf("%d\n", cHash(name) );

                cDelete(name, classtype);
            }
            break;
            default:
            return 0;
        };

        choice = showMenu();
        }
   return 0;
}

