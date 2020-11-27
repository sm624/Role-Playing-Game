#include <fstream>
#include <iostream>
#include "playerT.cpp"
#include "ChallengeT.cpp"

using namespace std;

const int OPP_SIZE = 10;
const int CHAL_SIZE = 10;
const int SLEEP = 30;
const int REST = 10;

void OpenFile(ifstream &loadFile);
void LoadPlayer(ifstream &loadFile, PlayerT &player);
string SeptLine(string &line, size_t &i, size_t &k, size_t &j);
void SetPlayer(int control, string word, PlayerT &player);
void LoadEncounters(ifstream &loadFile, int &encounters);
void LoadChallenge(ifstream &loadFile, ChallengeT &challenge);
bool DoTheChallenge(PlayerT &player, ChallengeT &challenge);
string StringToLower(string word);
void Execute(size_t &chalSize, size_t &oppSize, int encounters, PlayerT &player, PlayerT opponentsArray[], ChallengeT chalArray[]);
bool FightOpponent(PlayerT &player, PlayerT &opponent);
void Battle(PlayerT &player, PlayerT &opponent);
void OutputChallenge(ChallengeT &challenge);
void OutputOpponent(PlayerT &opponent);
bool Choice(PlayerT &player, size_t &chalSize, size_t &oppSize, PlayerT opponentsArray[], ChallengeT chalArray[], int control);
void CheckLevelUp(PlayerT &player);
void Map(size_t &chalSize, size_t &oppSize, PlayerT opponentsArray[], ChallengeT chalArray[], int control);

int main(){
    int encounters;
    size_t chalSize =0, oppSize =0;
    ifstream loadFile;
    PlayerT player, opponent;
    ChallengeT challenge;
    PlayerT opponentsArray[OPP_SIZE];
    ChallengeT chalArray[CHAL_SIZE];
    OpenFile(loadFile);
    LoadPlayer(loadFile, player); //loads player
    LoadEncounters(loadFile, encounters); //loads encounters
    while(loadFile){
        LoadPlayer(loadFile, opponent); //loads opponent
        opponentsArray[oppSize] = opponent;
        oppSize++;
        LoadChallenge(loadFile, challenge); //loads challenge
        chalArray[chalSize] = challenge;
        chalSize++;
    }
    Execute(chalSize, oppSize, encounters, player, opponentsArray, chalArray); //high level loop for adventure
    return 0;
}
//high level execution of encounters
void Execute(size_t &chalSize, size_t &oppSize, int encounters, PlayerT &player, PlayerT opponentsArray[], ChallengeT chalArray[]){
    bool oppDefeated = true; //true if opponent is defeated, false if otherwise
    bool chalCompleted = true;
    PlayerT opponent;
    ChallengeT challenge;
    int control = 0;
    chalSize--;
    oppSize--;
    while(control != encounters){
        opponent = opponentsArray[control];
        oppDefeated = FightOpponent(player, opponent);
        if(oppDefeated){
            challenge = chalArray[control];
            chalCompleted = DoTheChallenge(player, challenge);
            if(!chalCompleted && !player.CheckHitpoints()){
                break;
            }
            CheckLevelUp(player);
        }
        else if(!player.CheckHitpoints()){
            cout << "Your adventure is over." << endl;
            break;
        }
        control++;
        if(!Choice(player, chalSize, oppSize, opponentsArray, chalArray, control)){
            break;
        }
    }
  
    return;
}
//choice returns true if player continues, false if player resigns
bool Choice(PlayerT &player, size_t &chalSize, size_t &oppSize, PlayerT opponentsArray[], ChallengeT chalArray[], int control){
    int choice, health=0;
    bool advance = true;
    cout << endl << endl;
    while(choice != 1 || choice != 2){
        cout << endl << "You've found a quiet spot to relax. What would you like to do?" << endl;
        cout << "Advance = 1" << endl;
        cout << "Resign = 2" << endl;
        cout << "Rest = 3" << endl;
        cout << "Sleep = 4" << endl;
        cout << "Inventory = 5" << endl;
        cout << "Look = 6" << endl << endl;
        cout << "=>";
        cin >> choice;
        cout << endl;

        switch(choice){
            case 1:
                cout << "You've chosen to continue on your path!" << endl << endl;
                return advance;
            case 2:
                cout << "You've chosen to end your journey." << endl;
                advance = false;
                return advance;
            case 3:
                cout << "You've chosen to rest." << endl;
                health = player.Rest(REST);
                cout << "You've recovered " << health << " hitpoints in your rest." << endl;
                cout << "You now have " << player.GetHitpoints() << "/" << player.GetMaxHitpoints() << " hitpoints." << endl;
                break;
            case 4:
                cout << "You've chosen to sleep." << endl;
                health = player.Rest(SLEEP);
                cout << "You've recovered " << health << " hitpoints in your sleep." << endl;
                cout << "You now have " << player.GetHitpoints() << "/" << player.GetMaxHitpoints() << " hitpoints." << endl;
                break;
            case 5:
                cout << "You wish to look through your things, here is what you found: " << endl;
                player.PrintInventory();
                break;
            case 6:
                cout << "You open your map to see what lies next in your adventure, here is what you see:" << endl;
                Map(chalSize, oppSize, opponentsArray, chalArray, control);
                break;
        }
    }
}
//opens data file
void OpenFile(ifstream &loadFile){
    string name;

    cout << "Please enter the load file name ->";
    cin >> name;
    cout << endl;
    loadFile.open(name);

    return;
}
//loads PlayerT
void LoadPlayer(ifstream &loadFile, PlayerT &player){
    string line, word; //these are generic because i reuse the same variable to save space
    size_t i=0, j=0, k=0;
    int control = 0;

    getline(loadFile, line); 
    while(control != 13){ //14 values to be assigned
        word = SeptLine(line, i, k, j);
        SetPlayer(control, word, player);
        control++;
    }
    word = line.substr(i,k);
    SetPlayer(control, word, player); //this is the 14th value

    return;
}
//Sets values given to appropriate areas in PlayerT
void SetPlayer(int control, string word, PlayerT &player){
    switch(control){
        case 0:
            player.SetName(word);
            break;
        case 1:
            player.SetBeef(atoi(word.c_str()));
            break;
        case 2:
            player.SetBrains(atoi(word.c_str()));
            break;
        case 3:
            player.SetHammer(atoi(word.c_str()));
            break;
        case 4:
            player.SetCoruba(atoi(word.c_str()));
            break;
        case 5:
            player.SetHP(atoi(word.c_str()));
            break;
        case 6:
            player.SetMaxHP(atoi(word.c_str()));
            break;
        case 7:
            player.SetNumHD(atoi(word.c_str()));
            break;
        case 8:
            player.SetValHD(atoi(word.c_str()));
            break;
        case 9:
            player.SetLevel(atoi(word.c_str()));
            break;
        case 10:
            player.SetExp(atoi(word.c_str()));
            break;
        case 11:
            player.SetCash(atoi(word.c_str()));
            break;
        case 12:
            word = StringToLower(word);
            player.SetWeapon(word);
            break;
        default:
            player.SetWeaponDescription(word);
    }   
  
    return;
}
//separtates line from file
string SeptLine(string &line, size_t &i, size_t &k, size_t &j){
    string word;
    
    for(; i<line.size(); i++){
        if(ispunct(line[i])){
            j = i-k; 
            word = line.substr(k,j);   
            i++;
            k=i;
            break;
        }
    }

    return word;
}
//gets the encounters from data file
void LoadEncounters(ifstream &loadFile, int &encounters){
    string line;
    getline(loadFile, line);
    encounters = atoi(line.c_str());

    return;
}
//Loads the challenges from file to ChallengeT
void LoadChallenge(ifstream &loadFile, ChallengeT &challenge){
    string line, word;
    int control=0;
    size_t i=0, j=0, k=0;

    getline(loadFile, line); //name
    challenge.SetName(line);
    getline(loadFile, line); //description
    challenge.SetDescription(line);
    getline(loadFile, line); //attributes and such

    while(control != 4){
        word = SeptLine(line, i, k, j);
        switch(control){
            case 0:
                word = StringToLower(word);
                challenge.SetAttribute(word);
                break;
            case 1:
                challenge.SetLevel(atoi(word.c_str()));
                break;
            case 2:
                challenge.SetDamage(atoi(word.c_str()));
                break;
            case 3:
                challenge.SetExperience(atoi(word.c_str()));
                break;
        }
        control++;
    }
    word = line.substr(i,k);
    challenge.SetCash(atoi(word.c_str()));

    return;
}
//Will do the calculations, Battle will do the actual damage and health checking
bool FightOpponent(PlayerT &player, PlayerT &opponent){
    bool returnVal = true; //true if opponent is defeated, false otherwise
    bool controlVal = true;
    OutputOpponent(opponent);
    while(controlVal){
        if(opponent.CheckHitpoints()){ //i added this because opponents would kill themselves and then the player would attack.
            Battle(player, opponent); //player attacks
        }
        if (opponent.CheckHitpoints()){
            Battle(opponent, player); //if opponent not dead, opponent attacks
            if(!player.CheckHitpoints()){
                returnVal = false;
                break; 
            }
        }
        else{
            cout << opponent.GetName() << " has been defeated!" << endl;
            player.DefeatsOpponent(player, opponent);
            break;
        }
    }
    return returnVal;
}
//Outputs opponents name and message
void OutputOpponent(PlayerT &opponent){
    cout << "Looks like " << opponent.GetName() << " wants to fight!" << endl;

    return;
}
//outputs challenge and details about challenge
void OutputChallenge(ChallengeT &challenge){
    cout << "Theres a " << challenge.GetName() << " in your path!" << endl;
    cout << "It will require " << challenge.GetLevel() << " " << challenge.GetAttribute() << " to get passed it!" << endl;
    cout << "You rolled a ";
    return;
}
//in this function, player will always attack opponent. when opponent's turn to attack player, I pass opponent as player and player as the opponent
void Battle(PlayerT &player, PlayerT &opponent){
    cout << player.GetName() << " attacks and does ";
    player.Attack(player, opponent);
    return;
}
//high level execution of challenge
bool DoTheChallenge(PlayerT &player, ChallengeT &challenge){
    bool returnVal = true;
    cout << endl << endl;
    OutputChallenge(challenge);
    returnVal = player.DoChallenge(challenge);

    return returnVal;
}
//takes string and returns same string with all lowercase letters
string StringToLower(string word){
    size_t i;

    for(i=0; i<word.size(); i++){
        word[i] = static_cast<char>(tolower(word[i]));
    }
    
    return word;
}
//checks for level up, continues looping until there are no more levels to be upped
void CheckLevelUp(PlayerT &player){
    int choice = 0, levelUp = player.GetLevel();
    levelUp *= levelUp; //effectively squaring it

    while(player.GetExperience() >= levelUp){
        player.LevelUp();
        cout << endl << "Congratulations! You've leveled up!" << endl;
        cout << "You are now level " << player.GetLevel() << "!" << endl;
        cout << "Which attribute would you like to increase?" << endl << endl;
        cout << "1 - Beef: " << player.GetBeef() << endl;
        cout << "2 - Brains: " << player.GetBrains() << endl;
        cout << "3 - Hammer: " << player.GetHammer() << endl;
        cout << "4 - Coruba: " << player.GetCoruba() << endl << endl;
        cout << "=>";
        cin >> choice;
        choice = player.AddAttribute(choice);
        levelUp = player.GetLevel() * player.GetLevel();
    }

    return;
}
//goes through arrays to show player what challenges and opponents wait in his journey.
void Map(size_t &chalSize, size_t &oppSize, PlayerT opponentsArray[], ChallengeT chalArray[], int control){
    while(control != chalSize && control != oppSize){ 
        cout << "Opponent:" << endl;
        cout << opponentsArray[control].GetName() << endl;
        cout << "Level: " << opponentsArray[control].GetLevel() << endl << endl;
        cout << "Challenge:" << endl;
        cout << chalArray[control].GetName() << endl;
        cout << chalArray[control].GetDescription() << endl << endl;
        control++;
    }

    return;
}