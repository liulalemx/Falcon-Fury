#include "highScoreFile.hpp"
#include<iostream>
#include<fstream>

using namespace std;

void HighScoreFile::setHighScore(int score){
    ofstream wf("gameData.dat", ios::out | ios::binary);
    
    if(!wf) {
      cout << "Cannot open file!" << endl;
    }
    
    wf.write((char *) &score, sizeof(score));
    wf.close();
    if(!wf.good()) {
      cout << "Error occurred at writing time!" << endl;
    }
}

int HighScoreFile::getHighScore(){
    int highScore;

    ifstream rf("gameData.dat", ios::out | ios::binary);
    
    if(!rf) {
      cout << "Cannot open file!" << endl;
    }
    
    rf.read((char *) &highScore, sizeof(highScore));
    rf.close();
    if(!rf.good()) {
      cout << "Error occurred at reading time!" << endl;
      return 0;
    }

    return highScore;
}