#include <iostream>
#include <vector>
#include <stdio.h>
#include <ctype.h>
#include <string>
using namespace std;

vector<string> validWords = {"Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine",
"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifthteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen", 
"Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety", "Hundred", "Thousand", "Million",
 "Billion", "Trillion", "Quadrillion", "Quintillion", "-", "And", "Point"};

//works!
string ignoreCase(string w){
    for(int i = 0; i < w.length(); i++){
        w.at(i) = tolower(w.at(i));
    }
    return w;
}

//works!
string spaceHyphen(string w){
    vector<int> hyphenPositions;
    int startPos = 0;
    for(int i = 0; i < w.length() ; i++){
        if(w.at(i) == '-'){
            hyphenPositions.push_back(i);
        }
    }
    for(int i = 0; i < hyphenPositions.size(); i++){
        w = w.substr(startPos, (hyphenPositions.at(i)-startPos)) + " " + w.at(hyphenPositions[i]) + " " + w.substr(hyphenPositions[i]+1);
        if(i < hyphenPositions.size()-1){
            hyphenPositions[i+1] += (i+1)*2;
        }
    }
    return w;
}

//works!
string popHyphen(string w){
    for(int i = 0; i < w.length(); i++){
        if(w.at(i) == '-'){
            w.at(i) = ' ';
        }
    }
    return w;
}

//works!
vector<string> splitWords(string w){
    vector<string> usersWords;
    string temp = spaceHyphen(w);
    string holder = "";
    int wordStartPos = 0;
    int wordEndPos = 0;

    while(temp.find(" ") != string::npos){
        wordEndPos = temp.find(" ");
        holder = temp.substr(wordStartPos, wordEndPos);
        usersWords.push_back(holder);
        temp = temp.substr(temp.find(" ") + 1);
    }
    usersWords.push_back(temp);
    return usersWords;
}

//works!
bool pointFound(string w){
    vector<string> words = splitWords(w);
    for(int i = 0; i < words.size(); i++){
        if(ignoreCase(words[i]) == ignoreCase(validWords[validWords.size()-1])){
            return true;
        }
    }
    return false;
}

//works!
int findPointPosition(string w){
    vector<string> words = splitWords(w);
    for(int i = 0; i < words.size(); i++){
        if(ignoreCase(words[i]) == ignoreCase(validWords[validWords.size()-1])){
            return i;
        }
    }
    return -1;
}

//works!
bool correctPointUsage(string w){
    vector<string> words = splitWords(w);
    int x = findPointPosition(w);
    int checkPass = 0;
    if((words.size() - x) > 6){
        return false;
    }
    x++;
    for(int i = x; i < words.size(); i++){
        for(int j = 0; j < 10; j++){
            if(ignoreCase(words[x]) == ignoreCase(validWords[j])){
                checkPass++;
            }
        }
        if(checkPass != 1){
            return false;
        }
        checkPass = 0;
    }
    return true;
}

//works!
bool wordsAreValid(string w){
    int check = 0;
    vector<string> userWords = splitWords(w);
    for(int i = 0; i < userWords.size(); i++){
        for(int j = 0; j < validWords.size(); j++){
            if(ignoreCase(userWords[i]) == ignoreCase(validWords[j])){
                check++;
            }
        }
        if(check != 1){
            return false;
        }
        check = 0;
    }
    return true;
}

//works!
bool unitCheck(string w){
    vector<string> words = splitWords(w);
    int wCounter = 0;
    int x = words.size();
    if(pointFound(w)){
        x = findPointPosition(w);
    }
    for(int i = 28; i < 35; i++){
        if(ignoreCase(words[0]) == ignoreCase(validWords[i])){
            return false;
        }
    }
    if(x > 1){
        for(int i = 1; i < x; i++){
            for(int j = 10; j < 28; j++){
                if(ignoreCase(words[i]) == ignoreCase(validWords[j])){
                    for(int k = 1; k < 28; k++){
                        if(ignoreCase(words[i-1]) == ignoreCase(validWords[k])){
                            return false;
                        }
                    }
                }
            }
            for(int l = 29; l < 35; l++){
                if(ignoreCase(words[i]) == ignoreCase(validWords[l])){
                    while(wCounter < i){
                        if(ignoreCase(words[wCounter]) == ignoreCase(validWords[l])){
                            return false;
                        }
                        wCounter++;
                    }
                    wCounter = 0;
                }
            }
            wCounter = i;
            for(int m = 29; m <36; m++){
                if(ignoreCase(words[i]) == ignoreCase(validWords[m])){
                    for(int n = m+1; n < 39; n++){
                        while(wCounter < words.size()){    
                            if(ignoreCase(words[wCounter]) == ignoreCase(validWords[n])){
                                return false;
                            }
                            wCounter++;
                        }
                    }
                }    
            }
            wCounter = 0;
            for(int o = 1; o < 10; o++){
                if(ignoreCase(words[i]) == ignoreCase(validWords[o])){
                    for(int p = 1; p < 10; p++){
                        if(ignoreCase(words[i-1]) == ignoreCase(validWords[p])){
                            return false;
                        }
                    }
                }
            }
            if(ignoreCase(words[i]) == ignoreCase(validWords[28])){
                for(int q = 10; q < 27; q++){
                    if(ignoreCase(words[i-1]) == ignoreCase(validWords[q])){
                            return false;
                    }
                }
            }
            for(int r = 28; r < 36; r++){
                if(ignoreCase(words[i]) == ignoreCase(validWords[r])){
                    for(int s = 29; s<validWords.size(); s++){
                        if(ignoreCase(words[i-1]) == ignoreCase(validWords[s])){
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

//works!
bool repeatingWords(string w){
    vector<string> words = splitWords(w);
    int x = words.size();
    if(pointFound(w)){
         x = findPointPosition(w);
    }
    if(x > 1){
        for(int i = 1; i < x; i++){
            for(int j = 0; j < validWords.size(); j++){
                if(ignoreCase(words[i]) == ignoreCase(validWords[j])){    
                    if(ignoreCase(words[i-1]) == ignoreCase(words[i])){
                        return false;
                    } 
                }
            }
        }
    }
    return true;
}

//works!
bool correctHyphenUsage(string w){
    vector<string> words = splitWords(w);
    int check = 0;
    int x = words.size();
    if(pointFound(w)){
        x = findPointPosition(w);
    }
    if(words.front() == "-" || words.back() == "-"){
        return 0;
    }
    for(int i = 1; i < x; i++){
        if(words[i] == "-"){
            for(int j = 21; j < 29; j++){
                if(ignoreCase(words[i-1]) == ignoreCase(validWords[j])){
                    check++;
                }
            }
            if(check == 0) return false;
        }
        check = 0;
    }

    for(int i = 0; i < x; i++){
        for(int j = 21; j < 29; j++){
            if(ignoreCase(words[i])==ignoreCase(validWords[j])){
                if(i < x-1){
                    for(int k = 1; k < 10; k++){
                        if(ignoreCase(words[i+1])==ignoreCase(validWords[k])){
                            return false;
                        }
                    }
                }
            }
        }
    }

    return true;
}

//works!
bool correctAndUsage(string w){
    vector<string> words = splitWords(w);
    int x = words.size();
    if(pointFound(w)){
        x = findPointPosition(w);
    }
    if(words.size()>1){
        for(int i = 1; i < x; i++){
            if(ignoreCase(words[i]) == ignoreCase(validWords[36])){
                if(ignoreCase(words[i-1]) != ignoreCase(validWords[28])){
                    return false;
                }
            }
        }
    }
    return true;
}

//works! Might expand(or reduce).
bool correctSpecialWordsUsage(string w){
    vector<string> userWords = splitWords(w);
    if((userWords.size() == 1 && (ignoreCase(userWords[0]) == ignoreCase("Point") ||ignoreCase(userWords[0]) == ignoreCase("And")))||
    userWords[userWords.size()-1] == ignoreCase("Point") || userWords[userWords.size()-1] == ignoreCase("and")){
        return false;
    }
    return true;
}

//works!
bool validInput(string w){
    if(wordsAreValid(w) == false) return false;
    if(unitCheck(w) == false) return false;
    if(repeatingWords(w) == false) return false;
    if(correctHyphenUsage(w) == false) return false;
    if(correctAndUsage(w) == false) return false;
    if(correctSpecialWordsUsage(w) == false) return false;
    if(correctPointUsage(w) == false) return false;
    return true;
}

//Doesn't Work with cin>>. Must look into...
long Calculations(string w){
    vector<string> words = splitWords(w);
    long long sum = 0;
    long long total = 0;
    int x  = words.size();
    if(pointFound(w)){
        x = findPointPosition(w);
    }
    for(int i = 0; i < x; i++){
        for(int j = 0; j < validWords.size(); ++j){
            if(ignoreCase(words.at(i)) == ignoreCase(validWords.at(j))){
                switch (j){
                    case 0:
                        sum += j;
                        break;
                    case 1:
                        sum += j;
                        break;
                    case 2:
                        sum += j;
                        break;
                    case 3:
                        sum += j;
                        break;
                    case 4:
                        sum += j;
                        break;
                    case 5:
                        sum += j;
                        break;
                    case 6:
                        sum += j;
                        break;
                    case 7:
                        sum += j;
                        break;
                    case 8:
                        sum += j;
                        break;
                    case 9:
                        sum += j;
                        break;
                    case 10:
                        sum += j;
                        break;
                    case 11:
                        sum += j;
                        break;
                    case 12:
                        sum += j;
                        break;
                    case 13:
                        sum += j;
                        break;
                    case 14:
                        sum += j;
                        break;
                    case 15:
                        sum += j;
                        break;
                    case 16:
                        sum += j;
                        break;
                    case 17:
                        sum += j;
                        break;
                    case 18:
                        sum += j;
                        break;
                    case 19:
                        sum += j;
                        break;
                    case 20:
                        sum += j;
                        break;
                    case 21:
                        sum += 30;
                        break;
                    case 22:
                        sum += 40;
                        break;
                    case 23:
                        sum += 50;
                        break;
                    case 24:
                        sum += 60;
                        break;
                    case 25:
                        sum += 70;
                        break;
                    case 26:
                        sum += 80;
                        break;
                    case 27:
                        sum += 90;
                        break;
                    case 28:
                        sum *= 100;
                        break;
                    case 29:
                        sum *= 1000;
                        total += sum;
                        sum = 0;
                        break;
                    case 30:
                        sum *= 1000000;
                        total += sum;
                        sum = 0;
                        break;
                    case 31:
                        sum *= 1000000000;
                        total += sum;
                        sum = 0;
                        break;
                    case 32:
                        sum *= 1000000000000;
                        total += sum;
                        sum = 0;
                        break;
                    case 33:
                        sum *= 1000000000000000;
                        total += sum;
                        sum = 0;
                        break;
                    case 34:
                        sum *= 1000000000000000000;
                        total += sum;
                        sum = 0;
                        break;
                }
            }
        }
    }
    total += sum;
    return total;
}

//works!
string pointAdder(string w){
    string decimal = "";
    if(pointFound(w)){
        decimal = ".";
        vector<string> words = splitWords(w);
        for(int i = findPointPosition(w)+1; i < words.size(); i++){
            for(int j = 0; j < 10; j++){
                if(ignoreCase(words[i]) == ignoreCase(validWords[j])){
                    decimal = decimal + to_string(j);
                }
            }
        }
    }
    return decimal;
}

//works!
void conversion(){
    string userInput = "Ninety-One Point One One One One One";
    if(!validInput(userInput)){
        cout << "Invalid Input." << endl;
    } else {
    int n = Calculations(userInput);
    string num = to_string(n);
    string x = pointAdder(userInput);
    cout << num << x << endl;
    }

}

int main(){
    conversion();
    return 0;
}