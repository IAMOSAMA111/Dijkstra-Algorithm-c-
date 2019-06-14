#include <iostream>
#include <stdlib.h>
//#include <limits>
using namespace std;

/* Structures part - 1 */

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

/* Structures part - 2 */

struct minimumHeapNode{
    int  v;
    int dist;
};

// Structure to represent a min heap
struct minimumHeapStruct{
    int size;      // Number of heap nodes present currently
    int capacity;  // Capacity of min heap
    int *position;     // This is needed for decreaseDistValue()
    struct minimumHeapNode **array;
};

// Global Declarations
double dist[25];
int parent[25];
int DBL_MAX = 1.79769e+308;

// Function Definitions
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
void printWholeGraph(Graph* Islamabad);
void showtheSectors();
bool checkSectorString(string);

// Driver coder
int main() {

    // Make a graph Islamabad of pointer-type Graph
    Graph* Islamabad = createISB(25);
    string sourc, dest;
    int choice;
    bool flag;

    // add edges
    initializeSectors(Islamabad);

    /*
     * If you want to print the whole graph
     * printWholeGraph(Islamabad);
    */


    cout << " ===== ISLAMABAD PATHS =====\n\n";

    while (true){

        cout << R"(Press "1" to get a path from source to destination or "0" to exit: )";
        cin >> choice;

        cout << endl;

        if ( choice == 0 ){
            cout << "=== Program is terminating! ===\n";
            return 0;
        }

        else if ( choice == 1 ){

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
        }

        else {
            cout << "Invalid choice!\n";
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
            // if not the switch case, return E-11 as default
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
    newSector->next = graph->City[src].head; // like with stack, add the new destination on top of the old destination so that traversal is not needed.
    graph->City[src].head = newSector;

    newSector = createSector(src, dist);
    newSector->next = graph->City[dest].head;
    graph->City[dest].head = newSector;
}

// A utility function to create a new Min Heap Node
minimumHeapNode* newMinimumHeapNode(int v, int dist){
    minimumHeapNode* minHeapNode = new minimumHeapNode; 
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}

// A utility function to create a Min Heap
minimumHeapStruct* createminimumHeapStruct(int capacity){

    minimumHeapStruct* minHeap = new minimumHeapStruct;

    minHeap->position = (int *) malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct minimumHeapNode**)
                                malloc(capacity * sizeof(struct minimumHeapNode*));

    return minHeap;
}

// A utility function to swap two nodes of min heap. Needed for min heapify
void swapminimumHeapNode(minimumHeapNode** a, minimumHeapNode** b){

    minimumHeapNode* temp = *a;
    *a = *b;
    *b = temp;

}

// A standard function to heapify at given idx
// This function also updates positionition of nodes when they are swapped.
// Position is needed for decreaseDistValue()
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
        // The nodes to be swapped in min heap
        minimumHeapNode *smallestNode = minHeap->array[smallest];
        minimumHeapNode *idxNode = minHeap->array[idx];

        // Swap positions
        minHeap->position[smallestNode->v] = idx;
        minHeap->position[idxNode->v] = smallest;

        // Swap nodes
        swapminimumHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

        heapifyMinimum(minHeap, smallest);
    }
}

// A utility function to check if the given minHeap is empty or not
int isEmpty(minimumHeapStruct* minHeap){
    return minHeap->size == 0;
}

// Standard function to extract minimum node from heap
minimumHeapNode* extractMinimum(minimumHeapStruct* minHeap){

    if (isEmpty(minHeap))
        return NULL;

    // Store the root node
    minimumHeapNode* root = minHeap->array[0];

    // Replace root node with last node
    minimumHeapNode* last = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = last;

    // Update positionition of last node
    minHeap->position[root->v] = minHeap->size-1;
    minHeap->position[last->v] = 0;

    // Reduce heap size and heapify root
    --minHeap->size;
    heapifyMinimum(minHeap, 0);

    return root;
}

// Function to decreasy dist value of a given vertex v. This function
// uses position[] of min heap to get the current index of node in min heap
void decreaseDistValue(minimumHeapStruct* minHeap, int v, int dist){

    // Get the index of v in  heap array
    int i = minHeap->position[v];

    // Get the node and update its dist value
    minHeap->array[i]->dist = dist;

    // Travel up while the complete tree is not hepified.
    // This is a O(Logn) loop
    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist)
    {
        // Swap this node with its parent
        minHeap->position[minHeap->array[i]->v] = (i-1)/2;
        minHeap->position[minHeap->array[(i-1)/2]->v] = i;
        swapminimumHeapNode(&minHeap->array[i],  &minHeap->array[(i - 1) / 2]);

        // move to parent index
        i = (i - 1) / 2;
    }
}

// A utility function to check if a given vertex
// 'v' is in min heap or not
bool isInminimumHeapStruct(minimumHeapStruct *minHeap, int v){

    return ( minHeap->position[v] < minHeap->size ) ;
}

void printPathRecursively(int parent[], int j){

    // Base Case : If j is source
    if (parent[j] == - 1)
        return;

    printPathRecursively(parent, parent[j]);

    cout << vertexToSector(j) << "   ";
}


// The main function that calulates distances of shortest paths from src to all
// vertices. It is a O(ELogV) function
void implementDijkstra(Graph* graph, int sourc){

    int V = graph->vertices;// Get the number of vertices in graph


    //double dist[V];      // dist values used to pick minimum weight edge in cut
    //int parent[V];
    // both above are set global

    // minHeap represents set E
    minimumHeapStruct* minHeap = createminimumHeapStruct(V);

    // Initialize min heap with all vertices. dist value of all vertices
    for (int v = 0; v < V; ++v)
    {
        dist[v] = DBL_MAX;
        minHeap->array[v] = newMinimumHeapNode(v, dist[v]);
        minHeap->position[v] = v;

        parent[v] = -1;
    }

    // Make dist value of src vertex as 0 so that it is extracted first
    minHeap->array[sourc] = newMinimumHeapNode(sourc, dist[sourc]);
    minHeap->position[sourc]   = sourc;
    dist[sourc] = 0;
    decreaseDistValue(minHeap, sourc, dist[sourc]);

    // Initially size of min heap is equal to V
    minHeap->size = V;

    // In the following loop, min heap contains all nodes
    // whose shortest distance is not yet finalized.
    while (!isEmpty(minHeap))
    {
        // Extract the vertex with minimum distance value
        minimumHeapNode* minHeapNode = extractMinimum(minHeap);
        int u = minHeapNode->v; // Store the extracted vertex number

        // Traverse through all adjacent vertices of u (the extracted
        // vertex) and update their distance values
        sector* pCrawl = graph->City[u].head;

        while (pCrawl != NULL){

            int v = pCrawl->dvertex;

            // If shortest distance to v is not finalized yet, and distance to v
            // through u is less than its previously calculated distance
            if (isInminimumHeapStruct(minHeap, v) && dist[u] != DBL_MAX &&
                pCrawl->distance + dist[u] < dist[v])
            {
                dist[v] = dist[u] + pCrawl->distance;
                parent[v] = u;
                // update distance value in min heap also
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
