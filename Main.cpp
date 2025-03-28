#include <iostream>
#include <queue>
#include <vector>
#include <map>

using namespace std;

class Panel {
private:
    string name;
public:
    Panel(string name) : name(name) {}
    string getName() { return name; }
};

class ScheduleInterview {
private:
    queue<int> candidates;
    priority_queue<pair<int, Panel*>, vector<pair<int, Panel*>>, greater<pair<int, Panel*>>> schedules;
    int rooms, interviewers;

public:
    void settleInterview(int rooms, int interviewers, int candidates_no) {
        map<int, pair<int, int>> slots;
        slots[1] = {9, 11};
        slots[2] = {11, 13};  // Fixed 1 PM to 13:00
        slots[3] = {15, 17};  // Fixed 3 PM to 15:00

        this->rooms = rooms;
        this->interviewers = interviewers;
        int max_parallel_interviews = min(rooms, interviewers);

        vector<Panel*> panel;
        for (int i = 0; i < max_parallel_interviews; i++) {
            panel.push_back(new Panel("Panel " + to_string(i + 1)));
        }

        for (int i = 1; i <= candidates_no; i++) {
            candidates.push(i);
        }

        // Initialize priority queue with available panels
        for (int i = 0; i < max_parallel_interviews; i++) {
            schedules.push({1, panel[i]});
        }

        cout << "Interview slots are as follows:\n";

        while (!candidates.empty() && !schedules.empty()) {
            int candidate = candidates.front();
            candidates.pop();

            pair<int, Panel*> current_slot = schedules.top();
            schedules.pop();

            int slot_id = current_slot.first;
            Panel* assigned_panel = current_slot.second;

            cout << "Candidate " << candidate << " is scheduled for an interview with " 
                 << assigned_panel->getName() << " from " << slots[slot_id].first 
                 << " to " << slots[slot_id].second << endl;

            int next_slot_id = slot_id + 1;
            if (next_slot_id <= slots.size()) {
                schedules.push({next_slot_id, assigned_panel});
            }
        }

        // If any candidates are left, they cannot be interviewed
        while (!candidates.empty()) {
            cout << "Candidate " << candidates.front() << " could not be scheduled for an interview.\n";
            candidates.pop();
        }
    }
};

int main() {
    ScheduleInterview schedule;
    schedule.settleInterview(2, 3, 5);
    return 0;
}
