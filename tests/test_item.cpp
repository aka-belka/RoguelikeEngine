#include "catch.hpp"
#include "Item.h"

TEST_CASE("Item initialization", "[Item]") {
    SECTION("Potion item") {
        Item potion("hp_pot", "Health Potion", "potion", 50, 0, 0);
        REQUIRE(potion.getName() == "Health Potion");
        REQUIRE(potion.getType() == "potion");
        REQUIRE(potion.getHealAmount() == 50);
        REQUIRE(potion.getAttackBonus() == 0);
        REQUIRE(potion.getDefenseBonus() == 0);
    }
    
    SECTION("Weapon item") {
        Item sword("sword", "Iron Sword", "weapon", 0, 15, 0);
        REQUIRE(sword.getName() == "Iron Sword");
        REQUIRE(sword.getType() == "weapon");
        REQUIRE(sword.getHealAmount() == 0);
        REQUIRE(sword.getAttackBonus() == 15);
        REQUIRE(sword.getDefenseBonus() == 0);
    }
    
    SECTION("Armor item") {
        Item armor("armor", "Steel Armor", "armor", 0, 0, 10);
        REQUIRE(armor.getName() == "Steel Armor");
        REQUIRE(armor.getType() == "armor");
        REQUIRE(armor.getHealAmount() == 0);
        REQUIRE(armor.getAttackBonus() == 0);
        REQUIRE(armor.getDefenseBonus() == 10);
    }
    
    SECTION("Misc item") {
        Item misc("key", "Golden Key", "misc", 0, 0, 0);
        REQUIRE(misc.getName() == "Golden Key");
        REQUIRE(misc.getType() == "misc");
    }
}

TEST_CASE("Item copy constructor", "[Item]") {
    Item original("hp_pot", "Health Potion", "potion", 50, 0, 0);
    Item copy(original);
    
    SECTION("Copy has same attributes") {
        REQUIRE(copy.getName() == "Health Potion");
        REQUIRE(copy.getType() == "potion");
        REQUIRE(copy.getHealAmount() == 50);
    }
}

TEST_CASE("Item with zero values", "[Item]") {
    Item empty("empty", "Empty Item", "misc");
    REQUIRE(empty.getHealAmount() == 0);
    REQUIRE(empty.getAttackBonus() == 0);
    REQUIRE(empty.getDefenseBonus() == 0);
}