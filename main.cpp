#include<string>
#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include<sstream>
#include<cctype>
#include<algorithm>
#define SIZE 50
using namespace std;
struct Student{
	string FullName, lastfirstname[3];
	string ID;
	int Scores[6];
	int Quiz;
	char Grade;
	double Avg;
};
struct Course {
	Student stud[50];
	string CourseName, SepCourseName[10];
	string CourseID;
	string CourseLocation;
	double ClassAvg;
};
bool OpenFile(ifstream&);
void ReadStudent(ifstream& fin, Student& temp);
int ReadData(ifstream& fin, Student list[], int size);
void ProcessStudent(Student& temp, int size);
void ProcessList(Student list[], int size, Course& C1);
void PrintTable(Student list[], int size);
void assignGrade(float avg, char& grade);
void ReadCourse(ifstream& fin, Course& C1, int& counter);
void PrintCourse(Course& C1, int counter, string& CourseName, string& CourseLocation);
void bubblesortScores(Student& temp, int size);
void printData(Student list[], int size);
void SortName(Student list[], int size); 
void SortAvg(Student list[], int size);
void Tablechoice(Student S1[], int size, char& userChoice);
void separateName(Student& temp);
int Search(Student list[], int size, string target);
void FindIt(Student list[], int size);
void addStudent(Student list[], int& size, Course& C1);
void Pausing(char&);
void EntireProcess(Student S1[], int& size, char& TableChoice, char& userchar, string& USERCHOICE, ofstream& fout, Course C1, int& counter);
void deleteStudent(Student list[], int& size);
void editStudent(Student list[], int size, Course& C1);
void saveFile(ofstream& fout, Student list[], int size, Course C1, int& counter);
void ClassAvg(Student S1[], Course& C1, int size, int& counter);
void processCourse(Course& C1, Student S1[], int size);


int main() {
	ifstream fin;
	ofstream fout;
	string FileName, outputFileName;
	Student S1[SIZE];
	Course C1;
	char TableChoice, userchar;
	string USERCHOICE;
	int size, Counter, counter, Sindex;

	if (OpenFile(fin)) {
		ReadCourse(fin, C1, counter);
		PrintCourse(C1, counter, C1.CourseName, C1.CourseLocation);
		size = ReadData(fin, S1, SIZE);
		if (size > 0) {
			while (USERCHOICE != "Quit") {
				ProcessList(S1, size, C1);
				PrintTable(S1, size);
				EntireProcess(S1, size, TableChoice, userchar, USERCHOICE, fout, C1, Counter);
			}
		}
		else
			cout << "Empty file.\n";
	}
	else
		cout << "Failed to open file.\n\n";
	



	return (0);
}
bool OpenFile(ifstream& fin) {
	string FileName;
	cout << "Enter a file name or location: ";
	cin >> FileName;
	fin.open(FileName.c_str());
	if (fin.fail()) {
		return false;
	}
	else
		return true;
}
void ReadStudent(ifstream& fin, Student& temp) {
	getline(fin, temp.FullName);
	fin >> temp.ID;
	fin >> temp.Quiz;
	for (int i = 0; i < 6; i++) {
		fin >> temp.Scores[i];
	}
	fin.ignore(10, '\n');
	}
int ReadData(ifstream& fin, Student list[], int size) {
	int counter = 0;
	ReadStudent(fin, list[counter]);
	while (!fin.eof()) {
		counter++;
		if (counter < size) {
			ReadStudent(fin, list[counter]);
		}
		else {
			cout << "Array is full.\n";
			break;
		}
	}
	fin.close();
	return counter;
}
void ReadCourse(ifstream& fin, Course& C1, int& counter) {
	int i = 0;
	counter = 0;
	getline(fin, C1.CourseName);
	stringstream sin(C1.CourseName);
	while (sin.good() && i < 10) {
		sin >> C1.SepCourseName[i];
		++i;
	}
	while (!C1.SepCourseName[counter].empty()) {
		counter++;
	}
	getline(fin, C1.CourseLocation);
}
void PrintCourse(Course& C1, int counter, string& CourseName, string& CourseID) {
	CourseName = "";
	for (int i = 0; i < counter - 1; i++) {
		CourseName = CourseName + C1.SepCourseName[i] + " ";
	}
	C1.CourseID = C1.SepCourseName[counter - 1];
	cout << "Course Name:     " << CourseName << "Course" << endl;
	cout << "ID:               " << C1.CourseID << endl;
	cout << "Class Location:  " << C1.CourseLocation << endl;
}
void processCourse(Course& C1, Student S1[], int size) {
	for (int i = 0; i < size; i++) {
		C1.stud[i] = S1[i];
	}
}
void ProcessStudent(Student& temp, int size) {
	int total = 0;
	for (int i = 0; i < 5; i++) {
		total += (temp.Scores[i] * 90);
	}
	total += (temp.Quiz * 10);
	temp.Avg = total / (10.0 + 90.0 + 90.0 + 90.0 + 90.0 + 90.0);
	for (int i = 0; i < 6; i++) {
		if (temp.Scores[i] < 0 || temp.Quiz < 0 || temp.Scores[i] > 100 || temp.Quiz > 100) {
			temp.Avg = -1;
		}
	}
	assignGrade(temp.Avg, temp.Grade);
}
void ProcessList(Student list[], int size, Course& C1) {
	for (int i = 0; i < size; i++) {
		separateName(list[i]);
		bubblesortScores(list[i], 6);
		ProcessStudent(list[i], size);
	}
	processCourse(C1, list, size);
}
void printData(Student list[], int size) {
	for (int j = 0; j < size; j++) {
		cout << list[j].FullName << " ";
		for (int i = 0; i < 6; i++) {
			cout << list[j].Scores[i] << " ";
		}
		cout << endl;
	}
}
void PrintTable(Student list[], int size) {
	cout << fixed << setprecision(1) << left;
	cout << setw(20) << "Name" << setw(10) << "ID" << setw(13) << "Average" << setw(15) << "Grade" << endl;
	for (int i = 0; i < size; i++) {
		cout << setw(20) << list[i].lastfirstname[1] + list[i].lastfirstname[2] + ", " + list[i].lastfirstname[0];
		cout << setw(10) << list[i].ID;
		cout << setw(13) << list[i].Avg;
		cout << setw(15) << list[i].Grade;
		cout << endl;

	}
}
void assignGrade(float avg, char& grade) {
	if (avg >= 90 && avg <= 100)
		grade = 'A';
	else if (avg >= 80 && avg < 90)
		grade = 'B';
	else if (avg >= 70 && avg < 80)
		grade = 'C';
	else if (avg >= 60 && avg < 70)
		grade = 'D';
	else if (avg >= 0 && avg < 60)
		grade = 'F';
	else
		grade = 'I';
}
void bubblesortScores(Student& temp, int size) {
	int Temp;
	bool flag;
	do {
		size--;
		flag = false; 
			for(int j = 0; j < size; j++){
				if (temp.Scores[j] < temp.Scores[j + 1]) {
					Temp = temp.Scores[j + 1];
					temp.Scores[j + 1] = temp.Scores[j];
					temp.Scores[j] = Temp;
					flag = true;
			}
		}
	} while (flag);
}
void SortName(Student list[], int size) {
	Student Temp;
	bool flag;
	do {
		size--;
		flag = false;
		for (int i = 0; i < size; i++) {
			if (list[i].lastfirstname[1] > list[i + 1].lastfirstname[1]) {
				Temp = list[i + 1];
				list[i + 1] = list[i];
				list[i] = Temp;
				flag = true;
			}
		}
	} while (flag);
}
void SortAvg(Student list[], int size) {
	Student temp;
	bool flag;
	do {
		size--;
		flag = false;
		for (int i = 0; i < size; i++) {
			if (list[i].Avg < list[i + 1].Avg) {
				temp = list[i + 1];
				list[i + 1] = list[i];
				list[i] = temp;
				flag = true;
			}
		}
	} while (flag);
}
void Tablechoice(Student S1[], int size, char& userChoice) {
	cout << endl;
	cout << "Your choice of sort:" << endl;
	cout << "1) Alphabetical based on last name: Press 'A'" << endl;
	cout << "2) Descending order based on student average: Press 'B'" << endl;
	cout << "Enter your choice: ";
	cin >> userChoice;
	if (userChoice == 'A') {
		SortName(S1, size);
		PrintTable(S1, size);
		cout << "_______________________________________________________________" << endl;
	}
	else if (userChoice == 'B') {
		SortAvg(S1, size);
		PrintTable(S1, size);
		cout << "_______________________________________________________________" << endl;
	}
}
void separateName(Student& temp) {
	int i = 0;
	stringstream sin(temp.FullName);
	while (sin.good() && i < 3) {
		sin >> temp.lastfirstname[i];
		++i;
	}
	if (!temp.lastfirstname[2].empty()) {
		temp.lastfirstname[1] += " ";
	}
}
int Search(Student list[], int size, string target) {
	string temp1, temp3, temp2 = target;
	for (int i = 0; i < size; i++) {
		temp1 = list[i].lastfirstname[1];
		temp3 = list[i].lastfirstname[2];
		transform(temp1.begin(), temp1.end(), temp1.begin(), tolower);
		transform(temp2.begin(), temp2.end(), temp2.begin(), tolower);
		transform(temp3.begin(), temp3.end(), temp3.begin(), tolower);
		if (temp1 == temp2 || temp2 == (temp1 + temp3)) {
			return i;
		}
	}
	return -1;
}
void FindIt(Student list[], int size) {
	string target;
	int index;
	cout << "Enter the last name to search for: ";
	cin.ignore(10, '\n');
	getline(cin, target);
	index = Search(list, size, target);
	if (index == -1) {
		cout << target << " not on the list." << endl;
	}
	else {
		cout << endl;
		cout << "Here is the data for " << list[index].FullName << ":" << endl;
		cout << setw(20) << "Name" << setw(10) << "ID" << setw(13) << "Average" << setw(15) << "Grade" << endl;
		cout << setw(20) << list[index].lastfirstname[1] + list[index].lastfirstname[2] + ", " + list[index].lastfirstname[0];
		cout << setw(10) << list[index].ID;
		cout << setw(13) << list[index].Avg;
		cout << setw(15) << list[index].Grade;
		cout << endl;
		cout << "_______________________________________________________________" << endl;
	}
}
void addStudent(Student list[], int& size, Course& C1) {
	cout << "Enter student's full name: ";
	cin.ignore(10, '\n');
	getline(cin, list[size].FullName);
	separateName(list[size]);
	for (int i = 0; i < size; i++) {
		if (list[size].lastfirstname[1] == list[i].lastfirstname[1] || (list[size].lastfirstname[1] + list[size].lastfirstname[2]) == (list[i].lastfirstname[1] + list[i].lastfirstname[2])) {
			cout << list[i].FullName << " is already in the list." << endl;
			exit(0);
		}
	}
	cout << "Enter student's ID: ";
	cin >> list[size].ID;
	cout << "Enter student's quiz scores: ";
	cin >> list[size].Quiz;
	cout << "Enter student's test scores(separated by space): ";
	for (int i = 0; i < 6; i++) {
		cin >> list[size].Scores[i];
	}
	size++;
	ProcessList(list, size, C1);
	PrintTable(list, size);
	cout << "_______________________________________________________________" << endl;
}
void deleteStudent(Student list[], int& size) {
	string userChoice;
	cout << "Enter the last name of the student you want to delete: ";
	cin.ignore(10, '\n');
	getline(cin, userChoice);
	for (int i = 0; i < size; i++) {
		if (userChoice == list[i].lastfirstname[1] || userChoice == (list[i].lastfirstname[1] + list[i].lastfirstname[2])) {
			for (i; i < size; i++) {
				list[i] = list[i + 1];
			}
			size--;
			PrintTable(list, size);
			break;
		}
		else if (i == size - 1) {
			cout << userChoice << " is not on the list." << endl;
				break;
		}
	}
}
void editStudent(Student list[], int size, Course& C1) {
	int newScore, scoreIndex, newQuiz, index;
	string name, userResponse;
	cout << "Enter the last name of the student you want to edit: ";
	cin.ignore(10, '\n');
	getline(cin, name);
	index = Search(list, size, name);
	if (index == -1) {
		cout << name << " not on the list." << endl;
	}
	else {
		while (userResponse != "done") {
			cout << " ____________________________" << endl;
			cout << "|To edit Quiz score: Enter 1.|" << endl;
			cout << "|To edit Test score: Enter 2.|" << endl;
			cout << "|____________________________|" << endl;
			cout << "Type 'done' to exit the editing function." << endl;
			cout << "Your response: ";
			cin >> userResponse;
			if (userResponse == "1") {
				cout << "Enter a new quiz score for " << name << ": ";
				cin >> newQuiz;
				if (!cin) {
					cout << "Enter a number please.";
					cin >> newQuiz;
				}
				list[index].Quiz = newQuiz;
				cout << "\nHere is a new list: " << endl;
				ProcessList(list, size, C1);
				PrintTable(list, size);
				cout << "_______________________________________________________________" << endl;
			}
			else if (userResponse == "2") {
				cout << "Test scores for " << name << endl;
				for (int i = 0; i < 6; i++) {
					cout << i + 1 << ". " << list[index].Scores[i] << "  ";
				}
				cout << endl;
				cout << "Which test scores do you want to edit? ";
				cin >> scoreIndex;
				if (scoreIndex > 0) {
					cout << "Enter a new test " << scoreIndex << " score: ";
					cin >> newScore;
					list[index].Scores[scoreIndex - 1] = newScore;
					cout << "\nHere is a new list: " << endl;
					ProcessList(list, size, C1);
					PrintTable(list, size);
					cout << "_______________________________________________________________" << endl;
				}
				else {
					cout << "Invalid choice." << endl;
				}
			}
		}
	}
	
}
void saveFile(ofstream& fout, Student list[], int size, Course C1, int& counter) {
	string newFile;
	cout << "Enter the new file name: ";
	cin >> newFile;
	fout.open(newFile);
	fout << "Course Name:     " << C1.CourseName << "Course" << endl;
	fout << "ID:               " << C1.CourseID << endl;
	fout << "Class Location:  " << C1.CourseLocation << endl;
	fout << endl;
	fout << fixed << setprecision(1) << left;
	fout << setw(20) << "Name" << setw(10) << "ID" << setw(13) << "Average" << setw(15) << "Grade" << endl;
	fout << endl;
	for (int i = 0; i < size; i++) {
		fout << setw(20) << list[i].lastfirstname[1] + list[i].lastfirstname[2] + ", " + list[i].lastfirstname[0];
		fout << setw(10) << list[i].ID;
		fout << setw(13) << list[i].Avg;
		fout << setw(15) << list[i].Grade;
		fout << endl;
	}
	ClassAvg(list, C1, size, counter);
	fout << endl;
	fout << "Class Average for " << counter << " students: " << C1.ClassAvg << endl;
	fout.close();
	cout << endl;
	cout << "Successfully saved your data into " << newFile << endl;
}
void Pausing(char& next) {
	do {
		cout << '\n' << "Press the Enter key to continue.";
		cin.get(next);
	} while (cin.get() != '\n');

}
void EntireProcess(Student S1[], int& size, char& TableChoice, char& userchar, string& USERCHOICE, ofstream& fout, Course C1, int& counter) {
	cout << " ______________________________________" << endl;
	cout << "|What do you want to do?               |" << endl;
	cout << "|1. Organize table.                    |" << endl;
	cout << "|2. Find a student from a list.        |" << endl;
	cout << "|3. Add a student into the list.       |" << endl;
	cout << "|4. Delete a student from the list.    |" << endl;
	cout << "|5. Edit student information.          |" << endl;
	cout << "|6. Save your final table into a file. |" << endl;
	cout << "|______________________________________|" << endl;
	cout << " ***Enter <Quit> to exit****" << endl;
	cout << "Enter your number: ";
	cin >> USERCHOICE;
	if (USERCHOICE == "1") {
		Tablechoice(S1, size, TableChoice);
		Pausing(userchar);
	}
	else if (USERCHOICE == "2") {
		FindIt(S1, size);
		Pausing(userchar);
	}
	else if (USERCHOICE == "3") {
		addStudent(S1, size, C1);
		Pausing(userchar);
	}
	else if (USERCHOICE == "4") {
		deleteStudent(S1, size);
		Pausing(userchar);
	}
	else if (USERCHOICE == "5") {
		editStudent(S1, size, C1);
		Pausing(userchar);
	}
	else if (USERCHOICE == "6") {
		saveFile(fout, S1, size, C1, counter);
		exit(0);
	}
}
void ClassAvg(Student S1[], Course& C1, int size, int& counter) {
	float ClassTotal = 0;
	counter = 0;
	for (int i = 0; i < size; i++) {
		if (S1[i].Avg >= 0 && S1[i].Avg <= 100) {
			ClassTotal += S1[i].Avg;
			counter++;
		}
	} 
	C1.ClassAvg = ClassTotal / counter;
}


