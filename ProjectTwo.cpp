// Project 2.cpp :
// Steve Klabunde 
// 10-17-2024
//

// import neeeded libraries
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <Windows.h>
#include <vector>

using namespace std;

//creates a delay to wait for input
const int GLOBAL_SLEEP_TIME = 5000;

//create structure
struct Course {
    //create variables
    string courseNum;
    string courseName;
    vector<string> perReqs;
};

//create class
class BinarySearchTree {
private:
    //define structure for tree Node that will hold courses 
        struct Node {
        Course course;
        Node* right;
        Node* left;

        //create the default constructor
        Node() {
            left = nullptr;
            right = nullptr;
        }

        //initialize constructor
        Node(Course aCourse) {
            course = aCourse;
            left = nullptr;
            right = nullptr;
        }
    };

    Node* root;
    //define method
    void inOrder(Node* node);
    //create and initialize variable
    int size = 0;

public:
    //define methods
    BinarySearchTree();
    void InOrder();
    void Insert(Course aCourse);
    void Remove(string courseNum);
    Course Search(string courseNum);
    int Size();
};

//create default constructor and asign root as null
BinarySearchTree::BinarySearchTree() {
    this->root = nullptr;
}

//method that traverses the tree in order
void BinarySearchTree::InOrder() {
    inOrder(root);
}
//create method to insert course
void BinarySearchTree::Insert(Course aCourse) {
    Node* currentNode = root;

    //create if statement so if root is null, new course becomes the root
    if (root == NULL) {
        root = new Node(aCourse);
    }
    //else statement for if root is not null
    else {
        while (currentNode != NULL) {
            //create if/else statements to insert new course into the correct node
            if (aCourse.courseNum < currentNode->course.courseNum) {
                if (currentNode->left = nullptr) {
                    currentNode->left = new Node(aCourse);
                    currentNode = NULL;
                }
                else {
                    currentNode = currentNode ->left;
                }
            }
            else {
                if (currentNode->right == nullptr) {
                    currentNode->right = new Node(aCourse);
                    currentNode = NULL;
                }
                else {
                    currentNode = currentNode->right;
                }
            }
        }
    }
    //increase size of tree to account for new course
    size++;
}
//create method to remove a course
void BinarySearchTree::Remove(string courseNum) {
    Node* temp = NULL;
    Node* curr = root;
    //when course removed adjust other courses locations
    while (curr != NULL) {
        if (curr->course.courseNum == courseNum) {
            if (curr->left == NULL && curr->right == NULL) {
                if (temp == NULL) {
                    root = nullptr;
                }
                else if (temp->left == curr) {
                    temp->left = NULL;
                }
                else {
                    temp->right = NULL;
                }
            }
            else if (curr->right == NULL) {
                if (temp == NULL) {
                    root = curr->left;
                }
                else if (temp->left == curr) {
                    temp->left = curr->left;
                }
                else {
                    temp->right = curr->left;
                }
            }
            else if (curr->left == NULL) {
                if (temp == NULL) {
                    root = curr->right;
                }
                else if (temp->left == curr) {
                    temp->left = curr->right;
                }
                else {
                    temp->right = curr->right;
                }
            }
            else {
                Node* suc = curr->right;

                while (suc->left != NULL) {
                    suc = suc->left;
                }
                Node successorData = Node(suc->course);
                Remove(suc->course.courseNum);
                curr->course = successorData.course;
            }
            return;
        }
        else if (curr->course.courseNum < courseNum) {
            temp = curr;
            curr = curr->right;
        }
        else {
            temp = curr;
            curr = curr->left;
        }
    }
    //output course not found if the course being removed is not located
    cout << "\n Value not found. ={" << endl;
    return;
}

//create a method to search for a course
Course BinarySearchTree::Search(string courseNum) {
    Course aCourse;
    Node* currentNode = root;

    //use of while and if statements to find the inputted course info
    while (currentNode != NULL) {
        if (currentNode->course.courseNum == courseNum) {
            return currentNode->course;
        }
        else if (courseNum < currentNode->course.courseNum) {
            currentNode = currentNode->left;
        }
        else if (courseNum < currentNode->course.courseNum) {
            currentNode = currentNode->left;
        }
        else {
            currentNode = currentNode->right;
        }
    }
    return aCourse;
}
//create method to traveerse the tree in order
void BinarySearchTree::inOrder(Node* node) {
    //stops the movement if an empty node is found
    if (node == NULL) {
        return;
    }
    //moves from left node to right node
    inOrder(node->left);

    cout << node->course.courseNum << ", " << node->course.courseName << endl;

    inOrder(node->right);
}
int BinarySearchTree::Size() {
    return size;
}
//create a way to split the sections of lines
vector<string> Split(string lineFeed) {
    // create and assign variable for the character that splits the lines
    char delim = ',';

    lineFeed += delim;
    vector<string> lineTokens;
    string temp = "";

    //create a for statement to continue to read the line
    for (int i = 0; i < lineFeed.length(); i++) {
        if (lineFeed[i] == delim) {
            lineTokens.push_back(temp);
            temp = "";
            i++;
        }
        temp += lineFeed[i];
    }
    return lineTokens;
}

//create method to load the information
//Note - when ran indicates that 8 lines read and one line doesn't meet requirements
void loadCourses(string csvPath, BinarySearchTree* courseList) {
    ifstream inFS;
    string line;
    vector<string> stringTokens;

    //open file
    inFS.open(csvPath);

    //verifies file is open
    if (!inFS.is_open()) {
        cout << "Could not open file. Please check file path." << endl;
        return;
    }

    //creates while statement to read through lines and insert them into file
   while (!inFS.eof()) {
        Course aCourse;

        getline(inFS, line);
        stringTokens = Split(line);

        if (stringTokens.size() >= 2) {
            aCourse.courseNum = stringTokens[0];
            aCourse.courseName = stringTokens[1];

            for (unsigned int i = 2; i < stringTokens.size(); i++) {
                aCourse.perReqs.push_back(stringTokens[i]);
            }
            courseList->Insert(aCourse);
            line.erase(0,stringTokens.size() + 1);
        }
        //output for if line does not have at least courseNumber and courseName
         else {
             cout << "\n Error. Skipping line." << endl;
         }
    }
   //close input file
    inFS.close();
}

//create method to print the courses
// Note only prints one course, unsure why it is not printing the rest
void displayCourse(Course aCourse) {
    cout << aCourse.courseNum << "," << aCourse.courseName;
    cout << "Prerequisites: ";
    //if statement to check for Prerequistes
    
    if (aCourse.perReqs.empty()) {
        cout << "none" << endl;
    }
    else {
        for (unsigned int i = 0; i < aCourse.perReqs.size(); i++) {
            cout << aCourse.perReqs.at(i);

            if (aCourse.perReqs.size() > 1 && i < aCourse.perReqs.size() - 1) {
                cout << ", ";
            }
        }
    }
    cout << endl;
}
//create method to convert lower case input to upper case
void convertCase(string& toConvert) {
    for (unsigned int i = 0; i < toConvert.length(); i++) {
        if (isalpha(toConvert[i])) {
            toConvert[i] = toupper(toConvert[i]);
        }
    }
}

int main(int argc, char* argv[]) {//create main method

    string csvPath, aCourseKey;

    switch (argc) {
    case 2:
        csvPath = argv[1];
        break;
        
    case 3:
        csvPath = argv[1];
        aCourseKey = argv[2];
        break;

    default:
        csvPath = "CS 300 ABCU_Advising_Program_Input.csv";
    }
    
    BinarySearchTree* courseList = new BinarySearchTree(); //create structure

    Course course;
    bool goodInput;
    int choice = 0;

    while (choice != 9) { //create output for user
        cout << "Menu:" << endl;
        cout << "1. Load Course" << endl;
        cout << "2. Display All Course " << endl;
        cout << "3. Find Course" << endl;
        cout << "4. Remove Course " << endl;
        cout << "9. Exit " << endl;
        cout << "Enter choice: ";

        aCourseKey = ""; //clear previous choices
        string anyKey = " ";
        choice = 0;

        try {//verify user input valid
            cin >> choice;

            if ((choice > 0 && choice < 5) || (choice == 9)) {
                goodInput = true;
            }
            else {
                goodInput = false;
                throw 1;
            }
            switch (choice) {//create switch to take appropriate action
            case 1:
                loadCourses(csvPath, courseList);
                cout << courseList->Size() << " courses read" << endl;

                Sleep(GLOBAL_SLEEP_TIME);

                break;

            case 2:
                courseList->InOrder();

                cout << "\n Enter \'y\' to continue..." << endl;

                cin >> anyKey;

                break;
            case 3:
                cout << "\n What course do you want to know about? " << endl;
                cin >> aCourseKey;

                convertCase(aCourseKey);

                course = courseList->Search(aCourseKey);

                if (!course.courseNum.empty()) {
                    displayCourse(course);
                }
                else {
                    cout << "\n Course ID: " << aCourseKey << " not found." << endl;
                }
                Sleep(GLOBAL_SLEEP_TIME);
                break;

            case 4:
                cout << "\n What course do you want to delete?" << endl;
                cin >> aCourseKey;

                convertCase(aCourseKey);

                courseList->Remove(aCourseKey);

                Sleep(GLOBAL_SLEEP_TIME);
                break;

            case 9:
                exit;
                break;

            default:
                throw 2;
            }
        }
        catch (int err) { //catch statement 
            std::cout << "\n Please check your input." << endl;
            Sleep(GLOBAL_SLEEP_TIME);
        }
        cin.clear();
        cin.ignore();

        system("cls");
    }
    cout << "Good bye." << endl;

    Sleep(GLOBAL_SLEEP_TIME);

    return 0;
}


