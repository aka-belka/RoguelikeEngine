#include "catch.hpp"
#include "Monster.h"
#include "Player.h"

TEST_CASE("Monster initialization", "[Monster]") {
    Monster m("goblin", "Goblin", 50, 12, 3, 100);
    
    SECTION("Default values are correct") {
        REQUIRE(m.getName() == "Goblin");
        REQUIRE(m.getHealth() == 50);
        REQUIRE(m.getMaxHealth() == 50);
        REQUIRE(m.getAttackPower() == 12);
        REQUIRE(m.getDefense() == 3);
        REQUIRE(m.getExpReward() == 100);
        REQUIRE(m.isAlive() == true);
    }
}

TEST_CASE("Monster copy constructor", "[Monster]") {
    Monster original("orc", "Orc", 80, 15, 5, 150);
    original.addDropItemId("potion");
    original.addDropItemId("gold");
    
    Monster copy(original);
    
    SECTION("Copy has same attributes") {
        REQUIRE(copy.getName() == "Orc");
        REQUIRE(copy.getHealth() == 80);
        REQUIRE(copy.getAttackPower() == 15);
        REQUIRE(copy.getExpReward() == 150);
    }
    
    SECTION("Copy has same drop items") {
        REQUIRE(copy.getDropItemIds().size() == 2);
        REQUIRE(copy.getDropItemIds()[0] == "potion");
    }
}

TEST_CASE("Monster takes damage", "[Monster]") {
    Monster m("goblin", "Goblin", 50, 12, 3, 100);
    
    SECTION("Damage reduces health") {
        m.takeDamage(20);
        REQUIRE(m.getHealth() == 30);
        REQUIRE(m.isAlive() == true);
    }
    
    SECTION("Damage can kill monster") {
        m.takeDamage(50);
        REQUIRE(m.getHealth() == 0);
        REQUIRE(m.isAlive() == false);
    }
}

TEST_CASE("Monster setters", "[Monster]") {
    Monster m("goblin", "Goblin", 50, 12, 3, 100);
    
    SECTION("setHealth works") {
        m.setHealth(200);
        REQUIRE(m.getHealth() == 200);
        REQUIRE(m.getMaxHealth() == 200);
    }
    
    SECTION("setAttackPower works") {
        m.setAttackPower(30);
        REQUIRE(m.getAttackPower() == 30);
    }
    
    SECTION("setExpReward works") {
        m.setExpReward(500);
        REQUIRE(m.getExpReward() == 500);
    }
}

TEST_CASE("Monster drop items", "[Monster]") {
    Monster m("goblin", "Goblin", 50, 12, 3, 100);
    
    SECTION("Add drop item") {
        m.addDropItemId("health_potion");
        REQUIRE(m.getDropItemIds().size() == 1);
        REQUIRE(m.getDropItemIds()[0] == "health_potion");
    }
    
    SECTION("Add multiple drop items") {
        m.addDropItemId("potion");
        m.addDropItemId("sword");
        m.addDropItemId("gold");
        REQUIRE(m.getDropItemIds().size() == 3);
    }
}

TEST_CASE("Monster attacks player", "[Monster]") {
    Monster m("goblin", "Goblin", 50, 12, 3, 100);

    SECTION("Attack deals damage to player") {
        Player p;
        int oldHealth = p.getHealth();
        m.attack(&p);
        // ATK=12, Player DEF=5, damage=7
        REQUIRE(p.getHealth() == oldHealth - 7);
    }
    
    SECTION("Minimum damage is 1") {
        Player p;
        Monster weak("rat", "Rat", 10, 1, 100, 10);
        int oldHealth = p.getHealth();
        weak.attack(&p);
        // ATK=1, Player DEF=5 -> damage should be 1 (minimum)
        REQUIRE(p.getHealth() == oldHealth - 1);
    }
}