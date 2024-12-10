#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

// ����ü ����
typedef struct {
    int currentWeight;
    int currentFloor;
    int skipped;
    int effectFloor;
    int weightChange;
    int previousEffectFloor;
} Player;
    
// �Լ� ������ ����
typedef void (*CardFunction)(Player*);

// �Լ� ������
void decreaseWeight(Player* player) {
    player->weightChange = ((rand() % 151) + 200);
    player->currentWeight -= (player->weightChange);
    if (player->currentWeight <= 0) {
        player->currentWeight = 0;
    }
    printf("���԰� %dkg �����߽��ϴ�! ���� ����: %dkg\n", player->weightChange, player->currentWeight);
}

void increaseWeight(Player* player) {
    player->weightChange = ((rand() % 51) + 50);
    player->currentWeight += player->weightChange;
    if (player->currentWeight <= 0) {
        player->currentWeight = 0;
    }
    printf("���԰� %dkg �����߽��ϴ�! ���� ����: %dkg\n", player->weightChange, player->currentWeight);
}

void resetToPreviousFloorWeight(Player* player) {
    player->previousEffectFloor = 1;
    player->currentWeight += player->weightChange;
    printf("���� ���� ���Է� ���ư��ϴ�! ���� ����: %dkg\n", player->currentWeight);
}

void skipFloor(Player* player) {
    player->currentFloor++;
    player->weightChange = 0;
    player->skipped = 1;  // �� �ǳʶٱ� ī�� ��� ǥ��
    printf("���� �����ϰ� �Ѿ�ϴ�! ���� ��: %d��\n", player->currentFloor);
}

void applyBalloonEffect(Player* player) {
    player->effectFloor = 3;
    player->currentWeight -= 400;
    player->weightChange = 400;
    printf("ǳ�� ȿ���� 3�� ���� 400kg �����߽��ϴ�! ���� ����: %dkg\n", player->currentWeight);
}

void randomWeight(Player* player) {
    int minIncrease = -500;
    int maxIncrease = 500;
    int weightIncrease = (rand() % (maxIncrease - minIncrease + 1)) + minIncrease;
    player->currentWeight += weightIncrease;
    player->weightChange = weightIncrease;
    if (player->currentWeight <= 0) {
        player->currentWeight = 0;
    }
    if (weightIncrease > 0) {
        printf("�������Է� %dkg��ŭ �þ���ϴ�.\n", weightIncrease);
    }
    else {
        printf("�������Է� %dkg��ŭ �پ������ϴ�\n", weightIncrease);
    }
    printf("�������� ���Ը� ���ϰų� ���ϴ�! ���� ����: %dkg\n", player->currentWeight);
}

void randomMultiple(Player* player) {
    int effect = rand() % 2;
    if (effect == 0) {
        player->weightChange = player->currentWeight - player->currentWeight * 2;
        player->currentWeight = player->currentWeight *= 2; //���� �ι� ����
    }
    else {
        player->weightChange = player->currentWeight - (player->currentWeight / 2);
        player->currentWeight = (player->currentWeight + 1) / 2; //���� ���� ����

    }
    printf("�������� ���԰� 2��� �������ų� �������ϴ�! ���� ����: %dkg\n", player->currentWeight);
}


void showRules() {
    printf("\n���� ��Ģ:\n");
    printf("1. �÷��̾�� 2000kg�� ���� ���� ä �����մϴ�.\n");
    printf("2. ž�� �� ������ ���� ������ ������, ������ �ʰ��ϸ� ������ ����˴ϴ�.\n");
    printf("3. ī�� ������ ���� ���Ը� �����ϰų� ���� �ǳʶ� �� �ֽ��ϴ�.\n");
    printf("4. 20���� �����ϸ� ���ӿ� �¸��մϴ�.\n\n");
    printf("�ƹ� Ű�� ���� ���� ȭ������ ���ư�����...\n");
    (void)getchar();
}

void selectCard(Player* player, CardFunction cards[], const char* cardDescriptions[]) {
    int cardChoice;
    printf("ī�带 �����ϼ���: 1, 2 �Ǵ� 3\n");
    for (int i = 0; i < 3; i++) {
        printf("%d. %s\n", i + 1, cardDescriptions[i]);
    }
    scanf_s("%d", &cardChoice);

    if (cardChoice >= 1 && cardChoice <= 3) {
        cards[cardChoice - 1](player); // ������ ī�� ����
    }
    else {
        printf("�߸��� �����Դϴ�. ī�尡 ������� �ʾҽ��ϴ�.\n");
    }
}
