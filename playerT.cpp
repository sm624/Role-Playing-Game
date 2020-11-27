#include "playerT.h"
#include <iostream>
#include "ChallengeT.h"

using namespace std;

PlayerT::PlayerT(){
    weapon = "None";
    weaponDesc = "Nothing";
    weaponDam = 0;
    level = 0;
    beef = 0;
    brains = 0;
    hammer = 0;
    coruba = 0;
    hitPoints = 0;
    maxHitPoints = 0;
    experience = 0;
    cash = 0;
    hitDice = 0;
    hitValue = 0;
    hitOrMiss = 0;
    nearMiss = false;
    badMiss = false;
}
void PlayerT::SetName(std::string n){
    name = n;
}
void PlayerT::SetBeef(int a){
    beef = a;
}
void PlayerT::SetBrains(int a){
    brains = a;
}
void PlayerT::SetHammer(int a){
    hammer = a;
}
void PlayerT::SetCoruba(int a){
    coruba = a;
}
void PlayerT::SetHP(int a){
    hitPoints = a;
}
void PlayerT::SetMaxHP(int a){
    maxHitPoints = a;
}
void PlayerT::SetNumHD(int a){
    hitDice = a;
}
void PlayerT::SetValHD(int a){
    hitValue = a;
}
void PlayerT::SetLevel(int a){
    level = a;
}
void PlayerT::SetExp(int a){
    experience = a;
}
void PlayerT::SetCash(int a){
    cash = a;
}
void PlayerT::SetWeapon(string word){
    weapon = word;
    PlayerT::SetDamage(weapon);
}
void PlayerT::SetDamage(string weap){
    int wep = ChangeWeaponToInt(weap);
    switch(wep){
        case 0:
            weaponDam = 0;
            break;
        case 1:
            weaponDam = 1;
            break;
        case 2:
            weaponDam = 2;
            break;
        case 3:
            weaponDam = 3;
            break;
        case 4:
            weaponDam = 4;
            break;
    }
}
bool PlayerT::CheckHitpoints(){
    if(hitPoints > 0){ //if not dead return true
        return true; 
    }
    else{
        return false; 
    }
}
int PlayerT::ChangeWeaponToInt(string weaponStr){
    int wep = -1;
    if(weaponStr == "none"){
        wep = 0; 
    }
    else if(weaponStr == "wimpy"){
        wep = 1;
    }
    else if(weaponStr == "normal"){
        wep = 2;
    }
    else if(weaponStr == "beefy"){
        wep = 3;
    }
    else if(weaponStr == "mega"){
        wep = 4;
    }
    return wep;
}
void PlayerT::SetWeaponDescription(string word){
    weaponDesc = word;
}
int PlayerT::GetHitpoints(){
    return hitPoints;
}
int PlayerT::GetMaxHitpoints(){
    return maxHitPoints;
}
string PlayerT::GetName(){
    return name;
}
int PlayerT::GetLevel(){
    return level;
}
int PlayerT::GetExperience(){
    return experience;
}
int PlayerT::GetBeef(){
    return beef;
}
int PlayerT::GetBrains(){
    return brains;
}
int PlayerT::GetHammer(){
    return hammer;
}
int PlayerT::GetCoruba(){
    return coruba;
}
int PlayerT::GetMoney(){
    return cash;
}
int PlayerT::GetDamage(){
    damage = PlayerT::CalculateDamage();
    return damage;
}
void PlayerT::LevelUp(){
    level++;
    hitPoints++;
    maxHitPoints++;
}
int PlayerT::AddAttribute(int choice){
    switch(choice){
        case 1:
            beef++;
            cout << "You're Beef is now: " << beef << endl;
            break;
        case 2:
            brains++;
            cout << "You're Brains is now: " << brains << endl;
            break;
        case 3:
            hammer++;
            cout << "You're Hammer is now: " << hammer << endl;
            break;
        case 4:
            coruba++;
            cout << "You're Coruba is now: " << coruba << endl;
            break;
        default:
            choice = 10; //this is so i can check for incorrect input
    }
    return choice;
}
int PlayerT::ChangeHitPoints(int dam){
    hitPoints -= dam;
    return hitPoints;
}
void PlayerT::DefeatsOpponent(PlayerT &player, PlayerT &opponent){ 
    char yOrN = 'a';
    experience++;
    if(opponent.weaponDam != 0){
        cout << "You look through your opponents things to find that they had " << opponent.GetMoney() << " cash and a weapon!" << endl;
        cout << "You pick up to examine the weapon, and due to your expansive knowledge of all 4 weapons in the world";
        cout << " you immediately realize that this is a " << opponent.weapon << "." << endl;
        cout << "It does " << opponent.weaponDam << " damage." << endl;
        cout << "Would you like to pick it up? Y or N?" << endl;
        cin >> yOrN;
        if(yOrN == 'Y' || yOrN == 'y'){
            cout << "You chose to take his weapon!" << endl;
            player.weaponDam = opponent.weaponDam;
            player.weapon = opponent.weapon;
            player.weaponDesc = opponent.weaponDesc;
        }
        else{
            cout << "You chose to leave his weapon." << endl;
        }
    }
    else{
        cout << "You look through your opponents things to find that he had " << opponent.GetMoney() << " cash, but no weapon." << endl;
    }
    cout << endl << "You took your opponents money, and carried on with your adventure." << endl << endl;
    player.cash += opponent.cash;
    if(player.cash > 1000){
        experience++;
    }
}
bool PlayerT::DoChallenge(ChallengeT &challenge){ //high level to do the challenge, not sure if this should have been more so in the main.cpp 
    int roll = RollDie(1, 12), combat = 0, total = challenge.GetLevel(); //combat = the die roll and attribute bonus, total = the challenge's total required attribute
    cout << roll << "!" << endl;
    string attribute = challenge.GetAttribute();
    int attri = ConvertAttributeStringToInteger(attribute); //so i can use switch
    switch(attri){
        case 0:
            attri = GetBeef();
            break;
        case 1:
            attri = GetBrains();
            break;
        case 2:
            attri = GetHammer();
            break;
        case 3:
            attri = GetCoruba();
            break;
    }
    attri = AttributeBonus(attri); //converts to the bonus between -4 and 4
    cout << "Your attribute bonus is " << attri << "!" << endl;
    combat = attri + roll;
    if(combat > total){ //im not sure if the player should win if they score an equal amount
        PlayerT::CompleleteChallenge(challenge);
        return true;
    }
    else{
        PlayerT::FailedChallenge(challenge);
        return false;
    }
}
void PlayerT::FailedChallenge(ChallengeT &challenge){
    int dam = challenge.GetDamage();
    PlayerT::ChangeHitPoints(dam);
    cout << "You've failed the challenge and have taken " << challenge.GetDamage() << " damage!" << endl;
}
void PlayerT::CompleleteChallenge(ChallengeT &challenge){
    cout << "You've completed the challenge!" << endl;
    experience += challenge.GetExperience();
}
void PlayerT::Attack(PlayerT &player, PlayerT &opponent){
    damage = PlayerT::CalculateDamage();
    if(damage > -17){
        if(player.nearMiss = true){
            damage--;
            player.nearMiss = false;
        }
        else if(player.badMiss = true){
            damage++;
            player.badMiss = false;
        }
        if(damage < 0){ //no negative damage
            damage = 0;
        }
        opponent.ChangeHitPoints(damage);
        cout << damage << " damage!" << endl;
    }
    else{
        switch(damage){
            case -17: //near miss
                cout << "no damage! It was a near miss!" << endl; 
                cout << "1 attack is subtracted from their opponents next attack!" << endl;
                opponent.nearMiss = true;
                break;
            case -18: 
                cout << "no damage! It was a bad miss!" << endl; 
                cout << "1 attack is added to their opponents next attack!" << endl;
                opponent.badMiss = true;
                break;
            case -19:
                cout << "no damage! Their weapon broke!" << endl;
                break;
            case -20: //kills self
                cout << "no damage! " << player.GetName() << " killed themself!" << endl;
                player.ChangeHitPoints(player.GetHitpoints());
                break;
            case -21: //instant kill
                damage = opponent.GetHitpoints();
                opponent.ChangeHitPoints(damage);
                cout << damage << " damage!" << endl;
                break;    
            }
    }
}
int PlayerT::CalculateDamage(){ //im not sure if using negative integers was the best way to deal with this, it may have been better
    int combat = AttributeBonus(hammer) + RollDie(1,12), dam = 0; //to use several booleans to determine if it was an instant kill or such
    dam = PlayerT::CombatTable(combat);
    if (dam > -17){ //if damage is not one of the special cases
        dam += PlayerT::AttributeBonus(beef);
        dam += weaponDam; 
    }
    return dam;
}
int PlayerT::ConvertAttributeToInteger(int attribute){ //this is so i can use the switch to determine the bonus
    if(attribute < 2){
        attribute = 0;
    }
    else if(attribute >= 3 && attribute <= 4){ 
        attribute = 4;
    }
    else if(attribute >= 5 && attribute <= 7){ 
        attribute = 5;
    }
    else if(attribute >= 8 && attribute <= 12){ 
        attribute = 8;
    }
    else if(attribute >= 13 && attribute <= 17){ 
        attribute = 13;
    }
    else if(attribute >= 18 && attribute <= 22){ 
        attribute = 18;
    }
    else if(attribute >= 23 && attribute <= 25){ 
        attribute = 23;
    }
    else if(attribute >= 26 && attribute <= 27){ 
        attribute = 26;
    }
    else if(attribute >= 28){ 
        attribute = 28;
    }
    return attribute;
}
int PlayerT::AttributeBonus(int attribute){ //converts attribute to one of these values and returns the bonus, i read online
    attribute = ConvertAttributeToInteger(attribute);//that you can do something like 1...2 and 2...7 in a switch and the compiler
    switch (attribute){ //will read it like all values between those numbers, but i figured it would be better if this compiled on every compiler
        case 0:
            return -4;
        case 3:
            return -3;
        case 5:
            return -2;
        case 8:
            return -1;
        case 13:
            return 0;
        case 18:
            return 1;
        case 23:
            return 2;
        case 26:
            return 3;
        case 28:
            return 4;
    }
    return -20;
}
int PlayerT::CombatTable(int combat){ //combat table that determines instant kills and such
    int attack = -2;
    combat = ReturnCombatToRange(combat);
    switch(combat){
        case 1: 
            attack = -20; //kill self
            break;
        case 2: 
            attack = -19; //Weapon broke
            PlayerT::BrokeWeapon();
            break;
        case 3: 
            attack = PlayerT::RollDie(2,4) * -1;
            break;
        case 4: 
            attack = -18; //Add 1 to opponent damage
            break;
        case 5: 
            attack = 0;
            break;
        case 6: 
            attack = -17; //Subtract 1 from opponent damage
            break;
        case 7: 
            attack = PlayerT::RollDie(1, 4);
            break;
        case 8: 
            attack = PlayerT::RollDie(2, 4);
            break;
        case 9: 
            attack = PlayerT::RollDie(2, 6);          
            break;
        case 10: 
            attack = PlayerT::RollDie(2, 8);
            break;
        case 11: 
            attack = PlayerT::RollDie(2, 10);
            break;
        case 12:
            attack = -21; //instant kill
            break; 
    }
    return attack;
}
int PlayerT::RollDie(int dice, int sides){ //rolls given amount of dice with the given amount of sides
    int control=0, result = 0;
    
    while(control < dice){
        result += rand() % sides + 1;
        control++;
    }

    return result;
}
int PlayerT::ConvertAttributeStringToInteger(string attribute){
    if(attribute == "beef"){ 
        return 0;
    }
    else if(attribute == "brains"){
        return 1;
    }
    else if(attribute == "hammer"){
        return 2;
    }
    else if(attribute == "coruba"){
        return 3;
    }

    return -1;
}
void PlayerT::BrokeWeapon(){ //sets weapon to nothing, called when weapon breaks in battle
    weaponDesc = "none";
    weapon = "nothing";
    weaponDam = 0;
}
int PlayerT::ReturnCombatToRange(int combat){ //combat is the hammer bonus + the 1D12 roll
    if(combat > 12){
        combat = 12;
    }
    else if (combat < 1){
        combat = 1;
    }
    return combat;
}
void PlayerT::PrintInventory(){
    cout << "Name: " << name << endl;
    cout << "Weapon: " << weapon << endl;
    cout << "Weapon description: " << weaponDesc << endl;
    cout << "Hitpoints: " << hitPoints << "/" << maxHitPoints << endl;
    cout << "Level: " << level << endl;
    cout << "Beef: " << beef << endl;
    cout << "Brains: " << brains << endl;
    cout << "Hammer: " << hammer << endl;
    cout << "Coruba: " << coruba << endl;
    cout << "Cash: " << cash << endl;
}
int PlayerT::Rest(int restSleep){
    int dif = maxHitPoints - hitPoints;

    if(dif > restSleep){
        dif = restSleep;
    }
    hitPoints += dif;

    return dif;
}