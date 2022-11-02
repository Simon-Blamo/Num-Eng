#include <iostream>
#include <string>
#include <utility>
#include <list>
#include <vector>
#include <stdio.h>
#include <ctype.h>
using namespace std;

vector<pair <string, string>> sets = {{"0", "Zero "}, {"1", "One "}, {"2", "Two "}, {"3", "Three "}, {"4", "Four "}, {"5", "Five "}, {"6", "Six "}, {"7", "Seven "}, 
{"8", "Eight "}, {"9", "Nine "}, {"11", "Eleven "}, {"12", "Twelve "}, {"13", "Thirteen "}, {"14", "Fourteen "}, {"15", "Fifthteen "}, {"16", "Sixteen "}, {"17", "Seventeen "}, 
{"18", "Eighteen "}, {"19", "Nineteen "}};

vector<string> tens = {"Ten ", "Twenty ", "Thirty ", "Forty ", "Fifty ", "Sixty ", "Seventy ", "Eighty ", "Ninety "};

vector<pair <int, string>> units = {{0, "Hundred "}, {1, "Thousand "}, {2, "Million "}, {3, "Billion "}, {4, "Trillion "}, {5, "Quadrillion "}, {6, "Quintillion "}};

vector<string> specInserts = {"-", "and ", "point "};

string Adjust(long double num){
    long x = num;
    int y;
    string s = "";
    string number = to_string(num);
    if(x == num){
        y = number.find(".");
        return number.substr(0, y);
    }
    s = to_string (num);
    s.erase ( s.find_last_not_of('0') + 1, string::npos );
    s.erase ( s.find_last_not_of('.') + 1, string::npos );
    return s;
}

bool pointUsed(long double num){
    string number = Adjust(num);
    if(!(number.find(".") == string::npos)) return true;
    return false;
}


int findPointPosition(long double num){
    string number = Adjust(num);
    return number.find(".");
}

bool correctLength(long double num){
    string number = Adjust(num);
    if(pointUsed(num)){
        if((number.length()-1)-findPointPosition(num) <=5){
            if(number.length() <= 26){
                return true;
            }
        }
    } else if(!pointUsed(num)) {
        if(number.length() <= 20){
            return true;
        }
    }
    return false;
}

bool correctPointUsage(long double num){
    if(pointUsed(num)){
    string number = Adjust(num);
    if(number.at(number.length()-1) == '.') {return false;}
    for(int i = 0; i < number.length(); i++){
        if(number.at(i) == '.'){
             for(int j = i+1; j < number.length(); j++){
                    if(number.at(j) == '.'){
                        return false;
                    }
            } 
        }
    }
    }
    return true;
}

bool validInput(long double num){
    if(correctPointUsage(num) ==  false){return false;}
    //if(correctLength(num) ==  false){return false;}
    return true;

}

vector<string> splitingNum(long double num){
    string number = Adjust(num);
    vector<string> groupOfNumbers;
    string holder = "";
    int unitCounter = 0;
    int numOfDigits = 0;

    if(pointUsed(num) == true){
        for(int i = findPointPosition(num)+1; i < number.length(); i++){
            holder = holder + number.at(i);
            numOfDigits++;
        }
        numOfDigits++;
        groupOfNumbers.insert(groupOfNumbers.begin(), holder);
        holder = "";
    }
    for(int i = (number.length()-1) - (numOfDigits); i >= 0; i--){
        holder = number.at(i)+ holder;
        unitCounter++;
        if(unitCounter == 3){
            groupOfNumbers.insert(groupOfNumbers.begin(), holder);
            unitCounter = 0;
            holder = "";
        }
    }

    if(holder.length()!=0){
       groupOfNumbers.insert(groupOfNumbers.begin(), holder); 
    }

    return groupOfNumbers;
}

void conversion(long double num){
    vector<string> groupOfNum = splitingNum(num);
    string numb = "";
    string holder = "";
    string converted = "";
    string decimal = "";
    int checkCount = 0;
    if(pointUsed(num)){
        numb = groupOfNum[groupOfNum.size()-1];
        for(int i = 0; i < numb.length(); i++){
            for(int j = 0; j < 10; j++){
                if(numb.at(i) == sets[j].first.at(0)){
                    decimal = decimal + sets[j].second;
                }
            }
        }
        decimal = specInserts[2] + decimal;
        groupOfNum.pop_back();
   }

    //loops through each pairing of three digits starting from the last index
    for(int i = groupOfNum.size()-1; i >= 0; i--){
        //if the length is equal to three
        if(groupOfNum[i].length() == 3){
            for(int q = 1; q < 10; q++){
                if(groupOfNum[i].at(0) == sets[q].first.at(0)){
                    holder = sets[q].second + units[0].second;
                }
            }

            //if the second digit is equal to zero
            if(groupOfNum[i].at(1) == sets[0].first.at(0)){
                if(groupOfNum[i].at(2) != sets[0].first.at(0)){
                    for(int r = 1; r < 10; r++){
                        if(groupOfNum[i].at(2) == sets[r].first.at(0)){
                            holder = holder + specInserts[1] + sets[r].second;
                        }
                    }
                }
            
            //if the second digit is equal to one
            } else if (groupOfNum[i].at(1) == sets[1].first.at(0)){
                if(groupOfNum[i].at(2) != sets[0].first.at(0)){
                    for(int s = 10; s < 19; s++){
                        if(groupOfNum[i].substr(1)==sets[s].first){
                            holder = holder + specInserts[1] + sets[s].second;
                        }
                    }
                } else {
                    holder = holder + specInserts[1] + tens[0];
                }
            //if the second digit is greater than one
            } else {
                for(int t = 2; t < 10; t++){
                    if(groupOfNum[i].at(1) == sets[t].first.at(0)){
                        holder = holder + specInserts[1] + tens[t-1];
                    }
                }
                //finding the last digit within the third place
                if(groupOfNum[i].at(2) != sets[0].first.at(0)){
                    for(int u = 1; u < 10; u++){
                        if(groupOfNum[i].at(2) == sets[u].first.at(0)){
                            holder = holder.substr(0, holder.length()-1) + specInserts[0] + sets[u].second;
                        }
                    }
                } 
            }
        //if length is equal to 2
        } else if (groupOfNum[i].length() == 2){
            if(groupOfNum[i].at(0) == sets[1].first.at(0)){
                if(groupOfNum[i].at(1) != sets[0].first.at(0)){
                    for(int v = 10; v < 19; v++){
                        if(groupOfNum[i] == sets[v].first){
                            holder = sets[v].second;
                        }
                    }
                } else {
                    holder = tens[0];
                }
            //if the second digit is greater than one
            } else {
                for(int w = 2; w < 10; w++){
                    if(groupOfNum[i].at(0) == sets[w].first.at(0)){
                        holder = tens[w-1];
                    }
                }
                //finding the last digit within the third place
                if(groupOfNum[i].at(1) != sets[0].first.at(0)){
                    for(int x = 1; x < 10; x++){
                        if(groupOfNum[i].at(1) == sets[x].first.at(0)){
                            holder = holder.substr(0, holder.length()-1) + specInserts[0] + sets[x].second;
                        }
                    }
                } 
            }
        
        //if length is equal to 1
        } else if (groupOfNum[i].length() == 1){
           if(groupOfNum[i].at(0) != sets[0].first.at(0)){
                    for(int y = 1; y < 10; y++){
                        if(groupOfNum[i].at(0) == sets[y].first.at(0)){
                            holder = sets[y].second;
                        }
                    }
                } 
        }

        if(groupOfNum[i] != "000"){
            for(int z = 1; z < units.size(); z++){
                if(checkCount == z){
                    holder = holder + units[z].second;
                }
            }
        }
        checkCount++;
        converted = holder + converted;
        holder = "";
    }
    converted = converted + decimal;
    cout << converted << endl;

}

void DoIt(long double x){
    if(!validInput(x)){
        cout << "Invalid Input." << endl;
    } else {
        conversion(x);
    }
}

int main(){
    double long k = 99999991111.1;
    cout << k << endl;
    long double n = 99999999999.1;
    string m = to_string(n);
    cout << m << endl;
    DoIt(n);
    return 0;
}