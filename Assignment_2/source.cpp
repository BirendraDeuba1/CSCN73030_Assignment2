#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;


// create a struct containing first and last name
struct STUDENT_DATA {
	string firstName;
	string lastName;
};


int main() {

	// pushing student data in vector space
	vector<STUDENT_DATA> students;

	// getting data from the resource file
	ifstream inputFile("StudentData.txt");

	if (!inputFile.is_open())
	{
		cout << "Error happened during opening StudentData.txt file" << endl;
		return 1;
	}


	string line;   //make a storage 

	//read the whole line 
	while (getline(inputFile, line))
	{
		size_t commaPosition = line.find(',');      // check from the whole line and look for the comma ','

		if (commaPosition != string::npos)
		{
			/// create a student object to store first and last name
			STUDENT_DATA student;

			// take the line from index 0 till it get to the commaposition 
			student.lastName = line.substr(0, commaPosition);

			// extract the letter from that commaPosition + 1 till the end of the line
			student.firstName = line.substr(commaPosition + 1);

			//now we pushing it back to vector
			students.push_back(student);

		}
	}

	inputFile.close();

	for (const STUDENT_DATA& student : students)
	{
		cout << student.firstName << " " << student.lastName << endl;
	}

	return 1;
}