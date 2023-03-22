#include <iostream>

using namespace std;

struct Queue {

    Queue* next;
    Queue* prev;
    int key;
    Queue(Queue* e, Queue* p, int k) : next(e), prev(p), key(k) { }
};

bool isEmptyQueue = 1;
Queue* first, * last; //wskazniki na koniec i poczatek kolejki
Queue* beg; //wskaznik na poczatek listy

void ADD_END(Queue** firstel, int key) {
    Queue* tmp = *firstel;
    Queue* newnode = new Queue(NULL, NULL, key);

    if (*firstel != NULL) {
        //szukam ostatniego
        while (tmp->next != *firstel) {
            tmp = tmp->next;
        }
        //ostatni->next = nowyelement
        tmp->next = newnode;
        //nowy->next = pierwszy element
        newnode->next = (*firstel);
        //nowy->prev = ostatni element
        newnode->prev = tmp;
        //pierwszy->prev = nowy
        (*firstel)->prev = newnode;


    }
    else {
        *firstel = newnode;
        newnode->next = newnode;
        newnode->prev = newnode;
    }

}
void PRINT_FORWARD(Queue** firstel)
{
    Queue* act = *firstel;
    // Queue* prev = NULL;
    // Queue* next;
    if (*firstel != NULL) {
        while (true)
        {
            printf("%d ", act->key);
            act = act->next;
            if (act == *firstel)break;
        }
        printf("\n");
    }
    else printf("NULL\n");
}
void DEL_BEG(Queue** firstel) {
    Queue* tmp = *firstel;

    if (*firstel != NULL) {
        while (true) {
            tmp = tmp->next;
            if (tmp->next == *firstel)break;
        }
        if ((*firstel)->next == *firstel) {
            *firstel = NULL;
            return;
        }

        if (first == *firstel) {
            first = first->prev;
        }
        else if (last == *firstel) {
            last = last->next;
        }
        else {
            Queue* act = first;
            while (true) {
                if (act == *firstel) {
                    (act->prev)->next = act->next;
                    (act->next)->prev = act->prev;
                }
                if (act == last)break;
                act = act->prev;
            }
        }


        *firstel = (*firstel)->next;
        tmp->next = (*firstel);
        (*firstel)->prev = tmp;

    }

}

void DEL_END(Queue** firstel) {

    if (*firstel != NULL) {
        Queue* tmp = *firstel;


        while (true) {
            tmp = tmp->next;
            if (tmp->next->next == *firstel)break;
        }
        if ((*firstel)->next == *firstel) {
            if (first == (*firstel)) {
                first = NULL;
                last = NULL;
            }
            *firstel = NULL;
            return;
        }

        Queue* act = first;
        //    cout << tmp->next->key << endl;
        while (true) {
            if (act == tmp->next) {
                (act->prev)->next = act->next;
                (act->next)->prev = act->prev;
            }
            if (tmp->next == last) {
                last = last->next;

                break;
            }

            if (act == last)break;
            act = act->prev;

        }

        tmp->next = *firstel;
        (*firstel)->prev = tmp;

    }
}
// 1 2 3 4 5

void ADD_BEG(Queue** firstel, int key) {
    Queue* newq = new Queue(NULL, NULL, key);

    if (*firstel == NULL) {
        //  newq->next = *firstel;
        *firstel = newq;
        (*firstel)->next = *firstel;
        (*firstel)->prev = *firstel;

    }
    else {

        Queue* tmp = *firstel;

        //szukam elementu ostatniego
        while (true) {
            if (tmp->next == *firstel)break;
            tmp = tmp->next;
        }


        newq->next = *firstel;
        (*firstel)->prev = newq;
        tmp->next = newq;
        newq->prev = tmp;
        *firstel = newq;

        //  7 4 5 7 8 9
    }

}

void PRINT_BACKWARDS() {

    if (beg != NULL) {
        Queue* tmp = beg->prev;
        while (true) {
            printf("%d ", tmp->key);
            if (tmp == beg)break;
            tmp = tmp->prev;

        }printf("\n");
    }
    else {
        printf("NULL\n");
    }

}
/*
ADD_BEG 1
ADD_BEG 2
ADD_BEG 3
ADD_BEG 4
PRINT_BACKWARD
*/
int SIZE(Queue** firstel) {
    Queue* act = *firstel;
    int i = 0;
    if (*firstel != NULL)
        while (true) {

            i++;
            if (act->next == *firstel)break;
            act = act->next;

        }
    return i;
}
//1 2 3 4 5 
//1 2 3 4 5

int COUNT() {
    Queue* act = first;

    int i = 0;

    if (first != NULL) {
        while (true) {

            i++;
            if (act == last)break;
            act = act->prev;
        }
    }
    return i;
}



void ATPOSS(int key) {
    Queue* tmp = beg;
    int location = 0;

    while (true) {
        tmp = tmp->next;

        location++;
        if (tmp->prev == last) {
            break;
        }
    }

    tmp = beg;
    Queue* newq = new Queue(NULL, NULL, key);
    //  cout << location;
    if (location > 0) {
        for (int i = 1; i < location - 1; i++) {
            tmp = tmp->next;
        }

        newq->next = tmp->next;
        (tmp->next)->prev = newq;
        tmp->next = newq;
        newq->prev = tmp;
    }
    else ADD_BEG(&beg, key);
    // PRINT_FORWARD(&beg);

    last = last->prev;
    // last=newq;
   //  PRINT_FORWARD(&beg);
    // last->next = beg;
     //beg->prev = newq;
}

void push(int key) {
    Queue* tmp = first;

    if (isEmptyQueue == 1) {
        if (beg == NULL) {
            //  cout << "FFF";
            ADD_BEG(&beg, key);
            isEmptyQueue = 0;
            first = beg;
            last = first;
            return;
        }
        else {
            //   cout << "KKK";

            first = beg->prev;
            first->key = key;
            last = first;
            isEmptyQueue = 0;
            return;
        }
    }
    else {
        if (COUNT() == SIZE(&beg)) {
            //   ADDATPOS(key);

              // if (beg == first) {


            //   cout << beg->key << endl;
            if (first == last) {
                ADD_BEG(&beg, key);
                last = beg;
                first->prev = last;
                return;
            }
            else if (beg == last) {
                // cout << "tuuuu";
                ADD_BEG(&beg, key);
                while (true) {
                    tmp = tmp->prev;
                    if (tmp->prev == first) {
                        last->prev = tmp;
                        last = tmp;
                        break;
                    }
                }
                return;
            }
            else {
                ATPOSS(key);
            }
            /*       // last = beg;
                    // first->prev = last;

                    while (true) {
                        tmp = tmp->prev;
                        if (tmp->prev == first) {
                            last->prev = tmp;
                            last = tmp;
                            break;
                        }
                    }
                    return;
                }
                return;*/
                //  }
        }
        else if (COUNT() < SIZE(&beg)) {
            //    cout << "SS";
            while (true) {
                tmp = tmp->prev;

                if (tmp == last->prev) {

                    tmp->key = key;
                    last = tmp;
                    break;
                }
            }

        }
    }
}

void PRINT_QUEUE() {
    if (first == NULL || isEmptyQueue) printf("NULL\n");
    else {
        Queue* tmp = first;
        while (true) {

            printf("%d ", tmp->key);
            if (tmp == last || tmp->prev == NULL)break;
            tmp = tmp->prev;

        }
        printf("\n");
    }
}

void POP() {


    if (isEmptyQueue == 0) {
        Queue* tmp = first;
        printf("%d\n", first->key);
        if (first == last) {
            last = NULL;
            first = NULL;
            isEmptyQueue = 1;
        }
        else if (first->prev == last) {
            first = first->prev;
            last = first;
        }
        else {
            first = first->prev;
        }
    }
    else {
        printf("NULL\n");
    }


}

void GARBAGE_SOFT() {
    Queue* tmp = last;

    if (first == NULL) {
        tmp = beg;
        while (true) {
            tmp->key = 0;
            if (tmp->prev = beg)break;
            tmp = tmp->prev;

        }
    }
    else {
        while (tmp != first) {
            tmp = tmp->prev;
            if (tmp == first)break;
            tmp->key = 0;
        }
    }
}

void GARBAGE_HARD() {



    if (isEmptyQueue == 1) {
        beg = NULL;
        //beg->next = NULL;
    }
    else
    {
        last->prev = first;
        first->next = last;
    }


}

int main()
{
    int key;
    char cmd[20];
    while (cin >> cmd) {
        if (strcmp(cmd, "ADD_END") == 0) {
            cin >> key;
            ADD_END(&beg, key);

        }
        if (strcmp(cmd, "ADD_BEG") == 0) {
            cin >> key;
            ADD_BEG(&beg, key);

        }
        else if (strcmp(cmd, "PRINT_FORWARD") == 0) {
            PRINT_FORWARD(&beg);
        }
        else if (strcmp(cmd, "PRINT_BACKWARD") == 0) {
            PRINT_BACKWARDS();
        }
        else if (strcmp(cmd, "DEL_BEG") == 0) {
            DEL_BEG(&beg);
        }
        else if (strcmp(cmd, "DEL_END") == 0) {
            DEL_END(&beg);
        }
        else if (strcmp(cmd, "SIZE") == 0) {
            cout << SIZE(&beg) << "\n";
        }
        else if (strcmp(cmd, "PRINT_QUEUE") == 0) {
            PRINT_QUEUE();
        }
        else if (strcmp(cmd, "PUSH") == 0) {
            cin >> key;
            push(key);
        }
        else if (strcmp(cmd, "POP") == 0) {
            POP();

        }
        else if (strcmp(cmd, "COUNT") == 0) {
            cout << COUNT() << endl;
        }
        else if (strcmp(cmd, "GARBAGE_SOFT") == 0) {
            GARBAGE_SOFT();
        }
        else if (strcmp(cmd, "GARBAGE_HARD") == 0) {
            GARBAGE_HARD();
        }
    }
}
