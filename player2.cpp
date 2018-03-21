// Neve Laughery
// CSCI330

#include "player2.h"

const string PlayerClass::DEFAULT_NAME = "DEFAULT"; 
const PlayerClass::PlayerType PlayerClass::DEFAULT_TYPE = PlayerClass::HUNTER;

const int PlayerClass::STATS[MAX_STATS][MAX_TYPES] = {
//   Hu  Sc  Fr  Sp  Vi
    {43, 82, 61, 51, 21},    // Max health
    {43, 82, 61, 51, 21},    // Health
    { 8, 10, 10,  9,  8},    // Willpower
    { 9,  6,  9, 16,  3},    // Max speed
    { 9,  6,  9, 16,  3},    // Current speed
    { 9,  6,  9, 16,  3},    // Momentum
    { 7, 10, 11, 12,  6},    // Power
    { 1,  3,  3,  2,  2},    // Physical damage rolls
    { 6,  6,  6,  6,  6},    // Faces on damage roll dice
    { 1,  9,  9,  8, 11},    // Defense value
    { 0,  0,  0,  0,  0},    // Current weapon skill
    {-1, -1, -1, -1, -1},    // Row
    {-1, -1, -1, -1, -1},    // Col
    { 0,  0,  0,  0,  0},    // Active
    { 0,  0,  0,  0,  0}};   // Direction

const int PlayerClass::INIT_WPN_SKILL[Weapon::NUM_DIFF_WEAPONS][NUM_HUMAN_TYPES] = {
//   Hu  Sc
    { 0,  0},   // GRENADE
    { 0,  0},   // HVYWPN
    { 0, 10},   // PISTOL
    { 5,  0}};  // RIFLE

const int PlayerClass::IMPACT[MAX_2D6][MAX_PWR] = {   
//                  Power Rating
//    0   1   2   3   4   5   6   7   8   9  10  11  12    Die Roll
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},  // 0
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},  // 1
    { 0,  0,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10},  // 2
    { 0,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10,  w},  // 3
    { 0,  0,  2,  3,  4,  5,  6,  7,  8,  9, 10,  w,  w},  // 4
    { 0,  0,  3,  4,  5,  6,  7,  8,  9, 10,  w,  w,  w},  // 5
    { 0,  0,  4,  5,  6,  7,  8,  9, 10,  w,  w,  w,  w},  // 6
    { 0,  0,  5,  6,  7,  8,  9, 10,  w,  w,  w,  w,  w},  // 7
    { 0,  0,  6,  7,  8,  9, 10,  w,  w,  w,  w,  w,  w},  // 8
    { 0,  0,  7,  8,  9, 10,  w,  w,  w,  w,  w,  w,  w},  // 9
    { 0,  0,  8,  9, 10,  w,  w,  w,  w,  w,  w,  w,  w},  // 10
    { 0,  0,  9, 10,  w,  w,  w,  w,  w,  w,  w,  w,  w},  // 11
    { 0,  0, 10,  w,  w,  w,  w,  w,  w,  w,  w,  w,  w}}; // 12

const int PlayerClass::CRITICAL_WOUND[MAX_2D6][MAX_WILL] = {
//                  Willpower Rating           
//    0   1   2   3   4   5   6   7   8   9  10  11  12    Die Roll
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  // 0
    { k, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  // 1
    { k,  k, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  // 2
    { k,  k,  k, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  // 3
    { k,  k,  k,  k, -1, -1, -1, -1, -1, -1, -1, -1, -1},  // 4
    { k,  k,  k,  k,  k, -1, -1, -1, -1, -1, -1, -1, -1},  // 5
    { k,  k,  k,  k,  k,  k, -1, -1, -1, -1, -1, -1, -1},  // 6
    { k,  k,  k,  k,  k,  k,  k, -1, -1, -1, -1, -1, -1},  // 7 
    { k,  k,  k,  k,  k,  k,  k,  k, -1, -1, -1, -1, -1},  // 8  
    { k,  k,  k,  k,  k,  k,  k,  k,  k, -1, -1, -1, -1},  // 9  
    { k,  k,  k,  k,  k,  k,  k,  k,  k,  k, -1, -1, -1},  // 10 
    { k,  k,  k,  k,  k,  k,  k,  k,  k,  k,  k, -1, -1},  // 11
    { k,  k,  k,  k,  k,  k,  k,  k,  k,  k,  k,  k, -1}}; // 12

PlayerClass::PlayerClass() {
    name = DEFAULT_NAME;
    type = DEFAULT_TYPE;

    for (int i=0; i<MAX_STATS; i++) {
        playerStats[i] = STATS[i][type];
    }

    for (int i=0; i<Weapon::NUM_DIFF_WEAPONS; i++) {
         allWeaponSkill[i] = INIT_WPN_SKILL[i][type];
    }
    // GrabWeapon(DEFAULT_HUNTER_WEAPON);
}

PlayerClass::PlayerClass(string initName, PlayerType initType) {
    if (initName.size() <= 0)
        name = DEFAULT_NAME;
    else {
        name = initName;
        stringstream ss(name);
        string word;
        while (ss >> word) {
            name += (word + " ");
        }
        name = name.substr(0, name.size()-1);
    }
    if (initType >= HUNTER && initType < MAX_TYPES)
        type = initType;
    else
        type = DEFAULT_TYPE;

    for (int i=0; i<MAX_STATS; i++) {
        playerStats[i] = STATS[i][type];
    }
    
    if (Human()) {
        for (int i=0; i<Weapon::NUM_DIFF_WEAPONS; i++) {
             allWeaponSkill[i] = INIT_WPN_SKILL[i][type];
        }
        
        switch (type) { 
            case HUNTER:
                // GrabWeapon(DEFAULT_HUNTER_WEAPON);
                break;
            case SCAVENGER:
                // GrabWeapon(DEFAULT_SCAVENGER_WEAPON);
                break;
        }
    }
}

string PlayerClass::Name() const {
    return name;
}

int PlayerClass::Type() const {
    return type;
}

string PlayerClass::TypeStr() const {
    string typeString;

    switch (type) {
        case HUNTER:
            typeString = "HUNTER";
            break;
        case SCAVENGER:
            typeString  = "SCAVENGER";
            break;
        case FROG:
            typeString = "FROG";
            break;
        case SPIDER:
            typeString = "SPIDER";
            break;
        case VIPER:
            typeString = "VIPER";
            break;
    }
    return typeString;
}

int PlayerClass::Row() const{
    return playerStats[ROW];
}

int PlayerClass::Col() const {
    return playerStats[COL];
}

char PlayerClass::Dir() const {
    return GameSpace::DIR_CHAR[playerStats[DIR]];  
}

int PlayerClass::Health() const {
    return playerStats[HEALTH];
}

int PlayerClass::WillPower() const {
    return playerStats[WILLPOWER];
}

int PlayerClass::MaxSpeed() const {
    return playerStats[MAX_SPEED];
}

int PlayerClass::CurrentSpeed() const {
    return playerStats[CUR_SPEED];
}

int PlayerClass::Momentum() const {
    return playerStats[MOMENTUM];
}

int PlayerClass::Power() const {
    return playerStats[POWER];
}

int PlayerClass::RollPhysDam() const {
    return Dice::Roll(name, GameSpace::DAMAGE, playerStats[DAMAGE_ROLLS], playerStats[ROLL_FACES]);
}

int PlayerClass::Defense() const {
    return playerStats[DEFENSE];
}

bool PlayerClass::Human() const {  
    bool isHuman;
    switch (type) {
        case HUNTER:
            isHuman = true;
            break;
        case SCAVENGER:
            isHuman = true;
            break;
        default:
            isHuman = false;
            break;
    }
    return isHuman;
}

bool PlayerClass::Venom() const {  
    bool isVenom;
    switch (type) {
        case FROG:
            isVenom = true;
            break;
        case SPIDER:
            isVenom = true;
            break;
        case VIPER:
            isVenom = true;
            break;
        default:
            isVenom = false;
            break;
    }
    return isVenom;
}

bool PlayerClass::IsAlive() const {
    return (playerStats[HEALTH] > 0 || playerStats[WILLPOWER] > 0);
}

bool PlayerClass::IsDead() const {
    return (playerStats[HEALTH] <= 0 || playerStats[WILLPOWER] <= 0);
}

bool PlayerClass::IsActive() const { 
    return (playerStats[ACTIVE] == 1); 
}

bool PlayerClass::IsMyEnemy(PlayerClass* p) const {
    bool isEnemy = false;
    if (p != NULL) 
        isEnemy = ((Human()) && !(p->Human()) || (Venom() && (type != p->Type())));

    return (isEnemy);
}

bool PlayerClass::MakeActive() {
    bool set = false;

    if (IsAlive()) {
        playerStats[ACTIVE] = 1;
        set = true;
    }
    return set;
}

bool PlayerClass::MakeInActive() {
    playerStats[ACTIVE] = 0;
    return true;
}

bool PlayerClass::MakeDead() {
    if (IsActive() || IsDead()) {
        playerStats[HEALTH] = 0;
        playerStats[WILLPOWER] = 0;
        playerStats[CUR_SPEED] = 0;
        playerStats[MOMENTUM] = 0;
        playerStats[ACTIVE] = 0;
    }
    return IsDead();
}

int PlayerClass::Wounded(int damage) {
    if (IsActive() && damage >= 0) 
        playerStats[HEALTH] -= damage;

    if (IsDead())
        MakeDead();

    return playerStats[HEALTH];
}

int PlayerClass::Invigorate(int vigor) {
    if ((IsActive()) && (vigor >= 0)) {
        playerStats[HEALTH] += vigor;
        if (playerStats[HEALTH] > playerStats[MAX_HEALTH])
            playerStats[HEALTH] = playerStats[MAX_HEALTH];
    }
    return playerStats[HEALTH];
}

bool PlayerClass::Heal() {
    int healAmount = 10;
    bool healed = false;

    if (IsActive() && IsAlive()) {
        playerStats[CUR_SPEED] = playerStats[MAX_SPEED];
        playerStats[HEALTH] += healAmount;
        if (playerStats[HEALTH] > playerStats[MAX_HEALTH])
            playerStats[HEALTH] = playerStats[MAX_HEALTH];
        healed = true;
    }
    return healed;
}

int PlayerClass::WillDamage(int willDmg) {
    if (IsActive() && (willDmg >= 0))
        playerStats[WILLPOWER] -= willDmg;

    if (playerStats[WILLPOWER] <= 0)
        MakeDead();
}

int PlayerClass::AddWill(int addWill) {
    if (IsActive() && (addWill >= 0))
        playerStats[WILLPOWER] += addWill;

    return playerStats[WILLPOWER];
}

int PlayerClass::SlowDown(int hazard) {
    if (IsActive() && hazard >= 0) {
        playerStats[CUR_SPEED] -= hazard;
        if (playerStats[CUR_SPEED] < 0)
            playerStats[CUR_SPEED] = 0;
        if (playerStats[MOMENTUM] > playerStats[CUR_SPEED])
            ResetMomentum();
    }
    return playerStats[CUR_SPEED];
}

int PlayerClass::ResetCurrentSpeed() {
    if (IsActive()) 
        playerStats[CUR_SPEED] = playerStats[MAX_SPEED];
    
    return playerStats[CUR_SPEED];
}

int PlayerClass::ResetMomentum() {
    if (IsActive()) 
        playerStats[MOMENTUM] = playerStats[CUR_SPEED];

    return playerStats[MOMENTUM];
}

int PlayerClass::UseMomentum(int num) {
    if (IsActive() && num >= 0) {
        playerStats[MOMENTUM] -= num;
        if (playerStats[MOMENTUM] < 0) 
            playerStats[MOMENTUM] = 0; 
    }
    return playerStats[MOMENTUM];
}

bool PlayerClass::SetCell(int newRow, int newCol) {
    bool set = false;

    if ((newRow >= 0 && newCol >= 0) || (newRow == -1 && newCol == -1)) {
        playerStats[ROW] = newRow;
        playerStats[COL] = newCol;
        set = true;
    }
    return set;
}

bool PlayerClass::SetDir(DirType newDir) {
    bool set = false;
    if (newDir >= GameSpace::NORTH && newDir <= GameSpace::WEST) {
        playerStats[DIR] = newDir;
        set = true;
    }
    return set;
}

// Needs modified to include weapon data
void PlayerClass::Write(ostream& out) const {
    out << TypeStr() << '#';
    if (IsActive())
        out << '1';
    else
        out << '0';
    out << '#' << Name() << '#' << '(' << Row() << ',' << Col() << ',' << Dir()
    << ")#" << Health() << '#' << WillPower() << '#' << Power() << '#' 
    << CurrentSpeed() << '#' << Momentum() << '#' << playerStats[DAMAGE_ROLLS] 
    << 'D' << playerStats[ROLL_FACES] << '#' << Defense() << '#' << endl;
}

// Might need modified along with Write
ostream& operator<<(ostream& out, const PlayerClass *p) {
    if (p != NULL)
        p->Write(out);
    return out;
}

int PlayerClass::UpdateDefense(int amount) {
    if (IsActive())
        playerStats[DEFENSE] += amount;
    if(playerStats[DEFENSE] < 0);
        playerStats[DEFENSE] = 0;

    return playerStats[DEFENSE];
}

int PlayerClass::HitScore() const {
    return Dice::Roll(name, GameSpace::HITSCORE, 2, 6); 
}

int PlayerClass::HitDamage() const {
    int damage = 0;

    if (IsActive()) {
        if (HasWeapon()) {
             // damage = playerStats[CUR_WPN_SKILL] + /*damage value of wpn*/;
        } else {
            damage = playerStats[POWER] + RollPhysDam();
        }
    }
    return damage;
}

int PlayerClass::Impact() const{
    int impact = 0;
    int power;
    if (IsActive()) {
        int roll = Dice::Roll(name, GameSpace::IMPACT, 2, 6);
        if (roll >= 2 && roll <= 12) { 
            if (HasWeapon())
                power = playerWeapon->WeaponPower();
            else if (playerStats[POWER] >= 2)
                power = playerStats[POWER];
            
        impact = IMPACT[roll][power]; 
        }
    }
    return impact;
}

bool PlayerClass::CriticalWound() {
    int damage =10;
    int willDmg = 1;
    int roll;
    int slowed = playerStats[CUR_SPEED] - playerStats[CUR_SPEED]/2 ;
    int crit;

    if(IsActive()) {
        Wounded(damage);
        SlowDown(slowed);
        if (IsAlive()) {
            // Is it appropriate to have the floating 2 and 6 here?
            roll = Dice::Roll(name, GameSpace::WOUND, 2, 6);
            crit = CRITICAL_WOUND[roll][playerStats[WILLPOWER]];

            if (crit = -1)
                WillDamage(willDmg);
            else
                MakeDead();
        }
    }
    return IsAlive();
}

string PlayerClass::WeaponName() const {
    return playerWeapon->WeaponName();
}

int PlayerClass::WeaponSkill() const {
    int skill = 0;
    if (HasWeapon())
        skill = playerStats[CUR_WPN_SKILL];
    return skill;
}

Weapon* PlayerClass::DropWeapon() {
    Weapon* dropped;

    if (IsActive()) {
        dropped = playerWeapon;
        playerWeapon = NULL;
    }
    return dropped;
}

bool PlayerClass::HasWeapon() const {
    return(playerWeapon != NULL);
}

Weapon* PlayerClass::GrabWeapon(Weapon* weapon) {
    Weapon* oldWeapon = playerWeapon;

    if (IsActive() && Human())
        playerWeapon = weapon;
    // If player has skill with weapon, skill is used
    // Otherwise weapon skill is set to 1
}

bool PlayerClass::ImprovedSkill(int improvement) {    
    
}

string PlayerClass::MakeUpper(string str) const {
    string makeUpper = str;
    transform(makeUpper.begin(), makeUpper.end(), makeUpper.begin(), ::toupper);
    return makeUpper;
}

bool PlayerClass::operator==(const PlayerClass &p) const {
    string pUpper = MakeUpper(p.Name());
    string thisUpper = MakeUpper(Name());

    return (thisUpper == pUpper);   
}

bool PlayerClass::operator!=(const PlayerClass &p) const {
    string pUpper = MakeUpper(p.Name());
    string thisUpper = MakeUpper(Name());

    return (thisUpper != pUpper);   
}

bool PlayerClass::operator<=(const PlayerClass &p) const {
    string pUpper = MakeUpper(p.Name());
    string thisUpper = MakeUpper(Name());

    return (thisUpper <= pUpper);   
}

bool PlayerClass::operator<(const PlayerClass &p) const {
    string pUpper = MakeUpper(p.Name());
    string thisUpper = MakeUpper(Name());

    return (thisUpper < pUpper);   
}

bool PlayerClass::operator>=(const PlayerClass &p) const {
    string pUpper = MakeUpper(p.Name());
    string thisUpper = MakeUpper(Name());

    return (thisUpper >= pUpper);   
}

bool PlayerClass::operator>(const PlayerClass &p) const {
    string pUpper = MakeUpper(p.Name());
    string thisUpper = MakeUpper(Name());

    return (thisUpper > pUpper);   
}
