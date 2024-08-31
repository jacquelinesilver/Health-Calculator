// Jacqueline Silver 
// Adapted from a class assignment in COMP 322 at McGill
#include <iostream> 
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <vector>
using namespace std;


string gender; // initialize global variables
int age;
double weight;
double waist;
double neck;
double height;
string lifestyle;
int hip;
int BF_percentage; //intialize variables
string group;
double carbs_output;
double protein_output;
double fat_output;


void getUserDetails(){

    cout << "Gender: Please specify your gender as either male or female."<< endl;
    //ask user for input
    cin >> gender; //get user input

    if ((gender != "female") && (gender != "Female") && (gender != "male") && (gender != "Male")){
        exit(0); // if other gender inputted than male or female, exit the program
    }
    if ((gender == "Female") || (gender == "female")){
        cout << "Hip Measurement: Enter your hip measurement in centimeters."<< endl; 
        cin >> hip;
    
    }
    else{
        hip = 1;
    }

    cout << "Age: Enter your age."<< endl; //^same as above
    cin >> age;
    if ((age < 20) || (age > 79)){
        exit(0); // if no data for inputted age, exit the program
    }

    cout << "Weight: Enter your body weight in kilograms."<< endl;
    cin >> weight;
    if (weight < 1){
        exit(0); //if 0 or negative number (invalid) exit the program
    }

    cout << "Waist: Input your waist measurement using centimeters."<< endl;
    cin >> waist;
    if (waist < 1){
        exit(0); 
    }

    cout << "Neck: Provide your neck measurement in centimeters."<< endl;
    cin >> neck;
    if (neck < 1){
        exit(0); 
    }

    cout << "Height: Input height measurement in centimeters."<< endl;
    cin >> height;
    if (height < 1){
        exit(0); 
    }

    cout << "Lifestyle: Provide information about your current lifestyle: sedentary, moderate (moderately active) or active."<< endl;
    cin >> lifestyle;

    if ((lifestyle != "sedentary") && (lifestyle != "Sedentary") && (lifestyle != "moderate") && (lifestyle != "Moderate") && (lifestyle != "Active") && (lifestyle != "active")){
        exit(0); // if invalid lifestyle, exit program
    }

}

std::pair<int, string> get_bfp(double waist, double neck, double height, double hip,
string gender, int age){
    if ((gender == "Female") || (gender == "female")){ //calculate bfp for females
        BF_percentage = (495 / ( 1.29579 - 0.35004 * log10(waist + hip - neck) + 0.22100 * log10(height)) - 450);
        if ((age >= 20) && (age <= 39)){ //within each age group check what the bfp is and return w its group label
            if (BF_percentage < 21){
                return (std::make_pair(BF_percentage, "Low"));
            }
            if ((BF_percentage >= 21) && (BF_percentage <= 32.9)){
                return (std::make_pair(BF_percentage, "Normal"));
            }
            if ((BF_percentage >= 33) && (BF_percentage <= 38.9)){
                return (std::make_pair(BF_percentage, "High"));
            }
            if (BF_percentage >= 39){
                return (std::make_pair(BF_percentage, "Very High"));
            }
        }
        if ((age >= 40) && (age <= 59)){
            if (BF_percentage < 23){
                return (std::make_pair(BF_percentage, "Low"));
            }
            if ((BF_percentage >= 23) && (BF_percentage <= 33.9)){
                return (std::make_pair(BF_percentage, "Normal"));
            }
            if ((BF_percentage >= 34) && (BF_percentage <= 39.9)){
                return (std::make_pair(BF_percentage, "High"));
            }
            if (BF_percentage >= 40){
                return (std::make_pair(BF_percentage, "Very High"));
            }
        }
        if ((age >= 60) && (age <= 79)){
            if (BF_percentage < 24){
                return (std::make_pair(BF_percentage, "Low"));
            }
            if ((BF_percentage >= 24) && (BF_percentage <= 35.9)){
                return (std::make_pair(BF_percentage, "Normal"));
            }
            if ((BF_percentage >= 36) && (BF_percentage <= 41.9)){
                return (std::make_pair(BF_percentage, "High"));
            }
            if (BF_percentage >= 42){
                return (std::make_pair(BF_percentage, "Very High"));
            }
            
        }
    }
    if ((gender == "Male") || (gender == "male")){ //same as above but for the males
        BF_percentage = (495 / ( 1.0324 - 0.19077 * log10(waist - neck) + 0.15456 * log10(height)) - 450);
         if ((age >= 20) && (age <= 39)){
            if (BF_percentage < 8){
                return (std::make_pair(BF_percentage, "Low"));
            }
            if ((BF_percentage >= 8) && (BF_percentage <= 19.9)){
                return (std::make_pair(BF_percentage, "Normal"));
            }
            if ((BF_percentage >= 20) && (BF_percentage <= 24.9)){
                return (std::make_pair(BF_percentage, "High"));
            }
            if (BF_percentage >= 25){
                return (std::make_pair(BF_percentage, "Very High"));
            }
        }
        if ((age >= 40) && (age <= 59)){
            if (BF_percentage < 11){
                return (std::make_pair(BF_percentage, "Low"));
            }
            if ((BF_percentage >= 11) && (BF_percentage <= 21.9)){
                return (std::make_pair(BF_percentage, "Normal"));
            }
            if ((BF_percentage >= 22) && (BF_percentage <= 27.9)){
                return (std::make_pair(BF_percentage, "High"));
            }
            if (BF_percentage >= 28){
                return (std::make_pair(BF_percentage, "Very High"));
            }
        }
        if ((age >= 60) && (age <= 79)){
            if (BF_percentage < 13){
                return (std::make_pair(BF_percentage, "Low"));
            }
            if ((BF_percentage >= 13) && (BF_percentage <= 24.9)){
                return (std::make_pair(BF_percentage, "Normal"));
            }
            if ((BF_percentage >= 25) && (BF_percentage <= 29.9)){
                return (std::make_pair(BF_percentage, "High"));
            }
            if (BF_percentage >= 30){
                return (std::make_pair(BF_percentage, "Very High"));
            }
        }

    }
}

int get_daily_calories(double age, string gender, string lifestyle){
    if ((gender == "male") || (gender == "Male")){
        if ((age >= 19) && (age <= 30)){
            if ((lifestyle == "sedentary") || (lifestyle == "Sedentary")){
                return 2400;
            }
            if ((lifestyle == "moderate") || (lifestyle == "Moderate")){
                return 2600;
            }
            if ((lifestyle == "active") || (lifestyle == "Active")){
                return 3000;
            }
        }
        if ((age >= 31) && (age <= 50)){
            if ((lifestyle == "sedentary") || (lifestyle == "Sedentary")){
                return 2200;
            }
            if ((lifestyle == "moderate") || (lifestyle == "Moderate")){
                return 2400;
            }
            if ((lifestyle == "active") || (lifestyle == "Active")){
                return 2800;
            }
        }
        if (age >= 51){
            if ((lifestyle == "sedentary") || (lifestyle == "Sedentary")){
                return 2000;
            }
            if ((lifestyle == "moderate") || (lifestyle == "Moderate")){
                return 2200;
            }
            if ((lifestyle == "active") || (lifestyle == "Active")){
                return 2400;
            }
        }

    }
    if ((gender == "female") || (gender == "Female")){
        if ((age >= 19) && (age <= 30)){
            if ((lifestyle == "sedentary") || (lifestyle == "Sedentary")){
                return 2000;
            }
            if ((lifestyle == "moderate") || (lifestyle == "Moderate")){
                return 2200;
            }
            if ((lifestyle == "active") || (lifestyle == "Active")){
                return 2400;
            }
        }
        if ((age >= 31) && (age <= 50)){
            if ((lifestyle == "sedentary") || (lifestyle == "Sedentary")){
                return 1800;
            }
            if ((lifestyle == "moderate") || (lifestyle == "Moderate")){
                return 2000;
            }
            if ((lifestyle == "active") || (lifestyle == "Active")){
                return 2200;
            }
        }
        if (age >= 51){
            if ((lifestyle == "sedentary") || (lifestyle == "Sedentary")){
                return 1600;
            }
            if ((lifestyle == "moderate") || (lifestyle == "Moderate")){
                return 1800;
            }
            if ((lifestyle == "active") || (lifestyle == "Active")){
                return 2000;
            }
        }
    }
    return 0;
}

void meal_prep(int calories_input, double& carbs_output, double& protein_output,
double& fat_output){
    double carbcal;
    double proteincal;
    double fatcal; 

    carbcal = (calories_input * (.5));
    proteincal = (calories_input * (.3));
    fatcal = (calories_input * (.2));

    carbs_output = (carbcal / 4);
    protein_output = (proteincal / 4);
    fat_output = (fatcal/9);

}

void display(){
    cout << "Your gender is " << gender << "." << endl;
    cout << "Your age is " << age << " years old." << endl;
    cout << "Your weight is " << weight << " kg." << endl;
    cout << "Your waist is " << waist << " cm." << endl;
    cout << "Your neck is " << neck << " cm." << endl;
    cout << "Your height is " << height << " cm." << endl;
    cout << "Your lifestle is " << lifestyle << "." << endl;
    if ((gender == "female") || (gender == "Female")){
        cout << "Your hips are " << hip << " cm." << endl;
    }
    std::pair<int, string> bfp = (get_bfp(waist, neck, height, hip, gender, age));
    cout << "Your bodyfat percentage is " << bfp.first << " %." << endl;
    cout << "Your bodyfat percentage group is " << bfp.second << "." << endl;
    cout << "Your suggested calorie intake is " << (get_daily_calories(age, gender, lifestyle)) << "." << endl;
    cout << "Your suggested carb amount is " << carbs_output << " g." << endl;
    cout << "Your suggested protein amount is " << protein_output << " g." << endl;
    cout << "Your suggested fat amount is " << fat_output << " g." << endl;
}

void serialize(string filename){
    fstream csvfile; //initialize pointer

    csvfile.open(filename, ios::out | ios::app); //open file if exists or create

    if ((gender == "male") || (gender == "Male")){
        csvfile << gender << ", " << age << ", " << weight << ", " << waist << ", " << neck << "," << ", " << height << ", " << lifestyle << "\n";
    } else{ //if male do ,, for female do hip
        csvfile << gender << ", " << age << ", " << weight << ", " << waist << ", " << neck << ", " << hip << ", " << height << ", " << lifestyle << "\n";
    }
    csvfile.close(); 

}

void readFromFile(string filename){

    ifstream csvfile(filename); //openfile

    if (!csvfile.is_open()){
        exit(0); // if cant open file, exit
    }
    string line; //intialize string for lines

    while (getline(csvfile, line)){
        vector<string> row; //initialize vector
        row.push_back(line);
        for (const auto& element : row){
            cout << element << endl;
        }
    }
    csvfile.close();
    
}

int main(int argc, char* argv[]) { //main from assignment instructions!!!
// Check if a filename is provided as an argument
if (argc > 1) {
// Load existing user data from the specified CSV file
readFromFile(argv[1]);
} else {
// Gather user details
getUserDetails();
// Calculate body fat percentage
auto bfpResult = get_bfp(waist, neck, height, hip,
gender, age);
std::cout << "Body Fat Percentage: " << bfpResult.first << "% (" <<
bfpResult.second << std::endl;
// Calculate daily calorie intake
int dailyCalories = get_daily_calories(age, gender,
lifestyle);
std::cout << "Daily Caloric Intake: " << dailyCalories << "calories" << std::endl;
// Calculate macronutrient breakdown
double carbs, protein, fat;
meal_prep(dailyCalories, carbs, protein, fat);
std::cout << "Macronutrient Breakdown:\n";
std::cout << "Carbs: " << carbs << "g, Protein: " << protein << "g,Fat: " << fat << "g" << std::endl;
// Display user information
display();
// Save user data to a CSV file
serialize("user_data.csv");
}
return 0;
}