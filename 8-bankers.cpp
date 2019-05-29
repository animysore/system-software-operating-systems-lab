#include <iostream>

using namespace std;

int p,r, *Max, *alloc , *need , *avail, *done;

int how_doable(int process) { 
    int greedy=0;
    for(int i=0; i<r; i++) { 
        int rem = avail[i] - need[process*r + i];
        if(rem<0) return 0;
        if(rem==0) greedy=1;
    }
    return (greedy)? 1 : 2;
}

void doit(int process) { 
    cout<<"==============\nDoing process "<<process<<"\nCurrently available: ";
    for(int i=0; i<r; i++) cout<<avail[i]<<" ";
    cout<<"\nWhile doing process, available: ";
    for(int i=0; i<r; i++) { 
        avail[i] -= need[process*r +i];
        cout<<avail[i]<<" "; 
    }
    cout<<"\nAfter process releases, available: ";
    for(int i=0; i<r; i++) { 
        avail[i] += Max[process*r +i];
        alloc[process*r + i] = 0;
        cout<<avail[i]<<" ";
    }
    cout<<endl;
}
int main(int argc, char * argv[]) {

    cout<<"Enter number of processes and resources\n";
    cin>>p>>r;
    Max = new int[p*r];
    alloc = new int[p*r];
    need = new int[p*r];
    avail = new int[r];
    done = new int[p];

    cout<<"Enter Max:\n";
    for (int i=0; i<p; i++) { 
        for (int j=0; j<r; j++) { 
            cin>>Max[i*r + j];
        }
        done[i] = 0;
    }
    cout<<"Enter alloc:\n";
    for (int i=0; i<p; i++) { 
        for (int j=0; j<r; j++) { 
            cin>>alloc[i*r + j];
            need[i*r + j] = Max[i*r +j] - alloc[i*r+j];
        }
    }
    cout<<"Need is: \n";
    for (int i=0; i<p; i++) { 
        for (int j=0; j<r; j++) { 
            cout<<need[i*r + j]<<" ";
        }
        cout<<endl;
    }

    cout<<"Enter avail:\n";
    for (int i=0; i<r; i++) {
        cin>>avail[i];
    }

    for (int counter=0; counter<p; counter++) {
        int flag = 0, alt=-1, takealt=1, i; 
        for (i=0; i<p; i++) { 
            if (done[i]) continue;

            int preference = how_doable(i);            
            if(preference>0) flag = 1; 
            if(preference==1 && alt==-1) alt=i;
            if(preference==2) { takealt =0; break; }
        }
        if (!flag) {
            cout<<"Unsafe state!\n";
            break;
        }
        else { 
            int selected = (takealt) ? alt: i;
            doit(selected);
            done[selected] = 1;
        }
    }
    return 0;
}
