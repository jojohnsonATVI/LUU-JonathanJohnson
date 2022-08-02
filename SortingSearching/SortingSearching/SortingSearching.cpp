#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>


//I made the terrible decision to put these into one .cpp file... oh well
struct Node {
    std::string nodeName;
    int pathEstimate = 0;
    int pathSoFar = 0;
    Node* parentNode = nullptr;
    std::vector<Node*> connectedNodes;
    std::vector<int> nodeCost;
};
std::unordered_map<std::string, Node*> nodeMap;

struct Data {
    std::string start;
    std::string end;
    std::vector<Node> nodeList;
};

//Useless here but implemented to show that I could actually implement A* logic. Also, isn't transfering information
void FindPathEstimate(Node* node) {
    //Set pathEstimate to some estimate of the distance left to make it an acutal A* algorithm
    int distance = 0;
    node->pathEstimate = distance + node->pathSoFar;
}



Node* findNodeAddress(std::string input) {
    Node* node;
    if (nodeMap.find(input) == nodeMap.end()) {
        node = new Node;
        nodeMap.insert(make_pair(input, node));
        node->nodeName = input;
    }
    else node = nodeMap.find(input)->second;
    return node;
}


void CalculateConnections(Node* node) {
    //Do stuff
    for (unsigned int i = 0; i < node->connectedNodes.size(); i++) {
        if (node->connectedNodes[i]->parentNode == nullptr) {
            node->connectedNodes[i]->parentNode = node;
            node->connectedNodes[i]->pathSoFar = node->nodeCost[i];
            FindPathEstimate(node->connectedNodes[i]);
        }
        else {
            int tempCost = node->nodeCost[i];
            if (tempCost < node->connectedNodes[i]->pathSoFar) {
                node->connectedNodes[i]->parentNode = node;
                node->connectedNodes[i]->pathSoFar += node->nodeCost[i];
                FindPathEstimate(node->connectedNodes[i]);
            }
        }

    }
}

void BubbleSort(std::vector<Node> array) {

    bool flip = 1;  
    while (flip) {
        flip = 0;
        for (unsigned int i = 0; i < array.size() - 1; i++) {
            if (array[i].parentNode == nullptr && array[i + 1].parentNode != nullptr) {
                Node temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
                flip = 1;
            }
            else if (array[i + 1].parentNode == nullptr) {

            }
            else if (array[i].pathEstimate > array[i + 1].pathEstimate) {
                Node temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
                flip = 1;
            }
        }
    }
}



void RunAStarSearch(Data* dataSet) {
    Node* nodeEnd = findNodeAddress(dataSet->end); //Uses Hashmap to find end node, same for next line, but start instead
    Node* node1 = findNodeAddress(dataSet->start);
    while (true) { //Finds Start value in node list
        int i = 0;
        if (dataSet->nodeList[i].nodeName != node1->nodeName) {
            i++;
            continue;
        }
        Node temp = dataSet->nodeList[i];
        dataSet->nodeList[i] = dataSet->nodeList[0];
        dataSet->nodeList[0] = temp;
        break;
    }
    while (dataSet->nodeList[0].nodeName != nodeEnd->nodeName) { //Runs through program and sorts until the cheapest possible path is at our end node 
        Node* currentNode = &dataSet->nodeList[0];
        CalculateConnections(currentNode);
        dataSet->nodeList[0] = *currentNode;
        dataSet->nodeList.erase(dataSet->nodeList.begin());
        BubbleSort(dataSet->nodeList);
    }
    std::cout << "The lowest cost possible to path between " << dataSet->start << " and " << dataSet->end << " is: " << dataSet->nodeList[0].pathSoFar << '\n';
    
}





void AddLink(Node* node1, Node* node2, int cost) {
    node1->connectedNodes.push_back(node2);
    node1->nodeCost.push_back(cost);
}





void BubbleSort(std::vector<int> array) {

    bool flip = 1;
    while (flip) {
        flip = 0;
        for (unsigned int i = 0; i < array.size() - 1; i++) {
            if (array[i] > array[i + 1]) {
                int temp = array[i];                                                                      
                array[i] = array[i + 1];
                array[i + 1] = temp;
                flip = 1;
            }
        }
    }
}

void ParseNodeString(std::string nodeInfo) {
    //take in node name for first node
    //findNodeAddress of node name for first node
    //take in node name for second node
    //findNodeAddress of node name for second node
    //AddLink(node 1, node 2)
}


Data ReadInNodeFile(std::string fileName) {
    Data dataSet;
    //While loop until last string in file:
        //Parse String
        //Get new string
    //Set start point and end point
    return dataSet;
}



//End of A* logic and beginning of sort logic
void BubbleSort(int array[], int arraySize) {
 
    bool flip = 1;
    while (flip) {
        flip = 0;
        for (int i = 0; i < arraySize - 1; i++) {
            if (array[i] > array[i + 1]) {
                int temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
                flip = 1;
            }
        }
    }
}
void FillArray(int array[], int arraySize) {
    for (int i = 0; i < arraySize; i++) {
        array[i] = rand() % arraySize + 1;
    }
}

void PrintArray(int array[], int arraySize) {
    for (int i = 0; i < arraySize; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << '\n';
}


int main()
{
   // constexpr int arraySizeOne = 5;
   // constexpr int arraySizeTwo = 100;
   // constexpr int arraySizeThree = 1000;
   //
   // int testArray1[arraySizeOne];
   // int testArray2[arraySizeTwo];
   // int testArray3[arraySizeThree];
   //
   // FillArray(testArray1, arraySizeOne);
   // FillArray(testArray2, arraySizeTwo);
   // FillArray(testArray3, arraySizeThree);
   //
   // BubbleSort(testArray1, arraySizeOne);
   // BubbleSort(testArray2, arraySizeTwo);
   // BubbleSort(testArray3, arraySizeThree);
   //
   // PrintArray(testArray1, arraySizeOne);
   // PrintArray(testArray2, arraySizeTwo);
   //PrintArray(testArray3, arraySizeThree);

    std::cout << "\n\n\n\n\n";

    //Implement Searching stuff

    Data dataSet;
    dataSet.nodeList.push_back(*findNodeAddress("A"));
    dataSet.nodeList.push_back(*findNodeAddress("B"));
    dataSet.nodeList.push_back(*findNodeAddress("C"));
    dataSet.nodeList.push_back(*findNodeAddress("D"));
    AddLink(&dataSet.nodeList[0], &dataSet.nodeList[1], 5);
    AddLink(&dataSet.nodeList[1], &dataSet.nodeList[2], 1);
    AddLink(&dataSet.nodeList[0], &dataSet.nodeList[3], 7);
    AddLink(&dataSet.nodeList[2], &dataSet.nodeList[3], 1);
    dataSet.start = "A";
    dataSet.end = "D";
    RunAStarSearch(&dataSet);
    




}
