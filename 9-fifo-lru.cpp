#include <iostream>

class Page {
    public: 
        int value;
        Page * next;        
};

using namespace std;

Page * Table;
int tsize, n, *inputs, pagefaults=0;
    
void FIFO() {
    int front=-1, found;
    for (int i=0; i<tsize; i++) Table[i].value = -1;
    for (int i=0; i<n; i++) {
        // search to see if already in page table
        found = 0;
        if (front>=0) { 
            for (int j=0; j<tsize; j++) { 
                if(Table[j].value == inputs[i]) { 
                    found = 1;
                    break;
                }
            } 
        }
        if (! found ){
            front = (front + 1)%tsize;
            Table[front].value = inputs[i];
            pagefaults++;
        }
    }
}
void printChain(Page* front) { 
    for (Page * temp = front; temp!=nullptr; temp = temp->next) cout<<temp->value<<" -> ";
    cout<<endl;
}
void LRU() { 
    Page *front = nullptr, *curr = nullptr, *prev = nullptr, *prev2;
    int found, avail = 0;
    for ( int i=0; i<n; i++) { 
        // search to see if already in page table
        found = 0;
        //cout<<inputs[i]<<endl;
        if (front!=nullptr) {
            prev = front;
            curr = front;
            while(curr != nullptr) {
                if(curr->value == inputs[i]) {
                    //cout<<"found "<<inputs[i]<<endl;
                    found = 1;
                    prev->next = curr->next;
                    curr->next = front;
                    front = curr;
                    //printChain(front);
                    break;
                }
                if (curr->next == nullptr) prev2 = prev;
                prev = curr;
                curr = curr->next;
            }
        }
        if(!found){
            pagefaults++;
            if(avail<tsize){
                Page *temp = new Page();
                temp->next = front;
                temp->value = inputs[i];
                front = temp;
                avail++;
            }
            else { 
                // prev holds last element in list
                //cout<<"Prev2: "<<prev2->value<<endl;
                prev2->next = nullptr;
                prev->value = inputs[i];
                prev->next = front;
                front = prev;
            }
        }
    }
}

int main() { 
    bool choice;
    cout<<"Enter size of page table and number of inputs: \n";
    cin>>tsize>>n;
    Table = new Page[n]();
    inputs = new int[n];
    cout<<"Enter values: \n";
    for (int i=0; i<n; i++) { 
        cin>>inputs[i];
    }
    cout<<"FIFO or LRU?";
    cin>>choice;
    (choice) ? FIFO() : LRU();
    cout<<"Page faults: "<<pagefaults<<endl; 
    return 0;
}
