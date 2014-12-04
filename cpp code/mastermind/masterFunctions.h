#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
using namespace std;

typedef char save;
typedef double (*p_function) (vector<int> &, int, int);

//blacks = exact color and position as code
//whites = color in other position of code to guess

const save A = 0;
const save B = 1; 
const save C = 2;
const save D = 3;
const save E = 4;
const save F = 5;
const save G = 6;

const int ONEMOVE = 1;
const int FIRST = 1;

double logb2( double n );

void playAllGames(int colors, int slots, string Strategy, p_function getMaxElement);
void playForOne(vector<save> &code, vector<vector<save> > &originalArray, vector<int> &turnWon, vector<save> &move, p_function getMaxElement);
void returnBlacks(vector<save> &code, vector<save> &move, int &currentBlacks, vector<int> &currentMarked, vector<int> &desiredMarked);
void returnWhites(vector<save> &code, vector<save> &move, int &currentWhites, vector<int> &currentMarked, vector<int> &desiredMarked);

void populateArray(vector<vector<save> > &array, int &row, int &digit, int MAX);

void compareUniqueMove(vector<vector<save> > &currentMoves, vector<save> &uniqueMove, int desiredBlacks, int desiredWhites, int &currentMoveValue, int REMAINS);
void checkForBlacks(vector<vector<save> > &currentMoves, vector<save> &uniqueMove, int &currentBlacks, vector<int> &currentMarked, vector<int> &desiredMarked, int forRows);
void checkForWhites(vector<vector<save> > &currentMoves, vector<save> &uniqueMove, int &currentWhites, vector<int> &currentMarked, vector<int> &desiredMarked, int forRows);
bool isSameAnswer(int desiredBlacks, int currentBlacks, int desiredWhites, int currentWhites);
void copyToTempArray(vector<vector<save> > &tempArray, vector<vector<save> > &currentMoves, int forRows, int &remainingMoves, int &arrayIndex,int SLOTS);
void assignForNextRun(vector<vector<save> > &currentMoves, vector<vector<save> > &tempArray, int &currentMoveValue, int remainingMoves, int SLOTS);

void compareAllMoves(vector<vector<save> > &originalArray, vector<vector<save> > &currentMoves, vector<save> &uniqueMove, int currentMoveValue,int ANSWERS,int P_MOVES, p_function getMaxElement);
double compareWithCurrent(vector<vector<save> > &currentMoves, vector<save> &uniqueMove, int currentMoveValue,int ANSWERS, p_function getMaxElement, int P_MOVES);
double compareWithOriginal(vector<vector<save> > &currentMoves, vector<vector<save> > &originalArray, vector<save> &uniqueMove, int currentMoveValue, int ANSWERS, int P_MOVES,p_function getMaxElement);
void checkForBlacksAll(vector<vector<save> > &originalArray, vector<vector<save> > &currentMoves, int q, int y, int &currentBlacks, vector<int> &currentMarked, vector<int> &desiredMarked);
void checkForWhitesAll(vector<vector<save> > &originalArray, vector<vector<save> > &currentMoves, int q, int y, int &currentWhites, vector<int> &currentMarked, vector<int> &desiredMarked);

double WORSTCASE(vector<int> &anArray, int aSize, int P_MOVES);
double MOSTPARTS(vector<int> &anArray, int aSize, int P_MOVES);
double EXPECTED(vector<int> &anArray, int aSize, int P_MOVES);
double ENTROPY(vector<int> &anArray, int aSize, int P_MOVES);

void arrayToConsole(vector<vector<save> > &array, int rows, int SLOTS);
void arrayToFile(vector<vector<save> > &anArray, int rows);

void copyArray(vector<save> &uniqueMove, vector<vector<save> > &originalArray, int found);
void copyMove(vector<save> &uniqueMove, vector<save> &tempMove);

void clearArray(vector<int> &anArray, int aSize);

void moveToConsole(vector<save> &uniqueMove);
void moveToFile(vector<save> &move, int aSize);

bool isSame(vector<save> &code, vector<save> &move);
void copy1DimArray(vector<save> &uniqueMove, vector<save> &uniqueMoveNum);

int answersArraySize(int SLOTS);
void prepareGameVariation(int colors, int slots);
vector<save> prepareStrategy(string STRATEGY);
void assignAnswersVector(int ANSWERS,vector<int> &answersArray);
void copyAnswersArrays(int answersArray[], vector<int> &miVector, int counter);