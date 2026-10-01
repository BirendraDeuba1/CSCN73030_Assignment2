#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;


// create a struct containing first and last name
struct STUDENT_DATA {
	string firstName;
	string lastName;

#ifdef PRE_RELEASE
	string email;
#endif
};


int main() {

#ifdef PRE_RELEASE
	cout << "Running Pre-Release source code" << endl;
#else
	cout << "Running Standard source code" << endl;
#endif

	// pushing student data in vector space
	vector<STUDENT_DATA> students;

	// getting data from the resource file
#ifdef PRE_RELEASE
	ifstream inputFile("StudentData_Emails.txt");
#else
	ifstream inputFile("StudentData.txt");
#endif

	if (!inputFile.is_open())
	{
		cout << "Error happened during opening input file" << endl;
		return 1;
	}


	string line;   //make a storage 

	//read the whole line 
    while (getline(inputFile, line))
    {
#ifdef PRE_RELEASE

        size_t firstComma = line.find(',');
        size_t secondComma = line.find(',', firstComma + 1);

        if (firstComma != string::npos && secondComma != string::npos)
        {
            STUDENT_DATA student;

            // Last name before first comma
            student.lastName = line.substr(0, firstComma);

            // First name between first and second comma
            student.firstName = line.substr(
                firstComma + 1,
                secondComma - firstComma - 1
            );

            // Remove the space before first name
            if (!student.firstName.empty() && student.firstName[0] == ' ')
            {
                student.firstName.erase(0, 1);
            }

            // Email after second comma
            student.email = line.substr(secondComma + 1);

            students.push_back(student);
        }

#else

        size_t commaPosition = line.find(',');

        if (commaPosition != string::npos)
        {
            STUDENT_DATA student;

            student.lastName = line.substr(0, commaPosition);
            student.firstName = line.substr(commaPosition + 1);

            students.push_back(student);
        }

#endif
    }

	inputFile.close();

#ifdef _DEBUG
    for (const STUDENT_DATA& student : students)
    {
        cout << student.firstName << " "
            << student.lastName;

#ifdef PRE_RELEASE
        cout << " " << student.email;
#endif

        cout << endl;
    }
#endif

	return 1;
}