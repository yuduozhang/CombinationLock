//==============================================================================
//  Problem: 
//
//  Consider a mechanical combination lock with buttons numbered from 1 to N. 
//  A combination consists of a sequence of button presses where no button is 
//  repeated. Each press may be either a single button, or a pair of buttons 
//  pressed simultaneously. The length of a combination must be at least 1.
//
//  Write a program in C or C++ (Java or PHP may also be used) that accepts a 
//  command line parameter for N (where N may be from 1 to 8). Your program 
//  should generate to stdout a list of all possible combinations. The order is 
//  not important, but no combination should be repeated. Each combination should 
//  be output as a single line of text. A single button press is represented by 
//  the decimal digit of the button. A simultaneous button press is represented 
//  by the two buttons separated by a dash, with the lowest valued button first 
//  in the pair. Each button press is separated by a space.
//==============================================================================


//==============================================================================
//  Solution:
//
//  My idea is to build a buttonTree for the lock, which is actually a trie,
//  where the value of the node is the rest buttons available to be pressed, and
//  the value of the edge is the button(s) chosen to be pressed.
//
//  The output of all the possible paths starting from root of the tree is the
//  list of all possible combinations of the lock.
//==============================================================================


#ifndef COMBINATIONLOCK_H_
#define COMBINATIONLOCK_H_

#include <vector>
#include <string>

class CombinationLock {
    public:
        /*----- member functions -----*/
        CombinationLock (const int numberOfButtons);
        void printAllCombinations();

        ~CombinationLock();

    private:
        /*----- nested structs -----*/
        struct Edge;
        struct Node {
            std::vector<std::string> _restButtons; 
            std::vector<Edge*> _edges;

            ~Node();
        }; 

        struct Edge {
            const std::string _pressedButtons;
            Node* const _target;

            Edge (const std::string& pressedButtons, Node* const target);
            ~Edge();
        };

    private: 
        /*----- data members -----*/
        Node* _root;
        const int _numberOfButtons;


        /*----- member functions -----*/

        // Disable the default constructor
        CombinationLock();

        void printAllCombinationsHelper (Node* const node, 
                std::string previousCombination) const;
        void buildButtonsTree();
        void buildButtonsTreeHelper (Node* const node);
        inline std::string convertIntegerToString (int i);

};

#endif // COMBINATIONLOCK_H_
