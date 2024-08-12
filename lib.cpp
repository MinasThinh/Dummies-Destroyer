// #include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <cstdlib> 
#include <iomanip>
#include <windows.h>
#include <conio.h> 

using namespace std;

const int LEVEL_CAP = 100;
const int STAGE_CAP = 25;

struct passive_attributes {
    string Type;
    int QualityID;
    int Impact; // Damage
    float CC,CD,CR;
    int Cooldown;
    string Description;
};
struct equipment_attributes {
    int ID;
    int Level;
    int QualityID;
    int baseHP;
    int baseATK;
    int baseDEF;
    float baseCC;
    float baseCD;
    float baseCR;
};

struct user_passives_attrs {
    user_passives_attrs() : equippedSlot(0), available(0) {}
    int equippedSlot;
    bool available;
};

map<string,float> EQUIPMENT_INCREASE {
    {"HelmetHP",2.0}, {"HelmetDEF",1.0}, {"ChesplateHP",6.0}, {"ChesplateDEF",3.0}, {"BootsHP",4}, {"BootsDEF",2},
    {"SwordATK",7}, {"SwordCD",5}, {"AccessoryCC",0.2},{"AccessoryCD",5}
};

vector<string> HELMETS {
    "Empty","Starter Helmet", "Strip Helmet", "Tammer Helmet", "Hero Helmet","Godness Helmet", "Universe Helmet"
};
vector<string> CHESTPLATES {
    "Empty","Starter Chestplate", "Clora Chestplate", "Knight Chestplate", "Sparta Chestplate", "Godness Chestplate", "Universe Chestplate",
};
vector<string> BOOTS {
    "Empty","Starter Boots", "Trim Boots", "Icy Icy Boots", "Fire Tracker Boots", "Godness Boots", "Universe Boots",
};
vector<string> SWORDS {
    "Empty","Starter Sword", "Golden Sword", "Awkward Sword", "Darkness Sword", "Godness Sword", "Universe Sword",
};
vector<string> ACCESSORIES {
    "Empty","Starter Necklace", "Blue Eyes Necklace", "Dark Knight Necklace", "Orc King Necklace", "Godness Chain", "Universe Chain",
};

vector<string> GAME_TIPS {
    "(TRAIN) Punch dummy in the trainning area to get new equipments!",
    "(TRAIN) Punching dummy gains you EXP which can level you up!",
    "(UPGRADES) Upgrade Dummies to increase the number of dummy punched / turn",
    "(UPGRADES) Upgrade Gold Forge to increase the gold gained from forging equipments!",
    "(UPGRADES) Upgrade Lucky to increase the chance of drops!",
    "(UPGRADES) Make sure to upgrade stats to make you stronger!",
    "(SHOP) You can buy potions in shop!",
    "(CHALLENGES) Challenging monsters gains you EXP, and even strong equipments!",
    "(SETTINGS) You can toggle auto punch in settings!",
    "(TIPS) Quality DOES affect the equipment's stats!",
};
vector<string> STRENGTHUP_TIPS {
    "Punch dummies to get new equipments!",
    "Level up yourself by gainning EXP from challenging stages, punching dummies",
};
map<string,int> UPGRADES;
map<string,int> UPGRADES_LIM {
    {"Gold Forge", 3}, {"Lucky", 12}
};
map<string,string> UPGRADES_DESC {
    {"Gold Forge","Increase the gold gained for forging equipments"},
    {"Lucky","Increase the chance of equipment drops (quality)"}
};
map<string,vector<long long>> UPGRADES_PRICE {
    // name , {prices}
    {"Gold Forge", {5000,25000,100000,0}},
    {"Lucky", {2500,5000,10000,20000,50000,100000,200000,400000,1000000,2000000,0}}
};
struct shopitem_attributes {
    string type;
    int cost; // by gold
    int duration; // by milsecond
};
int ___1h = 36e5;
unordered_map<string, shopitem_attributes> SHOP_ITEMS {
    // 1 hour = 36e5
    {"Light Kick",             {"PASSIVE", 100, 0}},
    {"Serious Punch",          {"PASSIVE", 1000, 0}},
    {"Healing Pot",            {"PASSIVE", 5000, 0}},
    {"Trap Stricter",          {"PASSIVE", 20000, 0}},
    {"Darkness Explosion",     {"PASSIVE", 200000, 0}},
    {"Holy Blessing",          {"PASSIVE", 500000, 0}},
    {"Immuneness",             {"PASSIVE", 1000000, 0}},
    {"Holy Wave",              {"PASSIVE", 5000000, 0}},
    {"Titan Transformation",   {"PASSIVE", 100000000, 0}},
    {"Darkness Transformation",{"PASSIVE", 100000000, 0}},
    {"Assassin Transformation",{"PASSIVE", 100000000, 0}},
    {"Domain Expansion",       {"PASSIVE", 2000000000, 0}},
};
vector<string> SHOP_ITEMS_LIST {
    "Light Kick","Serious Punch","Healing Pot","Trap Stricter","Darkness Explosion","Holy Blessing","Immuneness","Holy Wave","Titan Transformation","Darkness Transformation","Assassin Transformation","Domain Expansion",
};
map<string,pair<int,int>> SHOP_ITEMS_LIST_PHASES {
    {"PASSIVE", {0,11}},
};

vector<string> equipmentList 
{"Helmet","Chestplate","Boots","Sword","Accessory"};
vector<string> EquipmentQualities 
{"General","Starter","Common","Uncommon","Rare","Epic","Ultra","Legendary","Mythical","Holy","SUPREME"};
vector<string> PassiveQualities {
    "General","R","SR","SSR","S","SS","SSS","Holy","Supreme","GODLY",
};
vector<int> EQ_Qualities_Buff {0,1,2,3,4,5,7,10,15,20,50};
unordered_map<string,vector<string>> EQUIP_MAPS {
    {"Helmet", HELMETS}, {"Chestplate", CHESTPLATES}, {"Boots", BOOTS}, {"Sword", SWORDS}, {"Accessory", ACCESSORIES}
};
map<string,passive_attributes> PASSIVE_LIST {
    // if Impact < 0 then number will be -number%
    // if Impact is 32767, thats mean if its CC -> guaranted crit, ATK -> 1 shot, HP -> full HP, CD -> + 1000% CD
    // ,CR: bypass CR
    // 0      1           2        3    4    5    6          7
    // type - qualityid - impact - cc - cd - cr - cooldown - desc
    {"Light Kick",{"DMG",1, 50, 0, 0, 0, 2, "Kick a huge light, deals 50 damage"}},
    {"Serious Punch",{"DMG",2, 200, 10.0, 100.0, 25.0, 3, "Punch and release a strong wave, deals 200 damage, has a 10% (-25% CR) chance to deal 200% damage"}},
    {"Healing Pot",{"HEAL+-10",2,0, 0, 0, 0, 3, "Create a pot that heals you 10% HP"}},
    {"Trap Stricter",{"DMG",3, 500, 15.0, 150.0, 25.0, 5, "Place traps everywhere, explode will deals 500 damage, has a 15% (-25% CR) chance to deal 250% damage"}},
    {"Darkness Explosion",{"DMG",4, 2500, 20.0, 200.0, 30.0, 7, "Create a big dark explosion, causes 2500 damage, has a 20% (-30% CR) chance to deal 300% damage"}},
    {"Holy Blessing", {"HEAL+-30",5, 0, 0, 0, 0, 8, "Create a blessing area, heals you 30% HP"}},
    {"Immuneness",{"STUN+2", 6, 3, 0, 0, 0, 5, "Stun enemy for 2 turn"}},
    {"Holy Wave",{"DMG|STUN+3", 7, 50000, 30.0, 500.0, 50.0, 10, "Create a massive wave, stun enemy for 3 turn and deals 50000 damage, has a 30% (-50% CR) chance to deal 600% damage"}},
    {"Titan Transformation",{"BUFF+DEF+-200", 8, 0, 0, 0, 0, 10, "Transform to titan form, gains +200% DEF for 2 turns"}},
    {"Darkness Transformation",{"BUFF+ATK+-100", 8, 0, 0, 0, 0, 10, "Transform to darkness form, gains +100% ATK for 2 turns"}},
    {"Assassin Transformation", {"BUFF+CC+32767",8,0 , 0, 0, 0, 10, "Transform to assassin form, next attack will be a guaranted crit."}},
    {"Domain Expansion",{"DMGPT+2+100000",9, 0, 50.0, 1000, 100, 20, "Activate an expansion, everywhere turns to darkness for 2 turns, every turn, enemy will get 100000 damage, has a 50% (-100% CR) chance to deal 1100% damage"}},
    {"Goblin Slam", {"DMG", 3, 100, 0, 0, 0, 3, "Use weapon to slam enemy, deal 100 damage to enemy"}},
    {"Orc Destruction", {"DMG",4, 200, 0, 0, 0, 4, "Activate Orc's specical destruct ability, deal 200 damage to enemy"}},
    {"Wolf Claw",{"DMG",3, 100, 10.0, 50.0, 10.0, 2, "Use wolf's claw to attack enemy, deals 100 damage, has a 10 (-10 %CR) to deal 150% damage"}},
    {"Wolf Roaw",{"DMG|HEAL+-20|BUFF+ATK+-20", 3, 200, 10.0, 50.0, 20.0, 5, "Init a large roaw to the enemy, caster will heal 20% HP and gain 20% ATK for 2 turns, roaw deals 200 damage, has a 10% (-20% CR) chance to deal 150% damage"}},
    {"Wolf Shield",{"BUFF+DEF+-50%|HEAL+-20%", 4, 0, 0, 0, 0, 5, "Cast a large-area skill which make caster gain 50% DEF and heal 20% HP for 2 turns"}},
    {"Tiger Claw", {"DMG",4, 150, 20.0, 100.0, 20.0, 3, "Strike a tiger claw to the enemy, deal 150 damage, has a 20% (-20% CR) chance to deal 200% damage"}},
    {"Tiger Protect",{"HEAL+-50|BUFF+DEF+-50", 5, 0, 0, 0, 0, 5, "Create an area which make caster heal 50% HP and gain 50% DEF for 2 turns"}},
    {"Tiger Roaw", {"HEAL+-30|BUFF+ATK+-40", 5, 350, 20.0, 100.0, 20.0, 6, "Init a large roaw to the enemy, caster will heal 30% HP and gains 40% ATK for 2 turns, roaw deals 350 damage, has a 20% (- 20% CR) chance to deal 200% damage"}},
    {"Heavy Shield", {"BUFF+DEF+-50", 5, 0, 0, 0, 0, 5, "Create a big and heavy shield to gain caster 50% DEF for 2 turns"}},
    {"Fatal Claw",{"DMG|DMGPT+2+150", 5, 100, 0, 0, 0, 6, "Strike a dangerous claw to the enemy, deal 100 damage, enemy will be dealt 150 damage per turn, apply 2 turns"}},
    {"Snake Posion", {"DMGPT+3+300", 6, 0, 0, 0, 0, 5, "Shoot a posion shot to the enemy, deal 300 damage per turn, apply 3 turns."}},
    {"Snake Strike", {"DMG", 5, 400, 0, 0, 0, 4, "Use tail to attack enemy, deals 400 damage"}},
    {"Snake Carp", {"BUFF+DEF+-50|BUFF+ATK+-20", 6, 0, 0, 0, 0, 7, "Enhance the scales, gains 50% DEF, 20% ATK"}},
    {"Snake Eyes",{"BUFF+DEF+-50|STUN+1", 7, 0, 0, 0, 0, 7, "Release eyes that stun enemy for 1 turn and gain 50% DEF for 2 turns"}}
};
vector<string> SETTINGS_LIST {
    "Auto Punch until get higher power"
};
// The chances of quality drop of equiments
vector<vector<int>> EQ_RARITY_TABLE {
    {0, 40, 30, 20, 10, 0,  0,  0,  0,  0,  0}, //1
    {0, 30, 40, 20, 10, 0,  0,  0,  0,  0,  0}, //2
    {0, 20, 40, 30, 10, 0,  0,  0,  0,  0,  0},//3
    {0, 0,  50, 30, 20, 0,  0,  0,  0,  0,  0},//4
    {0, 0,  0,  50, 40, 10, 0,  0,  0,  0,  0},//5
    {0, 0,  0,  0,  60, 30, 10, 0,  0,  0,  0},//6
    {0, 0,  0,  0,  0,  60, 35, 5,  0,  0,  0},//7
    {0, 0,  0,  0,  0,  10, 50, 35, 5,  0,  0},//8
    {0, 0,  0,  0,  0,  0,  20, 60, 15, 5,  0},//9
    {0, 0,  0,  0,  0,  0,  0,  10, 70, 20, 0},//10
    {0, 0,  0,  0,  0,  0,  0,  0,  50, 49, 1},//11
    {0, 0,  0,  0,  0,  0,  0,  0,  50, 45, 5},//12
};

vector<int> TimeByMilsecond(int milsec) {
    int hour = milsec / int(36e5);
    milsec %= int(36e5);
    int minute = milsec / int(6e4);
    milsec %= int(6e4);
    int second = milsec / 1000;
    milsec %= 1000;
    vector<int> time {hour,minute,second,milsec};
    return time;
}
vector<string> splitString(string str,char div) {
    int previous = 0;
    str += div; // prevent not updating the last phase.
    vector<string> result;
    for(int i = 0 ; i < str.size() ; ++i)
        if (str[i] == div) {
            result.push_back(str.substr(previous,i-previous)); 
            previous = i + 1;
        }
    return result;
};

auto getInput(auto &var) {
    cout << ">> ";
    cin >> var;
    return var;
}

vector<vector<string>> MOBS {
    // 0              1      2       3    4     5     6    7    8    9          10
    // threat level - name - level - hp - atk - def - cc - cd - cr - passives - rewards
    {"Noobies","Goblin Defender", "1", "50", "10", "5","0.0","0.0", "10.0", "", "100+GOLD+10|100+EXP+5"},
    {"Noobies","Goblin Fighter", "3", "50", "20","5", "0.0", "0.0", "0.0", "", "100+GOLD+20|100+EXP+10"},
    {"Noobies","Orc Boomer", "5", "100", "20", "10", "0.0", "0.0", "10.0", "", "100+GOLD+30|100+EXP+20"},
    {"Noobies","Orc Knight", "7", "150", "40", "20", "0.0", "0.0", "0.0", "", "100+GOLD+40|100+EXP+30"},
    {"Intermediate", "Wolfreid", "9", "700", "40", "20", "10.0", "50.0", "0.0", "Wolf Claw|Wolf Roaw", "100+GOLD+60|100+EXP+50"},
    {"Intermediate", "Worlprimes", "12", "1000", "20", "50", "0.0", "0.0", "0.0", "Wolf Claw|Wolf Shield","100+GOLD+80|100+EXP+70"},
    {"Intermediate", "Tiger Master", "14", "1500", "100", "20", "10.0", "50.0", "20.0", "Tiger Claw|Tiger Protect", "100+GOLD+100|100+EXP+100"},
    {"Intermediate", "Tiger Tammer", "17", "2000", "70", "30", "20.0", "100.0", "30.0", "Tiger Claw|Tiger Roaw", "100+GOLD+120|100+EXP+110"},
    {"Demonize", "Death Snake", "19", "2500", "50", "30", "0.0", "0.0", "20.0", "Snake Posion|Snake Strike|Snake Shield","100+GOLD+150|100+EXP+150"},
    {"Demonize", "Snake King", "24", "5500", "50", "60", "0.0", "0.0", "50.0", "Snake Posion|Snake Strike|Snake Carp","100+GOLD+200|100+EXP+200"},
};
vector<vector<string>> BOSSES {
    {"Intermediate", "Goblin King", "7", "400", "50", "20", "10.0", "25.0", "10.0", "Goblin Slam", "100+GOLD+50|100+EXP+30|20+MCOIN+5"},
    {"Intermediate", "Orc King", "10", "1000", "50", "30", "0.0", "0.0", "20.0", "Orc Destruction", "100+GOLD+100|100+EXP+50|20+MCOIN+5"},
    {"Demonize", "Wolf King", "15", "2200", "70", "50", "10.0", "50.0", "30.0", "Wolf Roaw|Wolf Claw|Heavy Shield", "100+GOLD+200|100+EXP+120|20+MCOIN+10"},
    {"Demonize", "Tiger Lord", "20", "4500", "100", "30", "25.0", "100.0", "30.0", "Tiger Claw|Heavy Shield|Fatal Claw", "100+GOLD+450|100+EXP+200|20+MCOIN+20"},
    {"Threaten", "Anaconda", "30", "10000", "50", "100", "0.0", "0.0", "0.0", "Snake Posion|Snake Carp|Snake Eyes|Snake Strike","100+GOLD+1200|100+EXP+500|20+MCOIN+30"},
};