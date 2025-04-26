#include <fstream>;
#include <iostream>;
#include <vector>;
#include <string>;
#include <set>;
using namespace std;

struct Records {
	string date;
	string timeStart;
	string timeEnd;
	string phone;
	string callType;

};
int TimeInSeconds(string &str) {
	return stoi(str.substr(0, 2)) * 3600 + stoi(str.substr(3, 2)) * 60 + stoi(str.substr(6, 2));
}

int main() {
	ifstream file("PhoneBook.txt");
	Records call[10];
	int count = 0;
	int cntCallsNumber = 0;
	int callTimeVh = 0;
	int callTimeIs = 0;
	int mxTimeCall = 0;
	int mnTimeCall = 100 * 100;
	int indMx = 0;
	int indMn = 0;
	int startTime = 0;
	int endTime = 0;
	int choice;
	string line;
	string number;
	bool isEmpty = true;
	set<char> allowedChar = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

	if (!file.is_open()) {
		cerr << "Failed to open file" << endl;
	}
	while (getline(file, line)) {
		if (!line.empty()) {
			isEmpty = false;
		}
	}

	if (isEmpty) {
		cout << "File is Empty";
		return 0;
	}
	file.clear();
	file.seekg(0);
	while (count < 10 && file
		>> call[count].date
		>> call[count].timeStart
		>> call[count].timeEnd
		>> call[count].phone
		>> call[count].callType) {
		count++;
	};
	while (count < 10) {
		if (call[count].date.empty() || call[count].timeStart.empty() ||
			call[count].timeEnd.empty() || call[count].phone.empty() ||
			call[count].callType.empty()) {
			cout << "Some fields empty " << endl;
			return 0;
		}
		count++;
	};
	count = 0;
	std:: cout << "Enter phone number: ";
	cin >> number;

	for (char c : number) {
		if (allowedChar.find(c) == allowedChar.end()) {
			std::cout << "Invalid characters in the number, the number must consist only of numbers" << endl;
			return 0;
		}
		else if (number.length() != 11) {
			std::cout << "The number does not have 11 digits" << endl;
			return 0;
		}
	}
	
	
	file.close();
	for (int i = 0; i < 10; i++) {
		if (call[i].phone == number) {
			cntCallsNumber++;
			startTime = TimeInSeconds(call[i].timeStart);
			endTime = TimeInSeconds(call[i].timeEnd);
			if (call[i].callType == "vhodyashi") {
				callTimeVh += endTime - startTime;
			}
			if (call[i].callType == "ishodyashi") {
				callTimeIs += endTime - startTime;
				
			}
		}
		else {
			cout << "Imvalid";
			return 0;
		}
	}
	
	for (int i = 0; i < 10; i++) {
		startTime = TimeInSeconds(call[i].timeStart);
		endTime = TimeInSeconds(call[i].timeEnd);

		if (mxTimeCall < (endTime - startTime)) {
			mxTimeCall = endTime - startTime;
			indMx = i;
		}
		if (mnTimeCall > (endTime - startTime)) {
			mnTimeCall = endTime - startTime;
			indMn = i;
		}

	}
	while (true) {
		std::cout << "\nMeny\n";
		std::cout << "1. Find total calls number and time of incoming and outgoing calls\n";
		std::cout << "2. Record of the longest call\n";
		std::cout << "3. Date and number of the subscriber with whom the shortest conversation took place\n";
		std::cout << "4. Leave\n";
		std::cout << "Choice action: ";
		cin >> choice;
		if (choice != 1 && choice != 2 && choice != 3 && choice != 4) {
			std::cout << "Incorrect number of action";
			break;
		}
		else if (choice == 1)
			std::cout << endl << "Quality calls: " << cntCallsNumber << "; Time incoming call: " << callTimeVh << "; Time outgoing call: " << callTimeIs << endl;
		else if (choice == 2)
			std::cout << endl << "Record of the longest call" << endl << "   " << call[indMx].date << endl << "   " << call[indMx].timeStart << endl << "   " << call[indMx].timeEnd << endl << "   " << call[indMx].phone << endl << "   " << call[indMx].callType << endl;
		else if (choice == 3)
			std::cout << endl << "Date" << endl << "   " << call[indMn].date << endl << "Number" << "   " << call[indMn].phone << endl;
		else if (choice == 4) {
			break;
		}
		else {
			std::cout << endl << "Error\n";
			break;
		}
	}
	return 0;
}
