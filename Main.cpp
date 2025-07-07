#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
using namespace std;

class Candidate
{
public:
    string name;
    int votes;

    Candidate(string n)
    {
        name = n;
        votes = 0;
    }
};

class VotingSystem
{
private:
    vector<Candidate> candidates;
    map<string, bool> voters;       // voter ID -> has voted
    const string adminPIN = "2301"; // simple PIN-based admin access

public:
    void addCandidate(string name)
    {
        candidates.push_back(Candidate(name));
        cout << "Candidate \"" << name << "\" added successfully.\n";
    }

    void castVote(string voterID)
    {
        if (voters[voterID])
        {
            cout << "You have already voted. Multiple votes are not allowed!\n";
            return;
        }

        cout << "\nVote for a candidate:\n";
        for (int i = 0; i < candidates.size(); ++i)
        {
            cout << i + 1 << ". " << candidates[i].name << endl;
        }

        int choice;
        cout << "Enter your choice (1-" << candidates.size() << "): ";
        cin >> choice;

        if (choice >= 1 && choice <= candidates.size())
        {
            candidates[choice - 1].votes++;
            voters[voterID] = true;
            cout << "Thanks for voting!\n";
        }
        else
        {
            cout << "Invalid choice!\n";
        }
    }

    void showResults()
    {
        cout << "\n=== Vote Count ===\n";
        for (const Candidate &c : candidates)
        {
            cout << setw(15) << left << c.name << " : " << c.votes << " votes\n";
        }
    }

    void showLeadingCandidate()
    {
        int maxVotes = -1;
        string winner;
        bool tie = false;

        for (const Candidate &c : candidates)
        {
            if (c.votes > maxVotes)
            {
                maxVotes = c.votes;
                winner = c.name;
                tie = false;
            }
            else if (c.votes == maxVotes)
            {
                tie = true;
            }
        }

        if (tie)
        {
            cout << "There is a tie between candidates.\n";
        }
        else
        {
            cout << "Leading candidate: " << winner << " with " << maxVotes << " votes.\n";
        }
    }

    void adminPanel()
    {
        string pin;
        cout << "Enter Admin PIN: ";
        cin >> pin;

        if (pin != adminPIN)
        {
            cout << "Invalid PIN! Access denied.\n";
            return;
        }

        int choice;
        do
        {
            cout << "\n=== Admin Panel ===\n";
            cout << "1. Show Vote Count\n";
            cout << "2. Show Leading Candidate\n";
            cout << "3. Back to Main Menu\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                showResults();
                break;
            case 2:
                showLeadingCandidate();
                break;
            case 3:
                break;
            default:
                cout << "Invalid option!\n";
            }
        } while (choice != 3);
    }
};

int main()
{
    VotingSystem vs;
    int choice;

    // Predefined candidates (or allow user to add)
    vs.addCandidate("John");
    vs.addCandidate("Sunny");
    vs.addCandidate("Charlie");

    do
    {
        cout << "\n=== Voting System ===\n";
        cout << "1. Cast Vote\n";
        cout << "2. Admin Panel\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string voterID;
            cout << "Enter your Voter ID: ";
            cin >> voterID;
            vs.castVote(voterID);
            break;
        }
        case 2:
            vs.adminPanel();
            break;
        case 3:
            cout << "Exiting Voting System. Thank you!\n";
            break;
        default:
            cout << "Invalid option. Try again.\n";
        }
    } while (choice != 3);

    return 0;
}
