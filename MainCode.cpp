#include <iostream>
#include <stdlib.h>
using namespace std;

struct sector{
    int dvertex;
    double distance;
    sector * next;
};

struct SectorList{
    sector* head;
};

struct Graph{
    int vertices;
    SectorList* City;
};

struct minimumHeapNode{
    int  v;
    int dist;
};

struct minimumHeapStruct{
    int size;      
    int capacity;  
    int *position;     
    struct minimumHeapNode **array;
};

double dist[25];
int parent[25];
int DBL_MAX = 1.79769e+308;


int sectorToVertex(string);
string vertexToSector(int);
Graph* createISB(int);
sector* createSector(int, double);
void initializeSectors(Graph*);
void addEdge(Graph*, int, int, double);
minimumHeapNode* newMinimumHeapNode(int, int);
minimumHeapStruct* createminimumHeapStruct(int);
void swapminimumHeapNode(minimumHeapNode**, minimumHeapNode**);
void heapifyMinimum(minimumHeapStruct*, int);
int isEmpty(minimumHeapStruct*);
minimumHeapNode* extractMinimum(minimumHeapStruct*);
void decreaseDistValue(struct minimumHeapStruct*, int, int);
bool isInminimumHeapStruct(struct minimumHeapStruct* , int);
void printPathRecursively(int[], int);
void implementDijkstra(Graph*, int);
void printWholeGraph(Graph*);
void showtheSectors();
bool checkSectorString(string);
void printAllDistances(int, double[], int);


int main() {

    Graph* Islamabad = createISB(25);
    string sourc, dest;
    int choice;
    bool flag;

    /*
     * if you print the whole graph
     * printWholeGraph(Islamabad);
     */

    initializeSectors(Islamabad);

    cout << " ===== ISLAMABAD PATHS =====\n\n";

    while (true){

        cout << "1. Get Shortest Distance and Path from a specific Source to a specific Destination.\n"
                    "2. Get Shortest Distances of all sectors from a specific source.\n"
                    "0. Exit.\n"
                    "Please enter your choice: ";
        cin >> choice;

        cout << endl;

        switch (choice){

            case 0: {
                cout << "=== Program is terminating! ===\n";
                return 0;
            }

            case 1: {

                showtheSectors();

                cout << "Please enter the source Sector: ";
                cin;

                flag = false;

                while (!flag) {
                    cin >> sourc;
                    flag = checkSectorString(sourc);
                }

                flag = false;

                cout << "Please enter the destination Sector: ";

                while (!flag) {
                    cin >> dest;
                    flag = checkSectorString(dest);
                }

                implementDijkstra(Islamabad, sectorToVertex(sourc));

                cout << "\n=== Required Path ===\n\n";

                cout << "Source: " << sourc << "\n\n";
                cout << "Destination: " << dest << "\n\n";
                cout << "Distance: " << dist[sectorToVertex(dest)] << " km" << "\n\n";

                cout << "Path: " << sourc << "   ";
                printPathRecursively(parent, sectorToVertex(dest));
                cout << "\n\n";

                break;

            }

            case 2 : {

                showtheSectors();

                cout << "Please enter the source Sector: ";
                cin;

                flag = false;

                while (!flag) {
                    cin >> sourc;
                    flag = checkSectorString(sourc);
                }

                implementDijkstra(Islamabad, sectorToVertex(sourc));

                printAllDistances(sectorToVertex(sourc),  dist, 25);

                break;
            }

            default: {
                cout << "Invalid choice!\n";
            }

        }

    }

}

int sectorToVertex (string sector){
    if (sector == "E-11")
        return 0;
    else if(sector == "E-10")
        return 1;
    else if (sector == "E-9")
        return 2;
    else if(sector == "E-8")
        return 3;
    else if (sector == "E-7")
        return 4;
    else if (sector == "F-11")
        return 5;
    else if (sector == "F-10")
        return 6;
    else if (sector == "F-9")
        return 7;
    else if (sector == "F-8")
        return 8;
    else if (sector == "F-7")
        return 9;
    else if (sector == "F-6")
        return 10;
    else if (sector == "G-11")
        return 11;
    else if (sector == "G-10")
        return 12;
    else if (sector == "G-9")
        return 13;
    else if (sector == "G-8")
        return 14;
    else if (sector == "G-7")
        return 15;
    else if (sector == "G-6")
        return 16;
    else if (sector == "H-11")
        return 17;
    else if (sector == "H-10")
        return 18;
    else if (sector == "H-9")
        return 19;
    else if (sector == "H-8")
        return 20;
    else if (sector == "I-11")
        return 21;
    else if (sector == "I-10")
        return 22;
    else if (sector == "I-9")
        return 23;
    else if (sector == "I-8")
        return 24;
}

string vertexToSector(int sector){

    switch (sector){

        case 0:
            return "E-11";
        case 1:
            return "E-10";
        case 2:
            return "E-9";
        case 3:
            return "E-8";
        case 4:
            return "E-7";
        case 5:
            return "F-11";
        case 6:
            return "F-10";
        case 7:
            return "F-9";
        case 8:
            return "F-8";
        case 9:
            return "F-7";
        case 10:
            return "F-6";
        case 11:
            return "G-11";
        case 12:
            return "G-10";
        case 13:
            return "G-9";
        case 14:
            return "G-8";
        case 15:
            return "G-7";
        case 16:
            return "G-6";
        case 17:
            return "H-11";
        case 18:
            return "H-10";
        case 19:
            return "H-9";
        case 20:
            return "H-8";
        case 21:
            return "I-11";
        case 22:
            return "I-10";
        case 23:
            return "I-9";
        case 24:
            return "I-8";
        default:
            return "E-11";
            
    }
}

Graph * createISB(int v){
    Graph * isb = new Graph;
    isb->vertices = v;
    isb->City = new SectorList [25];

    for (int i = 0; i<v; i++){
        isb->City[i].head = NULL;
    }
    return isb;
}

sector * createSector(int destination, double distance){
    sector * newSector = new sector;
    newSector->dvertex = destination;
    newSector->distance = distance;
    newSector ->next = NULL;
    return newSector;
}

void initializeSectors(Graph* Islamabad){

    addEdge(Islamabad, sectorToVertex("E-11"), sectorToVertex("E-10"), 4.98);
    addEdge(Islamabad, sectorToVertex("E-10"), sectorToVertex("E-9"), 4.24);
    addEdge(Islamabad, sectorToVertex("E-9"), sectorToVertex("E-8"), 2.63);
    addEdge(Islamabad, sectorToVertex("E-8"), sectorToVertex("E-7"), 2.86);

    addEdge(Islamabad, sectorToVertex("F-11"), sectorToVertex("F-10"), 1.78);
    addEdge(Islamabad, sectorToVertex("F-10"), sectorToVertex("F-9"), 1.83);
    addEdge(Islamabad, sectorToVertex("F-9"), sectorToVertex("F-8"), 4.37);
    addEdge(Islamabad, sectorToVertex("F-8"), sectorToVertex("F-7"), 3.21);
    addEdge(Islamabad, sectorToVertex("F-7"), sectorToVertex("F-6"), 1.97);

    addEdge(Islamabad, sectorToVertex("G-11"), sectorToVertex("G-10"), 1.89);
    addEdge(Islamabad, sectorToVertex("G-10"), sectorToVertex("G-9"), 3.04);
    addEdge(Islamabad, sectorToVertex("G-9"), sectorToVertex("G-8"), 2.13);
    addEdge(Islamabad, sectorToVertex("G-8"), sectorToVertex("G-7"), 3.12);
    addEdge(Islamabad, sectorToVertex("G-7"), sectorToVertex("G-6"), 2.73);

    addEdge(Islamabad, sectorToVertex("H-11"), sectorToVertex("H-10"), 2.07);
    addEdge(Islamabad, sectorToVertex("H-10"), sectorToVertex("H-9"), 8.85);
    addEdge(Islamabad, sectorToVertex("H-9"), sectorToVertex("H-8"), 2.83);
    addEdge(Islamabad, sectorToVertex("I-11"), sectorToVertex("I-10"), 2.54);
    addEdge(Islamabad, sectorToVertex("I-10"), sectorToVertex("I-9"), 3.73);
    addEdge(Islamabad, sectorToVertex("I-9"), sectorToVertex("I-8"), 1.91);

    addEdge(Islamabad, sectorToVertex("E-11"), sectorToVertex("F-11"), 4.56);
    addEdge(Islamabad, sectorToVertex("F-11"), sectorToVertex("G-11"), 2.41);
    addEdge(Islamabad, sectorToVertex("G-11"), sectorToVertex("H-11"), 3.91);
    addEdge(Islamabad, sectorToVertex("H-11"), sectorToVertex("I-11"), 1.79);

    addEdge(Islamabad, sectorToVertex("E-10"), sectorToVertex("F-10"), 3.21);
    addEdge(Islamabad, sectorToVertex("F-10"), sectorToVertex("G-10"), 3.31);
    addEdge(Islamabad, sectorToVertex("G-10"), sectorToVertex("H-10"), 5.74);
    addEdge(Islamabad, sectorToVertex("H-10"), sectorToVertex("I-10"), 6.37);

    addEdge(Islamabad, sectorToVertex("E-9"), sectorToVertex("F-9"), 3.8);
    addEdge(Islamabad, sectorToVertex("F-9"), sectorToVertex("G-9"), 3.52);
    addEdge(Islamabad, sectorToVertex("G-9"), sectorToVertex("H-9"), 4.53);
    addEdge(Islamabad, sectorToVertex("H-9"), sectorToVertex("I-9"), 4.64);

    addEdge(Islamabad, sectorToVertex("E-8"), sectorToVertex("F-8"), 3.15);
    addEdge(Islamabad, sectorToVertex("F-8"), sectorToVertex("G-8"), 3.37);
    addEdge(Islamabad, sectorToVertex("G-8"), sectorToVertex("H-8"), 3.81);
    addEdge(Islamabad, sectorToVertex("H-8"), sectorToVertex("I-8"), 2.48);

    addEdge(Islamabad, sectorToVertex("E-7"), sectorToVertex("F-7"), 1.74);
    addEdge(Islamabad, sectorToVertex("F-7"), sectorToVertex("G-7"), 4.17);

    addEdge(Islamabad, sectorToVertex("F-6"), sectorToVertex("G-6"), 3.46);

}

void addEdge(Graph* graph, int src, int dest, double dist){
    sector * newSector = createSector(dest,dist);
    newSector->next = graph->City[src].head; 
    graph->City[src].head = newSector;

    newSector = createSector(src, dist);
    newSector->next = graph->City[dest].head;
    graph->City[dest].head = newSector;
}


minimumHeapNode* newMinimumHeapNode(int v, int dist){
    minimumHeapNode* minHeapNode = new minimumHeapNode; 
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}


minimumHeapStruct* createminimumHeapStruct(int capacity){

    minimumHeapStruct* minHeap = new minimumHeapStruct;

    minHeap->position = new int[capacity];
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = new minimumHeapNode*[capacity];

    return minHeap;
}

void swapminimumHeapNode(minimumHeapNode** a, minimumHeapNode** b){

    minimumHeapNode* temp = *a;
    *a = *b;
    *b = temp;

}

void heapifyMinimum(minimumHeapStruct* minHeap, int idx){

    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < minHeap->size &&
        minHeap->array[left]->dist < minHeap->array[smallest]->dist )
        smallest = left;

    if (right < minHeap->size &&
        minHeap->array[right]->dist < minHeap->array[smallest]->dist )
        smallest = right;

    if (smallest != idx){
        
        minimumHeapNode *smallestNode = minHeap->array[smallest];
        minimumHeapNode *idxNode = minHeap->array[idx];

        minHeap->position[smallestNode->v] = idx;
        minHeap->position[idxNode->v] = smallest;

        swapminimumHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

        heapifyMinimum(minHeap, smallest);
    }
}


int isEmpty(minimumHeapStruct* minHeap){
    return minHeap->size == 0;
}

minimumHeapNode* extractMinimum(minimumHeapStruct* minHeap){

    if (isEmpty(minHeap))
        return NULL;

    minimumHeapNode* root = minHeap->array[0];

    minimumHeapNode* last = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = last;

    minHeap->position[root->v] = minHeap->size-1;
    minHeap->position[last->v] = 0;

    --minHeap->size;
    heapifyMinimum(minHeap, 0);

    return root;
}



void decreaseDistValue(minimumHeapStruct* minHeap, int v, int dist){

    int i = minHeap->position[v];

    minHeap->array[i]->dist = dist;

    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist){
        
        minHeap->position[minHeap->array[i]->v] = (i-1)/2;
        minHeap->position[minHeap->array[(i-1)/2]->v] = i;
        swapminimumHeapNode(&minHeap->array[i],  &minHeap->array[(i - 1) / 2]);

        i = (i - 1) / 2;
    }
}

bool isInminimumHeapStruct(minimumHeapStruct *minHeap, int v){

    return ( minHeap->position[v] < minHeap->size ) ;
}

void printPathRecursively(int parent[], int j){

    if (parent[j] == - 1)
        return;

    printPathRecursively(parent, parent[j]);

    cout << vertexToSector(j) << "   ";
}

void implementDijkstra(Graph* graph, int sourc){

    int V = graph->vertices;

    minimumHeapStruct* minHeap = createminimumHeapStruct(V);

    for (int v = 0; v < V; ++v)
    {
        dist[v] = DBL_MAX;
        minHeap->array[v] = newMinimumHeapNode(v, dist[v]);
        minHeap->position[v] = v;

        parent[v] = -1;
    }

    minHeap->array[sourc] = newMinimumHeapNode(sourc, dist[sourc]);
    minHeap->position[sourc]   = sourc;
    dist[sourc] = 0;
    decreaseDistValue(minHeap, sourc, dist[sourc]);

    minHeap->size = V;

    while (!isEmpty(minHeap)){
        
        minimumHeapNode* minHeapNode = extractMinimum(minHeap);
        int u = minHeapNode->v; 

        sector* pCrawl = graph->City[u].head;

        while (pCrawl != NULL){

            int v = pCrawl->dvertex;

            if (isInminimumHeapStruct(minHeap, v) && dist[u] != DBL_MAX &&
                pCrawl->distance + dist[u] < dist[v]){

                dist[v] = dist[u] + pCrawl->distance;
                parent[v] = u;
                
                decreaseDistValue(minHeap, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }
    }
}


void printWholeGraph(Graph* Islamabad){

    for (int i = 0; i<25; i++){
        sector* temp = Islamabad->City[i].head;
        while(temp!=NULL){
            cout<<vertexToSector(i)<<"   "<<vertexToSector(temp->dvertex)<<"   "<<temp->distance<<endl;
            temp=temp->next;
        }
    }

}

void showtheSectors(){

    cout << "These are the sectors:\n\n";

    cout << "E-11    E-10    E-9    E-8    E-7\n"
            "F-11    F-10    F-9    F-8    F-7    F-6\n"
            "G-11    G-10   G-9   G-8    G-7   G-6\n"
            "H-11    H-10   H-9   H-8\n"
            "I-11     I-10     I-9    I-8\n\n";

}

bool checkSectorString(string sec){

    if (sec == "E-11" || sec == "E-10" || sec == "E-9" || sec == "E-8" || sec == "E-7" ||
        sec == "F-11" || sec == "F-10" || sec == "F-9" || sec == "F-8" || sec == "F-7" || sec == "F-6" ||
        sec == "G-11" || sec == "G-10" || sec == "G-9" || sec == "G-8" || sec == "G-7" || sec == "G-6" ||
        sec == "H-11" || sec == "H-10" || sec == "H-9" || sec == "H-8" ||
        sec == "I-11" || sec == "I-10" || sec == "I-9" || sec == "I-8" )
        return true;

    cout << "Invalid sector entered. Please enter again: ";
    return false;

}

void printAllDistances(int sourc, double dist[], int n){

    cout << "Source   Sector   Distance from Source\n";

    for ( int i = 0 ; i < n ; ++i ) {

        if ( dist[i] != 0 ) {
            cout << vertexToSector(sourc) << "\t\t" << vertexToSector(i) << "\t\t" << dist[i] << " kms\n";
        }

        else{
            cout << vertexToSector(sourc) << "\t\t" << vertexToSector(i) << "\t\t Source and Destination are same. \"0 kms\" " << "\n";
        }
    }

    cout << "\n\n";

}
