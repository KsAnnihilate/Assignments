// @Ananth if you're reading this, this confirms C is a painful language :')


// Filename: Struct_lab.c
// Program author: [redacted]
// Program date: 23 November 2021
// Program description: This code implements a Student struct and an Address
//                      struct in accordance with [Assignment]. More details
//                      are given in comments below. 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 5

/*
 * Defines an information type for each member of a `Student` and `Address`,
 * as well as a type to indicate resetting a struct's members.
*/
enum InfoType {NAME, FNAME, MNAME, LNAME, ID, GRADE, ADDRESS,
               HNUM, SNAME, STYPE, CITY, STATE, PC,
               RESET};


/*
  * The `Address` struct contains six elements: a house number, a street name,
  * a street type, a city, a state, and a postal code. I chose this breakdown
  * of an address based on this guide by ARCGIS:
  *
  * https://desktop.arcgis.com/en/arcmap/10.3/guide-books/geocoding/
  * what-is-an-address.htm
  *
  * My implementation of this breakdown assumes that addresses are in the US
  * and have positive house numbers and postal codes. The only exception I
  * chose to handle is when there is no street type, as I wanted to play
  * around with ternary operators. My program ignores all other exceptions,
  * such as those detailed here:
  *
  * https://www.mjt.me.uk/posts/falsehoods-programmers-believe-about-addresses/
 */
typedef struct address
{
  unsigned int houseNumber;
  char* streetName;
  char* streetType;
  char* city;
  char* state;
  unsigned int postalCode;
} Address;


/*
 * The `Student` struct contains six elements: a first name, a middle name,
 * a last name, a student ID, a grade, and an `Address`. I chose this structure
 * arbitrarily and am aware that there are exceptions to this naming system,
 * as described here:
 *
 * https://www.kalzumeus.com/2010/06/17/falsehoods-programmers-believe-about
 * -names/
 *
 * Note that IDs are assumed to be different for different students.
*/
typedef struct student
{
  char* firstName;
  char* middleName;
  char* lastName;
  unsigned int studentID;
  unsigned int grade;
  Address address;
} Student;

/*
 * Standard functions to create an `Address` or `Student` given data for
 * their members.
*/
Address createAddress(
  unsigned int houseNumber, char* streetName, char* streetType, char* city,
  char* state, unsigned int postalCode);

Student createStudent(
  char* firstName, char* middleName, char* lastName, unsigned int studentID,
  unsigned int grade, Address address);

/*
 * Standard functions to get members of an `Address` or `Student` given the
 * struct and a requested infoType (defined as an `enum InfoType`).
*/
char* getAddressInfo(Address address, int infoType);
char* getStudentInfo(Student student, int infoType);

/*
 * Standard functions to get members of an `Address` or `Student` given the
 * struct and a requested infoType (defined as an `enum InfoType`)
 *
 * The function takes two types of newData parameters, one of which will be
 * filled with garbage ("" for newDataC and anything for newDataU) at runtime.
 * This is because C does not support function overloading. I tried using
 * _Generic but could not get it to work with type declarators in function
 * declarations/prototypes, so I decided this was the next best implementation.
*/
void setAddressInfo(Address* address, int infoType, char* newDataC,
  unsigned int newDataU);
void setStudentInfo(Student* student, int infoType, char* newDataC,
  unsigned int newDataU);

/*
 * Standard functions to add or delete `Student` structs given an array of
 * students and a student to add or delete. Delete in this context means
 * resetting their data members to "" and 0 for char* members and unsigned int
 * members, respectively.
*/
void addStudent(Student studentSet[SIZE], Student student);
void deleteStudent(Student studentSet[SIZE], Student student);

/*
 * Functions that print out each member of a `Student` or `Address` as well as
 * full names for a `Student` and a full address for an `Address`.
*/
void testStudentData(Student student);
void testAddressData(Address address);


int main(void)
{

  // Define six new students and an array of five students
  Student student1;
  Address address1;
  Student student2;
  Address address2;
  Student student3;
  Address address3;
  Student student4;
  Address address4;
  Student student5;
  Address address5;
  Student student6;
  Address address6;

  // Array to hold all `Student` records
  Student studentSet[SIZE] = {NULL};

  // Fill the first four students with actual structs with valid data
  address1 = createAddress(1, "StreetWithNoType", "", "City1",
                           "SD", 57301);
  student1 = createStudent("First", "Middle", "Last", 011942, 5, address1);

  address2 = createAddress(2, "Test", "Drive", "New York City", "NY", 10001);
  student2 = createStudent("Peter", "Jack", "Phillips", 803426, 9, address2);

  address3 = createAddress(3, "Blank", "Avenue", "Houston", "TX", 77219);
  student3 = createStudent("Jane", "Samuel", "Foster", 791534, 10, address3);

  address4 = createAddress(4, "East Elm", "St.", "Chicago", "IL", 60610);
  student4 = createStudent("Alex", "Scott", "Lee", 816992, 12, address4);

  // In case you want to manually define students 5 and 6 instead of
  // prompting user input
  // address5 = createAddress(5, "Five", "Road", "Washington DC", "DC", 20374);
  // student5 = createStudent("Alice", "J.", "O'Sullivan", 515253, 3, address5);
  //
  // address6 = createAddress(6, "West Six", "Boulevard", "Seattle", "WA", 60610);
  // student6 = createStudent("Rick", "A. B.", "McDonald", 646566, 2, address6);

  // Temporary variables to store user-inputted data
  char* tempFName5 = malloc(sizeof(char) * 25);
  char* tempMName5 = malloc(sizeof(char) * 25);
  char* tempLName5 = malloc(sizeof(char) * 25);
  unsigned int tempID5;
  unsigned int tempGrade5;

  unsigned int tempHNum5;
  char* tempSName5 = malloc(sizeof(char) * 25);
  char* tempSType5 = malloc(sizeof(char) * 25);
  char* tempCity5 = malloc(sizeof(char) * 25);
  char* tempState5 = malloc(sizeof(char) * 25);
  unsigned int tempPC5;

  char* tempFName6 = malloc(sizeof(char) * 25);
  char* tempMName6 = malloc(sizeof(char) * 25);
  char* tempLName6 = malloc(sizeof(char) * 25);
  unsigned int tempID6;
  unsigned int tempGrade6;

  unsigned int tempHNum6;
  char* tempSName6 = malloc(sizeof(char) * 25);
  char* tempSType6 = malloc(sizeof(char) * 25);
  char* tempCity6 = malloc(sizeof(char) * 25);
  char* tempState6 = malloc(sizeof(char) * 25);
  unsigned int tempPC6;

  // Take user input for the fifth `Student`
  printf("\nStudent 5 - Please enter a first name: ");
  scanf("%100[^\n]", tempFName5);

  printf("\nStudent 5 - Please enter a middle name: ");
  getchar();
  scanf("%100[^\n]", tempMName5);

  printf("\nStudent 5 - Please enter a last name: ");
  getchar();
  scanf("%100[^\n]", tempLName5);

  printf("\nStudent 5 - Please enter a student ID: ");
  scanf("%u", &tempID5);

  printf("\nStudent 5 - Please enter a grade: ");
  scanf("%u", &tempGrade5);

  printf("\nStudent 5 Address - Please enter a house number: ");
  scanf("%u", &tempHNum5);

  printf("\nStudent 5 Address - Please enter a street name: ");
  getchar();
  scanf("%100[^\n]", tempSName5);

  printf("\nStudent 5 Address - Please enter a street type: ");
  getchar();
  scanf("%100[^\n]", tempSType5);

  printf("\nStudent 5 Address - Please enter a city: ");
  getchar();
  scanf("%100[^\n]", tempCity5);

  printf("\nStudent 5 Address - Please enter a state: ");
  getchar();
  scanf("%100[^\n]", tempState5);

  printf("\nStudent 5 Address - Please enter a postal code: ");
  scanf("%u", &tempPC5);

  address5 = createAddress(tempHNum5, tempSName5, tempSType5, tempCity5,
    tempState5, tempPC5);
  student5 = createStudent(tempFName5, tempMName5, tempLName5, tempID5,
    tempGrade5, address5);

  // Take user input for the sixth `Student`
  printf("\nStudent 6 - Please enter a first name: ");
  getchar();
  scanf("%100[^\n]", tempFName6);

  printf("\nStudent 6 - Please enter a middle name: ");
  getchar();
  scanf("%100[^\n]", tempMName6);

  printf("\nStudent 6 - Please enter a last name: ");
  getchar();
  scanf("%100[^\n]", tempLName6);

  printf("\nStudent 6 - Please enter a student ID: ");
  scanf("%u", &tempID6);

  printf("\nStudent 6 - Please enter a grade: ");
  scanf("%u", &tempGrade6);

  printf("\nStudent 6 Address - Please enter a house number: ");
  scanf("%u", &tempHNum6);

  printf("\nStudent 6 Address - Please enter a street name: ");
  getchar();
  scanf("%100[^\n]", tempSName6);

  printf("\nStudent 6 Address - Please enter a street type: ");
  getchar();
  scanf("%100[^\n]", tempSType6);

  printf("\nStudent 6 Address - Please enter a city: ");
  getchar();
  scanf("%100[^\n]", tempCity6);

  printf("\nStudent 6 Address - Please enter a state: ");
  getchar();
  scanf("%100[^\n]", tempState6);

  printf("\nStudent 6 Address - Please enter a postal code: ");
  scanf("%u", &tempPC6);

  address6 = createAddress(tempHNum6, tempSName6, tempSType6, tempCity6,
    tempState6, tempPC6);
  student6 = createStudent(tempFName6, tempMName6, tempLName6, tempID6,
    tempGrade6, address6);

  // Place the first five students into the array
  addStudent(studentSet, student1);
  addStudent(studentSet, student2);
  addStudent(studentSet, student3);
  addStudent(studentSet, student4);
  addStudent(studentSet, student5);

  // Print the data of each `Student`
  printf("\nStudent 1 initially:\n");
  testStudentData(studentSet[0]);

  printf("\nStudent 2 initially:\n");
  testStudentData(studentSet[1]);

  printf("\nStudent 3 initially:\n");
  testStudentData(studentSet[2]);

  printf("\nStudent 4 initially:\n");
  testStudentData(studentSet[3]);

  printf("\nStudent 5 initially:\n");
  testStudentData(studentSet[4]);

  printf("\nStudent 6 initially (not in array):\n");
  testStudentData(student6);

  // Delete Student 1
  deleteStudent(studentSet, student1);

  printf("\nStudent 1 after being deleted:\n");
  testStudentData(studentSet[0]);

  // Add Student 6 into the array, taking Student 1's spot
  addStudent(studentSet, student6);

  // Change Student 2's first name
  setStudentInfo(&studentSet[1], FNAME, "Jake", 0);

  // Change Student 3's grade, middle name, and last name
  setStudentInfo(&studentSet[2], GRADE, "", 7);
  setStudentInfo(&studentSet[2], MNAME, "Kip", 0);
  setStudentInfo(&studentSet[2], LNAME, "Rin", 0);

  // Change Student 4's ID
  setStudentInfo(&studentSet[3], ID, "", 123456);

  // Change Student 5's address
  setStudentInfo(&studentSet[4], HNUM, "", 100);
  setStudentInfo(&studentSet[4], SNAME, "Replaced", 0);
  setStudentInfo(&studentSet[4], STYPE, "Road", 0);
  setStudentInfo(&studentSet[4], CITY, "NewCity", 0);
  setStudentInfo(&studentSet[4], STATE, "NewState", 0);
  setStudentInfo(&studentSet[4], PC, "", 100);

  // Print the updated data of all students
  printf("\nStudent 1 after:\n");
  testStudentData(studentSet[0]);

  printf("\nStudent 2 after:\n");
  testStudentData(studentSet[1]);

  printf("\nStudent 3 after:\n");
  testStudentData(studentSet[2]);

  printf("\nStudent 4 after:\n");
  testStudentData(studentSet[3]);

  printf("\nStudent 5 after:\n");
  testStudentData(studentSet[4]);

  printf("\n");

}


/*
 * Creates a new Address struct given data for its six members
*/
Address createAddress(
  unsigned int houseNumber, char* streetName, char* streetType, char* city,
  char* state, unsigned int postalCode)
{
  Address newAddress;

  newAddress.houseNumber = houseNumber;
  newAddress.streetName = streetName;
  newAddress.streetType = streetType;
  newAddress.city = city;
  newAddress.state = state;
  newAddress.postalCode = postalCode;

  return newAddress;
}


/*
 * Creates a new Student struct given data for its six members
*/
Student createStudent(
  char* firstName, char* middleName, char* lastName, unsigned int studentID,
  unsigned int grade, Address address)
{
  Student newStudent;

  newStudent.firstName = firstName;
  newStudent.middleName = middleName;
  newStudent.lastName = lastName;
  newStudent.studentID = studentID;
  newStudent.grade = grade;
  newStudent.address = address;

  return newStudent;
}


/*
 * Gets various members of an `Address`, or the entire address formatted as a
 * string, using an infoType as specified in `enum InfoType`
 *
 * Note how ternary operators are used to handle cases where there is no
 * street type.
*/
char* getAddressInfo(Address address, int infoType)
{
  char* info = malloc(sizeof(char) * 100);
  char* temp = malloc(sizeof(char) * 5);

  // Empty `Address` struct
  if (strcmp(address.streetName, "") == 0)
  {
    return "Error — no data";
  }

  switch(infoType)
  {
    // Get the full address
    case ADDRESS:

      sprintf(info, "%u", address.houseNumber);
      strcat(info, " ");
      strcat(info, address.streetName);
      strcat(info, strlen(address.streetType) == 0 ? ", " : " ");
      strcat(info, address.streetType);
      strcat(info, strlen(address.streetType) == 0 ? "" : ", ");
      strcat(info, address.city);
      strcat(info, ", ");
      strcat(info, address.state);
      strcat(info, " ");
      sprintf(temp, "%u", address.postalCode);
      strcat(info, temp);
      break;

    case HNUM:
      sprintf(info, "%u", address.houseNumber);
      break;

    case SNAME:
      strcpy(info, address.streetName);
      break;

    case STYPE:
      strcpy(info, address.streetType);
      break;

    case CITY:
      strcpy(info, address.city);
      break;

    case STATE:
      strcpy(info, address.state);
      break;

    case PC:
      sprintf(info, "%u", address.postalCode);
      break;

    default:
      strcat(info, "Error — invalid info type.\n");
  }

  return info;
}


/*
 * Gets various members of a `Student`, or their full name formatted as a
 * string, using an infoType as specified in `enum InfoType`
*/
char* getStudentInfo(Student student, int infoType)
{
  char* info = malloc(sizeof(char) * 100);

  // Empty `Student` struct
  if (strcmp(student.firstName, "") == 0)
  {
    return "Error — no data";
  }

  switch(infoType)
  {
    case NAME:
      strcpy(info, student.firstName);
      strcat(info, " ");
      strcat(info, student.middleName);
      strcat(info, " ");
      strcat(info, student.lastName);
      strcat(info, " ");
      break;

    case FNAME:
      strcpy(info, student.firstName);
      break;

    case MNAME:
      strcpy(info, student.middleName);
      break;

    case LNAME:
      strcpy(info, student.lastName);
      break;

    case ID:
      sprintf(info, "%u", student.studentID);
      break;

    case GRADE:
      sprintf(info, "%u", student.grade);
      break;

    case ADDRESS:
      strcpy(info, getAddressInfo(student.address, ADDRESS));
      break;

    default:
      strcat(info, "Error — invalid info type.\n");
  }

  return info;
}


/*
 * Sets a member of an `Address` given an infoType and new data.
 *
 * Note: Please see line 97 for why this function takes both newDataC and
 * newDataU as parameters.
*/
void setAddressInfo(Address* address, int infoType, char* newDataC,
  unsigned int newDataU)
{
  // Reset address data
  if (infoType == RESET)
  {
    address->houseNumber = 0;
    address->streetName = "";
    address->streetType = "";
    address->city = "";
    address->state = "";
    address->postalCode = 0;
  }

  // Change a char* member within address
  else if (strlen(newDataC) != 0)
  {
    switch(infoType)
    {
      case SNAME:
        address->streetName = newDataC;
        break;

      case STYPE:
        address->streetType = newDataC;
        break;

      case CITY:
        address->city = newDataC;
        break;

      case STATE:
        address->state = newDataC;
        break;

      default:
        printf("Error — invalid info type.\n");
    }

  // Change an unsigned int member within address
  } else
  {
    switch(infoType)
    {
      case HNUM:
        address->houseNumber = newDataU;
        break;

      case PC:
        address->postalCode = newDataU;
        break;

      default:
        printf("Error — invalid info type.\n");
    }
  }
}


/*
 * Sets a member of a `Student` given an infoType and new data.
 *
 * Note: Please see line 97 for why this function takes both newDataC and
 * newDataU as parameters.
*/
void setStudentInfo(Student* student, int infoType, char* newDataC,
  unsigned int newDataU)
{
  // Reset all data
  if (infoType == RESET)
  {
    student->firstName = "";
    student->middleName = "";
    student->lastName = "";
    student->studentID = 0;
    student->grade = 0;

    // Reset address info
    setAddressInfo(&student->address, RESET, "", 0);
  }

  // Change a char* member within student
  else if (strlen(newDataC) != 0)
  {
    switch(infoType)
    {
      case FNAME:
        student->firstName = newDataC;
        break;

      case MNAME:
        student->middleName = newDataC;
        break;

      case LNAME:
        student->lastName = newDataC;
        break;

      case ADDRESS:
        printf("Please change each part of the address individually.\n");
        break;

      case SNAME:
        student->address.streetName = newDataC;
        break;

      case STYPE:
        student->address.streetType = newDataC;
        break;

      case CITY:
        student->address.city = newDataC;
        break;

      case STATE:
        student->address.state = newDataC;
        break;

      default:
        printf("ERROR: Invalid info type.\n");
    }

  // Change an unsigned int member within student
  } else
  {
    switch(infoType)
    {
      case ID:
        student->studentID = newDataU;
        break;

      case GRADE:
        student->grade = newDataU;
        break;

      case HNUM:
        student->address.houseNumber = newDataU;
        break;

      case PC:
        student->address.postalCode = newDataU;
        break;

      default:
        printf("ERROR: Invalid info type.\n");
    }
  }
}


/*
 * Adds a `Student` to an array of students given the array and a `Student`.
 * Chooses the first unfilled position in the array to place the `Student`.
*/
void addStudent(Student studentSet[SIZE], Student student)
{
  for (size_t i = 0; i < SIZE; i++)
  {
    // Searches for an empty position by checking an arbitrarily chosen member
    // and checking if it is NULL or "", as a filled position will have a
    // `Student` whose members are neither. 
    if (studentSet[i].firstName == NULL ||
        strcmp(studentSet[i].firstName, "") == 0)
    {
      studentSet[i] = student;
      return;
    }
  }

  printf("Error — no room available for this student\n");
}


/*
 * Deletes a `Student` from an array of students given the array and a
 * student. Delete in this context means resetting their data members to ""
 * and 0 for char* members and unsigned int members, respectively.
*/
void deleteStudent(Student studentSet[SIZE], Student student)
{
  for (size_t i = 0; i < SIZE; i++)
  {
    // Finds the correct `Student` by comparing their IDs. Note that
    // getStudentInfo() returns a string, so strcmp is needed to compare.
    if (strcmp(getStudentInfo(studentSet[i], ID),
        getStudentInfo(student, ID)) == 0)
    {
      // Reset the data
      setStudentInfo(&studentSet[i], RESET, "", 0);
      return;
    }
  }
}


/*
 * Prints out each member of a `Student` using getStudentInfo().
*/
void testStudentData(Student student)
{
  printf("This student's full name is %s\n", getStudentInfo(student, NAME));
  printf("This student's first name is %s\n", getStudentInfo(student, FNAME));
  printf("This student's middle name is %s\n", getStudentInfo(student, MNAME));
  printf("This student's last name is %s\n", getStudentInfo(student, LNAME));
  printf("This student's ID is %s\n", getStudentInfo(student, ID));
  printf("This student's grade is %s\n", getStudentInfo(student, GRADE));
  printf("This student's address is: %s\n", getStudentInfo(student, ADDRESS));
}


/*
 * Prints out each member of an `Address` using getStudentInfo().
*/
void testAddressData(Address address)
{
  printf("This address's house number is %s\n", getAddressInfo(address, HNUM));
  printf("This address's street name is %s\n", getAddressInfo(address, SNAME));
  printf("This address's street type is %s\n", getAddressInfo(address, STYPE));
  printf("This address's city is %s\n", getAddressInfo(address, CITY));
  printf("This address's state is %s\n", getAddressInfo(address, STATE));
  printf("This address's postal code is %s\n", getAddressInfo(address, PC));
}
