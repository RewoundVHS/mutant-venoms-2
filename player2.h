// Neve Laughery
// CSCI330

#ifndef _PLAYER
#define _PLAYER

#include <string>
#include <iostream>
#include <sstream>
#include "gamespace.h"
#include "dice.h"
#include "wpn.h"

using namespace std;
using namespace GameSpace;

class PlayerClass {

    public:
        enum PlayerType {
            HUNTER,
            SCAVENGER,
            FROG,
            SPIDER,
            VIPER
        };

        enum StatType {
            MAX_HEALTH,
            HEALTH,
            WILLPOWER,
            MAX_SPEED,
            CUR_SPEED,
            MOMENTUM,
            POWER,
            DAMAGE_ROLLS,
            ROLL_FACES,
            DEFENSE,
            CUR_WPN_SKILL,
            ROW,
            COL,
            ACTIVE,
            DIR
        };

    private: 
        static const string DEFAULT_NAME; 
        static const PlayerType DEFAULT_TYPE;
        static const int MAX_TYPES = 5;
        static const int MAX_STATS = 15;
        static const int DEFAULT_POS = -1;
        static const int MAX_2D6 = 13;
        static const int MAX_PWR = 13;
        static const int MAX_WILL = 13;
        static const int NUM_HUMAN_TYPES = 2;
        static const int w = -1;
        static const int k = 0;
        static const int STATS[MAX_STATS][MAX_TYPES];
        static const int INIT_WPN_SKILL[Weapon::NUM_DIFF_WEAPONS][NUM_HUMAN_TYPES];
        static const int IMPACT[MAX_2D6][MAX_PWR];  
        static const int CRITICAL_WOUND[MAX_2D6][MAX_WILL];

        PlayerClass();

    public:
        /*
        Narrative: Initializes an instance of the player class
        */
        PlayerClass(string initName = DEFAULT_NAME, PlayerType initType = DEFAULT_TYPE);

        /*
        Narrative: Calls CopyIntoMe on the given instance of a player class to 
        copy into this instance
        Pre-condition: None
        Post-condition: The player class has been copied into this player class
        */
        PlayerClass(const PlayerClass &p);

        /*
        Narrative: Checks to see if this instance is not the same as the given 
        player then calls CopyIntoMe on the given instance of a player class to 
        copy into this instance
        Pre-condition: None
        Post-condition: The player class has been copied into this player class
        */
        PlayerClass& operator=(const PlayerClass &p);

        /*
        Narrative: Copies all of the data from the given player into the current
        player
        Pre-condition: None
        Post-condition: The given player's data has been copied into this player
        */
        void CopyIntoMe(const PlayerClass &p);

        /*
        Narrative: This destructor deallocates the dynamic memory for playerWeapon
        Pre-condition: None
        Post-condition: The dynamic memory has been properly deallocated
        */
        ~PlayerClass();

        /*
        Narrative: Returns the player's name
        Pre-condition: Player's name has been initialized
        Post-condition: Player's name has been returned
        */
        string Name() const;
        
        /*
        Narrative: Returns the player's type
        Pre-condition: Player's type is within boundaries
        Post-condition: Player's type has been returned  
        */
        int Type() const;
        
        /*
        Narrative: Returns the player's type as a string
        Pre-condition: Player's type has been initialized
        Post-condition: Type string has been returned
        */
        string TypeStr() const;
        
        /*
        Narrative: Returns the player's cell row
        Pre-condition: Player's cell row has been initialized
        Post-condition: Players's cell row has been returned
        */
        int Row() const;
        
        /*
        Narrative: Returns the player's cell col
        Pre-condition: Player's cell col has been initialized
        Post-condition: Players's cell col has been returned
        */
        int Col() const;
        
        /*
        Narrative: Returns the associated character for a DirType
        Pre-condition: Dir is within boundaries
        Post-condition: Character has been returned
        */
        char Dir() const;
        
        /*
        Narrative: Returns the player's health
        Pre-condition: Player's health has been initialized
        Post-condition: Player's health has been returned
        */
        int Health() const;
        
        /*
        Narrative: Returns the player's willpower
        Pre-condition: Player's willpower has been initialized
        Post-condition: Player's willpower has been returned
        */
        int WillPower() const;
        
        /*
        Narrative: Returns the player's maximum speed 
        Pre-condition: Player's maximum speed has been initialized
        Post-condition: Player's speed has been returned
        */
        int MaxSpeed() const;
        
        /*
        Narrative: Returns the player's current speed
        Pre-condition: Player's current speed has been initialized
        Post-condition: Player's current speed has been returned 
        */
        int CurrentSpeed() const;
        
        /*
        Narrative: Returns the player's momentum
        Pre-condition: Player's momentum has been initialized
        Post-condition: Player's momentum has been returned
        */
        int Momentum() const;
        
        /*
        Narrative: Returns the player's power
        Pre-condition: Player's power has been initialized
        Post-condition: Player's power has been returned 
        */
        int Power() const;
        
        /*
        Narrative: Returns the player's rolled physical damage
        Pre-condition: Player's rolled physical damage has been initialized
        Post-condition: Player's rolled physical damage has been returned  
        */
        int RollPhysDam() const;
        
        /*
        Narrative: Returns the player's defense value 
        Pre-condition: Player's defense value has been initialized
        Post-condition: Player's defense value has been returned 
        */
        int Defense() const;
        
        /*
        Narrative: Returns whether or not the player is a human
        Pre-condition: Human bool has been initialized
        Post-condition: Human bool has been returned 
        */
        bool Human() const;
        
        /*
        Narrative: Returns whether or not the player is a venom
        Pre-condition: Venom bool has been initialized
        Post-condition: Venom bool has been returned 
        */
        bool Venom() const;
        
        /*
        Narrative: Returns whether or not the player is alive
        Pre-condition: Alive bool has been initialized
        Post-condition: Alive bool has been returned
        */
        bool IsAlive() const;
        
        /*
        Narrative: Returns whether or not the player is dead
        Pre-condition: Alive bool has been initialized
        Post-condition: Opposite of the alive bool has been returned 
        */
        bool IsDead() const;
        
        /*
        Narrative: Returns whether or not the player is active
        Pre-condition: Active bool has been initialized
        Post-condition: Active bool has been returned 
        */
        bool IsActive() const;
        
        /*
        Narrative: Determines if player p is an enemy. P is an enemy if the 
        player is human and enemy is a venom or if the player is a venom and
        the enemy is any other type but their own.
        Pre-condition: P is not null
        Post-condition: Returns true if player p is an enemy and false if it is
        not.
        */
        bool IsMyEnemy(PlayerClass* p) const;
        
        /*
        Narrative: Sets the player's state to active if the player is alive
        Pre-condition: None
        Post-condition: Returns true if the function was able to set the state 
        to active and false if it could not
        */
        bool MakeActive();
        
        /*
        Narrative: Sets the player's status to inactive and returns true
        Pre-condition: None
        Post-condition: Player's status has been set to inactive and true has 
        been returned 
        */
        bool MakeInActive();
        
        /*
        Narrative: Sets all of the appropriate values to indicate the player 
        has died
        Pre-condition: None
        Post-condition: Health, willpower, current speed, and active have been 
        set to 0 then returns true 
        */
        bool MakeDead();
        
        /*
        Narrative: Applies the damage if the player is active and the damage is 
        greater than or equal to zero
        Pre-condition: None
        Post-condition: Damage has been applied if player is active and the 
        damage is greater than or equal to zero 
        */
        int Wounded(int damage);
        
        /*
        Narrative: If the player is active and vigor amount is greater than or 
        equal to zero the player is healed
        Pre-condition: None
        Post-condition: If the player is active it is healed for vigor amount 
        and health is returned
        */
        int Invigorate(int vigor);
        
        /*
        Narrative: If the player is active and alive the player's speed is set 
        to maximum speed and the player is healed
        Pre-condition: None
        Post-condition: If the player is active and alive, the player is healed 
        and gains maximum speed 
        */
        bool Heal();
        
        /*
        Narrative: A given amount is subtracted from the player's willpower, if
        the willpower drops below zero it is set to zero
        Pre-condition: None
        Post-condition: The amount has subtracted from the willpower
        */
        int WillDamage(int willDmg);

        /*
        Narrative: A given amount is added to the player's willpower
        Pre-condition: None
        Post-condition: The amount has been added to the willpower
        */
        int AddWill(int addWill);

        /*
        Narrative: Detracts an amount from the player's current speed if they are active
        Pre-condition: None
        Post-condition: Hazard has been applied, if the player's momentum is less 
        than their speed their momentum is set equal to current speed. Current 
        speed is returned.
        */
        int SlowDown(int hazard);
        
        /*
        Narrative: If the player is active their current speed is set to maximum
        speed
        Pre-condition: None
        Post-condition: If the player is active their current speed has been 
        reset to maximum speed 
        */
        int ResetCurrentSpeed();
        
        /*
        Narrative: If the player is active their momentum is set to their current speed
        Pre-condition: None
        Post-condition: If the player is active their momentum has been set to 
        their current speed 
        */
        int ResetMomentum();
        
        /*
        Narrative: If the player is active and num is greater than or equal to 
        0 num is subtracted from their momentum
        Pre-condition: None
        Post-condition: If the player is active num has been removed from their 
        momentum 
        */
        int UseMomentum(int num);
        
        /*
        Narrative: Sets the cell that the player will now reside in
        Pre-condition: None
        Post-condition: Checks to see if the new coordinates are valid. If they
        are, sets them and returns true, otherwise returns false. 
        */
        bool SetCell(int newRow, int newCol);
        
        /*
        Narrative: Sets the player's new direction
        Pre-condition: None
        Post-condition: New direction has been set and true has been returned
        */
        bool SetDir(DirType newDir);
        
        /*
        Narrative: An amount is added to or subtracted from the player's defense
        value, if defense drops below zero it is set to zero
        Pre-condition: None
        Post-condition: The amount has been added to or subtracted from defense
        */
        int UpdateDefense(int amount);

        /*
        Narrative: Performs a HitScore roll
        Pre-condition: Dice class has been properly linked
        Post-condition: HitScore roll is returned
        */
        int HitScore() const;

        /*
        Narrative: Returns the amount of damage done by an active player. This 
        damage value is found either by weapon damage or power if the player 
        does not have a weapon. 
        Pre-condition: Weapon class has been properly linked
        Post-condition: The damage is returned
        */
        int HitDamage() const;

        /*
        Narrative: Makes an impact roll for an active player then gets their 
        power from either weapon damage or power if they do not have a weapon. 
        These two values are used to index the impact table which returns the 
        result.
        Pre-condition: Dice class and weapon class have been properly linked.
        Post-condition: Impact table result has been returned
        */
        int Impact() const;

        /*
        Narrative: The player takes a critical wound which slows them for half 
        of their speed, then a critical wound roll and their willpower are 
        used to index the critical wound table. The player either takes 1 
        damage to willpower or is killed.
        Pre-condition: None
        Post-condition: The player is either killed or takes 1 damage to willpower.
        */
        bool CriticalWound();

        /*
        Narrative: Returns the name of the player's weapon.
        Pre-condition: Weapon class has been properly linked
        Post-condition: The weapon's name is returned. If the player did not have 
        a weapon an empty string is returned.
        */
        string WeaponName() const;

        /*
        Narrative: The player's weapon skill for their current weapon is returned
        Pre-condition: Weapon class has been properly linked
        Post-condition: Current weapon skill has been returned
        */
        int WeaponSkill() const;

        /*
        Narrative: The player's weapon is returned. If the player is holding a 
        weapon their weapon pointer is set to NULL.
        Pre-condition: None
        Post-condition: Weapon has been set to NULL if the player was holding 
        one and previous weapon has been returned
        */
        Weapon* DropWeapon();

        /*
        Narrative: Returns whether or not the player is holding a weapon
        Pre-condition: None
        Post-condition: Bool representing whether or not the player is holding 
        a weapon is returned
        */
        bool HasWeapon() const;

        /*
        Narrative: An active human player recieves the weapon. If they had no 
        weapon skill for this weapon they now have one weapon skill point for it.
        Pre-condition: None
        Post-condition: The player now has the given weapon and their previous 
        weapon has been returned.
        */
        Weapon* GrabWeapon(Weapon* weapon);

        /*
        Narrative: An amount is added to the player's skill for their current weapon
        Pre-condition: None
        Post-condition: The weapon skill improvement amount has been added 
        */
        bool ImprovedSkill(int improvement);

        /*
        Narrative: Converts a string to all uppercase
        Pre-condition: None
        Post-condition: The string has been made all uppercase
        */
        string MakeUpper(string str) const;

        /*
        Narrative: Compares the name of a given player and this player to see 
        if this player's name is equal to the given player's name
        Pre-condition: None
        Post-condition: Bool representing whether or not this player's name is 
        equal to the given player's name is returned
        */
        bool operator==(const PlayerClass &p) const;

        /*
        Narrative: Compares the name of a given player and this player to see 
        if this player's name is not equal to the given player's name
        Pre-condition: None
        Post-condition: Bool representing whether or not this player's name is 
        not equal to the given player's name is returned
        */
        bool operator!=(const PlayerClass &p) const;

        /*
        Narrative: Compares the name of a given player and this player to see 
        if this player's name is less than or equal to to the given player's name
        Pre-condition: None
        Post-condition: Bool representing whether or not this player's name is 
        less than or equal to the given player's name is returned
        */
        bool operator<=(const PlayerClass &p) const;

        /*
        Narrative: Compares the name of a given player and this player to see 
        if this player's name is less than the given player's name
        Pre-condition: None
        Post-condition: Bool representing whether or not this player's name is 
        less than the given player's name is returned
        */
        bool operator<(const PlayerClass &p) const;

        /*
        Narrative: Compares the name of a given player and this player to see 
        if this player's name is greater than or equal to the given player's name
        Pre-condition: None
        Post-condition: Bool representing whether or not this player's name is 
        greather than or equal to the given player's name is returned
        */
        bool operator>=(const PlayerClass &p) const;

        /*
        Narrative: Compares the name of a given player and this player to see 
        if this player's name is greater than the given player's name
        Pre-condition: None
        Post-condition: Bool representing whether or not this player's name is 
        greather than the given player's name is returned
        */
        bool operator>(const PlayerClass &p) const;

        /*
        Narrative: Adds the player's statistics in a human readable format to a 
        stream
        Pre-condition: None
        Post-condition: Player's statistics have been returned 
        */
        void Write(ostream& out) const;

    private:
        // Array of all of the stats a player has
        int playerStats[MAX_STATS];     

        // Array of the player's weapon skill values
        int allWeaponSkill[Weapon::NUM_DIFF_WEAPONS];

        string name;    // Player's name
        int type;       // Player's type
        DirType dir;    // Player's direction
        bool human;     // Whether or not the player is a human
        bool venom;     // Whether or not the player is a venom
        Weapon* playerWeapon;

};

/*
Narrative: Adds a player's statistics stream to a stream
Pre-condition: None
Post-condition: Statistics have been added to the stream and returned
*/
ostream& operator<<(ostream& out, const PlayerClass *p);

#endif
