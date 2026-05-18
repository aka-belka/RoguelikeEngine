#include "catch.hpp"
#include "Player.h"
#include "Monster.h"
#include "Item.h"

TEST_CASE("Player initialization", "[Player]") {
    Player p;
    
    SECTION("Default values are correct") {
        REQUIRE(p.getHealth() == 100);
        REQUIRE(p.getMaxHealth() == 100);
        REQUIRE(p.getLevel() == 1);
        REQUIRE(p.getExperience() == 0);
        REQUIRE(p.getAttackPower() == 15);
        REQUIRE(p.getDefense() == 5);
        REQUIRE(p.isAlive() == true);
        REQUIRE(p.getX() == 0);
        REQUIRE(p.getY() == 0);
    }
}

TEST_CASE("Player movement", "[Player]") {
    Player p;
    
    SECTION("Set position works") {
        p.setPosition(3, 4);
        REQUIRE(p.getX() == 3);
        REQUIRE(p.getY() == 4);
    }
}

TEST_CASE("Player takes damage", "[Player]") {
    Player p;
    
    SECTION("Damage reduces health correctly") {
        p.takeDamage(30);
        REQUIRE(p.getHealth() == 70);
        REQUIRE(p.isAlive() == true);
    }
    
    SECTION("Damage can kill player") {
        p.takeDamage(100);
        REQUIRE(p.getHealth() == 0);
        REQUIRE(p.isAlive() == false);
    }
    
    SECTION("Damage doesn't go below zero") {
        p.takeDamage(150);
        REQUIRE(p.getHealth() == 0);
        REQUIRE(p.isAlive() == false);
    }
}

TEST_CASE("Player healing", "[Player]") {
    Player p;
    p.takeDamage(50);
    REQUIRE(p.getHealth() == 50);
    
    SECTION("Heal increases health") {
        p.heal(30);
        REQUIRE(p.getHealth() == 80);
    }
    
    SECTION("Heal cannot exceed max health") {
        p.heal(60);
        REQUIRE(p.getHealth() == 100);
    }
}

TEST_CASE("Player gain experience", "[Player]") {
    Player p;
    
    SECTION("Gain EXP increases experience") {
        p.gainExp(50);
        REQUIRE(p.getExperience() == 50);
        REQUIRE(p.getLevel() == 1);
    }
    
    SECTION("Gaining 100 EXP triggers level up") {
        p.gainExp(100);
        REQUIRE(p.getLevel() == 2);
        REQUIRE(p.getAttackPower() == 20);
        REQUIRE(p.getDefense() == 7); 
        REQUIRE(p.getMaxHealth() == 120);
        REQUIRE(p.getHealth() == 120);    
    }
    
    SECTION("Gaining 250 EXP triggers one level up") {
        p.gainExp(250);
        REQUIRE(p.getLevel() == 2);  
        REQUIRE(p.getExperience() == 150);
    }
    SECTION("Gaining 300 EXP triggers two level ups") {
        p.gainExp(300);
        REQUIRE(p.getLevel() == 3);
        REQUIRE(p.getExperience() == 0);
    }
}

TEST_CASE("Player inventory", "[Player]") {
    Player p;
    
    SECTION("Pick up adds item to inventory") {
        Item* potion = new Item("p1", "Heal Potion", "potion", 50, 0, 0);
        p.pickUp(potion);
        REQUIRE(p.getInventory().size() == 1);
    }
    
    SECTION("Use potion heals and removes from inventory") {
        Item* potion = new Item("p1", "Heal Potion", "potion", 50, 0, 0);
        p.takeDamage(40);
        p.pickUp(potion);
        p.useItem(0);
        REQUIRE(p.getHealth() == 100);
        REQUIRE(p.getInventory().empty());
    }
    
    SECTION("Use weapon increases attack power") {
        Item* sword = new Item("s1", "Iron Sword", "weapon", 0, 10, 0);
        p.pickUp(sword);
        int oldAttack = p.getAttackPower();
        p.useItem(0);
        REQUIRE(p.getAttackPower() == oldAttack + 10);
        REQUIRE(p.getInventory().empty());
    }
    
    SECTION("Use armor increases defense") {
        Item* armor = new Item("a1", "Leather Armor", "armor", 0, 0, 5);
        p.pickUp(armor);
        int oldDefense = p.getDefense();
        p.useItem(0);
        REQUIRE(p.getDefense() == oldDefense + 5);
        REQUIRE(p.getInventory().empty());
    }
}

TEST_CASE("Player attack monster", "[Player]") {
    Player p;
    
    SECTION("Attack deals damage based on attack vs defense") {
        Monster* m = new Monster("gob", "Goblin", 50, 10, 3, 50);
        int oldHealth = m->getHealth();
        p.attack(m);
        // Player ATK=15, Monster DEF=3, damage = 12
        REQUIRE(m->getHealth() == oldHealth - 12);
        delete m;
    }

    SECTION("Attack deals minimum 1 damage even if defense higher") {
        Monster* tough = new Monster("tough", "Tough Monster", 50, 10, 100, 50);
        int oldHealth = tough->getHealth();
        p.attack(tough);
        // Player ATK=15, Monster DEF=100 → damage = min(1)
        REQUIRE(tough->getHealth() == oldHealth - 1);
        delete tough;
    }
}