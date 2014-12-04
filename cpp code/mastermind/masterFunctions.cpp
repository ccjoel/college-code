#include "masterFunctions.h"

// SLOTS    ////    Array with answers
vector<int> answersArray;

int allAnswersArray_2[] = {0,1,2,10,20};

int allAnswersArray_3[] = {0,1,2,3,10,11,12,20,30};

int allAnswersArray_4[] = {0,1,2,3,4,10,11,12,13,20,21,22,30,40};

int allAnswersArray_5[] = {0,1,2,3,4,5,10,11,12,13,14,20,21,22,23,30,31,32,40,50};

int allAnswersArray_6[] = {0,1,2,3, 4,5,6,10, 11,12,13,14, 15,20,21,22, 23,24,30,31, 32,33,40,41, 42,50,60};

//answersArray[14] = 0,0 | 0,1 | 0,2 | 0,3 | 0,4 | 1,0 | 1,1 | 1,2 | 1,3 | 2,0 | 2,1 | 2,2 | 3,0 | 4,0
//                    1     2     3     4     5     6     7     8     9    10    11    12     13   14

//ALL FUNCTION DEFINITIONS

double logb2( double n ) {
    return (log( n ) / log( 2.0 ));
}

//returnBlacks( ... ): Checks how many blacks a move has compared to a code. For use in main.
void returnBlacks(vector<save> &code, vector<save> &move, int &currentBlacks, vector<int> &currentMarked, vector<int> &desiredMarked) {
	int SLOTS = code.capacity();
	for(int forBlacks = 0; forBlacks < SLOTS; forBlacks++)
		if(code[forBlacks] == move[forBlacks]) {
			currentBlacks++;
			currentMarked[forBlacks]++;
			desiredMarked[forBlacks]++;
		}
}

//returnWhites( ... ): Checks how many whites a move has compared to the code. Used in main().
void returnWhites(vector<save> &code, vector<save> &move, int &currentWhites, vector<int> &currentMarked, vector<int> &desiredMarked) {
	bool elseTemp;
	int SLOTS = code.capacity();
	for(int forWhites = 0; forWhites < SLOTS; forWhites++)
		if(desiredMarked[forWhites] == 0) {
			elseTemp = false;
			for(int forUnique = 0; forUnique < SLOTS; forUnique++)
				if( (code[forWhites] == move[forUnique]) && (currentMarked[forUnique] == 0) && (elseTemp == false) ) {
					currentWhites++;
					currentMarked[forUnique]++;
					desiredMarked[forWhites]++;
					elseTemp = true;
				}
		}
}

//populate( ... ): Populate an array with all P_MOVES (possible moves)
void populateArray(vector<vector<save> > &array, int &row, int &digit, int MAX) {
	int SLOTS = array[0].capacity();
	if(array[row][SLOTS-1] < MAX) {
		digit=SLOTS-1;
		row++;
		for(int q=0; q<digit; q++)
			array[row][q] = array[row-1][q];
		array[row][digit]=array[row-1][digit] + 1;
		populateArray(array, row, digit,MAX);
	}
	else if(digit>=0) {
		digit--;
		if(digit>=0 && array[row][digit] != MAX) {
			row++;
			for(int q=0; q<digit; q++)
				array[row][q] = array[row-1][q];
			array[row][digit]=array[row-1][digit] + 1;
			for(int q=digit+1; q<SLOTS; q++)
				array[row][q]=0;
		}
		populateArray(array, row, digit,MAX);
	}
}

//compareUniqueMove( ... ): Compare a move to the remaining moves
void compareUniqueMove(vector<vector<save> > &currentMoves, vector<save> &uniqueMove, int desiredBlacks, int desiredWhites, int &currentMoveValue,int REMAINS) {
	int SLOTS = uniqueMove.capacity();
	vector<int> desiredMarked(SLOTS,0);
	vector<int> currentMarked(SLOTS,0);
	int    currentBlacks = 0, currentWhites = 0, arrayIndex = 0,
		remainingMoves = 0;

    vector<vector<save> > tempArray(REMAINS, vector<save>(SLOTS,0));

	for(int forRows = 0; forRows < currentMoveValue; forRows++){

		clearArray(desiredMarked, SLOTS);
		clearArray(currentMarked, SLOTS);
		currentBlacks = 0, currentWhites = 0;

		checkForBlacks(currentMoves, uniqueMove, currentBlacks, currentMarked, desiredMarked, forRows);
		checkForWhites(currentMoves, uniqueMove, currentWhites, currentMarked, desiredMarked, forRows);

		if ( isSameAnswer(desiredBlacks, currentBlacks, desiredWhites, currentWhites) )
			copyToTempArray(tempArray, currentMoves, forRows, remainingMoves, arrayIndex, SLOTS);
	}
	assignForNextRun(currentMoves, tempArray, currentMoveValue, remainingMoves, SLOTS);
}

//checkForBlacks( ... ): checks how many blacks a move has compared to remaining moves. Used in compareUniqueMove().
void checkForBlacks(vector<vector<save> > &currentMoves, vector<save> &uniqueMove, int &currentBlacks, vector<int> &currentMarked, vector<int> &desiredMarked, int forRows) {
	int SLOTS = uniqueMove.capacity();
	for(int forBlacks = 0; forBlacks < SLOTS; forBlacks++)
		if(currentMoves[forRows][forBlacks] == uniqueMove[forBlacks]) {
			currentBlacks++;
			currentMarked[forBlacks]++;
			desiredMarked[forBlacks]++;
		}
}

//checkForWhites( ... ): same as checkForBlacks but for whites.
void checkForWhites(vector<vector<save> > &currentMoves, vector<save> &uniqueMove, int &currentWhites, vector<int> &currentMarked, vector<int> &desiredMarked, int forRows) {
		bool elseTemp;
		int SLOTS = uniqueMove.capacity();
		for(int forWhites = 0; forWhites < SLOTS; forWhites++)
			if(desiredMarked[forWhites] == 0) {
				elseTemp = false;
				for(int forUnique = 0; forUnique < SLOTS; forUnique++)
					if( (currentMoves[forRows][forWhites] == uniqueMove[forUnique]) && (currentMarked[forUnique] == 0) && (elseTemp == false) ) {
						currentWhites++;
						currentMarked[forUnique] ++;
						desiredMarked[forWhites] ++;
						elseTemp = true;
					}
			}
}

//isSameAnswer( ... ): check if the current whites/blacks are the same as the desired whites/blacks. Used in compareUniqueMove().
bool isSameAnswer(int desiredBlacks, int currentBlacks, int desiredWhites, int currentWhites) {
	return ( (desiredBlacks == currentBlacks) && (desiredWhites == currentWhites) );
}

//copyToTempArray( ... ): blah. Used in compareUniqueMove().
void copyToTempArray(vector<vector<save> > &tempArray, vector<vector<save> > &currentMoves, int forRows, int &remainingMoves, int &arrayIndex,int SLOTS) {
	for(int slots = 0; slots < SLOTS; slots++)
		tempArray[arrayIndex][slots] = currentMoves[forRows][slots];
	arrayIndex++;
	remainingMoves++;
}

//assignForNextRun
void assignForNextRun(vector<vector<save> > &currentMoves, vector<vector<save> > &tempArray, int &currentMoveValue, int remainingMoves, int SLOTS) {
	for(int forRemains = 0; forRemains < remainingMoves; forRemains++)
		for(int forSlots = 0; forSlots < SLOTS; forSlots++)
			currentMoves[forRemains][forSlots] = tempArray[forRemains][forSlots];
	currentMoveValue = remainingMoves;
}

//compareAllMoves( ... ): Used for Strategy: compares remaining moves to all P_MOVES to select a new move for next turn (if not won)
void compareAllMoves(vector<vector<save> > &originalArray, vector<vector<save> > &currentMoves, vector<save> &uniqueMove, int currentMoveValue,int ANSWERS,int P_MOVES, p_function getMaxElement) {
	int SLOTS = uniqueMove.capacity();
	//double maxFromAllAnswersO;
	double maxFromAllAnswersC;
	//vector<save> uniqueMoveO(SLOTS,0);
	vector<save> uniqueMoveC(SLOTS,0);

    //maxFromAllAnswersO = compareWithOriginal(currentMoves, originalArray,uniqueMoveO, currentMoveValue,ANSWERS,P_MOVES, getMaxElement);
	maxFromAllAnswersC = compareWithCurrent(currentMoves, uniqueMoveC, currentMoveValue,ANSWERS, getMaxElement, P_MOVES);

    copy1DimArray(uniqueMove, uniqueMoveC);

}

//!!!!WARNING!!!!
//IN THE TWO FOLLOWING FUNCTIONS, GETMAXELEMENT IS THE KEY FOR WHICH
//STRATEGY IS USED TO SOLVE THE GAME. SEE ALL GETMAXELEMENT FUNCTIONS
//DEFINED BELOW.

double compareWithCurrent(vector<vector<save> > &currentMoves, vector<save> &uniqueMove, int currentMoveValue, int ANSWERS, p_function getMaxElement, int P_MOVES)
{
	int SLOTS = uniqueMove.capacity();
    double maxFromAllAnswers = 33000;
	vector<int> desiredMarked(SLOTS,0);
	vector<int> currentMarked(SLOTS,0);
	int currentBlacks = 0, currentWhites = 0;

	vector<int> currentAnswersArray(ANSWERS);
	double maxFromCurrentAnswers=0;

    for(int q = 0; q < currentMoveValue; q++) {
		for(int y = 0; y < currentMoveValue; y++) {
			clearArray(desiredMarked, SLOTS);
			clearArray(currentMarked, SLOTS);
			currentBlacks = 0, currentWhites = 0;

            checkForBlacksAll(currentMoves, currentMoves, q, y, currentBlacks, currentMarked, desiredMarked);
			checkForWhitesAll(currentMoves, currentMoves, q, y, currentWhites, currentMarked, desiredMarked);

			for(int  forAns = 0; forAns < ANSWERS; forAns++)
				if( (currentBlacks*10 + currentWhites) == answersArray[forAns] )
					currentAnswersArray[forAns]++;
		}
		maxFromCurrentAnswers = getMaxElement(currentAnswersArray, ANSWERS,P_MOVES);
		if( maxFromCurrentAnswers < maxFromAllAnswers) {
			maxFromAllAnswers = maxFromCurrentAnswers;
			copyArray(uniqueMove, currentMoves, q);
		}
		clearArray(currentAnswersArray, ANSWERS);
	}
	return maxFromAllAnswers;

}

double compareWithOriginal(vector<vector<save> > &currentMoves, vector<vector<save> > &originalArray, vector<save> &uniqueMove, int currentMoveValue, int ANSWERS, int P_MOVES, p_function getMaxElement)
{
	int SLOTS = uniqueMove.capacity();
	double maxFromAllAnswers = P_MOVES;
	vector<int> desiredMarked(SLOTS,0);
	vector<int> currentMarked(SLOTS,0);
	int	currentBlacks = 0, currentWhites = 0;

	vector<int> currentAnswersArray(ANSWERS,0);
	double maxFromCurrentAnswers=0;

	for(int q = 0; q < P_MOVES; q++) {
		for(int y = 0; y < currentMoveValue; y++) {
			clearArray(desiredMarked, SLOTS);
			clearArray(currentMarked, SLOTS);
			currentBlacks = 0, currentWhites = 0;

            checkForBlacksAll(originalArray, currentMoves, q, y, currentBlacks, currentMarked, desiredMarked);
			checkForWhitesAll(originalArray, currentMoves, q, y, currentWhites, currentMarked, desiredMarked);

			for(int forAns = 0; forAns < ANSWERS; forAns++)
				if( (currentBlacks*10 + currentWhites) == answersArray[forAns] )
					currentAnswersArray[forAns]++;
		}
		maxFromCurrentAnswers = getMaxElement(currentAnswersArray, ANSWERS,P_MOVES);
		if( maxFromCurrentAnswers < maxFromAllAnswers) {
			maxFromAllAnswers = maxFromCurrentAnswers;
			copyArray(uniqueMove, originalArray, q);
		}
		clearArray(currentAnswersArray, ANSWERS);
	}
	return maxFromAllAnswers;

}

//checkForBlacksAll( ... ):Used to check how many blacks in compareAllMoves
void checkForBlacksAll(vector<vector<save> > &originalArray, vector<vector<save> > &currentMoves, int q, int y, int &currentBlacks, vector<int> &currentMarked, vector<int> &desiredMarked) {
	int SLOTS = currentMarked.capacity();
	for(int forBlacks = 0; forBlacks < SLOTS; forBlacks++)
		if(originalArray[q][forBlacks] == currentMoves[y][forBlacks]) {
			currentBlacks++;
			currentMarked[forBlacks]++;
			desiredMarked[forBlacks]++;
		}
}

//checkForWhitesAll( ... ): Same as ...BlacksAll but with whites
void checkForWhitesAll(vector<vector<save> > &originalArray, vector<vector<save> > &currentMoves, int q, int y, int &currentWhites, vector<int> &currentMarked, vector<int> &desiredMarked) {
		int SLOTS = currentMarked.capacity();
		bool elseTemp;
		for(int forWhites = 0; forWhites < SLOTS; forWhites++)
			if(desiredMarked[forWhites] == 0) {
				elseTemp = false;
				for(int forUnique = 0; forUnique < SLOTS; forUnique++)
					if( (originalArray[q][forWhites] == currentMoves[y][forUnique]) && (currentMarked[forUnique] == 0) && (elseTemp == false) ) {
						currentWhites++;
						currentMarked[forUnique]++;
						desiredMarked[forWhites]++;
						elseTemp = true;
					}
			}
}

//arrayToConsole( ... ): outputs the code from a two dimensional array to console
void arrayToConsole(vector<vector<save> > &array, int rows, int SLOTS) {
	for(int q = 0; q < rows; q++){
		for(int w = 0; w < SLOTS; w++)
			cout<< array[q][w] << " ";
		cout<<endl;
	}
}

//getMaxElement : WORST-CASE
double WORSTCASE(vector<int> &anArray, int aSize, int P_MOVES) {
	double max = anArray[0];
	for(int q = 0; q < aSize; q++)
		if(anArray[q] > max)
			max = anArray[q];
	return max;
}

//getMaxElement : MOST-PARTS
double MOSTPARTS(vector<int> &anArray, int aSize, int P_MOVES) {
	double max=0;
	for(int q = 0; q < aSize; q++)
		if(anArray[q] == 0)
			max++;
	return max;
}

//getMaxElement: EXPECTED
double EXPECTED(vector<int> &anArray, int aSize, int P_MOVES) {
    double max = 0;
    for(int q = 0; q < aSize; q++)
       if (anArray[q] != 0)
          max += pow(anArray[q],2.0);
    max /= P_MOVES;
    return max;
}

//getMaxElement: ENTROPY
double ENTROPY(vector<int> &anArray, int aSize, int P_MOVES){
    double max = 0;
    for(int q = 0; q < aSize; q++)
        if(anArray[q] != 0)
           max += (anArray[q]/(double)P_MOVES) * ( logb2(anArray[q]/(double)P_MOVES) );
	if(max > 0)
		max = max * (-1);
    return max;
}

//copyArray( ... ): copies a move from two dimensional array to a one-dimesional
void copyArray(vector<save> &uniqueMove, vector<vector<save> > &originalArray, int found) {
	int SLOTS = uniqueMove.capacity();
	for(int z = 0; z < SLOTS; z++)
		uniqueMove[z] = originalArray[found][z];
}

//copyMove( ... ): copies a moves from 1-dim to 1-dim
void copyMove(vector<save> &uniqueMove, vector<save> &tempMove) {
    int SLOTS = uniqueMove.capacity();
	for(int temp = 0; temp < SLOTS; temp++)
             tempMove[temp] = uniqueMove[temp];
}

//clearArray( ... ): clears an entire 1-dim array of size aSize
void clearArray(vector<int> &anArray, int aSize) {
	for(int c = 0; c < aSize; c++)
		anArray[c] = 0;
}


//moveToConsole( ... ): outputs a move of SLOTS positions to console, from a 1-dim array
void moveToConsole(vector<save> &uniqueMove) {
	int SLOTS = uniqueMove.capacity();
	for(int out = 0; out < SLOTS; out++)
		cout<<uniqueMove[out]<< " ";
	cout<<endl;
}

bool isSame( vector<save> &code, vector<save> &move){
     bool itIsSame = true;
     int SLOTS = move.capacity();
     for(int verify = 0; verify < SLOTS; verify++)
         if(code[verify] != move[verify])
             itIsSame = false;

     return itIsSame;

}

void copy1DimArray(vector<save> &uniqueMove, vector<save> &uniqueMoveNum) {
	int SLOTS = uniqueMove.capacity();
	for(int toCopy = 0; toCopy < SLOTS; toCopy++)
	    uniqueMove[toCopy] = uniqueMoveNum[toCopy];
}

int answersArraySize(int SLOTS){
	int arraySize = 2 * SLOTS;
	for(int toMod = 0; toMod < SLOTS; toMod++)
       arraySize += toMod;
	return arraySize;
}


void copyAnswersArrays(int answersArray[], vector<int> &miVector, int counter){
	for(int i = 0; i < counter; i++){
		miVector[i] = answersArray[i];
	}
}

void assignAnswersVector(int ANSWERS,vector<int> &answersArray){
	answersArray.resize(ANSWERS);
	switch(ANSWERS){
		case(5):
			copyAnswersArrays(allAnswersArray_2,answersArray,ANSWERS);
			break;
		case(9):
			copyAnswersArrays(allAnswersArray_3,answersArray,ANSWERS);
			break;
		case(14):
			copyAnswersArrays(allAnswersArray_4,answersArray,ANSWERS);
			break;
		case(20):
			copyAnswersArrays(allAnswersArray_5,answersArray,ANSWERS);
			break;
		case(27):
			copyAnswersArrays(allAnswersArray_6,answersArray,ANSWERS);
			break;
		default:
			cout<<"Undefined action for 2<=SLOTS<=6 in <assignAnswersVector> function";
	}
}
