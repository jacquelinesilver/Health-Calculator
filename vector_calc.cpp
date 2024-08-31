//jacqueline silver 
// Adapted from a class assignment in COMP 322 at McGill
#include <iostream> 
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

//FIX THE CALCULATION PIECES THEY R NOT WORKING !!!
class UserInfoManager {
public:
UserInfoManager(){
    std::vector<UserInfo> users; //initialize vector
}; // constructor.

~UserInfoManager(){ // destructor. delete allocated memory 
users.clear(); //clear the vector 

};

void addUserInfo(){
    UserInfo user; // initialize user to add to vector
     user.weight = 0; //initialize everything as 0 / null / empty string before getting the inputs
     user.waist = 0;
     user.neck = 0;
     user.hip = 0;
     user.height = 0;
     user.carbs = 0;
     user.protein = 0;
     user.fat = 0;
     user.bfp = 0;
     user.bmi = 0;
     user.cal = 0;
     user.name = " ";
     user.gender = " ";
     user.lifestyle = " ";

    cout << "Name: Please enter your name."<< endl;
    //ask user for input
    cin >> user.name; //get user input and add to name attribute
    cout << "Gender: Please specify your gender as either male or female."<< endl;
    //ask user for input
    cin >> user.gender; //get user input
    if ((user.gender != "female") && (user.gender != "Female") && (user.gender != "male") && (user.gender != "Male")){
        string ex = "Gender is invalid."; 
        throw ex; // if other gender inputted than male or female, throw exception
    }
    if ((user.gender == "Female") || (user.gender == "female")){
        cout << "Hip Measurement: Enter your hip measurement in centimeters."<< endl; 
        cin >> user.hip;
        if (user.hip < 1){
        string ex = "Hip measurement is invalid."; //throw for invalid hip measurement
        throw ex;
        }
    }
    else{
        user.hip = 0;
    }
    cout << "Age: Enter your age."<< endl; //^same as above
    cin >> user.age;
    if ((user.age < 20) || ( user.age > 79)){
        string ex = "Age is invalid."; 
        throw ex;; // if no data for inputted age, throw
    }
    cout << "Weight: Enter your body weight in kilograms."<< endl;
    cin >> user.weight;
    if (user.weight < 1){
        string ex = "Weight is invalid."; 
        throw ex; //if 0 or negative number (invalid) exit the program
    }
    cout << "Waist: Input your waist measurement using centimeters."<< endl;
    cin >> user.waist;
    if (user.waist < 1){
        string ex = "Waist measurement is invalid."; 
        throw ex; 
    }
    cout << "Neck: Provide your neck measurement in centimeters."<< endl;
    cin >> user.neck;
    if (user.neck < 1){
        string ex = "Neck measurement is invalid."; 
        throw ex;
    }
    cout << "Height: Input height measurement in centimeters."<< endl;
    cin >> user.height;
    if (user.height < 1){
        string ex = "Height is invalid."; 
        throw ex;; 
    }
    cout << "Lifestyle: Provide information about your current lifestyle: sedentary, moderate (moderately active) or active."<< endl;
    cin >> user.lifestyle;
    if ((user.lifestyle != "sedentary") && (user.lifestyle != "Sedentary") && (user.lifestyle != "moderate") && (user.lifestyle != "Moderate") && (user.lifestyle != "Active") && (user.lifestyle != "active")){
        string ex = "Lifestyle is invalid."; 
        throw ex; // if invalid lifestyle, exit program
    }
    
    users.push_back(user); //add to vector
    
}; 

void deleteUser(string username){
if (users.size() != 0){
    for (int i = 0; i < users.size(); i++){ //iterate through list til the name is found
        if (users[i].name == username){
            users.erase(users.begin() + i); //once name is found remove that user from vector
        }
    }
}

};
void readFromFile(string filename){ 

    users.clear();
    ifstream csvfile(filename); //open file
    if (!csvfile.is_open()){
        string ex = "File cannot be opened.";
        throw ex; // if cant open file, throw
    }
    string line; //intialize string for lines

    while (getline(csvfile, line)){
        stringstream ss(line); 
        string element; //intialize variable to get each element from each row
        UserInfo user; //intiialize current user 
        getline(ss, user.name, ','); //get the name element and assign it to current user
        getline(ss, user.gender, ',');
        getline(ss, element, ','); //get element
        user.age = stod(element); //set age as this element converted to double
        getline(ss, element, ','); //get element
        user.weight = stod(element); //weight
        getline(ss, element, ','); //get element
        user.waist = stod(element); //waist
        getline(ss, element, ','); //get element
        user.neck = stod(element); //neck
        if (user.gender == "female" || user.gender == "Female"){
            getline(ss, element, ','); //get element
            user.hip = stod(element); //hip
        }else{
            getline(ss, element, ',');
        }
        getline(ss, element, ','); //get element
        user.height = stod(element); //height
        getline(ss, user.lifestyle, ','); //lifestyle
        /*
        getline(ss, element, ','); //get element
        user.bfp = stod(element); //bfp
        getline(ss, element, ','); //get element
        user.cal = stod(element); //calories
        getline(ss, element, ','); //get element
        user.carbs = stod(element); //carbs
        getline(ss, element, ','); //get element
        user.protein = stod(element); //protein
        getline(ss, element); //get element
        user.fat = stod(element); //fat
        */
        users.push_back(user); //add user to vector
        getbfp(user.name);
        getcals(user.name);
        mealprep(user.name);
    }
    csvfile.close();

}; // read and populate vector

void writeToFile(string filename){
    ofstream csvfile(filename); //open file if exists or overwrite
    if (!csvfile.is_open()){
        string ex = "File cannot be opened.";
        throw ex; // if cant open file, throw
    }
    if (users.size() != 0){
        for (int i = 0; i < users.size(); i++){
            UserInfo current = users[i];
            if ((current.gender == "male") || (current.gender  == "Male")){
                csvfile << (current.name) << "," << (current.gender) << ", " <<  (current.age) << ", " << (current.weight) << ", " << (current.waist) << ", " << (current.neck) << ", " << " , " << (current.height) << "," << (current.lifestyle) << ", " << (current.bfp) << ", " << (current.cal)<< ", " << (current.carbs)<< ", " << (current.protein)<< ", " << (current.fat)<< "\n";
            } 
            else{ //if male do ,, for female do hip
                csvfile << (current.name) << "," << (current.gender) << ", " <<  (current.age) << ", " << (current.weight) << ", " << (current.waist) << ", " << (current.neck) << "," << (current.hip) << ", " << (current.height) << "," << (current.lifestyle) << ", " << (current.bfp) << ", " << (current.cal)<< ", " << (current.carbs)<< ", " << (current.protein)<< ", " << (current.fat)<< "\n";
            }
        }
    }
   csvfile.close(); 
};
void getbfp(string username){
    int index;
    UserInfo* user = nullptr; //initialize user to be used for func
    if (users.size() != 0){
    for (int i = 0; i < users.size(); i++){ //iterate through list til the name is found
        if (users[i].name == username){
            user = &users[i];
            index = i;
        }
    }
}

    double BF_percentage; //initialize bfp
    if ((user -> gender == "Female") || (user -> gender == "female")){ //calculate bfp for females
        BF_percentage = (495 / ( 1.29579 - 0.35004 * log10(user -> waist + user -> hip - user  -> neck) + 0.22100 * log10(user -> height)) - 450);
    };
        
    if ((user -> gender == "Male") || (user -> gender == "male")){ //same as above but for the males
        BF_percentage = (495 / ( 1.0324 - 0.19077 * log10(user -> waist - user -> neck) + 0.15456 * log10(user -> height)) - 450);
        };
    users[index].bfp = BF_percentage;
    user -> bfp = BF_percentage;
    //cout<<BF_percentage;
    //cout<<user -> bfp;
    //cout<<users[index].bfp;
};

void getbmi(string username){
    int index;
    UserInfo* user = nullptr; //initialize user to be used for func
    if (users.size() != 0){
    for (int i = 0; i < users.size(); i++){ //iterate through list til the name is found
        if (users[i].name == username){
            user = &users[i];
            index = i;
        }
    }
}
    double BF_percentage; //initialize bfp
    double heightinmeters = user -> height / 100; //implement new formula 
    BF_percentage = (user -> weight) / (heightinmeters * heightinmeters); //weight over meters squared
    users[index].bfp = BF_percentage; //set new attributes
    user -> bfp = BF_percentage;
    user -> bmi = BF_percentage;
};

void getcals(string username){
    UserInfo user; //initialize user to be used for func
    int index;
    if (users.size() != 0){
        for (int i = 0; i < users.size(); i++){ //iterate through list til the name is found
            if (users[i].name == username){
                user = users[i];
                index = i;
            }
        }
    }
    //cout << user.name;
    double cals; //intialize calorie amount 
    if ((user.gender == "male") || (user.gender == "Male")){
        if ((user.age >= 19) && (user.age <= 30)){
            if ((user.lifestyle == "sedentary") || (user.lifestyle == "Sedentary")){
                cals = 2400;
            }
            if ((user.lifestyle == "moderate") || (user.lifestyle == "Moderate")){
                cals =  2600;
            }
            if ((user.lifestyle == "active") || (user.lifestyle == "Active")){
                cals =  3000;
            }
        }
        if ((user.age >= 31) && (user.age <= 50)){
            if ((user.lifestyle == "sedentary") || (user.lifestyle == "Sedentary")){
                cals =  2200;
            }
            if ((user.lifestyle == "moderate") || (user.lifestyle == "Moderate")){
                cals =  2400;
            }
            if ((user.lifestyle == "active") || (user.lifestyle == "Active")){
                cals =  2800;
            }
        }
        if (user.age >= 51){
            if ((user.lifestyle == "sedentary") || (user.lifestyle == "Sedentary")){
                cals =  2000;
            }
            if ((user.lifestyle == "moderate") || (user.lifestyle == "Moderate")){
                cals =  2200;
            }
            if ((user.lifestyle == "active") || (user.lifestyle == "Active")){
                cals =  2400;
            }
        }

    }
    if ((user.gender == "female") || (user.gender == "Female")){
        if ((user.age >= 19) && (user.age <= 30)){
            if ((user.lifestyle == "sedentary") || (user.lifestyle == "Sedentary")){
                cals =  2000;
            }
            if ((user.lifestyle == "moderate") || (user.lifestyle == "Moderate")){
                cals =  2200;
            }
            if ((user.lifestyle == "active") || (user.lifestyle == "Active")){
                cals =  2400;
            }
        }
        if ((user.age >= 31) && (user.age <= 50)){
            if ((user.lifestyle == "sedentary") || (user.lifestyle == "Sedentary")){
                cals =  1800;
            }
            if ((user.lifestyle == "moderate") || (user.lifestyle == "Moderate")){
                cals = 2000;
            }
            if ((user.lifestyle == "active") || (user.lifestyle == "Active")){
                cals = 2200;
            }
        }
        if (user.age >= 51){
            if ((user.lifestyle == "sedentary") || (user.lifestyle == "Sedentary")){
                cals = 1600;
            }
            if ((user.lifestyle == "moderate") || (user.lifestyle == "Moderate")){
                cals = 1800;
            }
            if ((user.lifestyle == "active") || (user.lifestyle == "Active")){
                cals = 2000;
            }
        }
    }
    user.cal = cals;
    users[index].cal = cals;
};
void mealprep(string username){
    UserInfo user; //initialize user to be used for func
    int index;
    if (users.size() != 0){
        for (int i = 0; i < users.size(); i++){ //iterate through list til the name is found
            if (users[i].name == username){
                user = users[i];
                index = i;
            }
        }
    }
    getcals(username);
    double cals = user.cal;
    double carbcal = (cals * (.5));
    double proteincal = (cals * (.3));
    double fatcal = (cals * (.2));

    users[index].carbs = (carbcal / 4);
    users[index].protein = (proteincal / 4);
    users[index].fat = (fatcal / 9);
    user.carbs = (carbcal / 4);
    user.protein = (proteincal / 4);
    user.fat = (fatcal / 9);
    //cout << "carbs: " << user.carbs << " g." << endl;
    //cout << "protein: " << user.protein << " g." << endl;
    //cout << "fat: " << user.fat << " g." << endl;

};
void display(string username){
    if (username == "all"){ // if name is all, do function for each user 
        for (int i = 0; i < users.size(); i++){//print info
            UserInfo* current1 = &users[i]; //make pointer for the user in the vector
            getbfp(current1 -> name);
            getcals(current1 -> name);
            mealprep(current1 -> name);
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
            cout << "Your bodyfat percentage is " << current1 -> bfp << " %." << endl;
            cout << "Your suggested calorie intake is " << current1 -> cal << "." << endl;
            cout << "Your suggested carb amount is " << current1 -> carbs << " g." << endl;
            cout << "Your suggested protein amount is " << current1 -> protein << " g." << endl;
            cout << "Your suggested fat amount is " << current1 -> fat << " g." << endl;
    }
    }
    else{
        //UserInfo user; //initialize user to be used for func
        if (users.size() != 0){
        for (int i = 0; i < users.size(); i++){ //iterate through list til the name is found
            if (users[i].name == username){
                UserInfo* user = &users[i];
                getbfp(username);
                //cout << user.bfp;
                getcals(username);
                //cout << user.bfp;
                mealprep(username);
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
                cout << "Your bodyfat percentage is " << user -> bfp << " %." << endl;
                cout << "Your suggested calorie intake is " << user -> cal << "." << endl;
                cout << "Your suggested carb amount is " << user -> carbs << " g." << endl;
                cout << "Your suggested protein amount is " << user -> protein << " g." << endl;
                cout << "Your suggested fat amount is " << user -> fat << " g." << endl;
                break;
                }
            }
        }
    }
};

std::vector<string> healthynavygirls(){
    std::vector<string> healthies; //intiialize healthy users string
    for (int i = 0; i < users.size(); i++){
        //DO FOR EACH VARIATION AND CREATE VECTORS OF NAMES TO BE USED LATER
        UserInfo* user = &users[i];
        getbfp(user -> name);
        if ((user -> gender) == "female"){
            if (user -> age <= 39 && user -> age >= 20){
                if (user -> bfp < 33 && user -> bfp >= 21){
                    healthies.push_back(user -> name);
                } //find healthy users and add to vector
            }
            if (user -> age <= 59 && user -> age >= 40){
                if (user -> bfp < 34 && user -> bfp >= 23){
                    healthies.push_back(user -> name);
                }
            }
            if (user -> age <= 79 && user -> age >= 60){
                if (user -> bfp < 36 && user -> bfp >= 24){
                    healthies.push_back(user -> name);
                }
            }

        }
    } return healthies; //return

}

std::vector<string> healthynavyboys(){
    std::vector<string> healthies; //intiialize healthy users string
    for (int i = 0; i < users.size(); i++){
       
        UserInfo* user = &users[i];
        getbfp(user -> name);
        if ((user -> gender) == "male"){
            if (user -> age <= 39 && user -> age >= 20){
                if (user -> bfp < 20 && user -> bfp >= 8){
                    healthies.push_back(user -> name);
                }
            } //same as above with male numbers
            if (user -> age <= 59 && user -> age >= 40){
                if (user -> bfp < 22 && user -> bfp >= 11){
                    healthies.push_back(user -> name);
                }
            }
            if (user -> age <= 79 && user -> age >= 60){
                if (user -> bfp < 25 && user -> bfp >= 12){
                    healthies.push_back(user -> name);
                }
            }
        }
    } return healthies;
}

std::vector<string> unfitnavygirls(){
    std::vector<string> unfits; //intialize vec for unfit 
    for (int i = 0; i < users.size(); i++){
        
        UserInfo* user = &users[i];
        getbfp(user -> name);
        if ((user -> gender) == "female"){
            if (user -> age > 39 && user -> age < 20){
                if (user -> bfp < 33 && user -> bfp >= 21){
                    unfits.push_back(user -> name);
                } //find unhealthy users and add to vector
            }
            if (user -> age <= 59 && user -> age >= 40){
                if (user -> bfp > 34 && user -> bfp < 23){
                    unfits.push_back(user -> name);
                }
            }
            if (user -> age <= 79 && user -> age >= 60){
                if (user -> bfp > 36 && user -> bfp < 24){
                    unfits.push_back(user -> name);
                }
            }

        }
    } return unfits; //return
}
std::vector<string> unfitnavyboys(){
    std::vector<string> unfits; //intiialize healthy users string
    for (int i = 0; i < users.size(); i++){
       
        UserInfo* user = &users[i];
        getbfp(user -> name);
        if ((user -> gender) == "male"){
            if (user -> age > 39 && user -> age < 20){
                if (user -> bfp < 20 && user -> bfp >= 8){
                    unfits.push_back(user -> name);
                }
            } //same as above with male numbers
            if (user -> age <= 59 && user -> age >= 40){
                if (user -> bfp > 22 && user -> bfp < 11){
                    unfits.push_back(user -> name);
                }
            }
            if (user -> age <= 79 && user -> age >= 60){
                if (user -> bfp > 25 && user -> bfp < 12){
                    unfits.push_back(user -> name);
                }
            }
        }
    } return unfits;
}

std::vector<string> healthybmigirls(){
    std::vector<string> healthies; //intiialize healthy users string
    for (int i = 0; i < users.size(); i++){
        //DO FOR EACH VARIATION AND CREATE VECTORS OF NAMES TO BE USED LATER
        UserInfo* user = &users[i];
        getbmi(user -> name);
        if ((user -> gender) == "female"){
            if (user -> bmi <= 24.9 && user -> bmi >= 18.5 ){
                healthies.push_back(user -> name);
            }
        }
    }return healthies;
}
std::vector<string> healthybmiboys(){
    std::vector<string> healthies; //intiialize healthy users string
    for (int i = 0; i < users.size(); i++){
        //DO FOR EACH VARIATION AND CREATE VECTORS OF NAMES TO BE USED LATER
        UserInfo* user = &users[i];
        getbmi(user -> name);
        if ((user -> gender) == "male"){
            if (user -> bmi <= 24.9 && user -> bmi >= 18.5 ){
                healthies.push_back(user -> name);
            }
        }
    }return healthies;
}

std::vector<string> unfitbmigirls(){
    std::vector<string> unfits; //intiialize healthy users string
    for (int i = 0; i < users.size(); i++){
        //DO FOR EACH VARIATION AND CREATE VECTORS OF NAMES TO BE USED LATER
        UserInfo* user = &users[i];
        getbmi(user -> name);
        if ((user -> gender) == "female"){
            if (user -> bmi > 24.9 && user -> bmi < 18.5 ){
                unfits.push_back(user -> name);
            }
        }
    } return unfits;
}
std::vector<string> unfitbmiboys(){
    std::vector<string> unfits; //intiialize healthy users string
    for (int i = 0; i < users.size(); i++){
        //DO FOR EACH VARIATION AND CREATE VECTORS OF NAMES TO BE USED LATER
        UserInfo* user = &users[i];
        getbmi(user -> name);
        if ((user -> gender) == "male"){
            if (user -> bmi > 24.9 && user -> bmi < 18.5 ){
                unfits.push_back(user -> name);
            }
        }
    }return unfits;
}
void massloadandcompute(string filename){
    readFromFile(filename); //read from file (list populates in this function)
    for (int i = 0; i < users.size(); i++){
        UserInfo* current = &users[i]; //get all the caluclations (list updates within these functions)
        getbfp(current -> name);
        getcals(current -> name);    
        mealprep(current -> name);  
    }
    writeToFile(filename); //save data into file
};


private:
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
     double bmi;
     double cal;
     std::string name;
     std::string gender;
     std::string lifestyle;
};
std::vector<UserInfo> users;
};


class HealthAssistant {
public:
virtual void getUserDetail(){
    manager.addUserInfo();
}; // wrapper method that simply calls addUserInfo in class UserInfoManager

virtual void getBfp(string username){
    manager.getbfp(username);
};
virtual void getDailyCalories(string username){
    manager.getcals(username);
};
virtual void getMealPrep(string username){
    manager.mealprep(username);
};

virtual void display(string username){
    manager.display(username);
}; //wrapper method

virtual void serialize(string filename){
    manager.writeToFile(filename);
}; //wrapper method

virtual void readFromFile(string filename){ //from my assignment 1
    manager.readFromFile(filename);
}; //wrapper method

virtual void deleteUser(string username){
    manager.deleteUser(username);
}; // wrapper method
virtual UserInfoManager getmanager(){
    return manager;
};
void massLoadAndCompute(string filename){
    manager.massloadandcompute(filename);
};

private:
UserInfoManager manager;
};


class USNavyMethod : public HealthAssistant{};

class BmiMethod : public HealthAssistant{
public:
void getBfp(string username) override {
   UserInfoManager manager = getmanager();
   manager.getbmi(username); //override w wrapper method calling new implementation
};
};

class UserStats : public HealthAssistant{
public:
std::vector<string> GetHealthyUsers(string method, string gender = " "){ //set default as a space (not specified male or female)
    std::vector<string> returns; //initialize vector to be returned
    UserInfoManager manager = getmanager();
    //call all helper functions to get vectors of various groups
    std::vector<string> healthyboysnavy = manager.healthynavyboys();
    std::vector<string> healthygirlssnavy = manager.healthynavygirls();
    std::vector<string> healthyboysbmi = manager.healthybmiboys();
    std::vector<string> healthygirlsbmi = manager.healthybmigirls();
    //iterate thru the lists depending on conditions to get the names of users to return 
    if (gender == "female"){
        if (method == "all"){
            for (int i = 0; i < healthygirlssnavy.size(); i++){
                returns.push_back(healthygirlssnavy[i]);
            }
            for (int j = 0; j < healthygirlsbmi.size(); j++){
                returns.push_back(healthygirlsbmi[j]);
            }
        }
        else if (method == "USArmy")
        {
        for (int i = 0; i < healthygirlssnavy.size(); i++){
            returns.push_back(healthygirlssnavy[i]);
        }
        }
        else if (method == "bmi"){
             for (int i = 0; i < healthygirlsbmi.size(); i++){
            returns.push_back(healthygirlsbmi[i]);
        }
        }
        else {
            string ex = "Invalid method";
            throw ex;
        }
    }
    else if (gender == "male"){
        if (method == "all"){
            for (int i = 0; i < healthyboysnavy.size(); i++){
                returns.push_back(healthyboysnavy[i]);
            }
            for (int j = 0; j < healthyboysbmi.size(); j++){
                returns.push_back(healthyboysbmi[j]);
            }
        }
        else if (method == "USArmy")
        {
        for (int i = 0; i < healthyboysnavy.size(); i++){
            returns.push_back(healthyboysnavy[i]);
        }
            
        }
        else if (method == "bmi"){
            for (int j = 0; j < healthyboysbmi.size(); j++){
                returns.push_back(healthyboysbmi[j]);
            }
        }
        else {
            string ex = "Invalid method";
            throw ex;

        }
    }
    else{
        if (method == "all"){
            for (int i = 0; i < healthygirlssnavy.size(); i++){
                returns.push_back(healthygirlssnavy[i]);
            }
            for (int j = 0; j < healthygirlsbmi.size(); j++){
                returns.push_back(healthygirlsbmi[j]);
            }
            for (int i = 0; i < healthyboysnavy.size(); i++){
                returns.push_back(healthyboysnavy[i]);
            }
            for (int j = 0; j < healthyboysbmi.size(); j++){
                returns.push_back(healthyboysbmi[j]);
            }
        }
        else if (method == "USArmy")
        {
            for (int i = 0; i < healthygirlssnavy.size(); i++){
                returns.push_back(healthygirlssnavy[i]);
            }
            for (int i = 0; i < healthyboysnavy.size(); i++){
                returns.push_back(healthyboysnavy[i]);
            }
            
        }
        else if (method == "bmi"){
            for (int j = 0; j < healthygirlsbmi.size(); j++){
                returns.push_back(healthygirlsbmi[j]);
            }
            for (int j = 0; j < healthyboysbmi.size(); j++){
                returns.push_back(healthyboysbmi[j]);
            }

        }
        else {
            string ex = "Invalid method";
            throw ex;
        }

    }
return returns;
};
std::vector<string> GetUnfitUsers(string method, string gender){
    std::vector<string> returns; //initialize vector to be returned
    UserInfoManager manager = getmanager();
    //call all helper functions to get vectors of various groups
    std::vector<string> unfitboysnavy = manager.unfitnavyboys();
    std::vector<string> unfitgirlsnavy = manager.unfitnavygirls();
    std::vector<string> unfitgirlsbmi = manager.unfitbmigirls();
    std::vector<string> unfitboysbmi = manager.unfitbmiboys();
    //iterate thru the lists depending on conditions to get the names of users to return 
    if (gender == "female"){
        if (method == "all"){
            for (int i = 0; i < unfitgirlsnavy.size(); i++){
                returns.push_back(unfitgirlsnavy[i]);
            }
            for (int j = 0; j < unfitgirlsbmi .size(); j++){
                returns.push_back(unfitgirlsbmi [j]);
            }
        }
        else if (method == "USArmy")
        {
        for (int i = 0; i < unfitgirlsnavy.size(); i++){
            returns.push_back(unfitgirlsnavy[i]);
        }
        }
        else if (method == "bmi"){
             for (int i = 0; i < unfitgirlsbmi .size(); i++){
            returns.push_back(unfitgirlsbmi [i]);
        }
        }
        else {
            string ex = "Invalid method";
            throw ex;
        }
    }
    else if (gender == "male"){
        if (method == "all"){
            for (int i = 0; i < unfitboysnavy.size(); i++){
                returns.push_back(unfitboysnavy[i]);
            }
            for (int j = 0; j < unfitboysbmi.size(); j++){
                returns.push_back(unfitboysbmi[j]);
            }
        }
        else if (method == "USArmy")
        {
        for (int i = 0; i < unfitboysnavy.size(); i++){
            returns.push_back(unfitboysnavy[i]);
        }
            
        }
        else if (method == "bmi"){
            for (int j = 0; j < unfitboysbmi.size(); j++){
                returns.push_back(unfitboysbmi[j]);
            }
        }
        else {
            string ex = "Invalid method";
            throw ex;

        }
    }
    else{
        if (method == "all"){
            for (int i = 0; i < unfitgirlsnavy.size(); i++){
                returns.push_back(unfitgirlsnavy[i]);
            }
            for (int j = 0; j < unfitgirlsbmi .size(); j++){
                returns.push_back(unfitgirlsbmi [j]);
            }
            for (int i = 0; i < unfitboysnavy.size(); i++){
                returns.push_back(unfitboysnavy[i]);
            }
            for (int j = 0; j < unfitboysbmi.size(); j++){
                returns.push_back(unfitboysbmi[j]);
            }
        }
        else if (method == "USArmy")
        {
            for (int i = 0; i < unfitgirlsnavy.size(); i++){
                returns.push_back(unfitgirlsnavy[i]);
            }
            for (int i = 0; i < unfitboysnavy.size(); i++){
                returns.push_back(unfitboysnavy[i]);
            }
            
        }
        else if (method == "bmi"){
            for (int j = 0; j < unfitgirlsbmi.size(); j++){
                returns.push_back(unfitgirlsbmi[j]);
            }
            for (int j = 0; j < unfitboysbmi.size(); j++){
                returns.push_back(unfitboysbmi[j]);
            }

        }
        else {
            string ex = "Invalid method";
            throw ex;
        }

    }
return returns;
};
void GetFullStats(){
    UserInfoManager manager = getmanager();
    //call all the methods to get vectors to take the length of 
    std::vector<string> healthyboysnavy = manager.healthynavyboys();
    std::vector<string> healthygirlssnavy = manager.healthynavygirls();
    std::vector<string> healthyboysbmi = manager.healthybmiboys();
    std::vector<string> healthygirlsbmi = manager.healthybmigirls();
    std::vector<string> unfitboysnavy = manager.unfitnavyboys();
    std::vector<string> unfitgirlsnavy = manager.unfitnavygirls();
    std::vector<string> unfitgirlsbmi = manager.unfitbmigirls();
    std::vector<string> unfitboysbmi = manager.unfitbmiboys();
    int total = (healthyboysnavy.size() + healthygirlssnavy.size() + unfitboysnavy.size() + unfitgirlsnavy .size());
    //get total by adding #s of not overlapping groups
    cout<< "Total number of users: " << (total) << "." << endl;
    //get other various group values
    int boys = (healthyboysnavy.size() + unfitboysnavy.size());
    int percentboys = ((boys / total) * 100); //get percent value
    cout<< "Percent male users: " << (percentboys) << "%" << endl;
    int girls = (healthygirlssnavy.size() + unfitgirlsnavy.size());
    int percentgirls = ((girls / total) * 100); //get percent value
    cout<< "Percent female users: " << (percentgirls) << "%" << endl;
    int healthybmi = (healthygirlsbmi.size() + healthyboysbmi.size());
    cout<< "Percent BMI healthy users: " << (healthybmi) << "%" << endl;
    int healthynavy = (healthygirlssnavy.size() + healthyboysnavy.size());
    cout<< "Percent US Navy healthy users: " << (healthynavy) << "%" << endl;
    int femalenavy = ((healthygirlssnavy.size() / total ) *100);
    cout<< "Percent US Navy Female healthy users: " << (femalenavy) << "%" << endl;
    int malenavy = ((healthyboysnavy.size() / total ) *100);
    cout<< "Percent US Navy Male healthy users: " << (malenavy) << "%" << endl;
    int femalebmi = ((healthygirlsbmi.size() / total ) *100);
    cout<< "Percent BMI Female healthy users: " << (femalebmi) << "%" << endl;
    int malebmi = ((healthyboysbmi.size() / total ) *100);
    cout<< "Percent BMI Male healthy users: " << (malebmi) << "%" << endl;
};

};

int main() {
HealthAssistant* ha = new USNavyMethod(); std::string userInput;
 // Loop until the user inputs "exit"
 while (true) {
     // Get user details
     ha->getUserDetail();
     // Ask for user input
     std::cout << "Enter 'exit' to quit, or press Enter to continue: ";
     std::getline(std::cin, userInput);
     // Check if the user wants to exit
     if (userInput == "exit") {
         break; // Exit the loop
} }
 ha->display("all");
 ha->getBfp("john");
 ha->getDailyCalories("john");
 ha->getMealPrep("john");
 ha->serialize("us_user_data->csv");
 delete ha;
  ha = new BmiMethod();
// Loop until the user inputs "exit"
while (true) {
    // Get user details
    ha->getUserDetail();
    // Ask for user input
    std::cout << "Enter 'exit' to quit, or press Enter to continue: ";
    std::cin.ignore();
    std::getline(std::cin, userInput);
    // Check if the user wants to exit
    if (userInput == "exit") {
        break; // Exit the loop
} }
ha->display("all");
ha->getBfp("john");
ha->getDailyCalories("john");
ha->getMealPrep("john");
ha->deleteUser("jack"); // assuming we have a user jack
ha->display("all"); // should display all except for jack
ha->serialize("bmi_user_data->csv");
delete ha;
ha = new USNavyMethod();
ha->massLoadAndCompute("us_user_data.csv");
ha->display("all");
delete ha;
ha = new BmiMethod();
ha->massLoadAndCompute("bmi_user_data.csv");
ha->display("all");

delete ha;
UserStats stat;
stat.GetHealthyUsers("bmi", "female");
stat.GetHealthyUsers("all");
stat.GetUnfitUsers("USArmy", "male");
stat.GetFullStats();
}