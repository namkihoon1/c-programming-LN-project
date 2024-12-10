#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "func.h"

#define MAX_WEIGHT 2000
#define MAX_FLOORS 20

const char* cardNames[] = {
    "���� ����",
    "���� ����",
    "���� �� ���Է� ����",
    "�� �ǳʶٱ�",
    "ǳ�� ȿ��",
    "���� ���� �ο�",
    "���� �ι� ���� Ȥ�� �ι� ����"
};

void showMainMenu() {
    printf("\n\n\n");
    printf("=====================================\n");
    printf("         ž ������ ����\n");
    printf("=====================================\n");
    printf("    1. ���� ����\n");
    printf("    2. ���� ��Ģ ����\n");
    printf("    3. ����\n");
    printf("=====================================\n");
    printf("�����ϼ���: ");
}

void playGame(Player* player) {
    CardFunction cardDeck[] = {
        decreaseWeight,
        increaseWeight,
        resetToPreviousFloorWeight,
        skipFloor,
        applyBalloonEffect,
        randomWeight,
        randomMultiple
    };

    while (player->currentFloor <= MAX_FLOORS && player->currentWeight > 0) {
        int weightLimit = MAX_WEIGHT - ((player->currentFloor - 1) * 100);

        if (player->currentWeight > weightLimit) {
            printf("���԰� �ʹ� ���ſ� %d���� ���� �� �����ϴ�. ���� ����!\n", player->currentFloor);
            return;
        }

        printf("\n%d���� �����߽��ϴ�. �ִ� ��� ����: %dkg\n", player->currentFloor, weightLimit);
        printf("���� ����: %dkg\n", player->currentWeight);

        CardFunction selectedCards[3];
        const char* selectedDescriptions[3];
        for (int i = 0; i < 3; i++) {
            int cardIndex = rand() % 7;
            selectedCards[i] = cardDeck[cardIndex];
            selectedDescriptions[i] = cardNames[cardIndex];
            if (i == 1 && selectedCards[0] == selectedCards[1])
            {
                i--;
            }
            if (i == 2 && (selectedCards[0] == selectedCards[2] || selectedCards[1] == selectedCards[2]))
            {
                i--;
            }
        }

        selectCard(player, selectedCards, selectedDescriptions);

        player->currentFloor++;
    }

    if (player->currentFloor > MAX_FLOORS) {
        printf("�����մϴ�! ž�� ������ �����߽��ϴ�!\n");
    }
    else {
        printf("������ ����Ǿ����ϴ�. �ٽ� �����غ�����!\n");
    }
}

int main() {
    srand(time(NULL));

    int choice;
    Player player;

    while (1) {
        system("cls"); // �ܼ� ȭ�� ����� (Windows ����)
        showMainMenu();
        scanf_s("%d", &choice);

        while (getchar() != '\n');

        if (choice == 1) {
            player.currentWeight = MAX_WEIGHT;
            player.currentFloor = 1;
            player.skipped = 0;
            player.effectFloor = 0;
            player.weightChange = 0;
            player.previousEffectFloor = 0;

            playGame(&player);
            printf("�ƹ� Ű�� ���� ���� ȭ������ ���ư�����...\n");
            (void)getchar(); // ��ȯ�� ����
        }
        else if (choice == 2) {
            showRules();
        }
        else if (choice == 3) {
            printf("������ �����մϴ�.\n");
            break;
        }
        else {
            printf("�߸��� �����Դϴ�. �ٽ� �Է��ϼ���.\n");
            (void)getchar(); // ��ȯ�� ����
        }
    }

    return 0;
}
