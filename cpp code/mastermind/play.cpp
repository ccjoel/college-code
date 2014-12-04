//Functions declared here
#include "masterFunctions.h"
#include <sstream>

int SLOTS;   //how many slots in the codes of the game, default MM is 4
int COLORS;  //number of possible colors to use for making the code, default in MM 6
int MAX;    //used in populate, COLORS - 1
int P_MOVES; //6^4 or COLORS^SLOTS, all possible move combinations
int ANSWERS; //all possible answers to receive with settings from above
int MAXTURNS;
int REMAINS; //Remaining moves after first type partition (ex: after AAAA,AAAB, etc)
int totalGuesses = 0;   //total number of guesses to solve al P_MOVES

extern vector<int> answersArray;
//File to output everything (basically for debugging purposes)
ofstream salida;

/*Estrategias Posibles:
Simple
*Worst-Case
*Most-Parts
*Expected
*Entropy
Standard-Deviation

* = implemented

*/

int main(){
	int forStrategy, colors, slots;
	cout<<"MASTERMIND"<<endl;
	cout<<"1. Worst Case\n2. Most Parts\n3. Expected\n4. Entropy"<<endl;
	cout<<"Enter Strategy Number: ";
	cin>>forStrategy;
	string Strategy;

	switch(forStrategy){
		case 1: Strategy = "Worst-Case";
			break;
		case 2: Strategy = "Most-Parts";
			break;
		case 3: Strategy = "Expected";
			break;
		case 4:Strategy = "Entropy";
			break;
		default: cout<<"Invalid Strategy";
			return 0;
	}

	cout<<"colors= ";
	cin>>colors;
	cout<<"slots= ";
	cin>>slots;

	system("cls");

	p_function getMaxElement;
	if (Strategy == "Worst-Case")
		getMaxElement = WORSTCASE;
	else if (Strategy == "Most-Parts")
		getMaxElement = MOSTPARTS;
	else if (Strategy == "Expected")
		getMaxElement = EXPECTED;
	else if (Strategy == "Entropy")
		getMaxElement = ENTROPY;
	else
		cout<<"ERROR: Unavailable strategy";

   
    totalGuesses = 0;
	playAllGames(colors,slots,Strategy,getMaxElement);
	
	
	cin.get();
	return 0;
}


//////////////////////////////////////////

void playAllGames(int COLORS, int SLOTS, string STRATEGY, p_function getMaxElement) {
	//arrays which will hold all the P_MOVES
	prepareGameVariation(COLORS,SLOTS);
	vector<save> move(SLOTS,0);
	move = prepareStrategy(STRATEGY);

	string fileName("vs");
	ostringstream getColors;
    getColors << COLORS;
    string fileName_temp = getColors.str(); //retrieve as a string
    fileName = fileName_temp+fileName;
    ostringstream getSlots;
	getSlots << SLOTS;
	fileName_temp = getSlots.str();
    fileName = fileName + fileName_temp;
	ostringstream getStrategy;
	getStrategy << STRATEGY;
	fileName_temp = getStrategy.str();
    fileName = fileName + "_" + fileName_temp;
	fileName += ".txt";
	salida.open(fileName.c_str(), ios::app);

    vector<vector<save> > originalArray( P_MOVES, vector<save>(SLOTS,0) );
	int row = 0, digit = SLOTS;    
    populateArray(originalArray, row, digit,MAX);
	
    vector<save> code(SLOTS,0);
    vector<int> turnWon(MAXTURNS,0);
    
    salida<<COLORS<<" vs "<<SLOTS<<endl;
    salida<<"P_MOVES= "<<P_MOVES<<endl;
    salida<<"Possible Answers= "<<ANSWERS<<endl;
    salida<<"First move to use= "; moveToFile(move,SLOTS);
    salida<<endl<<"Remains= "<<REMAINS<<endl<<endl;

	cout<<COLORS<<" vs "<<SLOTS<<endl;
    cout<<"P_MOVES= "<<P_MOVES<<endl;
    cout<<"Possible Answers= "<<ANSWERS<<endl;
    cout<<endl<<"Remains= "<<REMAINS<<endl<<endl;
    
	//solving for all P_MOVES
	for(int solve = 0; solve < P_MOVES; solve++){
        
        cout<<solve+1<<" ";
        salida<<"______________________________________________________________"<<endl;
        salida<<"Code# "<<solve+1<<": ";
        
        for(int copyCode = 0; copyCode < SLOTS; copyCode++){
                code[copyCode] = originalArray[solve][copyCode];
                if( sizeof(save) != sizeof(int) )
                    salida<<(int)(code[copyCode])<<" ";
                else
                    salida<<code[copyCode]<<" ";
        }
        
        salida<<endl<<"##############################################################"<<endl;
       
        if ( isSame(code, move) ){
            turnWon[FIRST]++;
            salida<<"Won in first turn!"<<endl;
            salida<<"Turn Table: ";
            
			totalGuesses++;
			for(int forWin = FIRST; forWin < MAXTURNS; forWin++)
               salida<<turnWon[forWin]<<" "; //output to console how many won in each turn
            salida<<endl;
        }
        else
            playForOne(code, originalArray, turnWon, move, getMaxElement);
     }
    
    //output to console the results for turn winnings
    cout<<endl<<endl;
    for(int forWin = FIRST; forWin < MAXTURNS; forWin++)
        cout<<turnWon[forWin]<<" "; //output to console how many won in each turn
    cout<<endl;

    salida<<"Total Guesses: "<<totalGuesses<<endl;
    double expected = (double)totalGuesses / P_MOVES;
    salida<<"Expected: "<<expected<<endl;

	cout<<"Total Guesses: "<<totalGuesses<<endl;
	cout<<"Expected: "<<expected<<endl;
	
	salida.close();
}

void playForOne(vector<save> &code, vector<vector<save> > &originalArray, vector<int> &turnWon, vector<save> &Amove, p_function getMaxElement){

    vector<vector<save> > currentMoves(P_MOVES,vector<save>(SLOTS,0));
	vector<save> move = Amove;
    //declaring variables to know how many whites, blacks you have (etc) and the turn in which the game was won
	int currentBlacksMain, currentWhitesMain;
	vector<int> currentMarked1(SLOTS,0); 
	vector<int> desiredMarked1(SLOTS,0);
	int turn = FIRST;
	
    int row = 0, digit = SLOTS;
    populateArray(currentMoves, row, digit,MAX);
        
    //This variable (CurrentMoveValueMain) holds the number of moves remaining in each game
    int CurrentMoveValueMain;
    
    CurrentMoveValueMain = P_MOVES;

    //while there's more than one answer remainig (i.e:not won)
	while( (CurrentMoveValueMain > ONEMOVE) && (!(isSame(code,move))) ){
        
	    totalGuesses++;
                      
        //initialize everything for each loop on this While                         
	    currentBlacksMain = 0, currentWhitesMain = 0;
        clearArray(currentMarked1, SLOTS);
	    clearArray(desiredMarked1, SLOTS);
               
        //put the move used to guess in the file getSim.txt
        salida<<"Guess: "; moveToFile(move, SLOTS); salida<<endl; 

        //check how many blacks and whites resemble from code to move 		
        returnBlacks(code, move, currentBlacksMain, currentMarked1, desiredMarked1);
		returnWhites(code, move, currentWhitesMain, currentMarked1, desiredMarked1);

		//more to output in file
        salida<<"("<<currentBlacksMain<<","<<currentWhitesMain<<")"<<endl;
		      
        compareUniqueMove(currentMoves, move, currentBlacksMain, currentWhitesMain, CurrentMoveValueMain,REMAINS);
	    salida<<"CurrentMoveValueMain: "<<CurrentMoveValueMain<<endl;
	    
        if( CurrentMoveValueMain != ONEMOVE)
		   compareAllMoves(originalArray, currentMoves, move, CurrentMoveValueMain,ANSWERS,P_MOVES, getMaxElement);
		       
		turn++;
		   
     }  
             
     //Adding game results (for each code) to file [getSim.txt]
     turnWon[turn]++;
     
     salida<<"Guess: ";
     
     if(CurrentMoveValueMain == ONEMOVE)
          arrayToFile(currentMoves, CurrentMoveValueMain);
     else
         moveToFile(move, SLOTS);
     
     totalGuesses++;
                 
     salida<<endl<<"Won!, in "<<turn<<"th turn."<<endl;
     salida<<"Turn Table: ";
     for(int forWin = FIRST; forWin < MAXTURNS; forWin++)
         salida<<turnWon[forWin]<<" ";
     salida<<endl;
}

//arrayToFIle( ... ):same as toConsole (see above) but in a file
void arrayToFile(vector<vector<save> > &anArray, int rows) {
	for(int q = 0; q < rows; q++){
		for(int w = 0; w < SLOTS; w++){
            if( sizeof(save) != sizeof(int))
			   salida<< (int)(anArray[q][w]) << " ";
			else
			   salida<< anArray[q][w] << " ";
            }
		salida<<endl;
	}
}

//moveToFile( ... ): outputs a move of SLOTS positions to a file, from a 1-dim array
void moveToFile(vector<save> &move, int aSize) {
    for(int moving = 0; moving < aSize; moving++){
        if( sizeof(save) != sizeof(int))
           salida<<(int)(move[moving])<<" ";
        else
           salida<<move[moving]<<" ";
    }
}

//Assign global non-constant variables
void prepareGameVariation(int colors, int slots){
	COLORS = colors;
	SLOTS = slots;
	MAX = COLORS - 1;
	P_MOVES = pow((double)COLORS,(double)SLOTS);
	ANSWERS = answersArraySize(SLOTS);
	answersArray.reserve(ANSWERS);
	MAXTURNS = 15;
	assignAnswersVector(ANSWERS, answersArray);
}

//Select best first move to use in each different strategy
vector<save> prepareStrategy(string STRATEGY){
	int specificGame = (COLORS * 10) + SLOTS;
	vector<save> AMOVE(SLOTS,0);
	if (STRATEGY == "Worst-Case"){
		switch(specificGame){
	case 22:
		REMAINS  = 2;
		AMOVE[0]=A;
		AMOVE[1]=A;
			break;
	case 23:
		REMAINS  =3;
		AMOVE[0]=A;
		AMOVE[1]=A;
		AMOVE[2]=A;
			break;
	case 24:
		REMAINS  =4;
		AMOVE[0]=A;
		AMOVE[1]=A;
		AMOVE[2]=A;
		AMOVE[3]=B;
			break;
	case 25:
		REMAINS  =6;
		AMOVE[0]=A;
		AMOVE[1]=A;
		AMOVE[2]=A;
		AMOVE[3]=A;
		AMOVE[4]=B;
			break;
	case 32:
		REMAINS  =4;
		AMOVE[0]=A;
		AMOVE[1]=A;
			break;
	case 33:
		REMAINS  =6;
		AMOVE[0]=A;
		AMOVE[1]=A;
		AMOVE[2]=B;
			break;
	case 34:
		REMAINS  =15;
		AMOVE[0]=A;
		AMOVE[1]=A;
		AMOVE[2]=A;
		AMOVE[3]=B;
			break;
	case 35:
		REMAINS  =36;
		AMOVE[0]=A;
		AMOVE[1]=A;
		AMOVE[2]=A;
		AMOVE[3]=B;
		AMOVE[4]=B;
			break;
	case 42:
		REMAINS  =6;
		AMOVE[0]=A;
		AMOVE[1]=B;
			break;
	case 43:
		REMAINS  =15;
		AMOVE[0]=A;
		AMOVE[1]=B;
		AMOVE[2]=C;
			break;
	case 44:
		REMAINS  =46;
		AMOVE[0]=A;
		AMOVE[1]=A;
		AMOVE[2]=B;
		AMOVE[3]=C;
			break;
	case 45:
		REMAINS  =164;
		AMOVE[0]=A;
		AMOVE[1]=A;
		AMOVE[2]=A;
		AMOVE[3]=B;
		AMOVE[4]=C;
			break;
	case 52:
		REMAINS  =9;
		AMOVE[0]=A;
		AMOVE[1]=B;
			break;
	case 53:
		REMAINS  =30;
		AMOVE[0]=A;
		AMOVE[1]=B;
		AMOVE[2]=C;
			break;
	case 54:
		REMAINS  =120;
		AMOVE[0]=A;
		AMOVE[1]=A;
		AMOVE[2]=B;
		AMOVE[3]=B;
			break;
	case 55:
		REMAINS  = 510;
		AMOVE[0]=A;
		AMOVE[1]=A;
		AMOVE[2]=B;
		AMOVE[3]=B;
		AMOVE[4]=C;
			break;
	case 62:
		REMAINS  =16;
		AMOVE[0]=A;
		AMOVE[1]=B;
			break;
	case 63:
		REMAINS  =63;
		AMOVE[0]=A;
		AMOVE[1]=B;
		AMOVE[2]=C;
			break;
	case 64:
		REMAINS  = 256;
		AMOVE[0]=A;
		AMOVE[1]=A;
		AMOVE[2]=B;
		AMOVE[3]=B;
			break;
	case 65:
		REMAINS  =1303;
		AMOVE[0]=A;
		AMOVE[1]=A;
		AMOVE[2]=B;
		AMOVE[3]=C;
		AMOVE[4]=D;
			break;
	case 72:
		REMAINS  =25;
		AMOVE[0]=A;
		AMOVE[1]=B;
			break;
	case 73:
		REMAINS  =108;
		AMOVE[0]=A;
		AMOVE[1]=B;
		AMOVE[2]=C;
			break;
	case 74:
		REMAINS  =582;
		AMOVE[0]=A;
		AMOVE[1]=B;
		AMOVE[2]=C;
		AMOVE[3]=D;
			break;
	case 75:
		REMAINS  =3012;
		AMOVE[0]=A;
		AMOVE[1]=A;
		AMOVE[2]=B;
		AMOVE[3]=B;
		AMOVE[4]=C;
			break;
	case 82:
		REMAINS  =36;
		AMOVE[0]=A;
		AMOVE[1]=B;
			break;
	case 83:
		REMAINS  =165;
		AMOVE[0]=A;
		AMOVE[1]=B;
		AMOVE[2]=C;
			break;
	case 84:
		REMAINS  =976;
		AMOVE[0]=A;
		AMOVE[1]=B;
		AMOVE[2]=C;
		AMOVE[3]=D;
			break;
	case 85:
		REMAINS  =7051;
		AMOVE[0]=A;
		AMOVE[1]=A;
		AMOVE[2]=B;
		AMOVE[3]=C;
		AMOVE[4]=D;
			break;
	case 92:
		REMAINS  =49;
		AMOVE[0]=A;
		AMOVE[1]=B;
			break;
	case 93:
		REMAINS  =234;
		AMOVE[0]=A;
		AMOVE[1]=B;
		AMOVE[2]=C;
			break;
	case 94:
		REMAINS  =1820;
		AMOVE[0]=A;
		AMOVE[1]=B;
		AMOVE[2]=C;
		AMOVE[3]=D;
			break;

			default:
				cout<<"ERROR in prepareStrategy"<<endl;
	   }
	}
	else if (STRATEGY == "Most-Parts"){
		switch(specificGame){
	case 22:
		REMAINS = 2;
		AMOVE[0]=A;
		AMOVE[1]=A;
			break;
	case 23:
		REMAINS = 3;
		AMOVE[0]=A;
		AMOVE[1]=A;
		AMOVE[2]=B;
			break;
	case 24:
		REMAINS =4;
		AMOVE[0]=A;
		AMOVE[1]=A;
		AMOVE[2]=A;
		AMOVE[3]=B;
			break;
	case 25:
		REMAINS =6;
		AMOVE[0]=A;
		AMOVE[1]=A;
		AMOVE[2]=A;
		AMOVE[3]=A;
		AMOVE[4]=B;
			break;
	case 32:
		REMAINS =4;
		AMOVE[0]=A;
		AMOVE[1]=B;
			break;
	case 33:
		REMAINS =6;
		AMOVE[0]=A;
		AMOVE[1]=A;
		AMOVE[2]=B;
			break;
	case 34:
		REMAINS = 16;
		AMOVE[0]=A;
		AMOVE[1]=A;
		AMOVE[2]=B;
		AMOVE[3]=B;
			break;
	case 35:
		REMAINS =36;
		AMOVE[0]=A;
		AMOVE[1]=A;
		AMOVE[2]=A;
		AMOVE[3]=B;
		AMOVE[4]=B;
			break;
	case 42:
		REMAINS =6;
		AMOVE[0]=A;
		AMOVE[1]=B;
			break;
	case 43:
		REMAINS =15;
		AMOVE[0]=A;
		AMOVE[1]=B;
		AMOVE[2]=C;
			break;
	case 44:
		REMAINS =46;
		AMOVE[0]=A;
		AMOVE[1]=A;
		AMOVE[2]=B;
		AMOVE[3]=C;
			break;
	case 45:
		REMAINS =192;
		AMOVE[0]=A;
		AMOVE[1]=A;
		AMOVE[2]=B;
		AMOVE[3]=B;
		AMOVE[4]=C;
			break;
	case 52:
		REMAINS = 9;
		AMOVE[0]=A;
		AMOVE[1]=B;
			break;
	case 53:
		REMAINS =30;
		AMOVE[0]=A;
		AMOVE[1]=B;
		AMOVE[2]=C;
			break;
	case 54:
		REMAINS =120;
		AMOVE[0]=A;
		AMOVE[1]=A;
		AMOVE[2]=B;
		AMOVE[3]=C;
			break;
	case 55:
		REMAINS =510;
		AMOVE[0]=A;
		AMOVE[1]=A;
		AMOVE[2]=B;
		AMOVE[3]=B;
		AMOVE[4]=C;
			break;
	case 62:
		REMAINS =16;
		AMOVE[0]=A;
		AMOVE[1]=B;
			break;
	case 63:
		REMAINS =63;
		AMOVE[0]=A;
		AMOVE[1]=B;
		AMOVE[2]=C;
			break;
	case 64:
		REMAINS = 276;
		AMOVE[0]=A;
		AMOVE[1]=A;
		AMOVE[2]=B;
		AMOVE[3]=C;
			break;
	case 65:
		REMAINS =1360;
		AMOVE[0]=A;
		AMOVE[1]=A;
		AMOVE[2]=B;
		AMOVE[3]=B;
		AMOVE[4]=C;
			break;
	case 72:
		REMAINS =25;
		AMOVE[0]=A;
		AMOVE[1]=B;
			break;
	case 73:
		REMAINS =108;
		AMOVE[0]=A;
		AMOVE[1]=B;
		AMOVE[2]=C;
			break;
	case 74:
		REMAINS =616;
		AMOVE[0]=A;
		AMOVE[1]=A;
		AMOVE[2]=B;
		AMOVE[3]=C;
			break;
	case 75:
		REMAINS =3012;
		AMOVE[0]=A;
		AMOVE[1]=A;
		AMOVE[2]=B;
		AMOVE[3]=B;
		AMOVE[4]=C;
			break;
	case 82:
		REMAINS =36;
		AMOVE[0]=A;
		AMOVE[1]=B;
			break;
	case 83:
		REMAINS =165;
		AMOVE[0]=A;
		AMOVE[1]=B;
		AMOVE[2]=C;
			break;
	case 84:
		REMAINS =1160;
		AMOVE[0]=A;
		AMOVE[1]=A;
		AMOVE[2]=B;
		AMOVE[3]=C;
			break;
	case 85:
		REMAINS =7105;
		AMOVE[0]=A;
		AMOVE[1]=A;
		AMOVE[2]=B;
		AMOVE[3]=B;
		AMOVE[4]=C;
			break;
	case 92:
		REMAINS =49;
		AMOVE[0]=A;
		AMOVE[1]=B;
			break;
	case 93:
		REMAINS =234;
		AMOVE[0]=A;
		AMOVE[1]=B;
		AMOVE[2]=C;
			break;
	case 94:
		REMAINS =1956;
		AMOVE[0]=A;
		AMOVE[1]=A;
		AMOVE[2]=B;
		AMOVE[3]=C;
			break;
	default:
		cout<<"ERROR in prepareStrategy"<<endl;
       }
	  }
   else if (STRATEGY == "Expected"){
	   switch(specificGame){
	case 22: 
		REMAINS= 2;
		AMOVE[0] =0;
		AMOVE[1] =0;
		break;
	case 23: 
		REMAINS= 3;
		AMOVE[0] =0;
		AMOVE[1] =0;
		AMOVE[2] =1;
		break;
	case 24: 
		REMAINS= 4;
		AMOVE[0] =0;
		AMOVE[1] =0;
		AMOVE[2] =0;
		AMOVE[3] =1;
		break;
	case 25: 
		REMAINS= 6;
		AMOVE[0] =0;
		AMOVE[1] =0;
		AMOVE[2] =0;
		AMOVE[3] =0;
		AMOVE[4] =1;
		break;
	case 32: 
		REMAINS= 4;
		AMOVE[0] =0;
		AMOVE[1] =1;
		break;
	case 33: 
		REMAINS= 6;
		AMOVE[0] =0;
		AMOVE[1] =0;
		AMOVE[2] =1;
		break;
	case 34: 
		REMAINS= 16;
		AMOVE[0] =0;
		AMOVE[1] =0;
		AMOVE[2] =1;
		AMOVE[3] =1;
		break;
	case 35: 
		REMAINS= 36;
		AMOVE[0] =0;
		AMOVE[1] =0;
		AMOVE[2] =0;
		AMOVE[3] =1;
		AMOVE[4] =2;
		break;
	case 42: 
		REMAINS= 6;
		AMOVE[0] =0;
		AMOVE[1] =1;
		break;
	case 43: 
		REMAINS= 15;
		AMOVE[0] =0;
		AMOVE[1] =1;
		AMOVE[2] =2;
		break;
	case 44: 
		REMAINS= 46;
		AMOVE[0] =0;
		AMOVE[1] =0;
		AMOVE[2] =1;
		AMOVE[3] =2;
		break;
	case 45: 
		REMAINS= 192;
		AMOVE[0] =0;
		AMOVE[1] =0;
		AMOVE[2] =1;
		AMOVE[3] =1;
		AMOVE[4] =2;
		break;
	case 52: 
		REMAINS= 9;
		AMOVE[0] =0;
		AMOVE[1] =1;
		break;
	case 53: 
		REMAINS= 30;
		AMOVE[0] =0;
		AMOVE[1] =1;
		AMOVE[2] =2;
		break;
	case 54: 
		REMAINS= 120;
		AMOVE[0] =0;
		AMOVE[1] =0;
		AMOVE[2] =1;
		AMOVE[3] =2;
		break;
	case 55: 
		REMAINS= 510;
		AMOVE[0] =0;
		AMOVE[1] =0;
		AMOVE[2] =1;
		AMOVE[3] =1;
		AMOVE[4] =2;
		break;
	case 62: 
		REMAINS= 16;
		AMOVE[0] =0;
		AMOVE[1] =1;
		break;
	case 63: 
		REMAINS= 63;
		AMOVE[0] =0;
		AMOVE[1] =1;
		AMOVE[2] =2;
		break;
	case 64: 
		REMAINS= 276;
		AMOVE[0] =0;
		AMOVE[1] =0;
		AMOVE[2] =1;
		AMOVE[3] =2;
		break;
	case 65: 
		REMAINS= 1360;
		AMOVE[0] =0;
		AMOVE[1] =0;
		AMOVE[2] =1;
		AMOVE[3] =1;
		AMOVE[4] =2;
		break;
	case 72: 
		REMAINS= 25;
		AMOVE[0] =0;
		AMOVE[1] =1;
		break;
	case 73: 
		REMAINS= 108;
		AMOVE[0] =0;
		AMOVE[1] =1;
		AMOVE[2] =2;
		break;
	case 74: 
		REMAINS= 582;
		AMOVE[0] =0;
		AMOVE[1] =1;
		AMOVE[2] =2;
		AMOVE[3] =3;
		break;
	case 75: 
		REMAINS= 3011;
		AMOVE[0] =0;
		AMOVE[1] =0;
		AMOVE[2] =1;
		AMOVE[3] =1;
		AMOVE[4] =2;
		break;
	case 82: 
		REMAINS= 36;
		AMOVE[0] =0;
		AMOVE[1] =1;
		break;
	case 83: 
		REMAINS= 165;
		AMOVE[0] =0;
		AMOVE[1] =1;
		AMOVE[2] =2;
		break;
	case 84: 
		REMAINS= 976;
		AMOVE[0] =0;
		AMOVE[1] =1;
		AMOVE[2] =2;
		AMOVE[3] =3;
		break;
	case 85: 
		REMAINS= 7051;
		AMOVE[0] =0;
		AMOVE[1] =0;
		AMOVE[2] =1;
		AMOVE[3] =2;
		AMOVE[4] =3;
		break;
	case 92: 
		REMAINS= 49;
		AMOVE[0] =0;
		AMOVE[1] =1;
		break;
	case 93: 
		REMAINS= 234;
		AMOVE[0] =0;
		AMOVE[1] =1;
		AMOVE[2] =2;
		break;
	case 94: 
		REMAINS= 1820;
		AMOVE[0] =0;
		AMOVE[1] =1;
		AMOVE[2] =2;
		AMOVE[3] =3;
		break;

	default:
		cout<<"ERROR in prepareStrategy"<<endl;
      }
	}

	else if (STRATEGY == "Entropy"){
		switch(specificGame){
	case 22: 
		REMAINS= 2;
		AMOVE[0] =0;
		AMOVE[1] =0;
		break;
	case 23: 
		REMAINS= 3;
		AMOVE[0] =0;
		AMOVE[1] =0;
		AMOVE[2] =1;
		break;
	case 24: 
		REMAINS= 4;
		AMOVE[0] =0;
		AMOVE[1] =0;
		AMOVE[2] =0;
		AMOVE[3] =1;
		break;
	case 25: 
		REMAINS= 6;
		AMOVE[0] =0;
		AMOVE[1] =0;
		AMOVE[2] =0;
		AMOVE[3] =0;
		AMOVE[4] =1;
		break;
	case 32: 
		REMAINS= 4;
		AMOVE[0] =0;
		AMOVE[1] =1;
		break;
	case 33: 
		REMAINS= 6;
		AMOVE[0] =0;
		AMOVE[1] =0;
		AMOVE[2] =1;
		break;
	case 34: 
		REMAINS= 16;
		AMOVE[0] =0;
		AMOVE[1] =0;
		AMOVE[2] =1;
		AMOVE[3] =1;
		break;
	case 35: 
		REMAINS= 36;
		AMOVE[0] =0;
		AMOVE[1] =0;
		AMOVE[2] =0;
		AMOVE[3] =1;
		AMOVE[4] =2;
		break;
	case 42: 
		REMAINS= 6;
		AMOVE[0] =0;
		AMOVE[1] =1;
		break;
	case 43: 
		REMAINS= 15;
		AMOVE[0] =0;
		AMOVE[1] =1;
		AMOVE[2] =2;
		break;
	case 44: 
		REMAINS= 46;
		AMOVE[0] =0;
		AMOVE[1] =0;
		AMOVE[2] =1;
		AMOVE[3] =2;
		break;
	case 45: 
		REMAINS= 192;
		AMOVE[0] =0;
		AMOVE[1] =0;
		AMOVE[2] =1;
		AMOVE[3] =1;
		AMOVE[4] =2;
		break;
	case 52: 
		REMAINS= 9;
		AMOVE[0] =0;
		AMOVE[1] =1;
		break;
	case 53: 
		REMAINS= 30;
		AMOVE[0] =0;
		AMOVE[1] =1;
		AMOVE[2] =2;
		break;
	case 54: 
		REMAINS= 120;
		AMOVE[0] =0;
		AMOVE[1] =0;
		AMOVE[2] =1;
		AMOVE[3] =2;
		break;
	case 55: 
		REMAINS= 510;
		AMOVE[0] =0;
		AMOVE[1] =0;
		AMOVE[2] =1;
		AMOVE[3] =1;
		AMOVE[4] =2;
		break;
	case 62: 
		REMAINS= 16;
		AMOVE[0] =0;
		AMOVE[1] =1;
		break;
	case 63: 
		REMAINS= 63;
		AMOVE[0] =0;
		AMOVE[1] =1;
		AMOVE[2] =2;
		break;
	case 64: 
		REMAINS= 312;
		AMOVE[0] =0;
		AMOVE[1] =1;
		AMOVE[2] =2;
		AMOVE[3] =3;
		break;
	case 65: 
		REMAINS= 1360;
		AMOVE[0] =0;
		AMOVE[1] =0;
		AMOVE[2] =1;
		AMOVE[3] =1;
		AMOVE[4] =2;
		break;
	case 72: 
		REMAINS= 25;
		AMOVE[0] =0;
		AMOVE[1] =1;
		break;
	case 73: 
		REMAINS= 108;
		AMOVE[0] =0;
		AMOVE[1] =1;
		AMOVE[2] =2;
		break;
	case 74: 
		REMAINS= 582;
		AMOVE[0] =0;
		AMOVE[1] =1;
		AMOVE[2] =2;
		AMOVE[3] =3;
		break;
	case 75: 
		REMAINS= 3402;
		AMOVE[0] =0;
		AMOVE[1] =0;
		AMOVE[2] =1;
		AMOVE[3] =2;
		AMOVE[4] =3;
		break;
	case 82: 
		REMAINS= 36;
		AMOVE[0] =0;
		AMOVE[1] =1;
		break;
	case 83: 
		REMAINS= 165;
		AMOVE[0] =0;
		AMOVE[1] =1;
		AMOVE[2] =2;
		break;
	case 84: 
		REMAINS= 976;
		AMOVE[0] =0;
		AMOVE[1] =1;
		AMOVE[2] =2;
		AMOVE[3] =3;
		break;
	case 85: 
		REMAINS= 7051;
		AMOVE[0] =0;
		AMOVE[1] =0;
		AMOVE[2] =1;
		AMOVE[3] =2;
		AMOVE[4] =3;
		break;
	case 92: 
		REMAINS= 49;
		AMOVE[0] =0;
		AMOVE[1] =1;
		break;
	case 93: 
		REMAINS= 234;
		AMOVE[0] =0;
		AMOVE[1] =1;
		AMOVE[2] =2;
		break;
	case 94: 
		REMAINS= 1820;
		AMOVE[0] =0;
		AMOVE[1] =1;
		AMOVE[2] =2;
		AMOVE[3] =3;
		break;

	default:
		cout<<"ERROR in prepare Strategy"<<endl;
		}
	}

	return AMOVE;
}
