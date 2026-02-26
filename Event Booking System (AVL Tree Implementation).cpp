#include <iostream>
#include <string>
using namespace std;

class EventDate
{
public:
    int year, month, day, hour, minute;

    EventDate() : year(0), month(0), day(0), hour(0), minute(0) {}

    bool isLessThan(const EventDate& date) const
    {
        if (year != date.year)
        {
            return year < date.year;
        }
        if (month != date.month)
        {
            return month < date.month;
        }
        if (day != date.day)
        {
            return day < date.day;
        }
        if (hour != date.hour)
        {
            return hour < date.hour;
        }
        return minute < date.minute;
    }

    bool isEqualTo(const EventDate& date) const
    {
        if (year == date.year && month == date.month &&
            day == date.day && hour == date.hour && minute == date.minute)
        {
            return true;
        }
        else return false;
    }

    void input()
    {
        cout << "Enter date (YYYY MM DD HH MM (0 or 30)): ";
        cin >> year >> month >> day >> hour >> minute;
        while (month > 12 || month < 1)
        {
            cout << "Please enter valid month (1-12): ";
            cin >> month;
        }
        while (day<1 || day>daysInMonth(month, year))
        {
            cout << "Please enter valid day (1-" << daysInMonth(month, year) << "): ";
            cin >> day;
        }
        while (hour > 23 || hour < 0 || (minute != 30 && minute != 0))
        {
            cout << "Please enter valid Hours (0-23) & Minutes (0 or 30): ";
            cin >> hour >> minute;
        }
    }
    int daysInMonth(int month, int year)
    {
        if (month == 2)
        {
            if (isLeap(year))
            {
                return 29;
            }
            else return 28;
        }
        else if (month == 4 || month == 6 || month == 9 || month == 11)
            return 30;
        else return 31;
    }
    bool isLeap(int year)
    {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    void display() const
    {
        cout << year << "-";

        if (month < 10)
        {
            cout << "0";
        }
        cout << month << "-";

        if (day < 10)
        {
            cout << "0";
        }
        cout << day << " ";

        if (hour < 10)
        {
            cout << "0";
        }
        cout << hour << ":";

        if (minute < 10)
        {
            cout << "0";
        }
        cout << minute;
    }

    void addMinutes(int m)
    {
        minute += m;
        while (minute >= 60)
        {
            minute -= 60;
            hour++;
            if (hour >= 24)
            {
                hour = 0;
                day++;
                if (day > daysInMonth(month, year))
                {
                    day = 1;
                    month++;
                    if (month > 12)
                    {
                        month = 1;
                        year++;
                    }
                }
            }
        }
    }
};

class Event
{
public:
    string name;
    EventDate date;

    Event() {}
    Event(string n, EventDate d) : name(n), date(d) {}

    void display() const
    {
        date.display();
        cout << " - " << name << endl;
    }
};

class AVLNode
{
public:
    Event data;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(Event e) : data(e), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree
{
private:
    AVLNode* root;

    int height(AVLNode* n)
    {
        if (n != nullptr)
            return n->height;
        else
            return 0;
    }

    int getBalance(AVLNode* n)
    {
        if (n != nullptr)
            return height(n->left) - height(n->right);
        else
            return 0;
    }

    int max(int a, int b)
    {
        if (a > b)
        {
            return a;
        }
        else return b;
    }

    AVLNode* rightRotate(AVLNode* temp)
    {
        AVLNode* temp2 = temp->left;
        temp->left = temp2->right;
        temp2->right = temp;
        temp->height = max(height(temp->left), height(temp->right)) + 1;
        temp2->height = max(height(temp2->left), height(temp2->right)) + 1;
        return temp2;
    }

    AVLNode* leftRotate(AVLNode* temp)
    {
        AVLNode* temp2 = temp->right;
        temp->right = temp2->left;
        temp2->left = temp;
        temp->height = max(height(temp->left), height(temp->right)) + 1;
        temp2->height = max(height(temp2->left), height(temp2->right)) + 1;
        return temp2;
    }

    AVLNode* insert(AVLNode* node, Event e)
    {
        if (node == nullptr)
        {
            return new AVLNode(e);
        }
        if (e.date.isLessThan(node->data.date))
        {
            node->left = insert(node->left, e);
        }
        else if (node->data.date.isLessThan(e.date))
        {
            node->right = insert(node->right, e);
        }
        else
        {
            cout << "Conflict with existing event: ";
            node->data.display();
            suggestNextSlot(node->data.date);
            return node;
        }

        node->height = max(height(node->left), height(node->right)) + 1;
        int balance = getBalance(node);

        if (balance > 1 && e.date.isLessThan(node->left->data.date))
        {
            return rightRotate(node);
        }
        if (balance < -1 && node->right->data.date.isLessThan(e.date))
        {
            return leftRotate(node);
        }
        if (balance > 1 && node->left->data.date.isLessThan(e.date))
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && e.date.isLessThan(node->right->data.date))
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void inOrder(AVLNode* node)
    {
        if (node == nullptr)
            return;
        inOrder(node->left);
        node->data.display();
        inOrder(node->right);
    }

    bool exists(AVLNode* node, const EventDate& dt)
    {
        if (node == nullptr)
        {
            return false;
        }
        if (dt.isEqualTo(node->data.date))
        {
            return true;
        }
        if (dt.isLessThan(node->data.date))
        {
            return exists(node->left, dt);
        }
        else
        {
            return exists(node->right, dt);
        }
    }
public:
    AVLTree() : root(nullptr) {}

    void addEvent(const Event& e)
    {
        root = insert(root, e);
    }

    void displayEvents()
    {
        if (root == nullptr)
        {
            cout << "No event is Scheduled\n";
        }
        else
        {
            cout << "Scheduled Events:\n";
            inOrder(root);
        }
    }

    bool isConflict(const EventDate& dt)
    {
        return exists(root, dt);
    }

    void suggestNextSlot(EventDate& dt)
    {
        while (isConflict(dt))
        {
            dt.addMinutes(30);
        }
        cout << "\nSuggested next available time: ";
        dt.display();
        cout << endl;
    }
};

class RecurringNode
{
public:
    Event event;
    RecurringNode* next;
    RecurringNode(Event e) : event(e), next(nullptr) {}
};

class RecurringList
{
private:
    RecurringNode* head;
    AVLTree& tree;

public:
    RecurringList(AVLTree& t) : head(nullptr), tree(t) {}
    int daysInMonth(int month, int year)
    {
        if (month == 2)
        {
            if (isLeap(year))
            {
                return 29;
            }
            else return 28;
        }
        else if (month == 4 || month == 6 || month == 9 || month == 11)
            return 30;
        else return 31;
    }
    bool isLeap(int year)
    {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }
    void addRecurring(string name, EventDate start, string type, int count)
    {
        EventDate temp = start;

        for (int i = 0; i < count; i++)
        {
            if (tree.isConflict(temp))
            {
                cout << "Conflict Detected, Aborted Adding Recurring Events\n";
                return;
            }
            if (type == "daily")
            {
                temp.day++;
                if (temp.day > daysInMonth(temp.month, temp.year))
                {
                    temp.month++;
                    temp.day = 1;
                    if (temp.month > 12)
                    {
                        temp.year++;
                        temp.month = 1;
                    }
                }
            }
            else if (type == "weekly")
            {
                temp.day += 7;
                while (temp.day > daysInMonth(temp.month, temp.year))
                {
                    temp.day -= daysInMonth(temp.month, temp.year);
                    temp.month++;
                }
                if (temp.month > 12)
                {
                    temp.year++;
                    temp.month = 1;
                }
            }
        }

        RecurringNode* last = nullptr;
        EventDate current = start;

        for (int i = 0; i < count; i++)
        {
            Event e(name + " #" + to_string(i + 1), current);
            tree.addEvent(e);
            RecurringNode* newNode = new RecurringNode(e);
            if (!head)
                head = newNode;
            else
                last->next = newNode;
            last = newNode;
            if (type == "daily")
            {
                current.day++;
                if (current.day > daysInMonth(current.month, current.year))
                {
                    current.month++;
                    current.day = 1;
                    if (current.month > 12)
                    {
                        current.year++;
                        current.month = 1;
                    }
                }
            }
            else if (type == "weekly")
            {
                current.day += 7;
                while (current.day > daysInMonth(current.month, current.year))
                {
                    current.day -= daysInMonth(current.month, current.year);
                    current.month++;
                }
                if (current.month > 12)
                {
                    current.year++;
                    current.month = 1;
                }
            }
            cout << "Event Added Successfully\n";
        }
    }
    ~RecurringList()
    {
        RecurringNode* temp = head;
        while (temp)
        {
            RecurringNode* temp2 = temp;
            temp = temp->next;
            delete temp2;
        }
    }
};

int main()
{
    AVLTree tree;
    RecurringList list(tree);

    cout << "\n=====================================================================================\n";
    cout << "                  * * *  WELCOME TO EVENT BOOKING SYSTEM  * * *                     \n";
    cout << "=====================================================================================\n";

    while (true)
    {
        cout << "\n-------------------------------------------------------------------------------------\n";
        cout << "Please choose an option:\n";
        cout << "1. Add Event\n";
        cout << "2. Add Recurring Event\n";
        cout << "3. View All Events\n";
        cout << "4. Exit\n";
        cout << "-------------------------------------------------------------------------------------\n";
        cout << "Your choice: ";

        int choice; cin >> choice;

        if (choice == 1)
        {
            string name;
            EventDate date;
            cout << "\n--- Add New Event ---\n";
            cout << "Event Name: ";
            cin.ignore();
            getline(cin, name);
            date.input();

            if (!tree.isConflict(date)) {
                tree.addEvent(Event(name, date));
                cout << "\nEvent added successfully!\n";
            }
            else {
                cout << "\nConflict detected. Event not added.\n";
                tree.suggestNextSlot(date);
                cout << "Do you want to book the suggested time? (y/n): ";
                char input;
                cin >> input;
                if (input == 'y')
                {
                    tree.addEvent(Event(name, date));
                    cout << "Suggested Time Booked Successfully\n";
                }
                else cout << "Suggested Time Not Booked\n";
            }
        }
        else if (choice == 2)
        {
            string name, type;
            int count;
            EventDate date;
            cout << "\n--- Add Recurring Event ---\n";
            cout << "Event Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Recurring Type (daily/weekly): ";
            cin >> type;
            cout << "How many times: ";
            cin >> count;
            date.input();
            list.addRecurring(name, date, type, count);
        }
        else if (choice == 3)
        {
            cout << "\n======================== SCHEDULED EVENTS ========================\n";
            tree.displayEvents();
            cout << "==================================================================\n";
        }
        else if (choice == 4)
        {
            cout << "\nExiting Program... Goodbye!\n";
            cout << "==================================================================\n";
            break;
        }
        else
        {
            cout << "\nInvalid choice. Please enter a number between 1 and 4.\n";
        }
    }

    return 0;
}