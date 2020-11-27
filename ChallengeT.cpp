#include <iostream>
#include "ChallengeT.h"

using namespace std;

ChallengeT::ChallengeT(){
    cash = 0;
    level = 0;
    damage = 0;
    attNum = 0;
    experience = 0;
}
void ChallengeT::SetName(string n){
    name = n;
}
void ChallengeT::SetDescription(string des){
    description = des;
}
void ChallengeT::SetCash(int a){
    cash = a;
}
void ChallengeT::SetLevel(int a){
    level = a;
}
void ChallengeT::SetDamage(int a){
    damage = a;
}
void ChallengeT::SetExperience(int a){
    experience = a;
}
void ChallengeT::SetAttribute(string word){
    attribute = word;
}
void ChallengeT::Level(int l){
    level = l;
}
int ChallengeT::Level(void) const{
    return level;
}
std::string ChallengeT::GetName(){
    return name;
}
std::string ChallengeT::GetDescription(){
    return description;
}
std::string ChallengeT::GetAttribute(){
    return attribute;
}
int ChallengeT::GetCash(){
    return cash;
}
int ChallengeT::GetLevel(){
    return level;
}
int ChallengeT::GetDamage(){
    return damage;
}
int ChallengeT::GetExperience(){
    return experience;
}
