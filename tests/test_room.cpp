#include "catch.hpp"
#include "Room.h"
#include "Monster.h"
#include "Item.h"

TEST_CASE("Room initialization", "[Room]") {
    Room r(2, 3, "normal");
    
    SECTION("Room has correct coordinates and type") {
        REQUIRE(r.getType() == "normal");
    }
    
    SECTION("Room starts with empty monsters and items") {
        REQUIRE(r.getMonsters().empty());
        REQUIRE(r.getItems().empty());
    }
}

TEST_CASE("Room add monsters", "[Room]") {
    Room r(0, 0, "normal");
    
    SECTION("Add single monster") {
        Monster* m1 = new Monster("gob", "Goblin", 50, 12, 3, 100);
        r.addMonster(m1);
        REQUIRE(r.getMonsters().size() == 1);
        REQUIRE(r.getMonsters()[0]->getName() == "Goblin");
    }
    
    SECTION("Add multiple monsters") {
        Monster* m1 = new Monster("gob", "Goblin", 50, 12, 3, 100);
        Monster* m2 = new Monster("orc", "Orc", 80, 15, 5, 150);
        r.addMonster(m1);
        r.addMonster(m2);
        REQUIRE(r.getMonsters().size() == 2);
    }
}

TEST_CASE("Room add items", "[Room]") {
    Room r(0, 0, "normal");
    
    SECTION("Add single item") {
        Item* i1 = new Item("p1", "Potion", "potion", 50, 0, 0);
        r.addItem(i1);
        REQUIRE(r.getItems().size() == 1);
        REQUIRE(r.getItems()[0]->getName() == "Potion");
    }
    
    SECTION("Add multiple items") {
        Item* i1 = new Item("p1", "Potion", "potion", 50, 0, 0);
        Item* i2 = new Item("s1", "Sword", "weapon", 0, 10, 0);
        r.addItem(i1);
        r.addItem(i2);
        REQUIRE(r.getItems().size() == 2);
    }
}

TEST_CASE("Room clear monsters", "[Room]") {
    Room r(0, 0, "normal");
    
    SECTION("Clear monsters empties the list") {
        Monster* m1 = new Monster("gob", "Goblin", 50, 12, 3, 100);
        Monster* m2 = new Monster("orc", "Orc", 80, 15, 5, 150);
        r.addMonster(m1);
        r.addMonster(m2);
        r.clearMonsters();
        REQUIRE(r.getMonsters().empty());
    }
}

TEST_CASE("Room set cleared", "[Room]") {
    Room r(0, 0, "normal");
    
    SECTION("Set cleared works") {
        r.setCleared(true);
        REQUIRE(r.isClearedRoom() == true);
        
        r.setCleared(false);
        REQUIRE(r.isClearedRoom() == false);
    }
}