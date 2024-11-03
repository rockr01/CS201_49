#include <bits/stdc++.h>
#include <string.h>
#include "Suffix_tree.hpp"
#include "PatternSearch.hpp" 
#include "bloom.hpp"
#include "BK_Tree.hpp"

using namespace std;

int main(void) {
    vector<string> Projects; // A vector to store project names
    bool bitarray[1000] = {false}; // Bloom filter to check project presence
    int arrSize = 1000; // Size of the Bloom filter
    int pos[100]; // Array to store positions for substring search
    BkNode* RootNode; // Root node of the BK tree for fuzzy matching
    string s1 = ""; // String to store freelancer interactions (project applications)

    vector<int> ratings = {
        3, 2, 3, 4, 3, 3, 5, 4, 3, 3,
        4, 2, 3, 3, 5, 3, 3, 4, 3, 2,
        3, 3, 3, 4, 3, 3, 3, 4, 2, 3,
        3, 4, 3, 3, 4, 3, 3, 3, 3, 4,
        3, 2, 4, 3, 3, 5, 3, 4, 3, 4,
        2, 3, 4, 3, 3, 3, 5, 3, 4, 3,
        3, 3, 4, 3, 3, 5, 3, 3, 3, 4,
        2, 4, 3, 3, 3, 5, 3, 4, 3, 3,
        3, 2, 3, 4, 3, 3, 4, 3, 3, 3,
        5, 3, 3, 3, 3, 4, 3, 5, 3, 4
    };

    vector<int> rating_count(100, 1);

    vector<string> freelancer_name = {
        "Olivia", "Liam", "Emma", "Noah", "Ava", "Elijah", "Sophia", "Lucas", "Isabella", "Mason",
        "Mia", "Logan", "Amelia", "James", "Harper", "Ethan", "Evelyn", "Alexander", "Abigail", "Henry",
        "Ella", "William", "Elizabeth", "Sebastian", "Sofia", "Benjamin", "Charlotte", "Michael", "Avery",
        "Jackson", "Scarlett", "Daniel", "Madison", "Matthew", "Aria", "Samuel", "Riley", "David", "Lily",
        "Joseph", "Hannah", "Carter", "Zoey", "Owen", "Grace", "Wyatt", "Victoria", "John", "Penelope",
        "Dylan", "Lillian", "Luke", "Nora", "Gabriel", "Stella", "Anthony", "Aurora", "Isaac", "Natalie",
        "Andrew", "Paisley", "Christopher", "Ellie", "Joshua", "Bella", "Nathan", "Naomi", "Julian", "Mila",
        "Levi", "Layla", "Caleb", "Lucy", "Ryan", "Brooklyn", "Adrian", "Savannah", "Maverick", "Skylar",
        "Eli", "Alice", "Asher", "Willow", "Dominic", "Hazel", "Hunter", "Violet", "Cameron", "Claire",
        "Thomas", "Anna", "Leo", "Samantha", "Charles", "Elena", "Jaxon", "Maya", "Aaron", "Aubrey"
    };

    cout << "Welcome to the Freelancing Management System!\n";

label:
    // User menu for freelancer/client options
    cout << "Please choose:\n-1 for freelancer end\n-2 for client end\n-3 exit\n";
    int x;
    cin >> x; // User input for the selected option

    if (x == 1) { // Freelancer end
        string freelancer_id;
        string project = ""; // Variables for freelancer ID and project input
        cout << "Please enter your freelancer ID: ";
        cin >> freelancer_id; // Get freelancer ID
        int rating = ratings[stoi(freelancer_id)]; // Get the rating of the freelancer
        cout << "Enter the task you want to opt for (enter 'end' when you're done): ";

        // Loop to get projects from the freelancer
        while (project != "end") {
            cin >> project; // Read project input
            if (project != "end") {
                RootNode = ReturnBNode(); // Get the root node of the BK tree
                vector<string> match = getSimilarWords(*RootNode, project, rating); // Find similar projects
                int found = 0; // Flag to check if the project is found

                // Check if the exact project is present
                for (auto x : match) {
                    if (x == project) {
                        found = 1; // Project found
                        cout << "The task seems to be present in the system\n";
                    }
                }

                // Handle misspellings
                if (!found && !match.empty()) {
                    cout << "It seems you misspelled.\nEnter the Index of the one you want from the following tasks :\n";
                    for (size_t i = 0; i < match.size(); i++) {
                        cout << i + 1 << ". " << match[i] << endl; // Display similar projects
                    }

                    int index;
                    cin >> index; // Get freelancer's choice
                    project = match[index - 1]; // Correct the misspelled project
                } else if (match.empty()) {
                    cout << "No such project/task or closely spelled project/task found.\n"; // No matches found
                }

                // If a valid project was matched, append to the application string
                if (!match.empty()) {
                    s1.append(freelancer_name[stoi(freelancer_id)] + to_string(freelancer_name[stoi(freelancer_id)].length())); // Append name and its length
                    s1.append(project); // Append the project
                }
            }
        }

        cout << "Thank you " << freelancer_name[stoi(freelancer_id)] << "!" << endl; // Thank the freelancer
        goto label; // Return to the main menu

    } else if (x == 2) { // Client end
        cout << "Please choose an operation:\n-1 for Posting Project\n-2 for Searching project\n";
        int op2;
        cin >> op2; // Get client's choice

        if (op2 == 1) { // Post project
            string s2;
            cout << "Please enter the keyword for Project/task : ";
            cin >> s2; // Get project name from client
            cout << "Please enter the minimum rating required for the project: ";
            int rate;
            cin >> rate; // Get the rating of the project

            // Insert project into Bloom filter and BK tree
            if (insert(bitarray, arrSize, s2)) {
                Projects.push_back(s2); // Add project to the list
                BkNode NodeOp2 = createNode(s2, rate); // Create a new node for the BK tree
                RootNode = ReturnBNode(); // Get the root node
                addNode(*RootNode, NodeOp2); // Add the new node to the BK tree
            }
        } else if (op2 == 2) { // Search project
                s1 += "$"; // Append delimiter to application string
                cout << s1 << endl;
                int z = s1.size();
                char Text[z + 1]; // Create char array with extra space for null terminator

                // Convert s1 to char array Text
                strcpy(Text, s1.c_str());

                // Build suffix tree using Text array
                buildSuffixTree(Text);
                cout << "-1 To display Opted work Summary\n-2 To Search Specific Job/task\n";
                int h;
                cin >> h;
                string hero;

                if (h == 2) {
                    cout << "Enter the task to be Searched: ";
                    cin >> hero;
                }

                for (auto x : Projects) {
                    if (h == 2) x = hero;

                    fill(begin(pos), end(pos), -1); // Reset pos array to -1

                    int y = 0; // Reset position index
                    z = x.length();
                    char Temp2[z + 1];
                    strcpy(Temp2, x.c_str());
                    cout<<x<<":"<<endl;

                    SNode* root = returnRoot();
                    checkForSubString(Temp2, root, Text, pos); // Search for substring in the suffix tree

                    // cout << "\nThe Following freelancers applied for " << x << ": ";
                    // bool foundFreelancer = false; // Flag to track if any freelancer was found

                    // Display freelancer names based on positions found
                    // while (pos[y] != -1) {
                    //     if (pos[y] < 2) {
                    //         cout << "Invalid position detected.\n";
                    //         break;
                    //     }
                        
                    //     int num = Text[pos[y] - 1] - '0';
                    //     //int num2 = Text[pos[y] - 2] - '0';
                    //     int found = 0;

                    //     if ( num <= 9) {
                    //         found = 1;
                    //         //num = 10 * num2 + num; // Calculate two-digit freelancer ID if applicable
                    //         cout<<"digit calculation"<<endl;
                    //     }

                    //     int startIdx = pos[y] - 1 - found - num;
                    //     if (startIdx < 0) {
                    //         cout << "Invalid start index.\n";
                    //         break;
                    //     }

                    //     for (int g = startIdx; g < pos[y] - 1 - found; g++) {
                    //         cout << Text[g];
                    //         foundFreelancer = true;
                    //     }

                    //     cout << " ";
                    //     y++;
                    // }

                    cout << endl;
                    cout << "\n";

                    if (h == 2) break;
                }
            s1.pop_back(); // Remove the last character from the application string
        }

        goto label; // Return to the main menu
    }
    return 0; // End of program
}
