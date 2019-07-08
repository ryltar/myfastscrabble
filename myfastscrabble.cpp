#include <iostream>
#include <list>
#include <string>
#include <tuple>
#include <set>
#include <fstream>
#include <algorithm>

using namespace std;

tuple<string, list<string>, int> parserCommandLine(char* argv[], int size){
    list<string> result;
    string dict;
    if((string)argv[1] == "-d" && argv[2][0] != '-' && argv[size-1][0] != '-' && size > 2 && argv[3][0] == '-'){
        dict = argv[2];
    }else{
        return make_tuple(dict, result, 2);
    }
    for(int i = 3; i < size; i++){
        string currentParam = argv[i];
        if(currentParam[0] == '-'){
            if(currentParam[1] == 's'){
                string nextElem = argv[i+1];
                if(nextElem[0] != '-'){
                    transform(nextElem.begin(), nextElem.end(), nextElem.begin(), ::tolower);
                    sort(nextElem.begin(), nextElem.end());
                    nextElem.erase(remove(nextElem.begin(), nextElem.end(), '"'), nextElem.end());
                    result.push_back(nextElem);
                }else{
                    return make_tuple(dict, result, 2);
                }
            }else{
                return make_tuple(dict, result, 2);
            }
        }
    }
    return make_tuple(dict, result, 10);
}

tuple<list<string>, int> solver(const string *path, list<string> words){
    list<string> anagrams;
    list<string>::iterator it_words;
    ifstream file(*path, ios::in);
    if(file){
        string line;
        while(getline(file,line)){
            if(line.size() <= 11){
                string rawLine = line;
                transform(rawLine.begin(), rawLine.end(), rawLine.begin(), ::tolower);
                sort(rawLine.begin(), rawLine.end());
                for(it_words = words.begin(); it_words != words.end(); ++it_words) {
                    string word = *it_words;
                    if (rawLine == word) {
                        anagrams.push_back(line);
                    }
                }
            }
        }
    }else{
        return make_tuple(anagrams, 3);
    }
    file.close();
    return make_tuple(anagrams, 10);
}

int main(int argc, char* argv[]) {
    tuple<string, list<string>, int> data = parserCommandLine(argv, argc);
    string filename = get<0>(data);
    list<string> words = get<1>(data);
    int parserStatus = get<2>(data);
    tuple<list<string>, int> solverData = solver(&filename, words);
    list<string> anagrams = get<0>(solverData);
    int solverStatus = get<1>(solverData);
    if(parserStatus != 10){
        return 2;
    }else if(solverStatus != 10){
        return 3;
    }
    if(anagrams.empty()){
        return 1;
    }else{
        cout << "Le dictionnaire comporte " << anagrams.size()  << " anagramme(s)" << endl;
        for(const string& x: anagrams) cout << x << endl;
    }

    return 0;
}

