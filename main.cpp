#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std; // Requirement: assume using namespace std [Saved Information]

struct Order {
    int id;
    string name;
    double dist;
    int time;
    string weather;
    string status;
};

void processBigData(vector<Order>& orders) {
    cout << "----------------------------------------------------" << endl;
    cout << "ZOMATO BIG DATA ENGINE: ANALYZING LIVE STREAM..." << endl;
    cout << "----------------------------------------------------" << endl;
    for (auto& o : orders) {
        // Data Cleaning & Real-time Logic
        if (o.dist <= 0) o.status = "REJECTED (Invalid GPS)";
        else if (o.weather == "Rain") o.status = "EXTENDED ETA (Weather)";
        else if (o.time > 40) o.status = "DELAY ALERT (Kitchen Busy)";
        else o.status = "ON TRACK";

        cout << "Order ID: " << o.id << " | User: " << o.name << " | Status: " << o.status << endl;
    }
}

int main() {
    ifstream file("orders.csv");
    string line, word;
    vector<Order> stream;

    if (!file.is_open()) {
        cout << "Error: orders.csv not found! Ensure the file is in the same directory." << endl;
        return 1;
    }

    getline(file, line); // Skip header row
    while (getline(file, line)) {
        stringstream ss(line);
        Order o;
        string temp;

        getline(ss, temp, ','); o.id = stoi(temp);
        getline(ss, o.name, ',');
        getline(ss, temp, ','); o.dist = stod(temp);
        getline(ss, temp, ','); o.time = stoi(temp);
        getline(ss, o.weather, ',');
        
        stream.push_back(o);
    }

    processBigData(stream);
    file.close();
    return 0;
}