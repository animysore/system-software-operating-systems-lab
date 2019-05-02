#include <iostream>

typedef struct node { 
    int pi;
    struct node* next;
} node;

using namespace std;

int n, tq, *at,*bt,*rbt,*tat,*wt;

void roundrobin() { 
    // current time 
    int ct = 0, pindex=1, tatsum=0, wtsum=0, timeleft=((bt[0]>=tq)?tq:bt[0]);
    node *head=NULL, *temp=NULL, *tail=NULL;

    head = new node;
    head->pi = 0;
    head->next = NULL;
    tail = head;
    while(true) { 
        cout<<"=======\nTime:"<<ct<<" Counter: "<<timeleft<<endl; 
        // if current time matches a process, 
        if( pindex<n && ct == at[pindex]) {
            cout<<"Arrived: Process "<<pindex+1<<endl; 
            // creating a new node and append into queue 
            temp = new node;
            temp->pi = pindex;
            temp->next = NULL;

            // append to tail.
            if(tail) { 
                tail->next = temp;
                tail = temp;
            }
            else { 
                tail = temp;
            }
            pindex++;
        }
        // if timer rings, finish the current process and start new one 
        if(timeleft==0) {
            int i = head->pi; 
            cout<<"Processed "<<i+1;
            rbt[i] = (rbt[i]>=tq)? rbt[i]-tq : 0;    
            cout<<"\nrbt of process = "<<rbt[i]<<endl;
            // if process complete
            if(rbt[i] == 0) {
                cout<<"Process completed!\n"; 
                // compute tat and wt
                tat[i] = ct - at[i];
                wt[i] = tat[i] - bt[i];
                tatsum += tat[i];
                wtsum += wt[i];
                // delete node from queue
                temp = head;
                head = head->next;
                delete temp;
            } 
            else { 
                // add process to end of queue
                tail->next = head;
                tail = tail->next;
                head = head->next;
                tail->next = NULL;
            }
        }
        if (head==NULL) break;
        else {
            if(timeleft == 0) { 
                int j = head->pi;
                timeleft = (rbt[j]<tq)?rbt[j]:tq;
                cout<<"Starting "<<head->pi+1<<" with counter="<<timeleft<<endl;
            }
        }
        
        ct++; timeleft--;
    }
    cout<<"\n+++\nAverage Turn around time = "<<(float)tatsum/n <<"\nAverage wait time = "<<(float)wtsum/n<<endl;    
}

void shortesttime() { 
    // current time 
    int ct = 1, pindex=1, tatsum=0, wtsum=0;
    node *head=NULL, *pos=NULL, *prev=NULL, *temp=NULL;
    head = new node;
    head->pi = 0;
    head->next = NULL;

    while(true) { 
        cout<<"=======\nTime:"<<ct<<endl; 
        
        // process the job 
        int i = head->pi;          
        cout<<"Processed "<<i+1;
        rbt[i] -= 1;    
        cout<<"\nrbt of process = "<<rbt[i]<<endl;
        // if process complete
        if(rbt[i] == 0) {
            // compute tat and wt
            tat[i] = ct - at[i];
            wt[i] = tat[i] - bt[i];
            cout<<"COMPLETED! TAT= "<<tat[i]<<" WT = "<<wt[i]<<endl; 

            tatsum += tat[i];
            wtsum += wt[i];
            // delete node from queue
            temp = head;
            head = head->next;
            delete temp;
        } 
        // if current time matches a process, 
        if( pindex<n && ct == at[pindex]) {
            cout<<"Arrived: Process "<<pindex+1<<endl; 
            // creating a new node and insert into queue at position correspondint to bt 
            temp = new node;
            temp->pi = pindex;
            temp->next = NULL;  
            // search for position 
            for( pos=head, prev=head; pos!=NULL; pos=pos->next) { 
                if(rbt[pos->pi] >= rbt[temp->pi]) break;
                prev = pos; 
            }
            // case 1- empty queue
            if(!head) { 
                cout<<"this shouldn't happen should it ? \n";
                head->next = temp;
                head = temp;
            }
            // case 2 - new process has max burst time
            else if (!pos) { 
                prev->next = temp;
            }
            else { 
                //case 3a processes have equal rbt - append after pos
                if((rbt[pos->pi] == rbt[temp->pi]) ) { 
                    temp->next = pos->next;
                    pos->next = temp;
                }
                //case 3b new process preempts pos
                else { 
                    cout<<"PREEMPTING P "<<pos->pi<<endl;
                    temp->next = pos;
                    
                    if(head==pos) head = temp;
                    else prev->next = temp;
                    
                }
            }
            pindex++;
        }
        if (head==NULL) break;
        
        ct++;
    }
    cout<<"\n+++\nAverage Turn around time = "<<(float)tatsum/n <<"\nAverage wait time = "<<(float)wtsum/n<<endl;    
}
int main() { 
    cout<<"No. of processes and Time quantum\n";
    cin>>n>>tq;
    
    at = new int[n];
    bt = new int[n];
    rbt = new int[n];
    tat = new int[n];
    wt = new int[n];
    
    cout<<"Arrival Time, Burst Time"<<endl;
    for (int i=0; i<n; i++) { 
        cin>>at[i]>>bt[i];
        rbt[i] = bt[i];
    }

    cout<<"Round Robin: \n";
    roundrobin();
    cout<<"Shortest Time: \n";
    //shortesttime();
    return 0;
}