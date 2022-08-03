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
    std::vector<int> nodeCost; //Last two should probably be contained in a vector of one object that has pointers to nodes and edge cost as values
};
std::unordered_map<std::string, Node*> nodeMap;
struct Data {
    std::string start;
    std::string end;
    std::vector<Node*> nodeList;
};
//Useless here but implemented to show that I could actually implement A* logic
void FindPathEstimate(Node* node) {
    //Set pathEstimate to some estimate of the distance left to make it an acutal A* algorithm
    int distance = 0;
    node->pathEstimate = distance + node->pathSoFar;
}
Node* FindOrAddNodeAddress(std::string input) {
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
            node->connectedNodes[i]->pathSoFar = node->nodeCost[i] + node->pathSoFar;
            FindPathEstimate(node->connectedNodes[i]);
        }
        else {
            int tempCost = node->nodeCost[i] + node->pathSoFar;
            if (tempCost < node->connectedNodes[i]->pathSoFar) {
                node->connectedNodes[i]->parentNode = node;
                node->connectedNodes[i]->pathSoFar = node->nodeCost[i] + node->pathSoFar;
                FindPathEstimate(node->connectedNodes[i]);
            }
        }
    }
}
void BubbleSort(std::vector<Node*> & array) {
    bool flip = true;
    while (flip) {
        flip = false;
        for (unsigned int i = 0; i < array.size() - 1; i++) {
            if (array[i]->parentNode == nullptr && array[i + 1]->parentNode != nullptr) {
                Node* temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
                flip = true;
            }
            else if (array[i + 1]->parentNode != nullptr && array[i]->pathEstimate > array[i + 1]->pathEstimate) {
                Node* temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
                flip = true;
            }
        }
    }
}
void DeleteAllPointers(std::vector<Node*> list) {
    for (int i = 0; i < list.size(); i++) {
        delete list[i];
        list[i] = nullptr;
    }
}
void RunAStarSearch(Data* dataSet) {
    std::vector<Node*> copyList = dataSet->nodeList;
    Node* nodeEnd = FindOrAddNodeAddress(dataSet->end); //Uses Hashmap to find end node, same for next line, but start instead
    Node* nodeStart = FindOrAddNodeAddress(dataSet->start);
    while (true) { //Finds Start value in node list
        int i = 0;
        if (dataSet->nodeList[i]->nodeName != nodeStart->nodeName) {
            i++;
            continue;
        }
        Node* temp = dataSet->nodeList[i];
        dataSet->nodeList[i] = dataSet->nodeList[0];
        dataSet->nodeList[0] = temp;
        break;
    }
    while (dataSet->nodeList[0]->nodeName != nodeEnd->nodeName) { //Runs through program and sorts until the cheapest possible path is at our end node
        CalculateConnections(dataSet->nodeList[0]);
        dataSet->nodeList.erase(dataSet->nodeList.begin());
        BubbleSort(dataSet->nodeList);
    }
    std::cout << "The lowest cost possible to path between " << dataSet->start << " and " << dataSet->end << " is: " << dataSet->nodeList[0]->pathSoFar << '\n';
    DeleteAllPointers(copyList); //Shouldn't be deleting here but oh well
}
void AddLink(Node* node1, Node* node2, int cost) {
    node1->connectedNodes.push_back(node2);
    node1->nodeCost.push_back(cost);
}
void ParseNodeString(std::string nodeInfo) { //TODO:
    //take in node name for first node
    //findNodeAddress of node name for first node
    //take in node name for second node
    //findNodeAddress of node name for second node
    //AddLink(node 1, node 2)
}
Data ReadInNodeFile(std::string fileName) { //TODO:
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
    dataSet.nodeList.push_back(FindOrAddNodeAddress("A"));
    dataSet.nodeList.push_back(FindOrAddNodeAddress("B"));
    dataSet.nodeList.push_back(FindOrAddNodeAddress("C"));
    dataSet.nodeList.push_back(FindOrAddNodeAddress("D"));
    AddLink(FindOrAddNodeAddress("A"), FindOrAddNodeAddress("B"), 5);
    AddLink(FindOrAddNodeAddress("B"), FindOrAddNodeAddress("C"), 1);
    AddLink(FindOrAddNodeAddress("A"), FindOrAddNodeAddress("D"), 6);
    AddLink(FindOrAddNodeAddress("C"), FindOrAddNodeAddress("D"), 1);
    dataSet.start = "A";
    dataSet.end = "D";
    RunAStarSearch(&dataSet);
}

















