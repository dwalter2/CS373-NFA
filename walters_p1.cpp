#include <fstream>
#include <cstring>
#include <vector>
#include <utility>
#include <unordered_set>
#include <cstdlib>
#include <iostream>
using namespace std;
int main(int argc, char const *argv[]) {
    /*if(argc!=3){
      cout << "error with command line arguments" << endl;
      return -1;
    }*/
    bool DDEBUG = true;
    vector<int> acceptstates;
    int startstate;
    vector<vector<pair<char,int>>> transitions(1001);
    ifstream infile(argv[1]);
    string s;
    int i = 0;
    while(getline(infile,s)){
      cout << "iteration : " << i++ << endl;

      size_t found = s.find("state");
      if(found != string::npos){
        //cout << "here" << endl;
        string num = "";
        for(int i = 5 ; i < s.length() ; i++){
          if (s[i]==' '){
            if (num!=""){
              break;
            }
          }
          else{
            num+=s[i];
          }
        }
        int x = stoi(num);
        size_t found1 = s.find("start");
        if(found1 != string::npos){
          //cout << "here" << endl;
          startstate = x;
        }
        size_t found2 = s.find("accept");
        if(found2 != string::npos){
          //cout << "here 2" << endl;
          acceptstates.push_back(x);
        }
      }
      else{
        string firstnum ="";
        int lastpos = 10;
        for(int i = 10 ; i < s.length() ; i++ ){
          if (s[i]=='\t'){
            if (firstnum!=""){
              lastpos = i;
              break;
            }
          }
          else{
            firstnum+=s[i];
          }
        }
        int beginstate = stoi(firstnum);
        //cout << "begin state: " << beginstate << endl;
        char trans ='\0';
        for(int i = lastpos ; i < s.length()  ;i++){
          cout << "s[i] " << s[i] << endl;
          if (s[i]=='\t'){
            //cout << "in first if" << endl;
            if (trans!='\0'){
              //cout << "now breaking" << endl;
              lastpos = i;
              break;
            }
          }
          else{
            //cout << "adding to string " << endl;
            trans=s[i];
          }
        }
        //cout << "last position: " << lastpos << endl;
        //cout << "transition : " << trans << endl;
        string secondnum = "";
        for(int i = lastpos ; i < s.length() ; i++){
          if (s[i]=='\t'){
            if (secondnum!=""){
              break;
            }
          }
          else{
            secondnum+=s[i];
          }
        }
        int endstate = stoi(secondnum);
        //cout << "endstate : " << endstate << endl;
        //if(DDEBUG) cout << "begin state : " << beginstate << " transition : " << trans << " ending state: " << endstate << endl;
        pair <char, int> p;
        p = make_pair (trans, endstate);
        transitions[beginstate].push_back(p);
      }
    }
    if(DDEBUG){
      for(int i = 0 ; i < acceptstates.size() ; i++){
        cout << "accept states: " << acceptstates[i] << endl;
      }
      cout << "start state: " << startstate << endl;
      for(int i = 0 ; i  < transitions.size() ; i++){
        for(int j = 0 ; j < transitions[i].size() ; j++){
          cout << "transition for " << i << " : from " << transitions[i][j].first << " to " << transitions[i][j].second << endl;
        }
      }
    }
    //beginning NFA
    string path = argv[2];
    vector<int> currentstates;
    currentstates.push_back(startstate);
    for(int i = 0 ; i < path.length() ; i++){
      vector<int> newcurrentstates;
      for(int j = 0 ; j < currentstates.size() ; j++){
        //cout << "current state : " << currentstates[j] << endl;
        for(int k = 0 ; k < transitions[currentstates[j]].size() ; k++){
          //cout << transitions[currentstates[j]].size() << "transition size" << endl;
          //cout << "transition symbol : " << transitions[currentstates[j]][k].first << endl;
          //cout << "compared to symbol : " << path[i] << endl;
          //cout << "possible path to : " << transitions[currentstates[j]][k].second << endl;
          if(transitions[currentstates[j]][k].first == path[i]){
            newcurrentstates.push_back(transitions[currentstates[j]][k].second);
          }
        }
      }
      //currentstates.erase(currentstates.begin());
      //infinite loop
      currentstates = newcurrentstates;
      /*for(int  q = 0 ; q < currentstates.size() ; q++){
        cout << " after loop : "<< currentstates[i] << endl;
      }*/
    }
    vector<int> acceptvalues;
    for(int i = 0 ; i < currentstates.size() ; i++){
      for(int j = 0 ; j < acceptstates.size() ; j++){
        if(currentstates[i]==acceptstates[j]){
          acceptvalues.push_back(currentstates[i]);
        }
      }
    }
    if(acceptvalues.size()==0){
      cout << "reject";
      unordered_set<int> accepts;
      for(int i = 0; i < currentstates.size() ; i++){
        if(accepts.find(currentstates[i])==accepts.end()){
          accepts.insert(currentstates[i]);
        }
      }
      for(auto it = accepts.begin() ; it != accepts.end() ; it++){
        cout <<" " << (*it)  ;
      }
      cout << endl;
    }
    else{
      unordered_set<int> accepts;
      for(int i = 0; i < acceptvalues.size() ; i++){
        if(accepts.find(acceptvalues[i])==accepts.end()){
          accepts.insert(acceptvalues[i]);
        }
      }
      cout << "accept";
      for(auto it = accepts.begin() ; it != accepts.end() ; it++){
        cout <<" " << (*it)  ;
      }
      cout << endl;
    }
}
