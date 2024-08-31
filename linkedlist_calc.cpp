//jacqueline silver 
// Adapted from a class assignment in COMP 322 at McGill
#include <iostream> 
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

struct UserInfo { int age;
     double weight;
     double waist;
     double neck;
     double hip;
     double height;
     double carbs;
     double protein;
     double fat;
     double bfp;
     double cal;
     std::string name;
     std::string gender;
     std::string lifestyle;
     UserInfo* next;
};


class UserInfoManager {
public:
UserInfoManager(){
    mylist = nullptr; //initialize the head of list to null
}; // constructor. initializes linked list 

~UserInfoManager(){ // destructor. delete allocated memory 
    UserInfo* current = mylist; //start at beginning of list
    while (current != nullptr){ //for all the values in mylist
        UserInfo* nextcur = current -> next; //get temp holder for next value
        delete current; //deallocate the mem space
        current = nextcur; //change current variable to the next
    }
};

void addUserInfo(){
    UserInfo* user = new UserInfo; // initialize user to add to
    user -> next = nullptr; //initialize its next as null
    
     user -> weight = 0; //initialize everything as 0 / null / empty string before getting the inputs
     user ->  waist = 0;
     user ->  neck = 0;
     user ->  hip = 0;
     user ->  height = 0;
     user ->  carbs = 0;
     user ->  protein = 0;
     user ->  fat = 0;
     user ->  bfp = 0;
     user ->  cal = 0;
     user ->  name = " ";
     user ->  gender = " ";
     user ->  lifestyle = " ";
     user ->  next = nullptr;

    cout << "Name: Please enter your name."<< endl;
    //ask user for input
    cin >> user -> name; //get user input and add to name attribute
    cout << "Gender: Please specify your gender as either male or female."<< endl;
    //ask user for input
    cin >> user -> gender; //get user input
    if ((user -> gender != "female") && (user -> gender != "Female") && (user -> gender != "male") && (user -> gender != "Male")){
        exit(0); // if other gender inputted than male or female, exit the program
    }
    if ((user -> gender == "Female") || (user -> gender == "female")){
        cout << "Hip Measurement: Enter your hip measurement in centimeters."<< endl; 
        cin >> user -> hip;
    }
    else{
        user -> hip = 1;
    }
    cout << "Age: Enter your age."<< endl; //^same as above
    cin >> user -> age;
    if ((user -> age < 20) || ( user -> age > 79)){
        exit(0); // if no data for inputted age, exit the program
    }
    cout << "Weight: Enter your body weight in kilograms."<< endl;
    cin >> user -> weight;
    if (user -> weight < 1){
        exit(0); //if 0 or negative number (invalid) exit the program
    }
    cout << "Waist: Input your waist measurement using centimeters."<< endl;
    cin >> user -> waist;
    if (user -> waist < 1){
        exit(0); 
    }
    cout << "Neck: Provide your neck measurement in centimeters."<< endl;
    cin >> user -> neck;
    if (user -> neck < 1){
        exit(0); 
    }
    cout << "Height: Input height measurement in centimeters."<< endl;
    cin >> user -> height;
    if (user -> height < 1){
        exit(0); 
    }
    cout << "Lifestyle: Provide information about your current lifestyle: sedentary, moderate (moderately active) or active."<< endl;
    cin >> user -> lifestyle;
    if ((user -> lifestyle != "sedentary") && (user -> lifestyle != "Sedentary") && (user -> lifestyle != "moderate") && (user -> lifestyle != "Moderate") && (user -> lifestyle != "Active") && (user -> lifestyle != "active")){
        exit(0); // if invalid lifestyle, exit program
    }
    if (mylist == nullptr){
        mylist = user; // if this is the first aspect in the list
    }else{
        UserInfo* current = mylist; //start at the head of the list
        while (current -> next != nullptr){
            current = current -> next; //find current last user in the list
            }
            current -> next = user; //set its next to added user
    }
}; // adds info to list adapted from assignment 1

void deleteUser(string username){
    UserInfo* current = mylist; //start at beginning of list
    UserInfo* prev = nullptr; //itialize value for prev to be used
    while (current != nullptr){ //for all the values in mylist
        UserInfo* nextcur = current -> next; //get temp holder for next value
        UserInfo* temp = current; //to use later in setting things
        if ((current -> name) == username){ //if given username 
            if (prev == nullptr){
                mylist = nextcur; //if this was the first element, make next the head
            }else{
                prev -> next = nextcur; //if prev is value not nullptr then set its next field to current
            }
        delete current; //delete
        }
        prev = temp; //set next prev to temp (current)
        current = nextcur; //change current variable to the next
    }
    };
 // removes a user

void readFromFile(string filename){ 

    UserInfo* current = mylist;
    while (current != nullptr){ //delete the entire list (deallocate mem)
        UserInfo* temp = current -> next;
        delete current;
        current = temp;
    }
    mylist = nullptr;
    ifstream csvfile(filename); //open file
    if (!csvfile.is_open()){
        exit(0); // if cant open file, exit
    }
    string line; //intialize string for lines
    UserInfo* prev = nullptr; //initialize var for previous to be used in creating the list

    while (getline(csvfile, line)){
        stringstream ss(line); 
        string element; //intialize variable to get each element from each row
        UserInfo* user = new UserInfo; //intiialize current user 
        getline(ss, user -> name, ','); //get the name element and assign it to current user
        getline(ss, user -> gender, ',');
        getline(ss, element, ','); //get element
        user -> age = stod(element); //set age as this element converted to double
        getline(ss, element, ','); //get element
        user -> weight = stod(element); //weight
        getline(ss, element, ','); //get element
        user -> waist = stod(element); //waist
        getline(ss, element, ','); //get element
        user -> neck = stod(element); //neck
        if (user -> gender == "female" || user -> gender == "Female"){
            getline(ss, element, ','); //get element
            user -> hip = stod(element); //hip
        } 
        getline(ss, element, ','); //get element
        user -> height = stod(element); //height
        getline(ss, user -> lifestyle, ',');
        if (mylist == nullptr){ //if this is first element then make head of list
            mylist = user;
        }
        if (prev != nullptr){ //if this isnt first element, then set prev element's next to this
        prev -> next = user;
        }
        prev = user;
        
    }
    csvfile.close();

}; // read and populate list 


void writeToFile(string filename){
    ofstream csvfile(filename); //open file if exists or overwrite
    if (!csvfile.is_open()){
        exit(0); //check if open
    }
    UserInfo* current = mylist; //itialize 
    while (current != nullptr){ //for each userinfo in the list
    if ((current -> gender == "male") || (current -> gender == "Male")){
        csvfile << (current -> name) << ", " << (current -> gender) << ", " <<  (current -> age) << ", " << (current -> weight) << ", " << (current -> waist) << ", " << (current -> neck) << "," << (current -> height) << ", " << (current -> lifestyle) << "\n";
    } else{ //if male do ,, for female do hip
        csvfile << (current -> name) << ", " << (current -> gender) << ", " <<  (current -> age) << ", " << (current -> weight) << ", " << (current -> waist) << ", " << (current -> neck) << "," << (current -> hip) << ", " << (current -> height) << ", " << (current -> lifestyle) << "\n";
    }
    current = current -> next;
    }
    csvfile.close(); 
};

double getbfpreturned(string username){
    UserInfo* current = mylist; //start at pointer
    UserInfo* user = nullptr; //initialize user to get bfp

    while (current != nullptr){
        if ((current -> name) == username){
            user = current; //find correct user
        }
        current = current -> next;
    }
    double BF_percentage; //initialize bfp
    if ((user -> gender == "Female") || (user -> gender == "female")){ //calculate bfp for females
        BF_percentage = (495 / ( 1.29579 - 0.35004 * log10(user -> waist + user -> hip - user -> neck) + 0.22100 * log10(user -> height)) - 450);
    };
        
    if ((user -> gender == "Male") || (user -> gender == "male")){ //same as above but for the males
        BF_percentage = (495 / ( 1.0324 - 0.19077 * log10(user -> waist - user -> neck) + 0.15456 * log10(user -> height)) - 450);
        };
    return BF_percentage;
};

void getbfp(string username){
    UserInfo* current = mylist; //start at pointer
    UserInfo* user = nullptr; //initialize user to get bfp
    while (current != nullptr){
        if ((current -> name) == username){
            user = current; //find correct user
        }
        current = current -> next;
    }
    double BF_percentage; //initialize bfp
    if ((user -> gender == "Female") || (user -> gender == "female")){ //calculate bfp for females
        BF_percentage = (495 / ( 1.29579 - 0.35004 * log10(user -> waist + user -> hip - user -> neck) + 0.22100 * log10(user -> height)) - 450);
    };
        
    if ((user -> gender == "Male") || (user -> gender == "male")){ //same as above but for the males
        BF_percentage = (495 / ( 1.0324 - 0.19077 * log10(user -> waist - user -> neck) + 0.15456 * log10(user -> height)) - 450);
        };
    user -> bfp = BF_percentage;
    //cout << "bfp: " << BF_percentage << " %." << endl;
};
double getcalsreturned(string username){
    UserInfo* current = mylist; //start at pointer
    UserInfo* user = nullptr; //initialize user to get bfp
    while (current != nullptr){
        if ((current -> name) == username){
            user = current; //find correct user
        }
        current = current -> next;
    }
    double cals; //intialize calorie amount 
    if ((user -> gender == "male") || (user -> gender == "Male")){
        if ((user -> age >= 19) && (user -> age <= 30)){
            if ((user -> lifestyle == "sedentary") || (user -> lifestyle == "Sedentary")){
                cals = 2400;
            }
            if ((user -> lifestyle == "moderate") || (user -> lifestyle == "Moderate")){
                cals =  2600;
            }
            if ((user -> lifestyle == "active") || (user -> lifestyle == "Active")){
                cals =  3000;
            }
        }
        if ((user -> age >= 31) && (user -> age <= 50)){
            if ((user -> lifestyle == "sedentary") || (user -> lifestyle == "Sedentary")){
                cals =  2200;
            }
            if ((user -> lifestyle == "moderate") || (user -> lifestyle == "Moderate")){
                cals =  2400;
            }
            if ((user -> lifestyle == "active") || (user -> lifestyle == "Active")){
                cals =  2800;
            }
        }
        if (user -> age >= 51){
            if ((user -> lifestyle == "sedentary") || (user -> lifestyle == "Sedentary")){
                cals =  2000;
            }
            if ((user -> lifestyle == "moderate") || (user -> lifestyle == "Moderate")){
                cals =  2200;
            }
            if ((user -> lifestyle == "active") || (user -> lifestyle == "Active")){
                cals =  2400;
            }
        }

    }
    if ((user -> gender == "female") || (user -> gender == "Female")){
        if ((user -> age >= 19) && (user -> age <= 30)){
            if ((user -> lifestyle == "sedentary") || (user -> lifestyle == "Sedentary")){
                cals =  2000;
            }
            if ((user -> lifestyle == "moderate") || (user -> lifestyle == "Moderate")){
                cals =  2200;
            }
            if ((user -> lifestyle == "active") || (user -> lifestyle == "Active")){
                cals =  2400;
            }
        }
        if ((user -> age >= 31) && (user -> age <= 50)){
            if ((user -> lifestyle == "sedentary") || (user -> lifestyle == "Sedentary")){
                cals =  1800;
            }
            if ((user -> lifestyle == "moderate") || (user -> lifestyle == "Moderate")){
                cals = 2000;
            }
            if ((user -> lifestyle == "active") || (user -> lifestyle == "Active")){
                cals = 2200;
            }
        }
        if (user -> age >= 51){
            if ((user -> lifestyle == "sedentary") || (user -> lifestyle == "Sedentary")){
                cals = 1600;
            }
            if ((user -> lifestyle == "moderate") || (user -> lifestyle == "Moderate")){
                cals = 1800;
            }
            if ((user -> lifestyle == "active") || (user -> lifestyle == "Active")){
                cals = 2000;
            }
        }
    }
    return cals;
};
void getcals(string username){
    UserInfo* current = mylist; //start at pointer
    UserInfo* user = nullptr; //initialize user to get bfp
    while (current != nullptr){
        if ((current -> name) == username){
            user = current; //find correct user
        }
        current = current -> next;
    }
    double cals; //intialize calorie amount 
    if ((user -> gender == "male") || (user -> gender == "Male")){
        if ((user -> age >= 19) && (user -> age <= 30)){
            if ((user -> lifestyle == "sedentary") || (user -> lifestyle == "Sedentary")){
                cals = 2400;
            }
            if ((user -> lifestyle == "moderate") || (user -> lifestyle == "Moderate")){
                cals =  2600;
            }
            if ((user -> lifestyle == "active") || (user -> lifestyle == "Active")){
                cals =  3000;
            }
        }
        if ((user -> age >= 31) && (user -> age <= 50)){
            if ((user -> lifestyle == "sedentary") || (user -> lifestyle == "Sedentary")){
                cals =  2200;
            }
            if ((user -> lifestyle == "moderate") || (user -> lifestyle == "Moderate")){
                cals =  2400;
            }
            if ((user -> lifestyle == "active") || (user -> lifestyle == "Active")){
                cals =  2800;
            }
        }
        if (user -> age >= 51){
            if ((user -> lifestyle == "sedentary") || (user -> lifestyle == "Sedentary")){
                cals =  2000;
            }
            if ((user -> lifestyle == "moderate") || (user -> lifestyle == "Moderate")){
                cals =  2200;
            }
            if ((user -> lifestyle == "active") || (user -> lifestyle == "Active")){
                cals =  2400;
            }
        }

    }
    if ((user -> gender == "female") || (user -> gender == "Female")){
        if ((user -> age >= 19) && (user -> age <= 30)){
            if ((user -> lifestyle == "sedentary") || (user -> lifestyle == "Sedentary")){
                cals =  2000;
            }
            if ((user -> lifestyle == "moderate") || (user -> lifestyle == "Moderate")){
                cals =  2200;
            }
            if ((user -> lifestyle == "active") || (user -> lifestyle == "Active")){
                cals =  2400;
            }
        }
        if ((user -> age >= 31) && (user -> age <= 50)){
            if ((user -> lifestyle == "sedentary") || (user -> lifestyle == "Sedentary")){
                cals =  1800;
            }
            if ((user -> lifestyle == "moderate") || (user -> lifestyle == "Moderate")){
                cals = 2000;
            }
            if ((user -> lifestyle == "active") || (user -> lifestyle == "Active")){
                cals = 2200;
            }
        }
        if (user -> age >= 51){
            if ((user -> lifestyle == "sedentary") || (user -> lifestyle == "Sedentary")){
                cals = 1600;
            }
            if ((user -> lifestyle == "moderate") || (user -> lifestyle == "Moderate")){
                cals = 1800;
            }
            if ((user -> lifestyle == "active") || (user -> lifestyle == "Active")){
                cals = 2000;
            }
        }
    }
    user -> cal = cals;
    //cout << "calories: " << cals << "." << endl;
};
void mealprep(string username){
    //copy and paste get cals function to get cals for this 
    UserInfo* current = mylist; //start at pointer
    UserInfo* user = nullptr; //initialize user to get bfp
    while (current != nullptr){
        if ((current -> name) == username){
            user = current; //find correct user
        }
        current = current -> next;
    }
    double cals = getcalsreturned(username);
    double carbcal = (cals * (.5));
    double proteincal = (cals * (.3));
    double fatcal = (cals * (.2));

    user -> carbs = (carbcal / 4);
    user -> protein = (proteincal / 4);
    user -> fat = (fatcal / 9);
    //cout << "carbs: " << user -> carbs << " g." << endl;
    //cout << "protein: " << user -> protein << " g." << endl;
    //cout << "fat: " << user -> fat << " g." << endl;

};


void display(string username){
    if (username == "all"){ // if name is all, do function for each user 
        UserInfo* current1 = mylist; //start at pointer
        while (current1 != nullptr){ //print info
            cout << "Your name is " << current1 -> name << "." << endl;
            cout << "Your gender is " << current1 -> gender << "." << endl;
            cout << "Your age is " << current1 -> age << " years old." << endl;
            cout << "Your weight is " << current1 -> weight << " kg." << endl;
            cout << "Your waist is " << current1 -> waist << " cm." << endl;
            cout << "Your neck is " << current1 -> neck << " cm." << endl;
            cout << "Your height is " << current1 -> height << " cm." << endl;
            cout << "Your lifestle is " << current1 -> lifestyle << "." << endl;
            if ((current1 -> gender == "female") || (current1 -> gender == "Female")){
                cout << "Your hips are " << current1 -> hip << " cm." << endl;
            }
            double bfp = getbfpreturned(current1 -> name);
            cout << "Your bodyfat percentage is " << bfp << " %." << endl;
            double cals = getcalsreturned(current1 -> name);
            cout << "Your suggested calorie intake is " << cals << "." << endl;
            mealprep(current1 -> name);
            cout << "Your suggested carb amount is " << current1 -> carbs << " g." << endl;
            cout << "Your suggested protein amount is " << current1 -> protein << " g." << endl;
            cout << "Your suggested fat amount is " << current1 -> fat << " g." << endl;
        current1 = current1 -> next;
    }
    }
    else{
    UserInfo* current = mylist; //start at pointer
    UserInfo* user = nullptr; //initialize user to get bfp
    while (current != nullptr){
        if ((current -> name) == username){
            user = current; //find correct user
        }
        current = current -> next;
    } //print info
    cout << "Your name is " << user -> name << "." << endl;
    cout << "Your gender is " << user -> gender << "." << endl;
    cout << "Your age is " << user -> age << " years old." << endl;
    cout << "Your weight is " << user -> weight << " kg." << endl;
    cout << "Your waist is " << user -> waist << " cm." << endl;
    cout << "Your neck is " << user -> neck << " cm." << endl;
    cout << "Your height is " << user -> height << " cm." << endl;
    cout << "Your lifestle is " << user -> lifestyle << "." << endl;
    if ((user -> gender == "female") || (user -> gender == "Female")){
        cout << "Your hips are " << user -> hip << " cm." << endl;
    }
    double bfp = getbfpreturned(username);
    cout << "Your bodyfat percentage is " << bfp << " %." << endl;
    double cals = getcalsreturned(username);
    cout << "Your suggested calorie intake is " << cals << "." << endl;
    mealprep(username);
    cout << "Your suggested carb amount is " << user -> carbs << " g." << endl;
    cout << "Your suggested protein amount is " << user -> protein << " g." << endl;
    cout << "Your suggested fat amount is " << user -> fat << " g." << endl;
    }
};
UserInfo* getmylist(){
    return mylist; //getter to access mylist outside of userinfo class
};

private:
UserInfo* mylist; // pointer to first element in linked list

};





class HealthAssistant {
public:
void getUserDetail(){
    manager -> addUserInfo();
}; // wrapper method that simply calls addUserInfo in class UserInfoManager

void getBfp(string username){
    manager -> getbfp(username);
};
void getDailyCalories(string username){
    manager -> getcals(username);
};
void getMealPrep(string username){
    manager -> mealprep(username);
};

void display(string username){
    manager -> display(username);
}; //wrapper method

void serialize(string filename){
    manager -> writeToFile(filename);
}; //wrapper method

void readFromFile(string filename){ //from my assignment 1
    manager -> readFromFile(filename);
}; //wrapper method

void deleteUser(string username){
    manager -> deleteUser(username);
}; // wrapper method

void massLoadAndCompute(string filename){
    manager -> readFromFile(filename); //read from file (list populates in this function)
    UserInfo* current = manager -> getmylist(); //make and use getter to access the head of the list
    while (current != nullptr){ //get all the caluclations (list updates within these functions)
        manager -> getbfp(current -> name);
        manager -> getcals(current -> name);    
        manager -> mealprep(current -> name);  
        current = current -> next;
    }
    manager -> writeToFile(filename); //save data into file
};

private:
static UserInfoManager* manager; //make into a static pointer so it remains the same outside of just one instance of ha
};
UserInfoManager* HealthAssistant::manager = new UserInfoManager; //allocate memory outside of function for static manager instance



int main() {
HealthAssistant ha;
// get user details from console input for 1st user ha.getUserDetail();
// get user details from console input for 2nd user ha.getUserDetail();
// display information for john (assuming that john is the name of the first user)
ha.getUserDetail();
ha.getUserDetail();
ha.display("john");
// display information for all the users
ha.display("all");
// get bfp for the 1st user
ha.getBfp("john");
ha.getDailyCalories("john");
ha.getMealPrep("john");
ha.serialize("user_data.csv");
// write all the data for all the users to file ha.serialize("user_data.csv");
 // Now let's get the data from file using a new instance of HealthAssistant
 HealthAssistant ha2;
 ha2.readFromFile("user_data.csv");
 ha2.display("all");
 ha2.deleteUser("jack"); // assuming 2nd user is jack
 ha2.display("all"); // should only display for john at this point
 // now use the first object to display all
 ha.display("all"); // both john and jack should be present
 ha.massLoadAndCompute("user_data.csv");
 }
 