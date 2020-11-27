#ifndef CHALLENGET
#define CHALLENGET

#include <string>
#include "playerT.h"

class ChallengeT {
    public:
        ChallengeT(void);
        void SetName(std::string n);
        void SetDescription(std::string des);
        void SetCash(int a);
        void SetLevel(int a);
        void SetDamage(int a);
        void SetExperience(int a);
        void SetAttribute(std::string word);

        void Level(int l);
        int Level(void) const;
        std::string GetName();
        std::string GetDescription();
        int GetCash();
        int GetLevel();
        int GetDamage();
        int GetExperience();
        std::string GetAttribute();


    private:
        std::string name;
        std::string description;
        std::string attribute;
        int damage = 0;
        int level = 0;
        int cash = 0;
        int attNum = 0;
        int experience = 0;
};

void PrintChallenge(const ChallengeT  & challenge);

#endif 
