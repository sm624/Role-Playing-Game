#ifndef PLAYERT
#define PLAYERT
#include "ChallengeT.h"
#include <string>

class PlayerT {
    public:
        PlayerT(void);
        void SetName(std::string n);
        void SetDescription(std::string desc);
        void SetBeef(int a);
        void SetBrains(int a);
        void SetHammer(int a);
        void SetCoruba(int a);
        void SetHP(int a);
        void SetMaxHP(int a);
        void SetNumHD(int a);
        void SetValHD(int a);
        void SetLevel(int a);
        void SetExp(int a);
        void SetCash(int a);
        void SetWeapon(std::string word);
        void SetWeaponDescription(std::string word);

        std::string GetName();
        int GetBeef();
        int GetHammer();
        int GetCoruba();
        int GetBrains();
        int GetLevel();
        int GetMoney();
        int GetDamage();
        int GetHitpoints();
        int GetMaxHitpoints();
        int GetExperience();

        bool CheckHitpoints();
        int ChangeWeaponToInt(std::string weapon);
        void LevelUp();
        int AddAttribute(int choice);
        int ChangeHitPoints(int damage);
        void DefeatsOpponent(PlayerT &player, PlayerT &opponent);
        bool DoChallenge(ChallengeT &challenge);
        void CompleleteChallenge(ChallengeT &challenge);
        void Attack(PlayerT &player, PlayerT &opponent);
        void SetDamage(std::string weapon);
        int CalculateDamage();
        int CombatTable(int combat);
        int AttributeBonus(int attribute);
        int RollDie(int dice, int sides);
        void FailedChallenge(ChallengeT &challenge);
        int CombatTable(int hammer, int damage, PlayerT &player);
        int ConvertAttributeStringToInteger(std::string attribute);
        int ConvertAttributeToInteger(int attribute);
        void BrokeWeapon();
        int ReturnCombatToRange(int combat);
        void PrintInventory();
        int Rest(int restSleep);
    private:
        std::string name;
        std::string weapon;
        std::string weaponDesc;
        int weaponDam = 0;
        int level = 0;
        int beef = 0;
        int brains = 0;
        int hammer = 0;
        int coruba = 0;
        int hitPoints = 0;
        int maxHitPoints = 0;
        int experience = 0;
        int cash = 0;
        int damage = 0;
        int hitDice = 0;
        int hitValue = 0;
        int hitOrMiss = 0;
        bool nearMiss = false;
        bool badMiss = false;
};

#endif