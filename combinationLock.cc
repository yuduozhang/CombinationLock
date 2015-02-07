#include "combinationLock.h"
#include <iostream>
#include <sstream>

//------------------------------------------------------------------------------
// Constructor:

CombinationLock::CombinationLock (const int numberOfButtons)
    : _root(NULL), _numberOfButtons(numberOfButtons){}


//------------------------------------------------------------------------------
// printAllCombinations:

void CombinationLock::printAllCombinations(){
    if(NULL == _root) buildButtonsTree();
    printAllCombinationsHelper(_root, "");
}

//------------------------------------------------------------------------------
// printAllCombinationsHelper: 
// Print all paths starting from root recursively

void CombinationLock::printAllCombinationsHelper(
        Node* const node, std::string previousCombination) const{

    if(node->_restButtons.empty()) return;
    for (std::vector<Edge*>::iterator it = node->_edges.begin(); 
            it != node->_edges.end(); ++it){
        std::string currentCombination = 
            previousCombination + (*it)->_pressedButtons;
        std::cout << currentCombination << std::endl;

        // Recursion
        printAllCombinationsHelper((*it)->_target, currentCombination+" ");
    }
}

//------------------------------------------------------------------------------
// buildButtonsTree:

void CombinationLock::buildButtonsTree(){
    _root = new Node();

    // At beginning, all buttons are available to be pressed 
    for (int i = 1; i<=_numberOfButtons; ++i){
        std::string buttonNumber = convertIntegerToString(i);
        _root->_restButtons.push_back(buttonNumber);
    }
    buildButtonsTreeHelper(_root);
}

//------------------------------------------------------------------------------
// buildButtonsTreeHelper: a recursive helper function

void CombinationLock::buildButtonsTreeHelper (Node* const node){
    if(node->_restButtons.empty()) return;
    // Presss 1 button
    //
    // Iterate by iterator+index so we can erase by index later
    {
        std::vector<std::string>::iterator it;
        int i;
        for (it = node->_restButtons.begin(), i=0;
                it+i != node->_restButtons.end(); ++i){

            // Choose a button to press
            std::string button = *(it+i);

            // Construct a new child node
            Node* child = new Node();

            // Copy the current rest Buttons and remove the pressed one
            child->_restButtons = node->_restButtons;
            child->_restButtons.erase(child->_restButtons.begin()+i);

            // Construct a new edge with the pressed button and the new child as
            // the target
            Edge* newEdge = new Edge(button, child);

            // Add this new edge to current node
            node->_edges.push_back(newEdge);

            // Recursion
            buildButtonsTreeHelper(child);
        }
    }


    // Presss 2 buttons simultaneously
    if (node->_restButtons.size()>1){
        std::vector<std::string>::iterator it;
        int i;
        for (it = node->_restButtons.begin(), i=0; 
                it+i != node->_restButtons.end(); ++i) {
            for (int j = i+1; it+j != node->_restButtons.end(); ++j) {

                // Choose 2 buttons to press simultaneously
                std::string button1 = *(it+i);
                std::string button2 = *(it+j);

                // Constrcut a new child node
                Node* child = new Node();
                
                // Copy the current rest Buttons and remove the pressed ones
                child->_restButtons = node->_restButtons;

                // Since j is always after i, so remove j first to avoid
                // the effect of shifting the array to left 
                child->_restButtons.erase(child->_restButtons.begin()+j);
                child->_restButtons.erase(child->_restButtons.begin()+i);

                // Constrcut a new edge with the pressed buttons and the new
                // child as the target
                Edge* newEdge = new Edge(button1 + "-" + button2, child);

                // Add this new edge to current node
                node->_edges.push_back(newEdge);

                // Recursion
                buildButtonsTreeHelper(child);
            }
        }
    }
}

//------------------------------------------------------------------------------
// convertIntegerToString: 

inline std::string CombinationLock::convertIntegerToString (const int i) {
    std::ostringstream convert;
    convert<<i;
    return convert.str();
}

//------------------------------------------------------------------------------
// Destructor of the nested struct Node

CombinationLock::Node::~Node(){

    for (std::vector<Edge*>::iterator it = _edges.begin();
            it != _edges.end(); ++it){
        if (NULL != (*it)) delete (*it);
    }
}

//------------------------------------------------------------------------------
// Constructor of the nested struct Edge

CombinationLock::Edge::Edge (const std::string& pressedButtons, 
                            Node* const target)
    : _pressedButtons(pressedButtons), _target(target) {}

//------------------------------------------------------------------------------
// Destructor of the nested struct Edge

CombinationLock::Edge::~Edge(){
    if (NULL != _target) delete _target;
}

//------------------------------------------------------------------------------
// Destructor of CombinationLock

CombinationLock::~CombinationLock() {
    if (NULL != _root) delete _root;
}
