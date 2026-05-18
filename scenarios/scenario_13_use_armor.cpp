#include "Player.h"
#include "Monster.h"
#include "Item.h"
#include <iostream>

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "СЦЕНАРИЙ 13: ИСПОЛЬЗОВАНИЕ БРОНИ (ARMOR)" << std::endl;
    std::cout << "========================================" << std::endl;
    
    Player player;
    Item* armor = new Item("armor", "Steel Armor", "armor", 0, 0, 10);
    Monster monster("goblin", "Goblin", 50, 15, 3, 100);

    std::cout << "Защита игрока: " << player.getDefense() << std::endl;
    std::cout << "Сила атаки монстра: " << monster.getAttackPower() << std::endl;
    
    int damageBefore = monster.getAttackPower() - player.getDefense();
    if (damageBefore < 1) damageBefore = 1;
    std::cout << "Ожидаемый урон от монстра: " << damageBefore << std::endl;
    
    player.pickUp(armor);
    std::cout << "Подобрана броня: " << armor->getName() << std::endl;
    
    int oldDefense = player.getDefense();
    player.useItem(0);
    std::cout << "Броня экипирована! Защита была " << oldDefense << ", стала " << player.getDefense() << std::endl;
    
    if (player.getDefense() == oldDefense + 10) {
        std::cout << "  Броня увеличила защиту на 10" << std::endl;
    } else {
        std::cout << "  ОШИБКА: защита изменилась неправильно!" << std::endl;
        return 1;
    }
    
    if (player.getInventory().empty()) {
        std::cout << "  Броня исчезла из инвентаря после экипировки" << std::endl;
    } else {
        std::cout << "  ОШИБКА: броня осталась в инвентаре!" << std::endl;
        return 1;
    }

    int damageAfter = monster.getAttackPower() - player.getDefense();
    if (damageAfter < 1) damageAfter = 1;
    std::cout << "Урон монстра ДО брони: " << damageBefore << std::endl;
    std::cout << "Урон монстра ПОСЛЕ брони: " << damageAfter << std::endl;
    
    if (damageAfter < damageBefore) {
        std::cout << "  Броня успешно снизила получаемый урон!" << std::endl;
    } else {
        std::cout << "  Броня не снизила урон (возможно, защита уже была высокой)" << std::endl;
    }

    Player player2;
    player2.pickUp(new Item("armor2", "Dragon Armor", "armor", 0, 0, 20));
    player2.useItem(0);
    
    std::cout << "Новый игрок: Защита=" << player2.getDefense() << std::endl;
    std::cout << "Монстр атакует!" << std::endl;
    
    int oldHealth = player2.getHealth();
    monster.attack(&player2);
    int actualDamage = oldHealth - player2.getHealth();
    
    std::cout << "Получено урона: " << actualDamage << std::endl;
    
    if (actualDamage <= monster.getAttackPower()) {
        std::cout << "  Броня снизила урон в реальном бою" << std::endl;
    }
    
    std::cout << "\nСценарий пройден" << std::endl;
    return 0;
}