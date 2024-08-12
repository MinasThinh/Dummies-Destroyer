#include "lib.cpp"
using namespace std;

class Player {
    public: 
        long long HP;
        long long ATK;
        long long DEF;
        float CC; // crit chance
        float CD; // crit damage
        float CR; // crit resistance
        map<string,equipment_attributes> equipments; //type - attrs
        map<string,user_passives_attrs> passives;
        long long EXP;
        int Level;
        long long Gold;
        long long Mcoin;
        int ChallengeStage;
        map<string,string> buffs;
        map<string,string> debuffs;
        map<string,bool> settings;
    void update_HP() {
        int base = 100; // base is 100
        auto helmet = equipments["Helmet"];
        auto chestplate = equipments["Chestplate"];
        auto boots = equipments["Boots"];
        // EQ level
        int helmetLevel = helmet.Level;
        int chestplateLevel = chestplate.Level;
        int bootsLevel = boots.Level;
        // EQ Quality buff
        int helmetQualityBuff = EQ_Qualities_Buff[helmet.QualityID];
        int chestplateQualityBuff = EQ_Qualities_Buff[chestplate.QualityID];
        int bootsQualityBuff = EQ_Qualities_Buff[boots.QualityID];
        // EQ base increasement
        long long helmetIncrease = EQUIPMENT_INCREASE["HelmetHP"] * helmetLevel;
        long long chestplateIncrease = EQUIPMENT_INCREASE["ChestplateHP"] * chestplateLevel;
        long long bootsIncrease = EQUIPMENT_INCREASE["BootsHP"] * bootsLevel;
        // EQ stats
        int helmetStats = helmet.baseHP; 
        int chestplateStats = chestplate.baseHP;
        int bootsStats = boots.baseHP;

        long long increasement = (helmetLevel * helmetQualityBuff + helmetIncrease) + (chestplateLevel * chestplateQualityBuff + chestplateIncrease) + (bootsLevel * bootsQualityBuff + bootsIncrease);
        long long hp = base + increasement + helmetStats + chestplateStats + bootsStats;
        this->HP = hp;
    }
    void update_ATK() {
        int base = 10; // base is 10
        auto sword = equipments["Sword"];
        // EQ level
        int swordLevel = sword.Level;
        // EQ Quality buff
        int swordQualityBuff = EQ_Qualities_Buff[sword.QualityID];
        // EQ base increasement
        long long swordIncrease = EQUIPMENT_INCREASE["SwordATK"] * swordLevel;
        // EQ stats
        int swordStats = sword.baseATK;

        long long increasement = (swordLevel * swordQualityBuff + swordIncrease);
        long long atk = base + increasement + swordStats;
        this->ATK = atk;
    }
    void update_DEF() {
        int base = 20; // base is 100
        auto helmet = equipments["Helmet"];
        auto chestplate = equipments["Chestplate"];
        auto boots = equipments["Boots"];
        // EQ level
        int helmetLevel = helmet.Level;
        int chestplateLevel = chestplate.Level;
        int bootsLevel = boots.Level;
        // EQ Quality buff
        int helmetQualityBuff = EQ_Qualities_Buff[helmet.QualityID];
        int chestplateQualityBuff = EQ_Qualities_Buff[chestplate.QualityID];
        int bootsQualityBuff = EQ_Qualities_Buff[boots.QualityID];
        // EQ base increasement
        long long helmetIncrease = EQUIPMENT_INCREASE["HelmetDEF"] * helmetLevel;
        long long chestplateIncrease = EQUIPMENT_INCREASE["ChestplateDEF"] * chestplateLevel;
        long long bootsIncrease = EQUIPMENT_INCREASE["BootsDEF"] * bootsLevel;
        // EQ stats
        int helmetStats = helmet.baseDEF;
        int chestplateStats = chestplate.baseDEF;
        int bootsStats = boots.baseDEF;

        long long increasement = (helmetLevel * helmetQualityBuff + helmetIncrease) + (chestplateLevel * chestplateQualityBuff + chestplateIncrease) + (bootsLevel * bootsQualityBuff + bootsIncrease);
        long long def = base + increasement + helmetStats + chestplateStats + bootsStats;
        this->DEF = def;
    }
    void update_CC() {
        int base = 0; // base is 0
        auto accessory = equipments["Accessory"];
        // EQ level
        int accessoryLevel = accessory.Level;
        // EQ Quality buff
        int accessoryQualityBuff = EQ_Qualities_Buff[accessory.QualityID];
        // EQ base increasement
        float accessoryIncrease = EQUIPMENT_INCREASE["AccessoryCC"] * accessoryLevel;
        // EQ stats
        float accessoryStats = accessory.baseCC;
        float increasement = accessoryLevel * accessoryQualityBuff + accessoryIncrease;
        float cc = base + increasement + accessoryStats;
        this->CC = cc;
    }
    void update_CD() {
        int base = 50; // base is 0
        auto accessory = equipments["Accessory"];
        auto sword = equipments["Sword"];
        // EQ level
        int accessoryLevel = accessory.Level;
        int swordLevel = sword.Level;
        // EQ Quality buff
        int accessoryQualityBuff = EQ_Qualities_Buff[accessory.QualityID];
        int swordQualityBuff = EQ_Qualities_Buff[sword.QualityID];
        // EQ base increasement
        float accessoryIncrease = EQUIPMENT_INCREASE["AccessoryCD"] * accessoryLevel;
        float swordIncrease = EQUIPMENT_INCREASE["SwordCD"] * swordLevel;
        // EQ stats
        float accessoryStats = accessory.baseCD;
        float swordStats = sword.baseCD;

        float increasement = (accessoryLevel * accessoryQualityBuff + accessoryIncrease) + (swordLevel * swordQualityBuff + swordIncrease);
        float cd = base + increasement + accessoryStats + swordStats;
        this->CD = cd;
    }
    void update_CR() {
        int base = 0; // base is 0
        auto helmet = equipments["Helmet"];
        auto chestplate = equipments["Chestplate"];
        // EQ level
        int helmetLevel = helmet.Level;
        int chestplateLevel = chestplate.Level;
        // EQ Quality buff
        int helmetQualityBuff = EQ_Qualities_Buff[helmet.QualityID];
        int chestplateQualityBuff = EQ_Qualities_Buff[chestplate.QualityID];
        // EQ base increasement
        float helmetIncrease = EQUIPMENT_INCREASE["HelmetCR"] * helmetLevel;
        float chestplateIncrease = EQUIPMENT_INCREASE["ChestplateCR"] * helmetLevel;
        // EQ stats
        float helmetStats = helmet.baseCR;
        float chestplateStats = chestplate.baseCR;

        float increasement = (helmetLevel * helmetQualityBuff + helmetIncrease) + (chestplateLevel * chestplateQualityBuff + chestplateIncrease);
        float cr = base + increasement + helmetStats + chestplateStats;
        this->CR = cr;
    }
    void update_AllStats() {
        update_HP();
        update_ATK();
        update_DEF();
        update_CC();
        update_CD();
        update_CR();
    }
    void update_equipments(string equipmentName,equipment_attributes equipment) {
        this->equipments[equipmentName] = equipment;
    }
    void display_stats() {
        update_AllStats();
        cout << "--[Stats]--\n";
        cout << "Level: " << Level << " (" << EXP << " / " << Level * 100 << ')' << '\n'; // *100 is next level
        if (Gold != -1) // ignore monster stats
            cout << "Gold: " << Gold << '\n';
        if (Mcoin != -1) // ignore monster stats
            cout << "MCoin: " << Mcoin << '\n';
        cout << "Health point: " << HP << '\n';
        cout << "Attack damage: " << ATK << '\n';
        cout << "Defense: " << DEF << '\n';
        cout << "Critical chance: ";
        cout << fixed << setprecision(2) << CC << "%\n";
        cout << "Critical damage: ";
        cout << fixed << setprecision(2) << CD << "%\n";
        cout << "Critical resistance: ";
        cout << fixed << setprecision(2) << CR << "%\n";
    }
    void display_equipments() {
        cout << "--[Equipments]--\n";
        for(auto eq : equipments) {
            auto equipType = eq.first;
            auto equip = eq.second;
            auto equipDatabase = EQUIP_MAPS[equipType]; 
            string name = equipDatabase[equip.ID];
            int level = equip.Level;
            string qualiy = EquipmentQualities[equip.QualityID];
            cout << '[' << equipType << "] " << qualiy << " - " << name << " Lv." << level << '\n';
            if (equip.baseHP != 0) cout << "--> + " << equip.baseHP << " Health point\n"; 
            if (equip.baseATK != 0) cout << "--> + " << equip.baseATK << " Attack damage\n"; 
            if (equip.baseDEF != 0) cout << "--> + " << equip.baseDEF << " Defense\n"; 
            if (equip.baseCC != 0) cout << "--> + " << fixed << setprecision(2) << equip.baseCC << "% Critical chance\n"; 
            if (equip.baseCD != 0) cout << "--> + " << fixed << setprecision(2) << equip.baseCD << "% Critital damage\n"; 
            if (equip.baseCR != 0) cout << "--> + " << fixed << setprecision(2) << equip.baseCR << "% Critital resistance\n"; 
        }
    }
    void display_passives() {
        cout << "--[Passives]--\n";
        if (passives.size() == 0) {
            cout << "No passives activated\n";
            return;
        }
        int idx = 1;
        vector<string> tmp;
        map<int,bool> slotAvailable;
        for(auto itr : PASSIVE_LIST) {
            string name = itr.first;
            auto passive = itr.second;
            if (passives[name].available) {
                slotAvailable[passives[name].equippedSlot] = 1;
                tmp.push_back(name);
                cout << '[' << idx << "] " << PassiveQualities[passive.QualityID] << " - " << name << '\n';
                cout << "--> " << passive.Description << '\n';
                cout << "Cooldown: " << passive.Cooldown << " turn(s)\n";
                if (passives[name].equippedSlot)
                    cout << "--> Equipped slot " << passives[name].equippedSlot << '\n';
                else cout << "--> Unequipped\n";
                ++idx;
            }
            if (!passives[name].available) passives.erase(name); // prevent creating new element
        }
        cout << '[' << idx << "] Back\n";
        cout << "Configure slot of passive: \n";
        int usr = getInput(usr);
        if (usr >= idx) return;
        string name = tmp[usr-1];
        cout << "Configuring slot of passive " << name << ": \n";
        if (passives[name].equippedSlot) {
            cout << "[1] Unequipped from slot " << passives[name].equippedSlot << '\n';
            cout << "[2] Back\n";
            usr = getInput(usr);
            if (usr >= 2) return;
            passives[name].equippedSlot = 0;
        }
        else {
            vector<int> tmp;
            for(int slot = 1;slot <= 5; ++slot) 
                if (!slotAvailable[slot]) {
                    tmp.push_back(slot);
                    cout << '[' << tmp.size() << "] Equip slot " << slot << "\n";
                }
            if (tmp.size() == 0)  {
                cout << "No slot available!";
                return;
            }
            cout << '[' << tmp.size() + 1 << "] Back\n";
            usr = getInput(usr);
            if (usr >= tmp.size() +1 ) return;
            passives[name].equippedSlot = tmp[usr-1];            
            cout << "Slot changed successfully!\n";
            cout << "Back to homepage? (1)\n";
            usr = getInput(usr);
        }
    }
    void display_eqRarity() {
        cout << "--[Equipments Quality Chance]--\n";
        vector<int> qualchances = EQ_RARITY_TABLE[UPGRADES["Lucky"]-1];
        for(int i = 0;i<qualchances.size();++i) {
            cout << EquipmentQualities[i] << " - " << qualchances[i] << "%\n";
        }
    }
    Player(int exp,int level,long long gold,long long Mcoin,int stage) : EXP(exp), Level(level), Gold(gold) , Mcoin(Mcoin),
    ChallengeStage(stage) {};
};
class Monster {
    public:
        vector<string> Reward;
        map<string,string> debuffs;
        map<string,string> buffs;
        string Threat;
        string Name;
        int ATK;
        int HP;
        int DEF;
        float CC;
        float CD;
        float CR;
        int Level;
        vector<string> passives;
        Monster(string name,string threat,vector<string> reward,vector<string> passives, int atk,int hp,int def,int cc,int cd,int cr,int level) 
        : Name(name), Threat(threat), Reward(reward), passives(passives), ATK(atk), HP(hp),DEF(def), CC(cc), CD(cd), CR(cr), Level(level) {};
        void display_stats() {
            cout << "--[Monster stats]--\n";
            cout << "Threat: " << Threat << '\n';
            cout << "Name: " << Name << '\n';
            cout << "Level: " << Level << '\n';
            cout << "HP: " << HP << '\n';
            cout << "ATK: " << ATK << '\n';
            cout << "DEF: " << DEF << '\n';
            cout << "CC: " << fixed << setprecision(2) <<  CC << "%\n";
            cout << "CD: " << fixed << setprecision(2) << CC << "%\n";
            cout << "CR: " << fixed << setprecision(2) << CC << "%\n";
            cout << "Reward: \n";
            for(auto rew : Reward) {
                vector<string> rewdata = splitString(rew,'+');
                cout << "--> [" << rewdata[0] << "%] " << rewdata[1] << " x" << rewdata[2] << '\n';
            }
            cout << "[Passives]\n";
            int idx = 1;
            for (auto passiveName : passives) {
                if (passiveName == "") break;
                auto passive = PASSIVE_LIST[passiveName];
                cout << '[' << idx << "] " << PassiveQualities[passive.QualityID] << " - " << passiveName << '\n';
                cout << "--> " << passive.Description << '\n';
                cout << "Cooldown: " << passive.Cooldown << " turn(s)\n";
                ++idx;
            }
            if (passives[0] == "") cout << "No passive activated!\n";
        }
};
Player* PLAYER;

long long CalculatePower(equipment_attributes eq) {
    long long power = eq.Level * EQ_Qualities_Buff[eq.QualityID] * (eq.baseATK + eq.baseHP + eq.baseDEF + eq.baseCC + eq.baseCD);
    return power;
}

Player* Load_Game() {

    // create player
    ifstream db("bin/data.dll");
    string line; 
    if (!db.is_open()) {
        throw invalid_argument("Data open failed!");
    }
    vector<string> data;
    while (getline(db,line)) {
        if (line[0] == '*') continue; // skipping the notice lines
        data = splitString(line,' ');
    }   
    db.close();
    Player* plr = new Player(stoi(data[0]),stoi(data[1]),stoll(data[2]),stoll(data[3]),stoi(data[4]));
    // set equipments
    ifstream eq("bin/equipments.dll");
    if (!eq.is_open()) 
        throw invalid_argument("Equipment open failed!");
    while(getline(eq,line)) {
        if (line[0] != '*') break; // skipping notice lines
    }
    for(int i = 0; i < equipmentList.size() ; ++i) {
        vector<string> equipmentDesc = splitString(line,'-');
        equipment_attributes equip;
        equip.ID = stoi(equipmentDesc[0]);
        equip.QualityID = stoi(equipmentDesc[1]);
        equip.Level = stoi(equipmentDesc[2]);
        equip.baseHP = stoi(equipmentDesc[3]);
        equip.baseATK = stoi(equipmentDesc[4]);
        equip.baseDEF = stoi(equipmentDesc[5]);
        equip.baseCC = stof(equipmentDesc[6]);
        equip.baseCD = stof(equipmentDesc[7]);
        equip.baseCR = stof(equipmentDesc[8]);
        plr->update_equipments(equipmentList[i],equip);
        getline(eq,line);
    }
    plr->update_AllStats();
    eq.close();
    //load upgrades
    ifstream upgr("bin/upgrades.dll");
    if (!upgr.is_open()) 
        throw invalid_argument("Upgrades open failed!");
    while(getline(upgr,line)) {
        // skipping notice lines
        if (line[0] == '*') continue;
        vector<string> upg = splitString(line,'-');
        UPGRADES["Gold Forge"] = stoi(upg[0]);
        UPGRADES["Lucky"] = stoi(upg[1]);
    }
    upgr.close();
    // load passives
    ifstream pasv("bin/passives.dll");
    if (!pasv.is_open()) 
        throw invalid_argument("Passives open failed!");
    while(getline(pasv,line)) {
        if (line[0] == '*') continue; // skipping notice lines
        vector<string> pas = splitString(line,'-');
        plr->passives[pas[0]].available = 1;
        plr->passives[pas[0]].equippedSlot = stoi(pas[1]);
    }
    pasv.close();
    //load settings
    ifstream sets("bin/settings.dll");
    if (!sets.is_open()) 
        throw invalid_argument("Settings open failed!");
    while(getline(sets,line)) {
        if (line[0] == '*') continue; // skipping otice lines
        vector<string> set = splitString(line,'-');
        for(int i = 0;i<SETTINGS_LIST.size();++i) {
            plr->settings[SETTINGS_LIST[i]] = stoi(set[i]);
        }
    }
    return plr; 
}

void System_Character() {
    system("cls");
    cout << "--[Character]--\n";
    cout << "[1] Stats\n";
    cout << "[2] Equipments\n";
    cout << "[3] Passives\n";
    cout << "[4] Equipment rarity\n";
    cout << "[5] Back\n";
    int phase = getInput(phase);
    if (phase == 1) PLAYER->display_stats();
    if (phase == 2) PLAYER->display_equipments();
    if (phase == 3) PLAYER->display_passives();
    if (phase == 4) PLAYER->display_eqRarity();
    if (phase >= 5) return;
    cout << "Back to homepage? (1)\n";
    int backornot = getInput(backornot);
    system("cls");
}
void System_Train() {
    system("cls");
    bool autopunch = PLAYER->settings["Auto Punch until get higher power"];
    cout << "--[Train]--" << '\n';
    cout << "Auto punch: " << (autopunch ? "Enabled" : "Disabled") << '\n';
    int usr;
    if(autopunch) {
        cout << "Punch dummy? \n";
        cout << "[1] Yes\n";
        cout << "[2] Back\n";
        usr = getInput(usr);
        if (usr >= 2) return;
    } else usr = 1;
    while(usr == 1) {
        if (!autopunch) {
            cout << "Punch dummy? \n";
            cout << "[1] Yes\n";
            cout << "[2] Back\n";
            usr = getInput(usr);
        }
        if (usr >= 2) return;
        cout << "Punching.....\n";
        vector<int> qual_chances = EQ_RARITY_TABLE[UPGRADES["Lucky"]-1];
        vector<pair<int,int>> possible_chances {{0,0}};
        for(int i = 0;i<qual_chances.size();++i) {
            if (qual_chances[i]) {
                possible_chances.push_back({i,qual_chances[i]});
            }
        }
        int qual_rd = rand() % 99 + 1; // prevent the General
        int qualID;
        for(int i = 1,sum=0;i<possible_chances.size();++i) {
            if (qual_rd >= sum + 1 && qual_rd <= possible_chances[i].second + sum) {
                qualID = possible_chances[i].first;
                break;
            }
            sum += possible_chances[i].second;
        }
        string equipmentType = equipmentList[rand() % equipmentList.size()];
        equipment_attributes currequip = PLAYER->equipments[equipmentType];
        // range from player level - 5 to + 5
        int equipmentLevel = min(rand() % (PLAYER->Level + 6) + max(PLAYER->Level - 5,1),LEVEL_CAP); 
        int equipmentID = int(equipmentLevel/ 20 + 1);
        string equipmentName = EQUIP_MAPS[equipmentType][equipmentID];
        Sleep(500);
        for(int i = 0;i<qualID;++i) {
            cout << EquipmentQualities[i];
            Sleep(200);
            cout << " - ";
        }
        cout << EquipmentQualities[qualID] << "!\n";
        cout << "You got [" << equipmentType << "] " << EquipmentQualities[qualID] << " - " << equipmentName <<
        " Lv." << equipmentLevel << '\n';
        int hp,atk,def; hp = atk = def = 0;
        float cc,cd,cr; cc = cd = cr = 0.0;
        if (equipmentType == "Helmet" || equipmentType == "Chestplate" || equipmentType == "Boots") {
            // range from 2x level - 3x level
            hp = rand() % (PLAYER->Level * 3 + 1) + PLAYER->Level * 2;
            cout << "--> + " << hp << " Health point (Current: + " << currequip.baseHP << ")\n";

            // range from 1x level - 2x level
            def = rand() % (PLAYER->Level * 2 + 1) + PLAYER->Level;
            cout << "--> + " << def << " Defense (Current: + " << currequip.baseDEF << ")\n";
            if (equipmentType != "Boots") {
                // rand from 20% - 50%
                cr = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/30)) + 20;
                cout << "--> + " << fixed << setprecision(2) << cr << "% Critical resistance (Current: + " << currequip.baseCR << "%)\n";
            }
        }
        if (equipmentType == "Sword") {
            //range from 1.5x level - 2x level
            atk = rand() % (PLAYER->Level * 2 + 1) + PLAYER->Level * 1.5;
            cout << "--> + " << atk << " Attack damage (Current: + " << currequip.baseATK << ")\n";
            //range from 25 - 200
            cd = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/175)) + 25;
            // cd = rand() % 176 + 25;
            cout << "--> + " << fixed << setprecision(2) << cd << "% Critical damage (Current: + " << currequip.baseCD << "%)\n";
            
        }
        if (equipmentType == "Accessory") {
            // range from 5 - 20
            cc = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/15)) + 5;
            // cc = rand() % 16 + 5;
            cout << "--> + " << fixed << setprecision(2) << cc << "% Critical chance (Current: + " << currequip.baseCC << "%)\n";
            //range from 25 - 200
            cd = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/175)) + 25;
            // cd = rand() % 176 + 25;
            cout << "--> + " << fixed << setprecision(2) << cd << "% Critical damage (Current: + " << currequip.baseCD << "%)\n";
        }
        equipment_attributes newequip;
        newequip.ID = equipmentID;
        newequip.QualityID = qualID;
        newequip.Level = equipmentLevel;
        newequip.baseHP = hp;
        newequip.baseATK = atk;
        newequip.baseDEF = def;
        newequip.baseCC = cc;
        newequip.baseCD = cd;
        newequip.baseCR = cr;
        long long newPower = CalculatePower(newequip);
        long long currPower = CalculatePower(currequip);
        cout << "New equipment power: " << newPower << '\n';
        cout << "Current equipment power: " << currPower << '\n';
        equipment_attributes del = newequip;
        bool stopable = 0;
        if ((!autopunch) || (autopunch && newPower > currPower)) {
            cout << "Do you want to change?\n";
            cout << "[1] Yes\n";
            cout << "[2] No\n";
            int usr = getInput(usr);
            if (usr == 1)  {
                del = currequip;
                PLAYER->update_equipments(equipmentType,newequip);
                PLAYER->update_AllStats();
                cout << "Changed successfully!\n";
            }
            stopable = autopunch;
        }
        PLAYER->EXP += 10;
        cout << "+ 10 EXP (" << PLAYER->EXP;
        if (PLAYER->Level == LEVEL_CAP) cout << ")\nEXP stored due to reached max level\n";
        else cout << " / " << PLAYER->Level * 100 << ")\n";
        if (PLAYER->EXP == PLAYER->Level * 100 && PLAYER->Level < LEVEL_CAP) {
            PLAYER->Level++;
            cout << "Leveled up to level " << PLAYER->Level << '\n';
        }
        long long goldGain = del.Level * UPGRADES["Gold Forge"];
        cout << "You got " << goldGain << " (x" << UPGRADES["Gold Forge"] << ") gold for forging equipment!\n";
        PLAYER->Gold += goldGain;
        if (stopable) {
            cout << "Do you want to continue?\n";
            cout << "[1] Yes\n";
            cout << "[2] No\n";
            usr = getInput(usr);
            stopable = usr-1;
        }
        if (stopable) break;
    }
    cout << "Back to homepage? (1)\n";
    int backornot = getInput(backornot);
    system("cls");
}
void System_Upgrades() {
    system("cls");
    cout << "--[Upgrades]--\n";
    int idx = 1;
    for(auto upgr : UPGRADES) {
        string name = upgr.first;
        int level = upgr.second;
        cout << '[' << idx << "] " << name << " (" << level << " / " << UPGRADES_LIM[name] << ")\n";
        cout << "--> " << UPGRADES_DESC[name] << '\n';
        cout << "Cost: ";
        if (level == UPGRADES_LIM[name]) cout << "Maxed\n";
        else cout << UPGRADES_PRICE[name][level-1] << " Gold\n";
        ++idx;
    }
    cout << '[' << idx << "] Back\n";
    int usr = getInput(usr);
    if (usr > UPGRADES.size()) return;
    string name;
    if (usr == 1) name = "Gold Forge";
    if (usr == 2) name = "Lucky";
    int level = UPGRADES[name];
    long long price = UPGRADES_PRICE[name][level-1];
    cout << "Upgrading.";
    Sleep(500);
    cout << '.';
    Sleep(500);
    cout << '.';
    Sleep(500);
    cout << '.';
    Sleep(500);
    cout << "\nStatus: ";
    if (UPGRADES[name] == UPGRADES_LIM[name]) 
        cout << "Maxed out!\n";
    else if(PLAYER->Gold < price)
        cout << "Gold insufficient!\n";
    else {

        PLAYER->Gold -= price;
        UPGRADES[name]++;
        cout << "Succeeded!\n";
    }
    cout << "Back to homepage? (1)\n";
    int backornot = getInput(backornot);
    system("cls");
}
void System_Shop() {
    system("cls");
    cout << "--[Shop]--\n";
    cout << "[1] Passives\n";
    cout << "[2] Back\n";
    int phase = getInput(phase);
    if (phase >= 2) return;
    int idx = 1;
    cout << "--[Passives]--\n";
    for(int i = SHOP_ITEMS_LIST_PHASES["PASSIVE"].first; i <= SHOP_ITEMS_LIST_PHASES["PASSIVE"].second;++i) {
        string name = SHOP_ITEMS_LIST[i];
        auto item = SHOP_ITEMS[name];
        if (item.type != "PASSIVE") continue;
        auto passive = PASSIVE_LIST[name];
        cout << '[' << idx << "] " << PassiveQualities[passive.QualityID] << " - " << name << '\n';
        cout << "--> " << passive.Description << '\n';
        cout << "Cooldown: " << passive.Cooldown << " turn(s)\n";
        cout << "Cost: " << item.cost << " Gold\n";
        ++idx;
    }
    cout << '[' << idx << "] Back\n";
    int itmidx = getInput(itmidx);
    if (itmidx >= idx) return;
    itmidx += SHOP_ITEMS_LIST_PHASES["PASSIVE"].first - 1;
    string name = SHOP_ITEMS_LIST[itmidx];
    auto item = SHOP_ITEMS[name];
    cout << "Confirm buying " << name << " with " << item.cost << " Gold?\n";
    cout << "[1] Yes\n";
    cout << "[2] No\n";
    int buyornot = getInput(buyornot);
    if (buyornot >= 2) return; 
    cout << "Transacting.";
    Sleep(500);
    cout << '.';
    Sleep(500);
    cout << '.';
    Sleep(500);
    cout << '.';
    Sleep(500);
    cout << '.';
    Sleep(500);
    cout << ".\n";
    cout << "Status: ";
    if (PLAYER->passives[name].available) {
        cout << "Already owned!\n";
        return;
    }
    if (PLAYER->Gold < item.cost) {
        cout << "Gold insufficient!\n";
        return;
    }
    PLAYER->Gold -= item.cost;
    PLAYER->passives[name].available = 1;
    cout << "Succeeded!\n";
    cout << "Passive added!\n";
    cout << "Back to homepage? (1)\n";
    int backornot = getInput(backornot);
    system("cls");
}
void System_Challenges() {
    cout << "--[Challenge Tower]--\n";
    if (PLAYER->ChallengeStage == STAGE_CAP) cout << "You have been cleared the tower!\n";
    cout << "Current stage: " << PLAYER->ChallengeStage << '\n';
    cout << "[1] Challenge stage " << '\n';
    cout << "[2] Select stage\n";
    cout << "[3] Back\n";
    int usr = getInput(usr);
    int usrStage = PLAYER->ChallengeStage;
    if (usr == 2) {
        if (PLAYER->ChallengeStage == 0)  {
            cout << "No stages cleared!\n";
        }
        else {
            cout << "Select stages: \n";
            for(int i = 1;i<=PLAYER->ChallengeStage;++i) {
                int phase = i / 5 + 1;
                int idx = i % 5;
                cout << "Stage " << i << ": ";
                if (i % 5 == 0) {
                    cout << '[' << BOSSES[phase-2][0] << "] BOSS - " << BOSSES[phase-2][1] << '\n';
                } else 
                    if (idx <= 2) 
                        cout << '[' << MOBS[phase * 2 - 2][0] << "] " << MOBS[phase * 2 - 2][1] << '\n';
                    else 
                        cout << '[' << MOBS[phase * 2 - 1][0] << "] " << MOBS[phase * 2 - 1][1] << '\n';
            }
            cout << '[' << PLAYER->ChallengeStage + 1 << "] Back\n"; 
            usrStage = getInput(usrStage);
            if (usrStage > PLAYER->ChallengeStage) return;
        }
    }
    if (usr >= 3) return;
    int phase = usrStage / 5 + 1;
    bool isBoss = 0;
    vector<string> enemy_data;
    if (usrStage % 5 == 0 && usrStage > 0) {
        // boss
        --phase;
        enemy_data = BOSSES[phase-1];
    }
    else {
        // mobs
        int stage = usrStage % 5;
        if (usrStage == 0) stage = 1; 
        enemy_data = (stage <= 2 ? MOBS[phase * 2 - 2] : MOBS[phase * 2 - 1]);
    }
    string enemy_threat = enemy_data[0];
    string enemy_name = enemy_data[1];
    int enemy_level = stoi(enemy_data[2]);
    int enemy_hp = stoi(enemy_data[3]);
    int enemy_atk = stoi(enemy_data[4]);
    int enemy_def = stoi(enemy_data[5]);  
    float enemy_cc = stof(enemy_data[6]);
    float enemy_cd = stof(enemy_data[7]);
    float enemy_cr = stof(enemy_data[8]);
    vector<string> enemy_passives = splitString(enemy_data[9], '|');
    vector<string> enemy_rewards = splitString(enemy_data[10],'|');
    Monster* Enemy = new Monster(enemy_name,enemy_threat,enemy_rewards,enemy_passives,enemy_atk,enemy_hp,enemy_def,enemy_cc,enemy_cd,enemy_cr,enemy_level);
    cout << (isBoss ? "=====[BOSS]=====\n" : "---[MOBS]---\n");
    cout << "[1] Enemy status\n";
    cout << "[2] Challenge\n";
    cout << "[3] Back\n";
    usr = getInput(usr);
    if (usr == 1) Enemy->display_stats();
    if (usr == 2) { // challenge
        cout << "Do you want to skip battle?\n";
        cout << "[1] Yes\n";
        cout << "[2] No\n";
        usr = getInput(usr); 
        bool skipbattle = !(usr-1);
        cout << "Loading game....\n";
        Player* plr = PLAYER;
        Monster* enm = Enemy;
        int gameTurn = 0;
        vector<passive_attributes> plr_pasvs,enm_pasvs;
        vector<int> plr_pasvs_cdwn, enm_pasvs_cdwn;
        vector<string> plr_pasv_name, enm_pasv_name;
        map<string,long long> plr_def_stats,enm_def_stats;
        map<string,float> fplr_def_stats,fenm_def_stats;
        plr_def_stats["ATK"] = plr->ATK;
        plr_def_stats["HP"] = plr->HP;
        plr_def_stats["DEF"] = plr->DEF;
        fplr_def_stats["CC"] = plr->CC;
        fplr_def_stats["CD"] = plr->CD;
        fplr_def_stats["CR"] = plr->CR;
        enm_def_stats["ATK"] = plr->ATK;
        enm_def_stats["HP"] = enm->HP;
        enm_def_stats["DEF"] = enm->DEF;
        fenm_def_stats["CC"] = enm->CC;
        fenm_def_stats["CD"] = enm->CD;
        fenm_def_stats["CR"] = enm->CR;
        for (auto pass : PLAYER->passives) {
            if (pass.second.equippedSlot) {
                plr_pasvs.push_back(PASSIVE_LIST[pass.first]);
                plr_pasvs_cdwn.push_back(PASSIVE_LIST[pass.first].Cooldown);
                plr_pasv_name.push_back(pass.first);
            }
        }
        for (auto pass : Enemy->passives) {
            enm_pasvs.push_back(PASSIVE_LIST[pass]);
            enm_pasvs_cdwn.push_back(PASSIVE_LIST[pass].Cooldown);
            enm_pasv_name.push_back(pass);
        }
        bool is_plrWin = 0;
        map<string,string> totalbuffs;
        map<string,string> totaldebuffs;
        map<string,string> etotalbuffs;
        map<string,string> etotaldebuffs;
        while(1) {
            if (gameTurn > 50) {
                cout << "Game lost due to too many turns!\n";
                break;
            }
            ++gameTurn;
            for(auto buff : plr->buffs) {
                if (totalbuffs[buff.first] == "") {// no such buff available
                    totalbuffs[buff.first] = buff.second;
                } else {
                    vector<string> tmp1 = splitString(totalbuffs[buff.first],'+');
                    vector<string> tmp2 = splitString(buff.second,'+');
                    totalbuffs[buff.first] = to_string(stoi(tmp1[0]) + stoi(tmp2[0])) + '+'; // turn
                    totalbuffs[buff.first] += to_string(stoi(tmp1[1]) + stoi(tmp2[1])); // percentage
                }
                plr->buffs.erase(buff.first);
            }
            for(auto debuff : plr->debuffs) {
                if(debuff.first.substr(0,5) == "DMGPT") {
                    totaldebuffs[debuff.first] = debuff.second;
                }
                if (debuff.first == "STUN") {
                    totaldebuffs[debuff.first] = to_string(stoi(totaldebuffs[debuff.first]) + stoi(debuff.second)); 
                }
                plr->debuffs.erase(debuff.first);
            }
            for(auto buff : enm->buffs) {
                if (etotalbuffs[buff.first] == "") {// no such buff available
                    etotalbuffs[buff.first] = buff.second;
                } else {
                    vector<string> tmp1 = splitString(etotalbuffs[buff.first],'+');
                    vector<string> tmp2 = splitString(buff.second,'+');
                    etotalbuffs[buff.first] = to_string(stoi(tmp1[0]) + stoi(tmp2[0])) + '+'; // turn
                    etotalbuffs[buff.first] += to_string(stoi(tmp1[1]) + stoi(tmp2[1])); // percentage
                }
                enm->buffs.erase(buff.first);
            }
            for(auto debuff : enm->debuffs) {
                if(debuff.first.substr(0,5) == "DMGPT") {
                    etotaldebuffs[debuff.first] = debuff.second;
                }
                if (debuff.first == "STUN") {
                    etotaldebuffs[debuff.first] = to_string(stoi(etotaldebuffs[debuff.first]) + stoi(debuff.second)); 
                }
                enm->debuffs.erase(debuff.first);
            }
            if (gameTurn % 2 == 1) { // player turn
                if (!skipbattle) cout << '[' << gameTurn << "]-----[PLAYER TURN]-----" << '[' << gameTurn << "]\n";
                int inc_hp = 0;
                int inc_atk = 0;
                int inc_def = 0;
                int inc_cc = 0;
                int inc_cd = 0;
                int inc_cr = 0;
                bool canBuff = 0;
                bool canDebuff = 0;
                bool isStunned = 0;
                if (!skipbattle) cout << "- Buffs: \n";
                for (auto buff : totalbuffs) {
                    long long* target = nullptr;
                    float* ftarget = nullptr;
                    int* inc;
                    if (buff.first == "ATK")  target = &plr->ATK, inc = &inc_atk; 
                    if (buff.first == "DEF")  target = &plr->DEF, inc = &inc_def;
                    if (buff.first == "HP")  target = &plr->HP, inc = &inc_hp;
                    if (buff.first == "CC")  ftarget = &plr->CC, inc = &inc_cc;
                    if (buff.first == "CD")  ftarget = &plr->CD, inc = &inc_cd;
                    if (buff.first == "CR")  ftarget = &plr->CR, inc = &inc_cr;
                    vector<string> tmp = splitString(buff.second,'+');
                    int turn = stoi(tmp[0]);
                    int perc = 100 + stoi(tmp[1]);
                    *inc = perc;
                    if (target == NULL) *ftarget = float((fplr_def_stats[buff.first] * perc) / 100);
                    else
                        *target = (long long)((plr_def_stats[buff.first] * perc) / 100);
                    if (turn == 0) {
                        totalbuffs.erase(buff.first);
                        if (target == NULL) *ftarget = fplr_def_stats[buff.first];
                        else
                            *target = plr_def_stats[buff.first];
                        continue;
                    }   
                    canBuff = 1;
                    --turn;
                    if (!skipbattle) cout << "--> + " << *inc - 100  << "% " << buff.first << " (" << turn << " turn(s) left)\n";
                    totalbuffs[buff.first] = to_string(turn) + '+' + tmp[1];
                }   
                if (!canBuff) if (!skipbattle) cout << "No buffs activated!\n";
                for(auto debuff : totaldebuffs) {
                    if (debuff.first.substr(0,5) == "DMGPT") {
                        vector<string> tmp = splitString(debuff.second,'+');
                        cout << "--> Be inflacted and be dealt " << tmp[1] << " damage\n";
                        plr->HP -= stoll(tmp[1]);
                        int turn = stoi(tmp[0]);
                        if (turn == 0) {
                            totaldebuffs.erase(debuff.first);
                            continue;
                        }
                        --turn;
                        cout << "--> Inflaction (- " << tmp[1] << "), " << turn << " left(s)\n";
                    }
                    if (debuff.first == "STUN") {
                        int turn = stoi(debuff.second);
                        if (turn == 0) {
                            totaldebuffs.erase(debuff.first);
                            continue;
                        }
                        isStunned = 1;
                        cout << "--> Stunned, " << turn << " left(s)\n";
                        --turn;
                    }
                }
                if (!canDebuff) if (!skipbattle) cout << "No debuffs activated\n";
                if (isStunned) continue;
                if (plr->HP <= 0) break;
                if (!skipbattle)  cout << "- Status: \n";
                if (!skipbattle)  cout << "- HP: " << plr->HP << " (+ " << max(inc_hp-100,0) << "%) " <<" --- Enemy: " << enm->HP << '\n';
                if (!skipbattle)  cout << "- ATK: " << plr->ATK << " (+ " << max(inc_atk-100,0) << "%) " <<" --- Enemy: " << enm->ATK << '\n';
                if (!skipbattle)  cout << "- DEF: " << plr->DEF << " (+ " << max(inc_def-100,0) << "%) " <<" --- Enemy: " << enm->DEF << '\n';
                if (!skipbattle)  cout << "- CC: " << fixed << setprecision(2) << plr->CC << "% (+ " << max(inc_cc-100,0) << "%) " <<" --- Enemy: " << enm->CC << "%\n";
                if (!skipbattle)  cout << "- CD: " << fixed << setprecision(2) << plr->CD << "% (+ " << max(inc_cd-100,0) << "%) " <<" --- Enemy: " << enm->CD << "%\n";
                if (!skipbattle)  cout << "- CR: " << fixed << setprecision(2) << plr->CR << "% (+ " << max(inc_cr-100,0) << "%) " <<" --- Enemy: " << enm->CR << "%\n";
                int total_deal = 0;
                if (!skipbattle)  cout << "- Passives: \n";
                if (plr_pasvs.size() == 0) cout << "No passives activated!\n";
                for(int i = 0;i < plr_pasvs.size(); ++i) {
                    auto passive = plr_pasvs[i];
                    if (plr_pasvs_cdwn[i] == 0) {// release now
                        if (!skipbattle) cout << "[!] Passive " << plr_pasv_name[i] << " is activating.";
                        Sleep(300);
                        if (!skipbattle) cout << '.';
                        Sleep(300);
                        if (!skipbattle) cout << ".\n";
                        plr_pasvs_cdwn[i] = passive.Cooldown;
                        vector<string> pasv_types = splitString(passive.Type,'|');
                        int critChance = max(int(Enemy->CR - (passive.CR + plr->CR + passive.CC + plr->CC)),0);  
                        for(string types : pasv_types) {
                            vector<string> type_data = splitString(types,'+');
                            string type = type_data[0];
                            if (type == "DMG") {
                                bool isCrit = 0;
                                if (critChance >= 100)
                                    isCrit = 1;
                                else {
                                    int crit_rd = rand() % 99 + 1;
                                    if (crit_rd <= critChance) isCrit = 1;
                                }
                                long long dmgDeal = passive.Impact;
                                if (isCrit) dmgDeal *= (100 + passive.CD + PLAYER->CD)/100;
                                if (!skipbattle)  cout << "--> Passive " << plr_pasv_name[i] << " released and deal " << dmgDeal << " damage ";
                                if (isCrit) if (!skipbattle)  cout << "(CRIT)";
                                if (!skipbattle)  cout << '\n';
                                total_deal += dmgDeal;
                            }
                            if (type == "HEAL") {
                                if (type_data[1][0] == '-') { // is percentage
                                    int percentage = stoi(type_data[1].substr(1,type_data[1].size()-1));
                                    int hpLost = PLAYER->HP - plr->HP;
                                    int hpCanHeal = PLAYER->HP * percentage / 100;
                                    plr->HP += min(hpLost,hpCanHeal);
                                    if (!skipbattle) cout << "--> Passive " << plr_pasv_name[i] << " healed caster " << percentage << "% HP (" << min(hpLost,hpCanHeal) << ")\n";
                                }   
                            }
                            if (type == "STUN") {
                                // by turn
                                Enemy->debuffs["STUN"] = to_string(stoi(Enemy->debuffs["STUN"]) + stoi(type_data[1].substr(1,type_data[1].size()-1)));
                            }
                            if (type == "BUFF") {
                                // stackable
                                // by turn -> percentage
                                string buff = type_data[1];
                                if (type_data[2][0] == '-') { // is percentage
                                    int percentage = stoi(type_data[2].substr(1,type_data[2].size()-1));
                                    if (plr->buffs[buff].empty()) {// no buffs
                                        plr->buffs[buff] = "2+" + to_string(percentage);
                                    }
                                    else {
                                        vector<string> tmp = splitString(plr->buffs[buff],'+');
                                        plr->buffs[buff] = to_string(stoi(tmp[0]) + 2) + '+' + to_string(stoi(tmp[1]) + percentage);
                                    }
                                }
                                vector<string> tmp = splitString(plr->buffs[buff],'+');
                                if (!skipbattle) cout <<"--> Passive " << plr_pasv_name[i] << " gained caster " << tmp[1] << "% " << buff << " for " << tmp[0] << " turn(s)\n";
                            }
                            if (type == "DMGPT") {
                                // unstackable
                                if (Enemy->debuffs["DMGPT"] != "") {// already available
                                    string idx = "1";
                                    string name = "DMGPT";
                                    while(Enemy->debuffs[name] != "") {
                                        idx = to_string(stoi(idx) + 1);
                                        name = "DMGPT" + idx;
                                    }
                                    Enemy->debuffs[name] = type_data[1] + '+' + type_data[2];
                                }
                                if (!skipbattle) cout << "--> Passive " << plr_pasv_name[i] << " inflected enemy " << type_data[2] << " damage/turn (apply " << type_data[1] << " turns)\n";
                            }
                        }
                    }
                    else {
                        if (!skipbattle) cout << "+ " << plr_pasv_name[i] << ": " << plr_pasvs_cdwn[i] << " more turn(s)\n";
                        --plr_pasvs_cdwn[i];
                    }
                }
                if (plr->ATK <= enm->DEF) {// can't attack through armor
                    if (!skipbattle) cout << "--> Player dealt 0 damage (- " << plr->ATK << " DEF)"<< "!\n";
                }
                else {
                    bool canCrit = 0;
                    if (plr->CC > enm->CR) {
                        int critc = plr->CC - enm->CR;
                        if (critc >= 100) {
                            canCrit = 1;
                        }
                        int crit_rd = rand() % 99 + 1;
                        if (crit_rd <= critc) canCrit = 1;
                    }
                    long long dmgdeal = plr->ATK - enm->DEF;
                    if (canCrit) dmgdeal = (dmgdeal * (100 + plr->CD)) / 100;
                    if (!skipbattle) cout << "--> Player dealt " << dmgdeal << " damage ";
                    if (!skipbattle) cout << (canCrit ? "(CRIT)\n" : "\n");
                    total_deal += dmgdeal;
                }
                enm->HP -= total_deal;
                if (enm->HP <= 0) {
                    is_plrWin = 1;
                    break;
                }
            }
            if (gameTurn % 2 == 0) { // Enemy turn
                if (!skipbattle) cout << '[' << gameTurn << "]-----[ENEMY TURN]-----" << '[' << gameTurn << "]\n";
                int inc_hp = 0;
                int inc_atk = 0;
                int inc_def = 0;
                int inc_cc = 0;
                int inc_cd = 0;
                int inc_cr = 0;
                bool canBuff = 0;
                bool canDebuff = 0;
                bool isStunned = 0;
                if (!skipbattle) cout << "- Buffs: \n";
                for (auto buff : etotalbuffs) {
                    int* target = nullptr;
                    float* ftarget = nullptr;
                    int* inc;
                    if (buff.first == "ATK")  target = &enm->ATK, inc = &inc_atk; 
                    if (buff.first == "DEF")  target = &enm->DEF, inc = &inc_def;
                    if (buff.first == "HP")  target = &enm->HP, inc = &inc_hp;
                    if (buff.first == "CC")  ftarget = &enm->CC, inc = &inc_cc;
                    if (buff.first == "CD")  ftarget = &enm->CD, inc = &inc_cd;
                    if (buff.first == "CR")  ftarget = &enm->CR, inc = &inc_cr;
                    vector<string> tmp = splitString(buff.second,'+');
                    int turn = stoi(tmp[0]);
                    int perc = 100 + stoi(tmp[1]);
                    *inc = perc;
                    if (target == NULL) *ftarget = float((fenm_def_stats[buff.first] * perc) / 100);
                    else
                        *target = (int)((enm_def_stats[buff.first] * perc) / 100);
                    if (turn == 0) {
                        etotalbuffs.erase(buff.first);
                        if (target == NULL) *ftarget = fenm_def_stats[buff.first];
                        else
                            *target = enm_def_stats[buff.first];
                        continue;
                    }   
                    canBuff = 1;
                    --turn;
                    if (!skipbattle) cout << "--> + " << *inc - 100  << "% " << buff.first << " (" << turn << " turn(s) left)\n";
                    etotalbuffs[buff.first] = to_string(turn) + '+' + tmp[1];
                }   
                if (!canBuff) if (!skipbattle) cout << "No buffs activated!\n";
                for(auto debuff : etotaldebuffs) {
                    if (debuff.first.substr(0,5) == "DMGPT") {
                        vector<string> tmp = splitString(debuff.second,'+');
                        if (!skipbattle) cout << "--> Be inflacted and be dealt " << tmp[1] << " damage\n";
                        enm->HP -= stoll(tmp[1]);
                        int turn = stoi(tmp[0]);
                        if (turn == 0) {
                            etotaldebuffs.erase(debuff.first);
                            continue;
                        }
                        --turn;
                        if (!skipbattle) cout << "--> Inflaction (- " << tmp[1] << "), " << turn << " left(s)\n";
                    }
                    if (debuff.first == "STUN") {
                        int turn = stoi(debuff.second);
                        if (turn == 0) {
                            etotaldebuffs.erase(debuff.first);
                            continue;
                        }
                        isStunned = 1;
                        if (!skipbattle) cout << "--> Stunned, " << turn << " left(s)\n";
                        --turn;
                    }
                }
                if (!canDebuff) if (!skipbattle) cout << "No debuffs activated\n";
                if (isStunned) continue;
                if (enm->HP <= 0) {
                    is_plrWin = 1;
                    break;
                }
                int total_deal = 0;
                for(int i = 0;i < enm_pasvs.size(); ++i) {
                    auto passive = enm_pasvs[i];
                    if (passive.Cooldown == 1) {// release now
                        if (!skipbattle) cout << "[!] Passive " << enm_pasv_name[i] << " is activating.";
                        Sleep(300);
                        if (!skipbattle) cout << '.';
                        Sleep(300);
                        if (!skipbattle) cout << ".\n";
                        if (!skipbattle) cout << "--> Passive " << enm_pasv_name[i];
                        passive.Cooldown = enm_pasvs_cdwn[i];
                        vector<string> pasv_types = splitString(passive.Type,'|');
                        int critChance = max(int(Enemy->CR - (passive.CR + enm->CR + passive.CC + enm->CC)),0);  
                        for(string types : pasv_types) {
                            vector<string> type_data = splitString(types,'+');
                            string type = type_data[0];
                            if (type == "DMG") {
                                bool isCrit = 0;
                                if (critChance >= 100)
                                    isCrit = 1;
                                else {
                                    int crit_rd = rand() % 99 + 1;
                                    if (crit_rd <= critChance) isCrit = 1;
                                }
                                long long dmgDeal = passive.Impact;
                                if (isCrit) dmgDeal *= (100 + passive.CD + Enemy->CD)/100;
                                if (!skipbattle) cout << " released and deal " << dmgDeal << " damage ";
                                if (isCrit) if (!skipbattle) cout << "(CRIT)";
                                if (!skipbattle) cout << '\n';
                                total_deal += dmgDeal;
                            }
                            if (type == "HEAL") {
                                if (type_data[1][0] == '-') { // is percentage
                                    int percentage = stoi(type_data[1].substr(1,type_data[1].size()-1));
                                    int hpLost = Enemy->HP - enm->HP;
                                    int hpCanHeal = Enemy->HP * percentage / 100;
                                    enm->HP += min(hpLost,hpCanHeal);
                                    if (!skipbattle) cout << " healed caster " << percentage << "% HP (" << min(hpLost,hpCanHeal) << ")\n";
                                }   
                            }
                            if (type == "STUN") {
                                // by turn
                                Enemy->debuffs["STUN"] = to_string(stoi(Enemy->debuffs["STUN"]) + stoi(type_data[1].substr(1,type_data[1].size()-1)));
                            }
                            if (type == "BUFF") {
                                // stackable
                                // by turn -> percentage
                                string buff = type_data[1];
                                if (type_data[2][0] == '-') { // is percentage
                                    int percentage = stoi(type_data[2].substr(1,type_data[2].size()-1));
                                    if (enm->buffs[buff].empty()) {// no buffs
                                        enm->buffs[buff] = "2+" + to_string(percentage);
                                    }
                                    else {
                                        vector<string> tmp = splitString(enm->buffs[buff],'+');
                                        enm->buffs[buff] = to_string(stoi(tmp[0]) + 2) + '+' + to_string(stoi(tmp[1]) + percentage);
                                    }
                                }
                                vector<string> tmp = splitString(enm->buffs[buff],'+');
                                if (!skipbattle) cout << " activated and gained caster + " << tmp[1] << "% " << buff << " for " << tmp[0] << " turn(s)\n";
                            }
                            if (type == "DMGPT") {
                                // unstackable
                                if (Enemy->debuffs["DMGPT"] != "") {// already available
                                    string idx = "1";
                                    string name = "DMGPT";
                                    while(Enemy->debuffs[name] != "") {
                                        idx = to_string(stoi(idx) + 1);
                                        name = "DMGPT" + idx;
                                    }
                                    Enemy->debuffs[name] = type_data[1] + '+' + type_data[2];
                                }
                            }
                        }
                    }
                    else --passive.Cooldown;
                }
                if (enm->ATK <= plr->DEF) {// can't attack through armor
                    if (!skipbattle) cout << "Enemy dealt 0 damage (- " << enm->ATK << " DEF)"<< "!\n";
                }
                else {
                    bool canCrit = 0;
                    if (enm->CC > plr->CR) {
                        int critc = enm->CC - plr->CR;
                        if (critc >= 100) {
                            canCrit = 1;
                        }
                        int crit_rd = rand() % 99 + 1;
                        if (crit_rd <= critc) canCrit = 1;
                    }
                    long long dmgdeal = enm->ATK - plr->DEF;
                    if (canCrit) dmgdeal = (dmgdeal * (100 + enm->CD)) / 100;
                    if (!skipbattle) cout << "Enemy dealt " << dmgdeal << " damage ";
                    if (!skipbattle) cout << (canCrit ? "(CRIT)\n" : "\n");
                    total_deal += dmgdeal;
                }
                plr->HP -= total_deal;
                if (plr->HP <= 0) break;
            }
            if (!skipbattle) cout << "Continue?\n";
            if (!skipbattle) cout << "[1] Yes\n";
            if (!skipbattle) cout << "[2] Retreat\n";
            if (!skipbattle) {
                int continueornot = getInput(continueornot);
                if (continueornot == 2) break;
            }
        }
        if (is_plrWin) {// give rewards here
            cout << "Congratulations! You have defeated the enemy!\n";
            cout << "Rewards: \n";
            for(string reward : enm->Reward) {
                vector<string> rewdata = splitString(reward,'+');
                int chance = stoi(rewdata[0]);
                string rewname = rewdata[1];
                long long quanity = stoi(rewdata[2]);
                cout << "--> " << rewname << " x" << quanity << '\n';
                int chance_rd = rand() % 99 + 1;
                if (chance_rd <= chance) {
                    if (rewname == "MCOIN") PLAYER->Mcoin += quanity;
                    if (rewname == "GOLD") PLAYER->Gold += quanity;
                    if (rewname == "EXP") PLAYER->EXP += quanity; 
                }
            }
        if (usrStage == PLAYER->ChallengeStage && usrStage < STAGE_CAP) ++PLAYER->ChallengeStage;
        } else {
            cout << "Unfortunately, you have been defeated by enemy!\n";
            int tip_idx = rand() % STRENGTHUP_TIPS.size();
            cout << STRENGTHUP_TIPS[tip_idx] << '\n';
        }
    }
    cout << "Back to homepage? (1)\n";
    int backornot = getInput(backornot);
    PLAYER->update_AllStats();
}
void System_Settings() {
    cout << "--[Settings]--\n";
    for(int i = 0;i<SETTINGS_LIST.size();++i) {
        string setname = SETTINGS_LIST[i];
        cout << '[' << i+1 << "] " << setname << " -- " << (PLAYER->settings[setname] ? "Enabled" : "Disabled") << '\n';
    }
    cout << '[' << SETTINGS_LIST.size() + 1 << "] Back\n";
    cout << "Select setting to configure: \n";
    int usr = getInput(usr);
    if (usr >= SETTINGS_LIST.size() + 1) return;
    string setname = SETTINGS_LIST[usr-1];
    cout << "Configure " << setname << ":\n";
    cout << "[1] Enable\n";
    cout << "[2] Disable\n";
    cout << "[3] Back\n";
    usr = getInput(usr);
    if(usr >= 3) return;
    PLAYER->settings[setname] = !(usr-1);
    cout << "Turned " << (PLAYER->settings[setname] ? "on " : "off ") << setname << '\n';
    cout << "Back to homepage? (1)\n";
    usr = getInput(usr);    
}
void Save() {
    // save data.dll
    string line;
    ifstream indata("bin/data.dll");
    vector<string> noticelines1;
    while(getline(indata,line)) {
        if (line[0] == '*') noticelines1.push_back(line);
    }
    indata.close();
    ofstream outdata("bin/data.dll");
    for(auto l : noticelines1) outdata << l << '\n';
    outdata << PLAYER->EXP << ' ' << PLAYER->Level << ' ' << PLAYER->Gold << ' ';
    outdata << PLAYER->Mcoin << ' ' << PLAYER->ChallengeStage;
    outdata.close();
    //save equipments.dll
    ifstream ineq("bin/equipments.dll");
    vector<string> noticelines2;
    while(getline(ineq,line)) {
        if (line[0] == '*') noticelines2.push_back(line);
    }
    ineq.close();
    ofstream outeq("bin/equipments.dll");
    for(auto l : noticelines2) outeq << l << '\n';
    for(auto eqName : equipmentList) {
        auto eq = PLAYER->equipments[eqName];
        outeq << eq.ID << '-' << eq.QualityID << '-' << eq.Level << '-' << eq.baseHP << '-' << eq.baseATK << '-';
        outeq << eq.baseDEF << '-' << eq.baseCC << '-' << eq.baseCD << '-' << eq.baseCR;
        if (eqName != "Accessory") outeq << '\n';
    }
    outeq.close();
    // save passives.dll
    ifstream inpas("bin/passives.dll");
    vector<string> noticelines3;
    while(getline(inpas,line)) {
        if (line[0] == '*') noticelines3.push_back(line);
    }
    inpas.close();
    ofstream outpas("bin/passives.dll");
    for(auto l : noticelines3) outpas << l << '\n';
    int idx = 0;
    for(auto passive : PLAYER->passives) {
        outpas << passive.first << '-' << passive.second.equippedSlot;
        ++idx;
        if (idx < PLAYER->passives.size()) outpas << '\n';
    }
    outpas.close();
    
    // save upgrades.dll
    ifstream inupgr("bin/upgrades.dll");
    vector<string> noticelines4;
    while(getline(inupgr,line)) {
        if (line[0] == '*') noticelines4.push_back(line);
    }
    inupgr.close();
    ofstream outupgr("bin/upgrades.dll");
    for(auto l : noticelines4) outupgr << l << '\n';
    idx = 0;
    for(auto upgr : UPGRADES_LIM) {
        outupgr << UPGRADES[upgr.first];
        ++idx;
        if (idx < UPGRADES_LIM.size()) outupgr << '-'; 
    }
    outupgr.close();
    // save settings.dll
    ifstream insetts("bin/settings.dll");
    vector<string> noticelines5;
    while(getline(insetts,line)) {
        if (line[0] == '*') noticelines5.push_back(line);
    }
    insetts.close();
    ofstream outsetts("bin/settings.dll");
    for(auto l : noticelines5) outsetts << l << '\n';
    idx = 0;
    for(auto sett : SETTINGS_LIST) {
        outsetts << PLAYER->settings[sett];
        ++idx;
        if (idx < SETTINGS_LIST.size()) outsetts << '-'; 
    }
    outsetts.close();
}
void GameSystem() {
    system("cls");    
    cout << "Welcome to Dummies Destoryer!\n";
    cout << GAME_TIPS[rand() % GAME_TIPS.size()] << '\n';
    cout << "--------[SYSTEM]--------" << '\n';    
    cout << "[1] Character" << '\n';    
    cout << "[2] Train" << '\n';    
    cout << "[3] Upgrades" << '\n';    
    cout << "[4] Shop" << '\n';
    cout << "[5] Challenges" << '\n';    
    cout << "[6] Settings" << '\n';    
    cout << "[7] Save and quit" << '\n';
    int user_option = getInput(user_option);
    if (user_option == 1) System_Character();
    if (user_option == 2) System_Train();
    if (user_option == 3) System_Upgrades();
    if (user_option == 4) System_Shop();
    if (user_option == 5) System_Challenges();
    if (user_option == 6) System_Settings();
    if (user_option >= 7) return;
    GameSystem();
}

int main() {
    // init random seed
    srand(time(0));
    PLAYER = Load_Game();
    GameSystem();
    Save();
}