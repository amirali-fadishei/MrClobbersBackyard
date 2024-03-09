#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 1250
#define SCREEN_HEIGHT 750
#define CELL_SIZE 50
#define NUM_MICE1 8
#define NUM_MICE2 6
#define NUM_MICE3 6
#define NUM_CHOCOLATES 6
#define NUM_FISH 10
#define NUM_TALE 6

typedef struct {
  int avilable;
  int x;
  int y;
} Mouse;

typedef struct {
  int avilable;
  int x;
  int y;
} Chocolate;

typedef struct {
  int avilable;
  int x;
  int y;
} Fish;

typedef struct {
  int avilable;
  int x;
  int y;
} Tale;

typedef struct {
  int live;
  int freeze;
  int future_freeze;
  int freezenum;
  int mice1num;
  int mice2num;
  int mice3num;
  int point, power, energy, xnow, ynow, futurex, futurey;
  int number_move;
  int store[2][20];
  int number_hunt;
} cats;

typedef struct {
  int avilable;
  int befor_move;
  int power;
  int energy;
  int speed;
  int x, y;
} dogs;

void shuffle(Mouse array[], int size) {
  for (int i = size - 1; i > 0; i--) {
    int j = rand() % (i + 1);
    Mouse temp = array[i];
    array[i] = array[j];
    array[j] = temp;
  }
}

int moving_dog(int x, int y, cats cat[], int walls[15][15]) {
  int up, down, left, right, upcat1, upcat2, upcat3, upcat4, downcat1, downcat2,
      downcat3, downcat4, rightcat1, rightcat2, rightcat3, rightcat4, leftcat1,
      leftcat2, leftcat3, leftcat4;
  int answer, min;
  if (y > 0 && walls[x][y] * walls[x][y - 1] != (-1)) {
    if (cat[0].freeze)
      upcat1 = 4 * ((((y - 1) - cat[0].ynow) * ((y - 1) - cat[0].ynow)) +
                    (((x)-cat[0].xnow) * ((x)-cat[0].xnow)));
    else
      upcat1 = -1;
    if (cat[1].freeze)
      upcat2 = 4 * ((((y - 1) - cat[1].ynow) * ((y - 1) - cat[1].ynow)) +
                    (((x)-cat[1].xnow) * ((x)-cat[1].xnow)));
    else
      upcat2 = -1;
    if (cat[2].freeze)
      upcat3 = 4 * ((((y - 1) - cat[2].ynow) * ((y - 1) - cat[2].ynow)) +
                    (((x)-cat[2].xnow) * ((x)-cat[2].xnow)));
    else
      upcat3 = -1;
    if (cat[3].freeze)
      upcat4 = 4 * ((((y - 1) - cat[3].ynow) * ((y - 1) - cat[3].ynow)) +
                    (((x)-cat[3].xnow) * ((x)-cat[3].xnow)));
    else
      upcat4 = -1;
  } else {
    upcat4 = -1;
    upcat3 = -1;
    upcat2 = -1;
    upcat1 = -1;
  }
  if (y < 14 && walls[x][y] * walls[x][y + 1] != (-1)) {
    if (cat[0].freeze)
      downcat1 = 4 * ((((y + 1) - cat[0].ynow) * ((y + 1) - cat[0].ynow)) +
                      (((x)-cat[0].xnow) * ((x)-cat[0].xnow)));
    else
      downcat1 = -1;
    if (cat[1].freeze)
      downcat2 = 4 * ((((y + 1) - cat[1].ynow) * ((y + 1) - cat[1].ynow)) +
                      (((x)-cat[1].xnow) * ((x)-cat[1].xnow)));
    else
      downcat2 = -1;
    if (cat[2].freeze)
      downcat3 = 4 * ((((y + 1) - cat[2].ynow) * ((y + 1) - cat[2].ynow)) +
                      (((x)-cat[2].xnow) * ((x)-cat[2].xnow)));
    else
      downcat3 = -1;
    if (cat[3].freeze)
      downcat4 = 4 * ((((y + 1) - cat[3].ynow) * ((y + 1) - cat[3].ynow)) +
                      (((x)-cat[3].xnow) * ((x)-cat[3].xnow)));
    else
      downcat4 = -1;
  } else {
    downcat4 = -1;
    downcat3 = -1;
    downcat2 = -1;
    downcat1 = -1;
  }
  if (x < 14 && walls[x][y] * walls[x + 1][y] != (-1)) {
    if (cat[0].freeze)
      rightcat1 = 4 * ((((y)-cat[0].ynow) * ((y)-cat[0].ynow)) +
                       (((x + 1) - cat[0].xnow) * ((x + 1) - cat[0].xnow)));
    else
      rightcat1 = -1;
    if (cat[1].freeze)
      rightcat2 = 4 * ((((y)-cat[1].ynow) * ((y)-cat[1].ynow)) +
                       (((x + 1) - cat[1].xnow) * ((x + 1) - cat[1].xnow)));
    else
      rightcat2 = -1;
    if (cat[2].freeze)
      rightcat3 = 4 * ((((y)-cat[2].ynow) * ((y)-cat[2].ynow)) +
                       (((x + 1) - cat[2].xnow) * ((x + 1) - cat[2].xnow)));
    else
      rightcat3 = -1;
    if (cat[3].freeze)
      rightcat4 = 4 * ((((y)-cat[3].ynow) * ((y)-cat[3].ynow)) +
                       (((x + 1) - cat[3].xnow) * ((x + 1) - cat[3].xnow)));
    else
      rightcat4 = -1;
  } else {
    rightcat4 = -1;
    rightcat3 = -1;
    rightcat2 = -1;
    rightcat1 = -1;
  }
  if (x > 0 && walls[x][y] * walls[x - 1][y] != (-1)) {
    if (cat[0].freeze)
      leftcat1 = 4 * ((((y)-cat[0].ynow) * ((y)-cat[0].ynow)) +
                      (((x - 1) - cat[0].xnow) * ((x - 1) - cat[0].xnow)));
    else
      leftcat1 = -1;
    if (cat[1].freeze)
      leftcat2 = 4 * ((((y)-cat[1].ynow) * ((y)-cat[1].ynow)) +
                      (((x - 1) - cat[1].xnow) * ((x - 1) - cat[1].xnow)));
    else
      leftcat2 = -1;
    if (cat[2].freeze)
      leftcat3 = 4 * ((((y)-cat[2].ynow) * ((y)-cat[2].ynow)) +
                      (((x - 1) - cat[2].xnow) * ((x - 1) - cat[2].xnow)));
    else
      leftcat3 = -1;
    if (cat[3].freeze)
      leftcat4 = 4 * ((((y)-cat[3].ynow) * ((y)-cat[3].ynow)) +
                      (((x - 1) - cat[3].xnow) * ((x - 1) - cat[3].xnow)));
    else
      leftcat4 = -1;
  } else {
    leftcat1 = -1;
    leftcat2 = -1;
    leftcat3 = -1;
    leftcat4 = -1;
  }
  if (y > 0 && walls[x][y] * walls[x][y - 1] != (-1)) {
    up = ((((y - 1) - cat[0].ynow) * ((y - 1) - cat[0].ynow)) +
          (((x)-cat[0].xnow) * ((x)-cat[0].xnow))) +
         ((((y - 1) - cat[1].ynow) * ((y - 1) - cat[1].ynow)) +
          (((x)-cat[1].xnow) * ((x)-cat[1].xnow))) +
         ((((y - 1) - cat[2].ynow) * ((y - 1) - cat[2].ynow)) +
          (((x)-cat[2].xnow) * ((x)-cat[2].xnow))) +
         ((((y - 1) - cat[3].ynow) * ((y - 1) - cat[3].ynow)) +
          (((x)-cat[3].xnow) * ((x)-cat[3].xnow)));
  } else
    up = -1;
  if (y < 14 && walls[x][y] * walls[x][y + 1] != (-1)) {
    down = ((((y + 1) - cat[0].ynow) * ((y + 1) - cat[0].ynow)) +
            (((x)-cat[0].xnow) * ((x)-cat[0].xnow))) +
           ((((y + 1) - cat[1].ynow) * ((y + 1) - cat[1].ynow)) +
            (((x)-cat[1].xnow) * ((x)-cat[1].xnow))) +
           ((((y + 1) - cat[2].ynow) * ((y + 1) - cat[2].ynow)) +
            (((x)-cat[2].xnow) * ((x)-cat[2].xnow))) +
           ((((y + 1) - cat[3].ynow) * ((y + 1) - cat[3].ynow)) +
            (((x)-cat[3].xnow) * ((x)-cat[3].xnow)));
  } else
    down = -1;
  if (x < 14 && walls[x][y] * walls[x + 1][y] != (-1)) {
    right = ((((y)-cat[0].ynow) * ((y)-cat[0].ynow)) +
             (((x + 1) - cat[0].xnow) * ((x + 1) - cat[0].xnow))) +
            ((((y)-cat[1].ynow) * ((y)-cat[1].ynow)) +
             (((x + 1) - cat[1].xnow) * ((x + 1) - cat[1].xnow))) +
            ((((y)-cat[2].ynow) * ((y)-cat[2].ynow)) +
             (((x + 1) - cat[2].xnow) * ((x + 1) - cat[2].xnow))) +
            ((((y)-cat[3].ynow) * ((y)-cat[3].ynow)) +
             (((x + 1) - cat[3].xnow) * ((x + 1) - cat[3].xnow)));
  } else
    right = -1;
  if (x > 0 && walls[x][y] * walls[x - 1][y] != (-1)) {
    left = ((((y)-cat[0].ynow) * ((y)-cat[0].ynow)) +
            (((x - 1) - cat[0].xnow) * ((x - 1) - cat[0].xnow))) +
           ((((y)-cat[1].ynow) * ((y)-cat[1].ynow)) +
            (((x - 1) - cat[1].xnow) * ((x - 1) - cat[1].xnow))) +
           ((((y)-cat[2].ynow) * ((y)-cat[2].ynow)) +
            (((x - 1) - cat[2].xnow) * ((x - 1) - cat[2].xnow))) +
           ((((y)-cat[3].ynow) * ((y)-cat[3].ynow)) +
            (((x - 1) - cat[3].xnow) * ((x - 1) - cat[3].xnow)));
  } else
    left = -1;

  min = up;
  answer = 8;
  if (down < min && down != (-1)) {
    min = down;
    answer = 2;
  }
  if (right < min && right != (-1)) {
    min = right;
    answer = 6;
  }
  if (left < min && left != (-1)) {
    min = left;
    answer = 4;
  }

  if (upcat1 < min && upcat1 != (-1)) {
    min = upcat1;
    answer = 8;
  }
  if (upcat2 < min && upcat2 != (-1)) {
    min = upcat2;
    answer = 8;
  }
  if (upcat3 < min && upcat3 != (-1)) {
    min = upcat3;
    answer = 8;
  }
  if (upcat4 < min && upcat4 != (-1)) {
    min = upcat4;
    answer = 8;
  }

  if (downcat1 < min && downcat1 != (-1)) {
    min = downcat1;
    answer = 2;
  }
  if (downcat2 < min && downcat2 != (-1)) {
    min = downcat2;
    answer = 2;
  }
  if (downcat3 < min && downcat3 != (-1)) {
    min = downcat3;
    answer = 2;
  }
  if (downcat4 < min && downcat4 != (-1)) {
    min = downcat4;
    answer = 2;
  }

  if (rightcat1 < min && rightcat1 != (-1)) {
    min = rightcat1;
    answer = 6;
  }
  if (rightcat2 < min && rightcat2 != (-1)) {
    min = rightcat2;
    answer = 6;
  }
  if (rightcat3 < min && rightcat3 != (-1)) {
    min = rightcat3;
    answer = 6;
  }
  if (rightcat4 < min && rightcat4 != (-1)) {
    min = rightcat4;
    answer = 6;
  }

  if (leftcat1 < min && leftcat1 != (-1)) {
    min = leftcat1;
    answer = 4;
  }
  if (leftcat2 < min && leftcat2 != (-1)) {
    min = leftcat2;
    answer = 4;
  }
  if (leftcat3 < min && leftcat3 != (-1)) {
    min = leftcat3;
    answer = 4;
  }
  if (leftcat4 < min && leftcat4 != (-1)) {
    min = leftcat4;
    answer = 4;
  }

  return answer;
}
int moving_mice(int x, int y, cats cat[], int walls[15][15]) {
  int up, down, left, right, upcat1, upcat2, upcat3, upcat4, downcat1, downcat2,
      downcat3, downcat4, rightcat1, rightcat2, rightcat3, rightcat4, leftcat1,
      leftcat2, leftcat3, leftcat4;
  int answer, min;
  if (y > 0 && walls[x][y] * walls[x][y - 1] != (-1)) {
    if (cat[0].freeze)
      upcat1 = 4 * ((((y - 1) - cat[0].ynow) * ((y - 1) - cat[0].ynow)) +
                    (((x)-cat[0].xnow) * ((x)-cat[0].xnow)));
    else
      upcat1 = -1;
    if (cat[1].freeze)
      upcat2 = 4 * ((((y - 1) - cat[1].ynow) * ((y - 1) - cat[1].ynow)) +
                    (((x)-cat[1].xnow) * ((x)-cat[1].xnow)));
    else
      upcat2 = -1;
    if (cat[2].freeze)
      upcat3 = 4 * ((((y - 1) - cat[2].ynow) * ((y - 1) - cat[2].ynow)) +
                    (((x)-cat[2].xnow) * ((x)-cat[2].xnow)));
    else
      upcat3 = -1;
    if (cat[3].freeze)
      upcat4 = 4 * ((((y - 1) - cat[3].ynow) * ((y - 1) - cat[3].ynow)) +
                    (((x)-cat[3].xnow) * ((x)-cat[3].xnow)));
    else
      upcat4 = -1;
  } else {
    upcat4 = -1;
    upcat3 = -1;
    upcat2 = -1;
    upcat1 = -1;
  }
  if (y < 14 && walls[x][y] * walls[x][y + 1] != (-1)) {
    if (cat[0].freeze)
      downcat1 = 4 * ((((y + 1) - cat[0].ynow) * ((y + 1) - cat[0].ynow)) +
                      (((x)-cat[0].xnow) * ((x)-cat[0].xnow)));
    else
      downcat1 = -1;
    if (cat[1].freeze)
      downcat2 = 4 * ((((y + 1) - cat[1].ynow) * ((y + 1) - cat[1].ynow)) +
                      (((x)-cat[1].xnow) * ((x)-cat[1].xnow)));
    else
      downcat2 = -1;
    if (cat[2].freeze)
      downcat3 = 4 * ((((y + 1) - cat[2].ynow) * ((y + 1) - cat[2].ynow)) +
                      (((x)-cat[2].xnow) * ((x)-cat[2].xnow)));
    else
      downcat3 = -1;
    if (cat[3].freeze)
      downcat4 = 4 * ((((y + 1) - cat[3].ynow) * ((y + 1) - cat[3].ynow)) +
                      (((x)-cat[3].xnow) * ((x)-cat[3].xnow)));
    else
      downcat4 = -1;
  } else {
    downcat4 = -1;
    downcat3 = -1;
    downcat2 = -1;
    downcat1 = -1;
  }
  if (x < 14 && walls[x][y] * walls[x + 1][y] != (-1)) {
    if (cat[0].freeze)
      rightcat1 = 4 * ((((y)-cat[0].ynow) * ((y)-cat[0].ynow)) +
                       (((x + 1) - cat[0].xnow) * ((x + 1) - cat[0].xnow)));
    else
      rightcat1 = -1;
    if (cat[1].freeze)
      rightcat2 = 4 * ((((y)-cat[1].ynow) * ((y)-cat[1].ynow)) +
                       (((x + 1) - cat[1].xnow) * ((x + 1) - cat[1].xnow)));
    else
      rightcat2 = -1;
    if (cat[2].freeze)
      rightcat3 = 4 * ((((y)-cat[2].ynow) * ((y)-cat[2].ynow)) +
                       (((x + 1) - cat[2].xnow) * ((x + 1) - cat[2].xnow)));
    else
      rightcat3 = -1;
    if (cat[3].freeze)
      rightcat4 = 4 * ((((y)-cat[3].ynow) * ((y)-cat[3].ynow)) +
                       (((x + 1) - cat[3].xnow) * ((x + 1) - cat[3].xnow)));
    else
      rightcat4 = -1;
  } else {
    rightcat4 = -1;
    rightcat3 = -1;
    rightcat2 = -1;
    rightcat1 = -1;
  }
  if (x > 0 && walls[x][y] * walls[x - 1][y] != (-1)) {
    if (cat[0].freeze)
      leftcat1 = 4 * ((((y)-cat[0].ynow) * ((y)-cat[0].ynow)) +
                      (((x - 1) - cat[0].xnow) * ((x - 1) - cat[0].xnow)));
    else
      leftcat1 = -1;
    if (cat[1].freeze)
      leftcat2 = 4 * ((((y)-cat[1].ynow) * ((y)-cat[1].ynow)) +
                      (((x - 1) - cat[1].xnow) * ((x - 1) - cat[1].xnow)));
    else
      leftcat2 = -1;
    if (cat[2].freeze)
      leftcat3 = 4 * ((((y)-cat[2].ynow) * ((y)-cat[2].ynow)) +
                      (((x - 1) - cat[2].xnow) * ((x - 1) - cat[2].xnow)));
    else
      leftcat3 = -1;
    if (cat[3].freeze)
      leftcat4 = 4 * ((((y)-cat[3].ynow) * ((y)-cat[3].ynow)) +
                      (((x - 1) - cat[3].xnow) * ((x - 1) - cat[3].xnow)));
    else
      leftcat4 = -1;
  } else {
    leftcat1 = -1;
    leftcat2 = -1;
    leftcat3 = -1;
    leftcat4 = -1;
  }
  if (y > 0 && walls[x][y] * walls[x][y - 1] != (-1)) {
    up = ((((y - 1) - cat[0].ynow) * ((y - 1) - cat[0].ynow)) +
          (((x)-cat[0].xnow) * ((x)-cat[0].xnow))) +
         ((((y - 1) - cat[1].ynow) * ((y - 1) - cat[1].ynow)) +
          (((x)-cat[1].xnow) * ((x)-cat[1].xnow))) +
         ((((y - 1) - cat[2].ynow) * ((y - 1) - cat[2].ynow)) +
          (((x)-cat[2].xnow) * ((x)-cat[2].xnow))) +
         ((((y - 1) - cat[3].ynow) * ((y - 1) - cat[3].ynow)) +
          (((x)-cat[3].xnow) * ((x)-cat[3].xnow)));
  } else
    up = -1;
  if (y < 14 && walls[x][y] * walls[x][y + 1] != (-1)) {
    down = ((((y + 1) - cat[0].ynow) * ((y + 1) - cat[0].ynow)) +
            (((x)-cat[0].xnow) * ((x)-cat[0].xnow))) +
           ((((y + 1) - cat[1].ynow) * ((y + 1) - cat[1].ynow)) +
            (((x)-cat[1].xnow) * ((x)-cat[1].xnow))) +
           ((((y + 1) - cat[2].ynow) * ((y + 1) - cat[2].ynow)) +
            (((x)-cat[2].xnow) * ((x)-cat[2].xnow))) +
           ((((y + 1) - cat[3].ynow) * ((y + 1) - cat[3].ynow)) +
            (((x)-cat[3].xnow) * ((x)-cat[3].xnow)));
  } else
    down = -1;
  if (x < 14 && walls[x][y] * walls[x + 1][y] != (-1)) {
    right = ((((y)-cat[0].ynow) * ((y)-cat[0].ynow)) +
             (((x + 1) - cat[0].xnow) * ((x + 1) - cat[0].xnow))) +
            ((((y)-cat[1].ynow) * ((y)-cat[1].ynow)) +
             (((x + 1) - cat[1].xnow) * ((x + 1) - cat[1].xnow))) +
            ((((y)-cat[2].ynow) * ((y)-cat[2].ynow)) +
             (((x + 1) - cat[2].xnow) * ((x + 1) - cat[2].xnow))) +
            ((((y)-cat[3].ynow) * ((y)-cat[3].ynow)) +
             (((x + 1) - cat[3].xnow) * ((x + 1) - cat[3].xnow)));
  } else
    right = -1;
  if (x > 0 && walls[x][y] * walls[x - 1][y] != (-1)) {
    left = ((((y)-cat[0].ynow) * ((y)-cat[0].ynow)) +
            (((x - 1) - cat[0].xnow) * ((x - 1) - cat[0].xnow))) +
           ((((y)-cat[1].ynow) * ((y)-cat[1].ynow)) +
            (((x - 1) - cat[1].xnow) * ((x - 1) - cat[1].xnow))) +
           ((((y)-cat[2].ynow) * ((y)-cat[2].ynow)) +
            (((x - 1) - cat[2].xnow) * ((x - 1) - cat[2].xnow))) +
           ((((y)-cat[3].ynow) * ((y)-cat[3].ynow)) +
            (((x - 1) - cat[3].xnow) * ((x - 1) - cat[3].xnow)));
  } else
    left = -1;

  min = up;
  answer = 8;
  if (down > min && down != (-1)) {
    min = down;
    answer = 2;
  }
  if (right > min && right != (-1)) {
    min = right;
    answer = 6;
  }
  if (left > min && left != (-1)) {
    min = left;
    answer = 4;
  }

  if (upcat1 > min && upcat1 != (-1)) {
    min = upcat1;
    answer = 8;
  }
  if (upcat2 > min && upcat2 != (-1)) {
    min = upcat2;
    answer = 8;
  }
  if (upcat3 > min && upcat3 != (-1)) {
    min = upcat3;
    answer = 8;
  }
  if (upcat4 > min && upcat4 != (-1)) {
    min = upcat4;
    answer = 8;
  }

  if (downcat1 > min && downcat1 != (-1)) {
    min = downcat1;
    answer = 2;
  }
  if (downcat2 > min && downcat2 != (-1)) {
    min = downcat2;
    answer = 2;
  }
  if (downcat3 > min && downcat3 != (-1)) {
    min = downcat3;
    answer = 2;
  }
  if (downcat4 > min && downcat4 != (-1)) {
    min = downcat4;
    answer = 2;
  }

  if (rightcat1 > min && rightcat1 != (-1)) {
    min = rightcat1;
    answer = 6;
  }
  if (rightcat2 > min && rightcat2 != (-1)) {
    min = rightcat2;
    answer = 6;
  }
  if (rightcat3 > min && rightcat3 != (-1)) {
    min = rightcat3;
    answer = 6;
  }
  if (rightcat4 > min && rightcat4 != (-1)) {
    min = rightcat4;
    answer = 6;
  }

  if (leftcat1 > min && leftcat1 != (-1)) {
    min = leftcat1;
    answer = 4;
  }
  if (leftcat2 > min && leftcat2 != (-1)) {
    min = leftcat2;
    answer = 4;
  }
  if (leftcat3 > min && leftcat3 != (-1)) {
    min = leftcat3;
    answer = 4;
  }
  if (leftcat4 > min && leftcat4 != (-1)) {
    min = leftcat4;
    answer = 4;
  }

  return answer;
}

int check_turn(int tc1, int tc2, int tc3, int tc4) {
  int sw = 1;
  if (tc1 == tc2 || tc1 == tc3 || tc1 == tc4)
    sw = 0;
  else if (tc2 == tc1 || tc2 == tc3 || tc2 == tc4)
    sw = 0;
  else if (tc3 == tc1 || tc3 == tc2 || tc3 == tc4)
    sw = 0;
  else if (tc4 == tc1 || tc4 == tc2 || tc4 == tc3)
    sw = 0;
  return (sw);
}

int containsObjectOrAnimal(int x, int y, Mouse mice1[], Mouse mice2[],
                           Mouse mice3[], Chocolate chocolates[], Fish fishes[],
                           Tale tales[], int numMice1, int numMice2,
                           int numMice3, int numChocolates, int numFishes,
                           int numTales) {
  for (int i = 0; i < numMice1; i++) {
    if (mice1[i].x == x && mice1[i].y == y) {
      return 41;
    }
  }
  for (int i = 0; i < numMice2; i++) {
    if (mice2[i].x == x && mice2[i].y == y) {
      return 42;
    }
  }
  for (int i = 0; i < numMice3; i++) {
    if (mice3[i].x == x && mice3[i].y == y) {
      return 43;
    }
  }
  for (int i = 0; i < numChocolates; i++) {
    if (chocolates[i].x == x && chocolates[i].y == y) {
      return 61;
    }
  }
  for (int i = 0; i < numFishes; i++) {
    if (fishes[i].x == x && fishes[i].y == y) {
      return 71;
    }
  }
  for (int i = 0; i < numTales; i++) {
    if (tales[i].x == x && tales[i].y == y) {
      return 51;
    }
  }
  if ((x == 12 && y == 2) || (x == 3 && y == 6) || (x == 2 && y == 11) ||
      (x == 11 && y == 12) || (x == 7 && y == 6) || (x == 8 && y == 7) ||
      (x == 7 && y == 8) || (x == 6 && y == 7)) {
    return 1;
  }

  if (x == 7 && y == 7) {
    return 1;
  }
  return 0;
}

int search_chocolates(int x, int y, Chocolate chocolates[]) {
  for (int i = 0; i < NUM_CHOCOLATES; i++) {
    if (chocolates[i].x == x && chocolates[i].y == y &&
        chocolates[i].avilable != 0)
      return i;
  }
  return -1;
}

int search_tales(int x, int y, Tale tales[]) {
  for (int i = 0; i < NUM_TALE; i++) {
    if (tales[i].x == x && tales[i].y == y) return i;
  }
  return -1;
}

int search_Mice1(int x, int y, Mouse mice1[]) {
  for (int i = 0; i < NUM_MICE1; i++) {
    if (mice1[i].x == x && mice1[i].y == y && mice1[i].avilable != 0) return i;
  }
  return -1;
}

int search_Mice2(int x, int y, Mouse mice2[]) {
  for (int i = 0; i < NUM_MICE2; i++) {
    if (mice2[i].x == x && mice2[i].y == y && mice2[i].avilable != 0) return i;
  }
  return -1;
}

int search_Mice3(int x, int y, Mouse mice3[]) {
  for (int i = 0; i < NUM_MICE3; i++) {
    if (mice3[i].x == x && mice3[i].y == y && mice3[i].avilable != 0) return i;
  }
  return -1;
}

int search_fishes(int x, int y, Fish fishes[]) {
  for (int i = 0; i < NUM_FISH; i++) {
    if (fishes[i].x == x && fishes[i].y == y && fishes[i].avilable != 0)
      return i;
  }
  return -1;
}

void drawMice1(ALLEGRO_BITMAP* mouseImage, Mouse mice1[], int numMice) {
  for (int i = 0; i < numMice; i++) {
    int mouseX = mice1[i].x * CELL_SIZE;
    int mouseY = mice1[i].y * CELL_SIZE;
    if (mice1[i].avilable) al_draw_bitmap(mouseImage, mouseX, mouseY, 0);
  }
}

void drawMice2(ALLEGRO_BITMAP* mouseImage, Mouse mice2[], int numMice) {
  for (int i = 0; i < numMice; i++) {
    int mouseX = mice2[i].x * CELL_SIZE;
    int mouseY = mice2[i].y * CELL_SIZE;
    if (mice2[i].avilable) al_draw_bitmap(mouseImage, mouseX, mouseY, 0);
  }
}

void drawMice3(ALLEGRO_BITMAP* mouseImage, Mouse mice3[], int numMice) {
  for (int i = 0; i < numMice; i++) {
    int mouseX = mice3[i].x * CELL_SIZE;
    int mouseY = mice3[i].y * CELL_SIZE;
    if (mice3[i].avilable) al_draw_bitmap(mouseImage, mouseX, mouseY, 0);
  }
}

void drawChocolates(ALLEGRO_BITMAP* chocolateImage, Chocolate chocolates[],
                    int numChocolates) {
  for (int i = 0; i < numChocolates; i++) {
    int chocolateX = (chocolates[i].x * CELL_SIZE) - 10;
    int chocolateY = chocolates[i].y * CELL_SIZE;
    if (chocolates[i].avilable)
      al_draw_bitmap(chocolateImage, chocolateX, chocolateY, 0);
  }
}

void drawTales(ALLEGRO_BITMAP* taleImage, Tale Tales[], int numTales) {
  for (int i = 0; i < numTales; i++) {
    int taleX = (Tales[i].x * CELL_SIZE) - 20;
    int taleY = (Tales[i].y * CELL_SIZE) - 10;
    if (Tales[i].avilable) al_draw_bitmap(taleImage, taleX, taleY, 0);
  }
}

void drawFishs(ALLEGRO_BITMAP* fishImage, Fish fishes[], int numFishes) {
  for (int i = 0; i < numFishes; i++) {
    int fishX = (fishes[i].x * CELL_SIZE) - 20;
    int fishY = (fishes[i].y * CELL_SIZE) - 15;
    if (fishes[i].avilable) al_draw_bitmap(fishImage, fishX, fishY, 0);
  }
}

int main() {
  ALLEGRO_DISPLAY* display = NULL;
  ALLEGRO_EVENT_QUEUE* queue = NULL;
  ALLEGRO_FONT* font = NULL;
  ALLEGRO_BITMAP* houseImage;
  ALLEGRO_BITMAP* mouse1Image;
  ALLEGRO_BITMAP* mouse2Image;
  ALLEGRO_BITMAP* mouse3Image;
  ALLEGRO_BITMAP* chocolateImage;
  ALLEGRO_BITMAP* taleImage;
  ALLEGRO_BITMAP* fishImage;
  ALLEGRO_BITMAP* cat1Image;
  ALLEGRO_BITMAP* cat2Image;
  ALLEGRO_BITMAP* cat3Image;
  ALLEGRO_BITMAP* cat4Image;
  ALLEGRO_BITMAP* dog1Image;
  ALLEGRO_BITMAP* dog2Image;
  ALLEGRO_BITMAP* dog3Image;
  ALLEGRO_BITMAP* dog4Image;
  ALLEGRO_BITMAP* brickImage;
  ALLEGRO_BITMAP* brick1Image;
  ALLEGRO_BITMAP* ice_cat1Image;
  ALLEGRO_BITMAP* ice_cat2Image;
  ALLEGRO_BITMAP* ice_cat3Image;
  ALLEGRO_BITMAP* ice_cat4Image;
  ALLEGRO_BITMAP* t1Image;
  ALLEGRO_BITMAP* t2Image;
  ALLEGRO_BITMAP* t3Image;
  ALLEGRO_BITMAP* t4Image;
  ALLEGRO_BITMAP* t5Image;
  ALLEGRO_BITMAP* t6Image;

  al_init();
  al_init_primitives_addon();
  al_init_image_addon();
  al_init_font_addon();
  al_init_ttf_addon();
  al_install_keyboard();
  display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
  queue = al_create_event_queue();
  al_register_event_source(queue, al_get_keyboard_event_source());
  al_set_window_title(display, "Mr Clobbers Backyard");
  font = al_load_font("./SansThirteenBlack.ttf", 24, 0);
  houseImage = al_load_bitmap("./images/home.png");
  mouse1Image = al_load_bitmap("./images/mouse1.png");
  mouse2Image = al_load_bitmap("./images/mouse2.png");
  mouse3Image = al_load_bitmap("./images/mouse3.png");
  cat1Image = al_load_bitmap("./images/cat1.png");
  cat2Image = al_load_bitmap("./images/cat2.png");
  cat3Image = al_load_bitmap("./images/cat3.png");
  cat4Image = al_load_bitmap("./images/cat4.png");
  dog1Image = al_load_bitmap("./images/dog1.png");
  dog2Image = al_load_bitmap("./images/dog2.png");
  dog3Image = al_load_bitmap("./images/dog3.png");
  dog4Image = al_load_bitmap("./images/dog4.png");
  chocolateImage = al_load_bitmap("./images/shokol.png");
  taleImage = al_load_bitmap("./images/tale.png");
  fishImage = al_load_bitmap("./images/fish.png");
  brickImage = al_load_bitmap("./images/brick2.png");
  brick1Image = al_load_bitmap("./images/brick1.png");
  ice_cat1Image = al_load_bitmap("./images/ice_cat1.png");
  ice_cat2Image = al_load_bitmap("./images/ice_cat2.png");
  ice_cat3Image = al_load_bitmap("./images/ice_cat3.png");
  ice_cat4Image = al_load_bitmap("./images/ice_cat4.png");
  t1Image = al_load_bitmap("./images/1.png");
  t2Image = al_load_bitmap("./images/2.png");
  t3Image = al_load_bitmap("./images/3.png");
  t4Image = al_load_bitmap("./images/4.png");
  t5Image = al_load_bitmap("./images/5.png");
  t6Image = al_load_bitmap("./images/6.png");

  int centerX = ((750 - al_get_bitmap_width(houseImage)) / 2) - 5;
  int centerY = ((750 - al_get_bitmap_height(houseImage)) / 2) - 10;

  srand(time(NULL));

  Mouse mice1[NUM_MICE1];
  Mouse mice2[NUM_MICE2];
  Mouse mice3[NUM_MICE3];
  Chocolate chocolates[NUM_CHOCOLATES];
  Fish fishes[NUM_FISH];
  Tale tales[NUM_TALE];
  dogs dog[4];
  cats cat[4];
  int hiddenFish = NUM_FISH;

  dog[0].power = 5;
  dog[0].energy = 30;
  dog[0].speed = 4;
  dog[0].x = 12;
  dog[0].y = 2;
  dog[0].avilable = 1;
  dog[1].power = 2;
  dog[1].energy = 20;
  dog[1].speed = 2;
  dog[1].x = 3;
  dog[1].y = 6;
  dog[1].avilable = 1;
  dog[2].power = 2;
  dog[2].energy = 20;
  dog[2].speed = 3;
  dog[2].x = 2;
  dog[2].y = 11;
  dog[2].avilable = 1;
  dog[3].power = 1;
  dog[3].energy = 15;
  dog[3].speed = 1;
  dog[3].x = 11;
  dog[3].y = 12;
  dog[3].avilable = 1;
  cat[0].xnow = 7;
  cat[0].ynow = 6;
  cat[1].xnow = 8;
  cat[1].ynow = 7;
  cat[2].xnow = 7;
  cat[2].ynow = 8;
  cat[3].xnow = 6;
  cat[3].ynow = 7;
  cat[0].future_freeze = 1;
  cat[1].future_freeze = 1;
  cat[2].future_freeze = 1;
  cat[3].future_freeze = 1;

  int walls[29][29];

  for (int i = 0; i < 15; i++) {
    for (int j = 0; j < 15; j++) walls[i][j] = 0;
  }

  walls[2][2] = 1;
  walls[2][3] = -1;
  walls[3][2] = 1;
  walls[3][3] = -1;
  walls[4][2] = 1;
  walls[4][3] = -1;
  walls[5][2] = -1;
  walls[9][1] = 1;
  walls[9][2] = 1;
  walls[10][1] = -1;
  walls[10][2] = -1;
  walls[4][5] = 1;
  walls[4][6] = 1;
  walls[5][5] = -1;
  walls[5][6] = -1;
  walls[11][5] = -1;
  walls[12][5] = -1;
  walls[11][6] = 1;
  walls[12][6] = 1;
  walls[2][8] = -1;
  walls[2][9] = 1;
  walls[12][9] = 1;
  walls[12][8] = 1;
  walls[13][8] = -1;
  walls[13][9] = -1;
  walls[12][10] = -1;
  walls[9][10] = -1;
  walls[9][11] = 1;
  walls[4][11] = 1;
  walls[5][11] = 1;
  walls[4][12] = -1;
  walls[5][12] = -1;
  walls[1][13] = -1;
  walls[2][13] = 1;

  for (int i = 0; i < NUM_MICE1; i++) {
    mice1[i].avilable = 1;
  }
  for (int i = 0; i < NUM_MICE2; i++) {
    mice2[i].avilable = 1;
  }
  for (int i = 0; i < NUM_MICE3; i++) {
    mice3[i].avilable = 1;
  }
  for (int i = 0; i < NUM_CHOCOLATES; i++) {
    chocolates[i].avilable = 1;
  }
  for (int i = 0; i < NUM_FISH; i++) {
    fishes[i].avilable = 1;
  }
  for (int i = 0; i < NUM_TALE; i++) {
    tales[i].avilable = 0;
  }

  for (int i = 0; i < 4; i++) {
    cat[i].live = 1;
    cat[i].freeze = 1;
    cat[i].point = 0;
    cat[i].power = 5;
    cat[i].energy = 2;
    cat[i].number_move = 0;
    cat[i].number_hunt = 0;
    cat[i].mice1num = 0;
    cat[i].mice2num = 0;
    cat[i].mice3num = 0;
    cat[i].freezenum = 0;
  }

  for (int i = 0; i < NUM_MICE1; i++) {
    int x, y;

    do {
      x = rand() % 15;
      y = rand() % 15;
    } while ((x == 7 && y == 7) ||
             containsObjectOrAnimal(x, y, mice1, mice2, mice3, chocolates,
                                    fishes, tales, NUM_MICE1, NUM_MICE2,
                                    NUM_MICE3, NUM_CHOCOLATES, NUM_FISH,
                                    NUM_TALE));
    mice1[i].x = x;
    mice1[i].y = y;
  }
  for (int i = 0; i < NUM_MICE2; i++) {
    int x, y;

    do {
      x = rand() % 15;
      y = rand() % 15;
    } while ((x == 7 && y == 7) ||
             containsObjectOrAnimal(x, y, mice1, mice2, mice3, chocolates,
                                    fishes, tales, NUM_MICE1, NUM_MICE2,
                                    NUM_MICE3, NUM_CHOCOLATES, NUM_FISH,
                                    NUM_TALE));
    mice2[i].x = x;
    mice2[i].y = y;
  }
  for (int i = 0; i < NUM_MICE3; i++) {
    int x, y;

    do {
      x = rand() % 15;
      y = rand() % 15;
    } while ((x == 7 && y == 7) ||
             containsObjectOrAnimal(x, y, mice1, mice2, mice3, chocolates,
                                    fishes, tales, NUM_MICE1, NUM_MICE2,
                                    NUM_MICE3, NUM_CHOCOLATES, NUM_FISH,
                                    NUM_TALE));
    mice3[i].x = x;
    mice3[i].y = y;
  }
  for (int i = 0; i < NUM_CHOCOLATES; i++) {
    int x, y;
    do {
      x = rand() % 15;
      y = rand() % 15;
    } while ((x == 7 && y == 7) ||
             containsObjectOrAnimal(x, y, mice1, mice2, mice3, chocolates,
                                    fishes, tales, NUM_MICE1, NUM_MICE2,
                                    NUM_MICE3, NUM_CHOCOLATES, NUM_FISH,
                                    NUM_TALE));
    chocolates[i].x = x;
    chocolates[i].y = y;
  }
  for (int i = 0; i < NUM_FISH; i++) {
    int x, y;
    do {
      x = rand() % 15;
      y = rand() % 15;
    } while ((x == 7 && y == 7) ||
             containsObjectOrAnimal(x, y, mice1, mice2, mice3, chocolates,
                                    fishes, tales, NUM_MICE1, NUM_MICE2,
                                    NUM_MICE3, NUM_CHOCOLATES, NUM_FISH,
                                    NUM_TALE));
    fishes[i].x = x;
    fishes[i].y = y;
  }
  for (int i = 0; i < NUM_TALE; i++) {
    int x, y;
    do {
      x = rand() % 15;
      y = rand() % 15;
    } while ((x == 7 && y == 7) ||
             containsObjectOrAnimal(x, y, mice1, mice2, mice3, chocolates,
                                    fishes, tales, NUM_MICE1, NUM_MICE2,
                                    NUM_MICE3, NUM_CHOCOLATES, NUM_FISH,
                                    NUM_TALE));
    tales[i].x = x;
    tales[i].y = y;
  }

  shuffle(mice1, NUM_MICE1);
  shuffle(mice2, NUM_MICE2);
  shuffle(mice3, NUM_MICE3);

  ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
  ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
  al_register_event_source(event_queue, al_get_keyboard_event_source());
  al_register_event_source(event_queue, al_get_timer_event_source(timer));

  bool function_move_dog = false;
  bool redraw = true;
  bool exit_game = false;
  bool exit_rand = false;
  bool exit_operation = true;

  al_start_timer(timer);
  int gameRound = 1;
  int turn = 0;
  int sw_move = 0;
  int first_move = 0;
  int t_c1, t_c2, t_c3, t_c4;
  int NUMperson = 0;
  int t_c1_cpy;
  int t_c2_cpy;
  int t_c3_cpy;
  int t_c4_cpy;
  int cat1points;
  int cat2points;
  int cat3points;
  int cat4points;
  do {
    t_c1 = rand() % 6 + 1;
    t_c2 = rand() % 6 + 1;
    t_c3 = rand() % 6 + 1;
    t_c4 = rand() % 6 + 1;

  } while (!check_turn(t_c1, t_c2, t_c3, t_c4));

  t_c1_cpy = t_c1;
  t_c2_cpy = t_c2;
  t_c3_cpy = t_c3;
  t_c4_cpy = t_c4;

  while (!exit_game && gameRound < 15) {
    if (first_move) {
      do {
        t_c1 = rand() % 6 + 1;
        t_c2 = rand() % 6 + 1;
        t_c3 = rand() % 6 + 1;
        t_c4 = rand() % 6 + 1;

      } while (!check_turn(t_c1, t_c2, t_c3, t_c4));
    }
    NUMperson = 0;
    while (NUMperson < 4 && !exit_rand) {
      if (exit_operation) {
        NUMperson++;
        exit_operation = false;
        cat[0].number_move = 0;
        cat[1].number_move = 0;
        cat[2].number_move = 0;
        cat[3].number_move = 0;
        if (t_c1 > t_c2 && t_c1 > t_c3 && t_c1 > t_c4) {
          turn = 0;
          t_c1 = -1;
        } else if (t_c2 > t_c1 && t_c2 > t_c3 && t_c2 > t_c4) {
          turn = 1;
          t_c2 = -1;
        } else if (t_c3 > t_c2 && t_c3 > t_c1 && t_c3 > t_c4) {
          turn = 2;
          t_c3 = -1;
        } else if (t_c4 > t_c2 && t_c4 > t_c3 && t_c4 > t_c1) {
          turn = 3;
          t_c4 = -1;
        }

        //  if(turn==0)

        if (function_move_dog) {
          gameRound++;
          cat[0].energy += 1;
          cat[1].energy += 1;
          cat[2].energy += 1;
          cat[3].energy += 1;
          t_c1_cpy = t_c1;
          t_c2_cpy = t_c2;
          t_c3_cpy = t_c3;
          t_c4_cpy = t_c4;

          if (hiddenFish < 4) {
            for (int i = 0; i < NUM_FISH; i++) {
              if (fishes[i].avilable == 0) {
                fishes[i].avilable = 1;
              }
            }
          }

          for (int x = 0; x < 4; x++) {
            if (cat[x].freeze == 0 && cat[x].future_freeze == 1) {
              cat[x].future_freeze = 0;
            } else if (cat[x].freeze == 0 && cat[x].future_freeze == 0) {
              cat[x].future_freeze = 1;
              cat[x].freeze = 1;
            }
          }
          function_move_dog = false;
          int new_move_dog;
          for (int i = 0, sw = 1; i < dog[0].speed && sw; i++) {
            new_move_dog = moving_dog(dog[0].x, dog[0].y, cat, walls);
            /// move_dog1
            if (new_move_dog == 8) {
              dog[0].y--;
            } else if (new_move_dog == 6) {
              dog[0].x++;
            } else if (new_move_dog == 4) {
              dog[0].x--;
            } else if (new_move_dog == 2) {
              dog[0].y++;
            }
            if (dog[0].x == cat[0].xnow && dog[0].y == cat[0].ynow) {
              sw = 0;
              if (cat[0].energy != 0 && dog[0].energy != 0 &&
                  dog[0].power != 0) {
                if (dog[0].power / cat[0].energy >
                    cat[0].power / dog[0].energy) {
                  dog[0].energy -=
                      (cat[0].power * cat[0].energy / dog[0].power);
                  cat[0].freeze = 0;
                  cat[0].power = 1;
                  cat[0].energy = 0;

                  for (int i = 0; i < cat[0].number_hunt; i++) {
                    if (cat[0].store[0][i] == 1)
                      mice1[cat[0].store[1][i]].avilable = 1;
                    else if (cat[0].store[0][i] == 2)
                      mice2[cat[0].store[1][i]].avilable = 1;
                    else if (cat[0].store[0][i] == 3)
                      mice3[cat[0].store[1][i]].avilable = 1;
                  }
                  cat[0].number_hunt = 0;
                } else {
                  dog[0].avilable = 0;
                  ///      cat[0].energy -=(dog[0].power * dog[0].energy /
                  ///      cat[0].power);
                }
              }
            }
            if (dog[0].x == cat[1].xnow && dog[0].y == cat[1].ynow) {
              sw = 0;
              if (cat[1].energy != 0 && dog[0].energy != 0 &&
                  dog[0].power != 0) {
                if (dog[0].power / cat[1].energy >
                    cat[1].power / dog[0].energy) {
                  dog[0].energy -=
                      (cat[1].power * cat[1].energy / dog[0].power);
                  cat[1].freeze = 0;
                  cat[1].power = 1;
                  cat[1].energy = 0;
                  for (int i = 0; i < cat[1].number_hunt; i++) {
                    if (cat[1].store[0][i] == 1)
                      mice1[cat[1].store[1][i]].avilable = 1;
                    else if (cat[1].store[0][i] == 2)
                      mice2[cat[1].store[1][i]].avilable = 1;
                    else if (cat[1].store[0][i] == 3)
                      mice3[cat[1].store[1][i]].avilable = 1;
                  }
                  cat[1].number_hunt = 0;
                } else {
                  dog[0].avilable = 0;
                  ///        cat[1].energy -=(dog[0].power * dog[0].energy /
                  ///        cat[1].power);
                }
              }
            }
            if (dog[0].x == cat[2].xnow && dog[0].y == cat[2].ynow) {
              sw = 0;
              if (cat[2].energy != 0 && dog[0].energy != 0 &&
                  dog[0].power != 0) {
                if (dog[0].power / cat[2].energy >
                    cat[0].power / dog[0].energy) {
                  dog[0].energy -=
                      (cat[2].power * cat[2].energy / dog[0].power);
                  cat[2].freeze = 0;
                  cat[2].power = 1;
                  cat[2].energy = 0;
                  for (int i = 0; i < cat[2].number_hunt; i++) {
                    if (cat[2].store[0][i] == 1)
                      mice1[cat[2].store[1][i]].avilable = 1;
                    else if (cat[2].store[0][i] == 2)
                      mice2[cat[2].store[1][i]].avilable = 1;
                    else if (cat[2].store[0][i] == 3)
                      mice3[cat[2].store[1][i]].avilable = 1;
                  }
                  cat[2].number_hunt = 0;
                } else {
                  dog[0].avilable = 0;
                  ///      cat[2].energy -=(dog[0].power * dog[0].energy /
                  ///      cat[2].power);
                }
              }
            }
            if (dog[0].x == cat[3].xnow && dog[0].y == cat[3].ynow) {
              sw = 0;
              if (cat[3].energy != 0 && dog[0].energy != 0 &&
                  dog[0].power != 0) {
                if (dog[0].power / cat[3].energy >
                    cat[3].power / dog[0].energy) {
                  dog[0].energy -=
                      (cat[3].power * cat[3].energy / dog[0].power);
                  cat[3].freeze = 0;
                  cat[3].power = 1;
                  cat[3].energy = 0;
                  for (int i = 0; i < cat[3].number_hunt; i++) {
                    if (cat[3].store[0][i] == 1)
                      mice1[cat[3].store[1][i]].avilable = 1;
                    else if (cat[3].store[0][i] == 2)
                      mice2[cat[3].store[1][i]].avilable = 1;
                    else if (cat[3].store[0][i] == 3)
                      mice3[cat[3].store[1][i]].avilable = 1;
                  }
                  cat[3].number_hunt = 0;
                } else {
                  dog[0].avilable = 0;
                  ///      cat[3].energy -=(dog[0].power * dog[0].energy /
                  ///      cat[3].power);
                }
              }
            }
          }
          for (int i = 0, sw = 1; i < dog[1].speed && sw; i++) {
            int new_move_dog = moving_dog(dog[1].x, dog[1].y, cat, walls);
            if (new_move_dog == 8) {
              dog[1].y--;
            } else if (new_move_dog == 6) {
              dog[1].x++;
            } else if (new_move_dog == 4) {
              dog[1].x--;
            } else if (new_move_dog == 2) {
              dog[1].y++;
            }
            if (dog[1].x == cat[0].xnow && dog[1].y == cat[0].ynow) {
              sw = 0;
              if (cat[0].energy != 0 && dog[1].energy != 0 &&
                  dog[1].power != 0) {
                if (dog[1].power / cat[0].energy >
                    cat[0].power / dog[1].energy) {
                  dog[1].energy -=
                      (cat[0].power * cat[0].energy / dog[1].power);
                  cat[0].freeze = 0;
                  cat[0].power = 1;
                  cat[0].energy = 0;
                  for (int i = 0; i < cat[0].number_hunt; i++) {
                    if (cat[0].store[0][i] == 1)
                      mice1[cat[0].store[1][i]].avilable = 1;
                    else if (cat[0].store[0][i] == 2)
                      mice2[cat[0].store[1][i]].avilable = 1;
                    else if (cat[0].store[0][i] == 3)
                      mice3[cat[0].store[1][i]].avilable = 1;
                  }
                  cat[0].number_hunt = 0;
                } else {
                  dog[1].avilable = 0;
                  ///     cat[0].energy -=(dog[1].power * dog[1].energy /
                  ///     cat[0].power);
                }
              }
            }

            if (dog[1].x == cat[1].xnow && dog[1].y == cat[1].ynow) {
              sw = 0;
              if (cat[1].energy != 0 && dog[1].energy != 0 &&
                  dog[1].power != 0) {
                if (dog[1].power / cat[1].energy >
                    cat[1].power / dog[1].energy) {
                  dog[1].energy -=
                      (cat[1].power * cat[1].energy / dog[1].power);
                  cat[1].freeze = 0;
                  cat[1].power = 1;
                  cat[1].energy = 0;
                  for (int i = 0; i < cat[1].number_hunt; i++) {
                    if (cat[1].store[0][i] == 1)
                      mice1[cat[1].store[1][i]].avilable = 1;
                    else if (cat[1].store[0][i] == 2)
                      mice2[cat[1].store[1][i]].avilable = 1;
                    else if (cat[1].store[0][i] == 3)
                      mice3[cat[1].store[1][i]].avilable = 1;
                  }
                  cat[1].number_hunt = 0;
                } else {
                  dog[1].avilable = 0;
                  ///     cat[1].energy -=(dog[1].power * dog[1].energy /
                  ///     cat[1].power);
                }
              }
            }

            if (dog[1].x == cat[2].xnow && dog[1].y == cat[2].ynow) {
              sw = 0;
              if (cat[2].energy != 0 && dog[1].energy != 0 &&
                  dog[1].power != 0) {
                if (dog[1].power / cat[2].energy >
                    cat[2].power / dog[1].energy) {
                  dog[1].energy -=
                      (cat[2].power * cat[2].energy / dog[1].power);
                  cat[2].freeze = 0;
                  cat[2].power = 1;
                  cat[2].energy = 0;
                  for (int i = 0; i < cat[2].number_hunt; i++) {
                    if (cat[2].store[0][i] == 1)
                      mice1[cat[2].store[1][i]].avilable = 1;
                    else if (cat[2].store[0][i] == 2)
                      mice2[cat[2].store[1][i]].avilable = 1;
                    else if (cat[2].store[0][i] == 3)
                      mice3[cat[2].store[1][i]].avilable = 1;
                  }
                  cat[2].number_hunt = 0;
                } else {
                  dog[1].avilable = 0;
                  ///       cat[2].energy -=(dog[1].power * dog[1].energy /
                  ///       cat[2].power);
                }
              }
            }

            if (dog[1].x == cat[3].xnow && dog[1].y == cat[3].ynow) {
              sw = 0;
              if (cat[3].energy != 0 && dog[1].energy != 0 &&
                  dog[1].power != 0) {
                if (dog[1].power / cat[3].energy >
                    cat[3].power / dog[1].energy) {
                  dog[1].energy -=
                      (cat[3].power * cat[3].energy / dog[1].power);
                  cat[3].freeze = 0;
                  cat[3].power = 1;
                  cat[3].energy = 0;
                  for (int i = 0; i < cat[3].number_hunt; i++) {
                    if (cat[3].store[0][i] == 1)
                      mice1[cat[3].store[1][i]].avilable = 1;
                    else if (cat[3].store[0][i] == 2)
                      mice2[cat[3].store[1][i]].avilable = 1;
                    else if (cat[3].store[0][i] == 3)
                      mice3[cat[3].store[1][i]].avilable = 1;
                  }
                  cat[3].number_hunt = 0;
                } else {
                  dog[1].avilable = 0;
                  ///       cat[3].energy -=(dog[1].power * dog[1].energy /
                  ///       cat[3].power);
                }
              }
            }
          }
          for (int i = 0, sw = 1; i < dog[2].speed && sw; i++) {
            int new_move_dog = moving_dog(dog[2].x, dog[2].y, cat, walls);
            if (new_move_dog == 8) {
              dog[2].y--;
            } else if (new_move_dog == 6) {
              dog[2].x++;
            } else if (new_move_dog == 4) {
              dog[2].x--;
            } else if (new_move_dog == 2) {
              dog[2].y++;
            }

            if (dog[2].x == cat[0].xnow && dog[2].y == cat[0].ynow) {
              sw = 0;
              if (cat[0].energy != 0 && dog[2].energy != 0 &&
                  dog[2].power != 0) {
                if (dog[2].power / cat[0].energy >
                    cat[0].power / dog[2].energy) {
                  dog[2].energy -=
                      (cat[0].power * cat[0].energy / dog[2].power);
                  cat[0].freeze = 0;
                  cat[0].power = 1;
                  cat[0].energy = 0;
                  for (int i = 0; i < cat[0].number_hunt; i++) {
                    if (cat[0].store[0][i] == 1)
                      mice1[cat[0].store[1][i]].avilable = 1;
                    else if (cat[0].store[0][i] == 2)
                      mice2[cat[0].store[1][i]].avilable = 1;
                    else if (cat[0].store[0][i] == 3)
                      mice3[cat[0].store[1][i]].avilable = 1;
                  }
                  cat[0].number_hunt = 0;
                } else {
                  dog[2].avilable = 0;
                  ///      cat[0].energy -=(dog[2].power * dog[2].energy /
                  ///      cat[0].power);
                }
              }
            }

            if (dog[2].x == cat[1].xnow && dog[2].y == cat[1].ynow) {
              sw = 0;
              if (cat[1].energy != 0 && dog[2].energy != 0 &&
                  dog[2].power != 0) {
                if (dog[2].power / cat[1].energy >
                    cat[1].power / dog[2].energy) {
                  dog[2].energy -=
                      (cat[1].power * cat[1].energy / dog[2].power);
                  cat[1].freeze = 0;
                  cat[1].power = 1;
                  cat[1].energy = 0;
                  for (int i = 0; i < cat[1].number_hunt; i++) {
                    if (cat[1].store[0][i] == 1)
                      mice1[cat[1].store[1][i]].avilable = 1;
                    else if (cat[1].store[0][i] == 2)
                      mice2[cat[1].store[1][i]].avilable = 1;
                    else if (cat[1].store[0][i] == 3)
                      mice3[cat[1].store[1][i]].avilable = 1;
                  }
                  cat[1].number_hunt = 0;
                } else {
                  dog[2].avilable = 0;
                  ///     cat[1].energy -=(dog[2].power * dog[2].energy /
                  ///     cat[1].power);
                }
              }
            }

            if (dog[2].x == cat[2].xnow && dog[2].y == cat[2].ynow) {
              sw = 0;
              if (cat[2].energy != 0 && dog[2].energy != 0 &&
                  dog[2].power != 0) {
                if (dog[2].power / cat[2].energy >
                    cat[2].power / dog[2].energy) {
                  dog[2].energy -=
                      (cat[2].power * cat[2].energy / dog[2].power);
                  cat[2].freeze = 0;
                  cat[2].power = 1;
                  cat[2].energy = 0;
                  for (int i = 0; i < cat[2].number_hunt; i++) {
                    if (cat[2].store[0][i] == 1)
                      mice1[cat[2].store[1][i]].avilable = 1;
                    else if (cat[2].store[0][i] == 2)
                      mice2[cat[2].store[1][i]].avilable = 1;
                    else if (cat[2].store[0][i] == 3)
                      mice3[cat[2].store[1][i]].avilable = 1;
                  }
                  cat[2].number_hunt = 0;
                } else {
                  dog[2].avilable = 0;
                  ///     cat[2].energy -=(dog[2].power * dog[2].energy /
                  ///     cat[2].power);
                }
              }
            }

            if (dog[2].x == cat[3].xnow && dog[2].y == cat[3].ynow) {
              sw = 0;
              if (cat[3].energy != 0 && dog[2].energy != 0 &&
                  dog[2].power != 0) {
                if (dog[2].power / cat[3].energy >
                    cat[3].power / dog[2].energy) {
                  dog[2].energy -=
                      (cat[3].power * cat[3].energy / dog[2].power);
                  cat[3].freeze = 0;
                  cat[3].power = 1;
                  cat[3].energy = 0;
                  for (int i = 0; i < cat[3].number_hunt; i++) {
                    if (cat[3].store[0][i] == 1)
                      mice1[cat[3].store[1][i]].avilable = 1;
                    else if (cat[3].store[0][i] == 2)
                      mice2[cat[3].store[1][i]].avilable = 1;
                    else if (cat[3].store[0][i] == 3)
                      mice3[cat[3].store[1][i]].avilable = 1;
                  }
                  cat[3].number_hunt = 0;
                } else {
                  dog[2].avilable = 0;
                  ///      cat[3].energy -=(dog[2].power * dog[2].energy /
                  ///      cat[3].power);
                }
              }
            }
          }
          for (int i = 0, sw = 1; i < dog[3].speed && sw; i++) {
            new_move_dog = moving_dog(dog[3].x, dog[3].y, cat, walls);
            if (new_move_dog == 8) {
              dog[3].y--;
            } else if (new_move_dog == 6) {
              dog[3].x++;
            } else if (new_move_dog == 4) {
              dog[3].x--;
            } else if (new_move_dog == 2) {
              dog[3].y++;
            }
            if (dog[3].x == cat[0].xnow && dog[3].y == cat[0].ynow) {
              sw = 0;
              if (cat[0].energy != 0 && dog[3].energy != 0 &&
                  dog[3].power != 0) {
                if (dog[3].power / cat[0].energy >
                    cat[0].power / dog[3].energy) {
                  dog[3].energy -=
                      (cat[0].power * cat[0].energy / dog[3].power);
                  cat[0].freeze = 0;
                  cat[0].power = 1;
                  cat[0].energy = 0;
                  for (int i = 0; i < cat[0].number_hunt; i++) {
                    if (cat[0].store[0][i] == 1)
                      mice1[cat[0].store[1][i]].avilable = 1;
                    else if (cat[0].store[0][i] == 2)
                      mice2[cat[0].store[1][i]].avilable = 1;
                    else if (cat[0].store[0][i] == 3)
                      mice3[cat[0].store[1][i]].avilable = 1;
                  }
                  cat[0].number_hunt = 0;
                } else {
                  dog[3].avilable = 0;
                  ///         cat[0].energy -=(dog[3].power * dog[3].energy /
                  ///         cat[0].power);
                }
              }
            }

            if (dog[3].x == cat[1].xnow && dog[3].y == cat[1].ynow) {
              sw = 0;
              if (cat[1].energy != 0 && dog[3].energy != 0 &&
                  dog[3].power != 0) {
                if (dog[3].power / cat[1].energy >
                    cat[1].power / dog[3].energy) {
                  dog[3].energy -=
                      (cat[1].power * cat[1].energy / dog[3].power);
                  cat[1].freeze = 0;
                  cat[1].power = 1;
                  cat[1].energy = 0;
                  for (int i = 0; i < cat[1].number_hunt; i++) {
                    if (cat[1].store[0][i] == 1)
                      mice1[cat[1].store[1][i]].avilable = 1;
                    else if (cat[1].store[0][i] == 2)
                      mice2[cat[1].store[1][i]].avilable = 1;
                    else if (cat[1].store[0][i] == 3)
                      mice3[cat[1].store[1][i]].avilable = 1;
                  }
                  cat[1].number_hunt = 0;
                } else {
                  dog[3].avilable = 0;
                  ///     cat[1].energy -=(dog[3].power * dog[3].energy /
                  ///     cat[1].power);
                }
              }
            }

            if (dog[3].x == cat[2].xnow && dog[3].y == cat[2].ynow) {
              sw = 0;
              if (cat[2].energy != 0 && dog[3].energy != 0 &&
                  dog[3].power != 0) {
                if (dog[3].power / cat[2].energy >
                    cat[2].power / dog[3].energy) {
                  dog[3].energy -=
                      (cat[0].power * cat[2].energy / dog[3].power);
                  cat[2].freeze = 0;
                  cat[2].power = 1;
                  cat[2].energy = 0;
                  for (int i = 0; i < cat[2].number_hunt; i++) {
                    if (cat[2].store[0][i] == 1)
                      mice1[cat[2].store[1][i]].avilable = 1;
                    else if (cat[2].store[0][i] == 2)
                      mice2[cat[2].store[1][i]].avilable = 1;
                    else if (cat[2].store[0][i] == 3)
                      mice3[cat[2].store[1][i]].avilable = 1;
                  }
                  cat[2].number_hunt = 0;
                } else {
                  dog[3].avilable = 0;
                  ///     cat[2].energy -=(dog[3].power * dog[3].energy /
                  ///     cat[2].power);
                }
              }
            }

            if (dog[3].x == cat[3].xnow && dog[3].y == cat[3].ynow) {
              sw = 0;
              if (cat[3].energy != 0 && dog[3].energy != 0 &&
                  dog[3].power != 0) {
                if (dog[3].power / cat[3].energy >
                    cat[3].power / dog[3].energy) {
                  dog[3].energy -=
                      (cat[3].power * cat[3].energy / dog[3].power);
                  cat[3].freeze = 0;
                  cat[3].power = 1;
                  cat[3].energy = 0;
                  for (int i = 0; i < cat[3].number_hunt; i++) {
                    if (cat[3].store[0][i] == 1)
                      mice1[cat[3].store[1][i]].avilable = 1;
                    else if (cat[3].store[0][i] == 2)
                      mice2[cat[3].store[1][i]].avilable = 1;
                    else if (cat[3].store[0][i] == 3)
                      mice3[cat[3].store[1][i]].avilable = 1;
                  }
                  cat[3].number_hunt = 0;
                } else {
                  dog[3].avilable = 0;
                  ///     cat[3].energy -=(dog[3].power * dog[3].energy /
                  ///     cat[3].power);
                }
              }
            }
          }

          mice1[NUM_MICE1];

          int new_move_mice = 0;
          for (int i = 0; i < NUM_MICE1; i++) {
            for (int j = 0; j < 1; j++) {
              new_move_mice = moving_mice(mice1[i].x, mice1[i].y, cat, walls);
              if (new_move_mice == 8)
                mice1[i].y--;
              else if (new_move_mice == 2)
                mice1[i].y++;
              else if (new_move_mice == 4)
                mice1[i].x--;
              else if (new_move_mice == 6)
                mice1[i].x++;
            }
          }
          for (int i = 0; i < NUM_MICE2; i++) {
            for (int j = 0; j < 2; j++) {
              new_move_mice = moving_mice(mice2[i].x, mice2[i].y, cat, walls);
              if (new_move_mice == 8)
                mice2[i].y--;
              else if (new_move_mice == 2)
                mice2[i].y++;
              else if (new_move_mice == 4)
                mice2[i].x--;
              else if (new_move_mice == 6)
                mice2[i].x++;
            }
          }
          for (int i = 0; i < NUM_MICE3; i++) {
            for (int j = 0; j < 3; j++) {
              new_move_mice = moving_mice(mice3[i].x, mice3[i].y, cat, walls);
              if (new_move_mice == 8)
                mice3[i].y--;
              else if (new_move_mice == 2)
                mice3[i].y++;
              else if (new_move_mice == 4)
                mice3[i].x--;
              else if (new_move_mice == 6)
                mice3[i].x++;
            }
          }
        }
      }

      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);
      if (ev.type == ALLEGRO_EVENT_TIMER) {
        redraw = true;
      } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
        switch (ev.keyboard.keycode) {
          case ALLEGRO_KEY_RIGHT:
            switch (turn) {
              case 0:
                if (cat[0].freeze && cat[turn].number_move < 3 &&
                    cat[0].xnow != 14 &&
                    (walls[cat[0].xnow][cat[0].ynow] *
                         walls[(cat[0].xnow) + 1][cat[0].ynow] !=
                     -1)) {
                  cat[turn].number_move++;
                  cat[0].xnow += 1;
                  sw_move = 1;
                }
                break;
              case 1:
                if (cat[1].freeze && cat[turn].number_move < 3 &&
                    cat[1].xnow != 14 &&
                    (walls[cat[1].xnow][cat[1].ynow] *
                         walls[(cat[1].xnow) + 1][cat[1].ynow] !=
                     -1)) {
                  cat[turn].number_move++;
                  cat[1].xnow += 1;
                  sw_move = 1;
                }
                break;
              case 2:
                if (cat[2].freeze && cat[turn].number_move < 3 &&
                    cat[2].xnow != 14 &&
                    (walls[cat[2].xnow][cat[2].ynow] *
                         walls[(cat[2].xnow) + 1][cat[2].ynow] !=
                     -1)) {
                  cat[turn].number_move++;
                  cat[2].xnow += 1;
                  sw_move = 1;
                }
                break;
              case 3:
                if (cat[3].freeze && cat[turn].number_move < 3 &&
                    cat[3].xnow != 14 &&
                    (walls[cat[3].xnow][cat[3].ynow] *
                         walls[(cat[3].xnow) + 1][cat[3].ynow] !=
                     -1)) {
                  cat[turn].number_move++;
                  cat[3].xnow += 1;
                  sw_move = 1;
                }
                break;
            }
            break;
          case ALLEGRO_KEY_LEFT:
            switch (turn) {
              case 0:
                if (cat[0].freeze && cat[turn].number_move < 3 &&
                    cat[0].xnow != 0 &&
                    (walls[cat[0].xnow][cat[0].ynow] *
                         walls[(cat[0].xnow) - 1][cat[0].ynow] !=
                     -1)) {
                  cat[turn].number_move++;
                  cat[0].xnow -= 1;
                  sw_move = 1;
                }
                break;
              case 1:
                if (cat[1].freeze && cat[turn].number_move < 3 &&
                    cat[1].xnow != 0 &&
                    (walls[cat[1].xnow][cat[1].ynow] *
                         walls[(cat[1].xnow) - 1][cat[1].ynow] !=
                     -1)) {
                  cat[turn].number_move++;
                  cat[1].xnow -= 1;
                  sw_move = 1;
                }
                break;
              case 2:
                if (cat[2].freeze && cat[turn].number_move < 3 &&
                    cat[2].xnow != 0 &&
                    (walls[cat[2].xnow][cat[2].ynow] *
                         walls[(cat[2].xnow) - 1][cat[2].ynow] !=
                     -1)) {
                  cat[turn].number_move++;
                  cat[2].xnow -= 1;
                  sw_move = 1;
                }
                break;
              case 3:
                if (cat[3].freeze && cat[turn].number_move < 3 &&
                    cat[3].xnow != 0 &&
                    (walls[cat[3].xnow][cat[3].ynow] *
                         walls[(cat[3].xnow) - 1][cat[3].ynow] !=
                     -1)) {
                  cat[turn].number_move++;
                  cat[3].xnow -= 1;
                  sw_move = 1;
                }
                break;
            }
            break;
          case ALLEGRO_KEY_DOWN:
            switch (turn) {
              case 0:
                if (cat[0].freeze && cat[turn].number_move < 3 &&
                    cat[0].ynow != 14 &&
                    (walls[cat[0].xnow][cat[0].ynow] *
                         walls[cat[0].xnow][(cat[0].ynow) + 1] !=
                     -1)) {
                  cat[turn].number_move++;
                  cat[0].ynow += 1;
                  sw_move = 1;
                }
                break;
              case 1:
                if (cat[1].freeze && cat[turn].number_move < 3 &&
                    cat[1].ynow != 14 &&
                    (walls[cat[1].xnow][cat[1].ynow] *
                         walls[cat[1].xnow][(cat[1].ynow) + 1] !=
                     -1)) {
                  cat[turn].number_move++;
                  cat[1].ynow += 1;
                  sw_move = 1;
                }
                break;
              case 2:
                if (cat[2].freeze && cat[turn].number_move < 3 &&
                    cat[2].ynow != 14 &&
                    (walls[cat[2].xnow][cat[2].ynow] *
                         walls[cat[2].xnow][(cat[2].ynow) + 1] !=
                     -1)) {
                  cat[turn].number_move++;
                  cat[2].ynow += 1;
                  sw_move = 1;
                }
                break;
              case 3:
                if (cat[3].freeze && cat[turn].number_move < 3 &&
                    cat[3].ynow != 14 &&
                    (walls[cat[3].xnow][cat[3].ynow] *
                         walls[cat[3].xnow][(cat[3].ynow) + 1] !=
                     -1)) {
                  cat[turn].number_move++;
                  cat[3].ynow += 1;
                  sw_move = 1;
                }
                break;
            }
            break;
          case ALLEGRO_KEY_UP:
            switch (turn) {
              case 0:
                if (cat[0].freeze && cat[turn].number_move < 3 &&
                    cat[0].ynow != 0 &&
                    (walls[cat[0].xnow][cat[0].ynow] *
                         walls[cat[0].xnow][(cat[0].ynow) - 1] !=
                     -1)) {
                  cat[0].ynow -= 1;
                  cat[turn].number_move++;
                  sw_move = 1;
                }
                break;
              case 1:
                if (cat[1].freeze && cat[turn].number_move < 3 &&
                    cat[1].ynow != 0 &&
                    (walls[cat[1].xnow][cat[1].ynow] *
                         walls[cat[1].xnow][(cat[1].ynow) - 1] !=
                     -1)) {
                  cat[1].ynow -= 1;
                  cat[turn].number_move++;
                  sw_move = 1;
                }
                break;
              case 2:
                if (cat[2].freeze && cat[turn].number_move < 3 &&
                    cat[2].ynow != 0 &&
                    (walls[cat[2].xnow][cat[2].ynow] *
                         walls[cat[2].xnow][(cat[2].ynow) - 1] !=
                     -1)) {
                  cat[turn].number_move++;
                  cat[2].ynow -= 1;
                  sw_move = 1;
                }
                break;
              case 3:
                if (cat[3].freeze && cat[turn].number_move < 3 &&
                    cat[3].ynow != 0 &&
                    (walls[cat[3].xnow][cat[3].ynow] *
                         walls[cat[3].xnow][(cat[3].ynow) - 1] !=
                     -1)) {
                  cat[turn].number_move++;
                  cat[3].ynow -= 1;
                  sw_move = 1;
                }
                break;
            }
            break;
          case ALLEGRO_KEY_ENTER:
            exit_operation = true;
            break;
          case ALLEGRO_KEY_ESCAPE:
            exit_operation = true;
            exit_rand = true;
            exit_game = true;
            break;
        }
      }
      if (sw_move) {
        int answer = search_Mice1(cat[turn].xnow, cat[turn].ynow, mice1);
        switch (answer) {
          case 0:
            mice1[0].avilable = 0;
            cat[turn].mice1num++;
            cat[turn].store[0][cat[turn].number_hunt] = 1;
            cat[turn].store[1][cat[turn].number_hunt] = 0;
            cat[turn].number_hunt++;
            break;
          case 1:
            mice1[1].avilable = 0;
            cat[turn].mice1num++;
            cat[turn].store[0][cat[turn].number_hunt] = 1;
            cat[turn].store[1][cat[turn].number_hunt] = 1;
            cat[turn].number_hunt++;
            break;
          case 2:
            mice1[2].avilable = 0;
            cat[turn].mice1num++;
            cat[turn].store[0][cat[turn].number_hunt] = 1;
            cat[turn].store[1][cat[turn].number_hunt] = 2;
            cat[turn].number_hunt++;
            break;
          case 3:
            mice1[3].avilable = 0;
            cat[turn].mice1num++;
            cat[turn].store[0][cat[turn].number_hunt] = 1;
            cat[turn].store[1][cat[turn].number_hunt] = 3;
            cat[turn].number_hunt++;
            break;
          case 4:
            mice1[4].avilable = 0;
            cat[turn].mice1num++;
            cat[turn].store[0][cat[turn].number_hunt] = 1;
            cat[turn].store[1][cat[turn].number_hunt] = 4;
            cat[turn].number_hunt++;
            break;
          case 5:
            mice1[5].avilable = 0;
            cat[turn].mice1num++;
            cat[turn].store[0][cat[turn].number_hunt] = 1;
            cat[turn].store[1][cat[turn].number_hunt] = 5;
            cat[turn].number_hunt++;
            break;
          case 6:
            mice1[6].avilable = 0;
            cat[turn].mice1num++;
            cat[turn].store[0][cat[turn].number_hunt] = 1;
            cat[turn].store[1][cat[turn].number_hunt] = 6;
            cat[turn].number_hunt++;
            break;
          case 7:
            mice1[7].avilable = 0;
            cat[turn].mice1num++;
            cat[turn].store[0][cat[turn].number_hunt] = 1;
            cat[turn].store[1][cat[turn].number_hunt] = 7;
            cat[turn].number_hunt++;
            break;
        }
        answer = search_Mice2(cat[turn].xnow, cat[turn].ynow, mice2);
        switch (answer) {
          case 0:
            mice2[0].avilable = 0;
            cat[turn].mice2num++;
            cat[turn].store[0][cat[turn].number_hunt] = 2;
            cat[turn].store[1][cat[turn].number_hunt] = 0;
            cat[turn].number_hunt++;
            break;
          case 1:
            mice2[1].avilable = 0;
            cat[turn].mice2num++;
            cat[turn].store[0][cat[turn].number_hunt] = 2;
            cat[turn].store[1][cat[turn].number_hunt] = 1;
            cat[turn].number_hunt++;
            break;
          case 2:
            mice2[2].avilable = 0;
            cat[turn].mice2num++;
            cat[turn].store[0][cat[turn].number_hunt] = 2;
            cat[turn].store[1][cat[turn].number_hunt] = 2;
            cat[turn].number_hunt++;
            break;
          case 3:
            mice2[3].avilable = 0;
            cat[turn].mice2num++;
            cat[turn].store[0][cat[turn].number_hunt] = 2;
            cat[turn].store[1][cat[turn].number_hunt] = 3;
            cat[turn].number_hunt++;
            break;
          case 4:
            mice2[4].avilable = 0;
            cat[turn].mice2num++;
            cat[turn].store[0][cat[turn].number_hunt] = 2;
            cat[turn].store[1][cat[turn].number_hunt] = 4;
            cat[turn].number_hunt++;
            break;
          case 5:
            mice2[5].avilable = 0;
            cat[turn].mice2num++;
            cat[turn].store[0][cat[turn].number_hunt] = 2;
            cat[turn].store[1][cat[turn].number_hunt] = 5;
            cat[turn].number_hunt++;
            break;
        }
        answer = search_Mice3(cat[turn].xnow, cat[turn].ynow, mice3);
        switch (answer) {
          case 0:
            mice3[0].avilable = 0;
            cat[turn].mice3num++;
            cat[turn].store[0][cat[turn].number_hunt] = 3;
            cat[turn].store[1][cat[turn].number_hunt] = 0;
            cat[turn].number_hunt++;
            break;
          case 1:
            mice3[1].avilable = 0;
            cat[turn].mice3num++;
            cat[turn].store[0][cat[turn].number_hunt] = 3;
            cat[turn].store[1][cat[turn].number_hunt] = 1;
            cat[turn].number_hunt++;
            break;
          case 2:
            mice3[2].avilable = 0;
            cat[turn].mice3num++;
            cat[turn].store[0][cat[turn].number_hunt] = 3;
            cat[turn].store[1][cat[turn].number_hunt] = 2;
            cat[turn].number_hunt++;
            break;
          case 3:
            mice3[3].avilable = 0;
            cat[turn].mice3num++;
            cat[turn].store[0][cat[turn].number_hunt] = 3;
            cat[turn].store[1][cat[turn].number_hunt] = 3;
            cat[turn].number_hunt++;
            break;
          case 4:
            mice3[4].avilable = 0;
            cat[turn].mice3num++;
            cat[turn].store[0][cat[turn].number_hunt] = 3;
            cat[turn].store[1][cat[turn].number_hunt] = 4;
            cat[turn].number_hunt++;
            break;
          case 5:
            mice3[5].avilable = 0;
            cat[turn].mice3num++;
            cat[turn].store[0][cat[turn].number_hunt] = 3;
            cat[turn].store[1][cat[turn].number_hunt] = 5;
            cat[turn].number_hunt++;
            break;
        }

        if (cat[0].xnow == cat[1].xnow && cat[0].ynow == cat[1].ynow) {
          if (cat[0].power != 0 && cat[1].power != 0) {
            if (cat[0].energy / cat[1].power > cat[1].energy / cat[0].power) {
              cat[0].energy -= cat[1].power * cat[1].energy / cat[0].power;
              cat[1].freeze = 0;
              cat[1].power = 1;
              cat[1].energy = 0;
              for (int i = 0; i < cat[1].number_hunt;
                   i++, cat[0].number_hunt++) {
                cat[0].store[0][cat[0].number_hunt] = cat[1].store[0][i];
                cat[0].store[1][cat[0].number_hunt] = cat[1].store[1][i];
                if (cat[1].store[0][i] == 1)
                  cat[0].mice1num++;
                else if (cat[1].store[0][i] == 2)
                  cat[0].mice2num++;
                else if (cat[1].store[0][i] == 3)
                  cat[0].mice3num++;
                cat[1].store[0][i] = -1;
                cat[1].store[1][i] = -1;

                cat[1].mice2num = 0;
                cat[1].mice1num = 0;
                cat[1].mice3num = 0;
              }
            } else
              cat[1].energy -= cat[0].power * cat[0].energy / cat[1].power;
            cat[0].freeze = 0;
            cat[0].power = 1;
            cat[0].energy = 0;
            for (int i = 0; i < cat[0].number_hunt; i++, cat[1].number_hunt++) {
              cat[1].store[0][cat[1].number_hunt] = cat[0].store[0][i];
              cat[1].store[1][cat[1].number_hunt] = cat[0].store[1][i];
              if (cat[0].store[0][i] == 1)
                cat[1].mice1num++;
              else if (cat[0].store[0][i] == 2)
                cat[1].mice2num++;
              else if (cat[0].store[0][i] == 3)
                cat[1].mice3num++;
              cat[0].store[0][i] = -1;
              cat[0].store[1][i] = -1;

              cat[0].mice2num = 0;
              cat[0].mice1num = 0;
              cat[0].mice3num = 0;
            }
          }
        }
        if (cat[0].xnow == cat[2].xnow && cat[0].ynow == cat[2].ynow) {
          if (cat[0].power != 0 && cat[2].power != 0) {
            if (cat[0].energy / cat[2].power > cat[2].energy / cat[0].power) {
              cat[0].energy -= cat[2].power * cat[2].energy / cat[0].power;
              cat[2].freeze = 0;
              cat[2].power = 1;
              cat[2].energy = 0;
              for (int i = 0; i < cat[2].number_hunt;
                   i++, cat[0].number_hunt++) {
                cat[0].store[0][cat[0].number_hunt] = cat[2].store[0][i];
                cat[0].store[1][cat[0].number_hunt] = cat[2].store[1][i];
                if (cat[2].store[0][i] == 1)
                  cat[0].mice1num++;
                else if (cat[2].store[0][i] == 2)
                  cat[0].mice2num++;
                else if (cat[2].store[0][i] == 3)
                  cat[0].mice3num++;
                cat[2].store[0][i] = -1;
                cat[2].store[1][i] = -1;

                cat[2].mice2num = 0;
                cat[2].mice1num = 0;
                cat[2].mice3num = 0;
              }
            } else
              cat[2].energy -= cat[0].power * cat[0].energy / cat[2].power;
            cat[0].freeze = 0;
            cat[0].power = 1;
            cat[0].energy = 0;
            for (int i = 0; i < cat[0].number_hunt; i++, cat[2].number_hunt++) {
              cat[2].store[0][cat[2].number_hunt] = cat[0].store[0][i];
              cat[2].store[1][cat[2].number_hunt] = cat[0].store[1][i];
              if (cat[0].store[0][i] == 1)
                cat[2].mice1num++;
              else if (cat[0].store[0][i] == 2)
                cat[2].mice2num++;
              else if (cat[0].store[0][i] == 3)
                cat[2].mice3num++;
              cat[0].store[0][i] = -1;
              cat[0].store[1][i] = -1;

              cat[0].mice2num = 0;
              cat[0].mice1num = 0;
              cat[0].mice3num = 0;
            }
          }
        }
        if (cat[0].xnow == cat[3].xnow && cat[0].ynow == cat[3].ynow) {
          if (cat[0].power != 0 && cat[3].power != 0) {
            if (cat[0].energy / cat[3].power > cat[3].energy / cat[0].power) {
              cat[0].energy -= cat[3].power * cat[3].energy / cat[0].power;
              cat[3].freeze = 0;
              cat[3].power = 1;
              cat[3].energy = 0;
              for (int i = 0; i < cat[3].number_hunt;
                   i++, cat[0].number_hunt++) {
                cat[0].store[0][cat[0].number_hunt] = cat[3].store[0][i];
                cat[0].store[1][cat[0].number_hunt] = cat[3].store[1][i];
                if (cat[3].store[0][i] == 1)
                  cat[0].mice1num++;
                else if (cat[3].store[0][i] == 2)
                  cat[0].mice2num++;
                else if (cat[3].store[0][i] == 3)
                  cat[0].mice3num++;
                cat[3].store[0][i] = -1;
                cat[3].store[1][i] = -1;

                cat[3].mice2num = 0;
                cat[3].mice1num = 0;
                cat[3].mice3num = 0;
              }
            } else
              cat[3].energy -= cat[0].power * cat[0].energy / cat[3].power;
            cat[0].freeze = 0;
            cat[0].power = 1;
            cat[0].energy = 0;
            for (int i = 0; i < cat[0].number_hunt; i++, cat[3].number_hunt++) {
              cat[3].store[0][cat[3].number_hunt] = cat[0].store[0][i];
              cat[3].store[1][cat[3].number_hunt] = cat[0].store[1][i];
              if (cat[0].store[0][i] == 1)
                cat[3].mice1num++;
              else if (cat[0].store[0][i] == 2)
                cat[3].mice2num++;
              else if (cat[0].store[0][i] == 3)
                cat[3].mice3num++;
              cat[0].store[0][i] = -1;
              cat[0].store[1][i] = -1;

              cat[0].mice2num = 0;
              cat[0].mice1num = 0;
              cat[0].mice3num = 0;
            }
          }
        }
        if (cat[2].xnow == cat[1].xnow && cat[2].ynow == cat[1].ynow) {
          if (cat[2].power != 0 && cat[1].power != 0) {
            if (cat[2].energy / cat[1].power > cat[1].energy / cat[2].power) {
              cat[2].energy -= cat[1].power * cat[1].energy / cat[2].power;
              cat[1].freeze = 0;
              cat[1].power = 1;
              cat[1].energy = 0;
              for (int i = 0; i < cat[1].number_hunt;
                   i++, cat[2].number_hunt++) {
                cat[2].store[0][cat[2].number_hunt] = cat[1].store[0][i];
                cat[2].store[1][cat[2].number_hunt] = cat[1].store[1][i];
                if (cat[1].store[0][i] == 1)
                  cat[2].mice1num++;
                else if (cat[1].store[0][i] == 2)
                  cat[2].mice2num++;
                else if (cat[1].store[0][i] == 3)
                  cat[2].mice3num++;
                cat[1].store[0][i] = -1;
                cat[1].store[1][i] = -1;

                cat[1].mice2num = 0;
                cat[1].mice1num = 0;
                cat[1].mice3num = 0;
              }
            } else
              cat[1].energy -= cat[2].power * cat[2].energy / cat[1].power;
            cat[2].freeze = 0;
            cat[2].power = 1;
            cat[2].energy = 0;
            for (int i = 0; i < cat[2].number_hunt; i++, cat[1].number_hunt++) {
              cat[1].store[0][cat[1].number_hunt] = cat[2].store[0][i];
              cat[1].store[1][cat[1].number_hunt] = cat[2].store[1][i];
              if (cat[2].store[0][i] == 1)
                cat[1].mice1num++;
              else if (cat[2].store[0][i] == 2)
                cat[1].mice2num++;
              else if (cat[2].store[0][i] == 3)
                cat[1].mice3num++;
              cat[2].store[0][i] = -1;
              cat[2].store[1][i] = -1;

              cat[2].mice2num = 0;
              cat[2].mice1num = 0;
              cat[2].mice3num = 0;
            }
          }
        }
        if (cat[3].xnow == cat[1].xnow && cat[3].ynow == cat[1].ynow) {
          if (cat[3].power != 0 && cat[1].power != 0) {
            if (cat[3].energy / cat[1].power > cat[1].energy / cat[3].power) {
              cat[3].energy -= cat[1].power * cat[1].energy / cat[3].power;
              cat[1].freeze = 0;
              cat[1].power = 1;
              cat[1].energy = 0;
              for (int i = 0; i < cat[1].number_hunt;
                   i++, cat[3].number_hunt++) {
                cat[3].store[0][cat[3].number_hunt] = cat[1].store[0][i];
                cat[3].store[1][cat[3].number_hunt] = cat[1].store[1][i];
                if (cat[1].store[0][i] == 1)
                  cat[3].mice1num++;
                else if (cat[1].store[0][i] == 2)
                  cat[3].mice2num++;
                else if (cat[1].store[0][i] == 3)
                  cat[3].mice3num++;
                cat[1].store[0][i] = -1;
                cat[1].store[1][i] = -1;

                cat[1].mice2num = 0;
                cat[1].mice1num = 0;
                cat[1].mice3num = 0;
              }
            } else
              cat[1].energy -= cat[3].power * cat[3].energy / cat[1].power;
            cat[3].freeze = 0;
            cat[3].power = 1;
            cat[3].energy = 0;
            for (int i = 0; i < cat[3].number_hunt; i++, cat[1].number_hunt++) {
              cat[0].store[0][cat[3].number_hunt] = cat[3].store[0][i];
              cat[0].store[1][cat[3].number_hunt] = cat[3].store[1][i];
              if (cat[3].store[0][i] == 1)
                cat[0].mice1num++;
              else if (cat[3].store[0][i] == 2)
                cat[0].mice2num++;
              else if (cat[3].store[0][i] == 3)
                cat[0].mice3num++;
              cat[3].store[0][i] = -1;
              cat[3].store[1][i] = -1;

              cat[3].mice2num = 0;
              cat[3].mice1num = 0;
              cat[3].mice3num = 0;
            }
          }
        }
        if (cat[3].xnow == cat[2].xnow && cat[3].ynow == cat[2].ynow) {
          if (cat[3].power != 0 && cat[2].power != 0) {
            if (cat[3].energy / cat[2].power > cat[2].energy / cat[3].power) {
              cat[3].energy -= cat[2].power * cat[2].energy / cat[3].power;
              cat[2].freeze = 0;
              cat[2].power = 1;
              cat[2].energy = 0;
              for (int i = 0; i < cat[3].number_hunt;
                   i++, cat[0].number_hunt++) {
                cat[3].store[0][cat[3].number_hunt] = cat[2].store[0][i];
                cat[3].store[1][cat[3].number_hunt] = cat[2].store[1][i];
                if (cat[3].store[0][i] == 1)
                  cat[2].mice1num++;
                else if (cat[3].store[0][i] == 2)
                  cat[2].mice2num++;
                else if (cat[3].store[0][i] == 3)
                  cat[2].mice3num++;
                cat[3].store[0][i] = -1;
                cat[3].store[1][i] = -1;

                cat[3].mice2num = 0;
                cat[3].mice1num = 0;
                cat[3].mice3num = 0;
              }
            } else
              cat[2].energy -= cat[3].power * cat[3].energy / cat[2].power;
            cat[3].freeze = 0;
            cat[3].power = 1;
            cat[3].energy = 0;
            for (int i = 0; i < cat[3].number_hunt; i++, cat[0].number_hunt++) {
              cat[2].store[0][cat[2].number_hunt] = cat[3].store[0][i];
              cat[2].store[1][cat[2].number_hunt] = cat[3].store[1][i];
              if (cat[2].store[0][i] == 1)
                cat[3].mice1num++;
              else if (cat[3].store[0][i] == 2)
                cat[2].mice2num++;
              else if (cat[3].store[0][i] == 3)
                cat[2].mice3num++;
              cat[3].store[0][i] = -1;
              cat[3].store[1][i] = -1;

              cat[2].mice2num = 0;
              cat[2].mice1num = 0;
              cat[2].mice3num = 0;
            }
          }
        }

        answer = search_chocolates(cat[turn].xnow, cat[turn].ynow, chocolates);
        if (answer >= 0) {
          chocolates[answer].avilable = 0;
          cat[turn].power += 2;
        }
        answer = search_fishes(cat[turn].xnow, cat[turn].ynow, fishes);

        if (answer >= 0) {
          hiddenFish--;
          fishes[answer].avilable = 0;
          cat[turn].energy += 2;
        }

        answer = search_tales(cat[turn].xnow, cat[turn].ynow, tales);
        if (answer >= 0 && cat[turn].freeze && cat[turn].future_freeze &&
            !cat[turn].freezenum) {
          tales[answer].avilable = 1;
          cat[turn].freeze = 0;
          cat[turn].freezenum++;
          if (cat[turn].mice1num != 0) {
            cat[turn].mice1num--;
          } else if (cat[turn].mice2num != 0) {
            cat[turn].mice2num--;
          } else if (cat[turn].mice3num != 0) {
            cat[turn].mice3num--;
          } else if (cat[turn].power >= 3) {
            cat[turn].power -= 2;
          } else if (cat[turn].energy > 3) {
            cat[turn].power -= 3;
          } else
            cat[turn].power = 0;
        }
      }
      cat1points =
          cat[0].mice1num * 3 + cat[0].mice2num * 2 + cat[0].mice3num * 1;
      cat2points =
          cat[1].mice1num * 3 + cat[1].mice2num * 2 + cat[1].mice3num * 1;
      cat3points =
          cat[2].mice1num * 3 + cat[2].mice2num * 2 + cat[2].mice3num * 1;
      cat4points =
          cat[3].mice1num * 3 + cat[3].mice2num * 2 + cat[3].mice3num * 1;
      if (NUMperson == 0 && first_move) function_move_dog = true;
      if (NUMperson == 3) first_move = 1;
      if (redraw && al_is_event_queue_empty(event_queue)) {
        redraw = false;

        al_clear_to_color(al_map_rgb(255, 255, 255));
        al_draw_text(font, al_map_rgb(0, 0, 0), 1000, 60, ALLEGRO_ALIGN_CENTRE,
                     "Score Board");
        al_draw_filled_rectangle(0, 0, 750, 750, al_map_rgb(277, 178, 102));
        for (int i = 0; i < 15; i++) {
          for (int j = 0; j < 15; j++) {
            al_draw_rectangle(i * 50, j * 50, (i + 1) * 50, (j + 1) * 50,
                              al_map_rgb(0, 0, 0), 2);
          }
        }

        al_draw_bitmap(houseImage, centerX, centerY, 0);
        drawMice1(mouse1Image, mice1, NUM_MICE1);
        drawMice2(mouse2Image, mice2, NUM_MICE2);
        drawMice3(mouse3Image, mice3, NUM_MICE3);
        drawChocolates(chocolateImage, chocolates, NUM_CHOCOLATES);
        drawFishs(fishImage, fishes, NUM_FISH);
        drawTales(taleImage, tales, NUM_TALE);
        if (cat[0].freeze)
          al_draw_bitmap(cat1Image, (cat[0].xnow * CELL_SIZE) - 25,
                         (cat[0].ynow * CELL_SIZE) - 20, 0);
        else
          al_draw_bitmap(ice_cat1Image, (cat[0].xnow * CELL_SIZE) - 25,
                         (cat[0].ynow * CELL_SIZE) - 20, 0);

        if (cat[1].freeze)
          al_draw_bitmap(cat2Image, (cat[1].xnow * CELL_SIZE) - 25,
                         (cat[1].ynow * CELL_SIZE) - 20, 0);
        else
          al_draw_bitmap(ice_cat2Image, (cat[1].xnow * CELL_SIZE) - 25,
                         (cat[1].ynow * CELL_SIZE) - 20, 0);

        if (cat[2].freeze)
          al_draw_bitmap(cat3Image, (cat[2].xnow * CELL_SIZE) - 25,
                         (cat[2].ynow * CELL_SIZE) - 20, 0);
        else
          al_draw_bitmap(ice_cat3Image, (cat[2].xnow * CELL_SIZE) - 25,
                         (cat[2].ynow * CELL_SIZE) - 20, 0);

        if (cat[3].freeze)
          al_draw_bitmap(cat4Image, (cat[3].xnow * CELL_SIZE) - 25,
                         (cat[3].ynow * CELL_SIZE) - 20, 0);
        else
          al_draw_bitmap(ice_cat4Image, (cat[3].xnow * CELL_SIZE) - 25,
                         (cat[3].ynow * CELL_SIZE) - 20, 0);

        if (dog[0].avilable)
          al_draw_bitmap(dog1Image, (dog[0].x * CELL_SIZE) - 25,
                         (dog[0].y * CELL_SIZE) - 10, 0);
        if (dog[1].avilable)
          al_draw_bitmap(dog2Image, (dog[1].x * CELL_SIZE) - 25,
                         (dog[1].y * CELL_SIZE) - 10, 0);
        if (dog[2].avilable)
          al_draw_bitmap(dog3Image, (dog[2].x * CELL_SIZE) - 25,
                         (dog[2].y * CELL_SIZE) - 10, 0);
        if (dog[3].avilable)
          al_draw_bitmap(dog4Image, (dog[3].x * CELL_SIZE) - 25,
                         (dog[3].y * CELL_SIZE) - 10, 0);
        al_draw_bitmap(brickImage, 100, 145, 0);
        al_draw_bitmap(brickImage, 100, 145, 0);
        al_draw_bitmap(brickImage, 150, 145, 0);
        al_draw_bitmap(brickImage, 200, 145, 0);
        al_draw_bitmap(brickImage, 600, 295, 0);
        al_draw_bitmap(brickImage, 550, 295, 0);
        al_draw_bitmap(brickImage, 600, 495, 0);
        al_draw_bitmap(brickImage, 450, 545, 0);
        al_draw_bitmap(brickImage, 100, 445, 0);
        al_draw_bitmap(brickImage, 200, 595, 0);
        al_draw_bitmap(brickImage, 250, 595, 0);
        al_draw_bitmap(brick1Image, 242, 100, 0);
        al_draw_bitmap(brick1Image, 92, 650, 0);
        al_draw_bitmap(brick1Image, 242, 250, 0);
        al_draw_bitmap(brick1Image, 242, 300, 0);
        al_draw_bitmap(brick1Image, 492, 50, 0);
        al_draw_bitmap(brick1Image, 492, 100, 0);
        al_draw_bitmap(brick1Image, 642, 450, 0);
        al_draw_bitmap(brick1Image, 642, 400, 0);
        al_draw_filled_rectangle(801, 51, 1198, 348, al_map_rgb(200, 200, 200));
        al_draw_rectangle(800, 50, 1200, 350, al_map_rgb(0, 0, 0), 3);
        al_draw_text(font, al_map_rgb(0, 0, 0), 1000, 60, ALLEGRO_ALIGN_CENTRE,
                     "Score Board");
        al_draw_text(font, al_map_rgb(0, 0, 0), 825, 110, ALLEGRO_ALIGN_CENTRE,
                     "P");
        al_draw_text(font, al_map_rgb(0, 0, 0), 875, 110, ALLEGRO_ALIGN_CENTRE,
                     "T");
        al_draw_text(font, al_map_rgb(0, 0, 0), 1175, 110, ALLEGRO_ALIGN_CENTRE,
                     "F");
        al_draw_textf(font, al_map_rgb(0, 0, 0), 1073, 160,
                      ALLEGRO_ALIGN_CENTRE, "%d", cat[0].power);
        al_draw_textf(font, al_map_rgb(0, 0, 0), 1073, 210,
                      ALLEGRO_ALIGN_CENTRE, "%d", cat[1].power);
        al_draw_textf(font, al_map_rgb(0, 0, 0), 1073, 260,
                      ALLEGRO_ALIGN_CENTRE, "%d", cat[2].power);
        al_draw_textf(font, al_map_rgb(0, 0, 0), 1073, 310,
                      ALLEGRO_ALIGN_CENTRE, "%d", cat[3].power);
        al_draw_textf(font, al_map_rgb(0, 0, 0), 1123, 160,
                      ALLEGRO_ALIGN_CENTRE, "%d", cat[0].energy);
        al_draw_textf(font, al_map_rgb(0, 0, 0), 1123, 210,
                      ALLEGRO_ALIGN_CENTRE, "%d", cat[1].energy);
        al_draw_textf(font, al_map_rgb(0, 0, 0), 1123, 260,
                      ALLEGRO_ALIGN_CENTRE, "%d", cat[2].energy);
        al_draw_textf(font, al_map_rgb(0, 0, 0), 1123, 310,
                      ALLEGRO_ALIGN_CENTRE, "%d", cat[3].energy);
        al_draw_textf(font, al_map_rgb(0, 0, 0), 923, 160, ALLEGRO_ALIGN_CENTRE,
                      "%d", cat[0].mice1num);
        al_draw_textf(font, al_map_rgb(0, 0, 0), 973, 160, ALLEGRO_ALIGN_CENTRE,
                      "%d", cat[0].mice2num);
        al_draw_textf(font, al_map_rgb(0, 0, 0), 1023, 160,
                      ALLEGRO_ALIGN_CENTRE, "%d", cat[0].mice3num);
        al_draw_textf(font, al_map_rgb(0, 0, 0), 1173, 160,
                      ALLEGRO_ALIGN_CENTRE, "%d", cat1points);
        al_draw_textf(font, al_map_rgb(0, 0, 0), 923, 210, ALLEGRO_ALIGN_CENTRE,
                      "%d", cat[1].mice1num);
        al_draw_textf(font, al_map_rgb(0, 0, 0), 973, 210, ALLEGRO_ALIGN_CENTRE,
                      "%d", cat[1].mice2num);
        al_draw_textf(font, al_map_rgb(0, 0, 0), 1023, 210,
                      ALLEGRO_ALIGN_CENTRE, "%d", cat[1].mice3num);
        al_draw_textf(font, al_map_rgb(0, 0, 0), 1173, 210,
                      ALLEGRO_ALIGN_CENTRE, "%d", cat2points);
        al_draw_textf(font, al_map_rgb(0, 0, 0), 923, 260, ALLEGRO_ALIGN_CENTRE,
                      "%d", cat[2].mice1num);
        al_draw_textf(font, al_map_rgb(0, 0, 0), 973, 260, ALLEGRO_ALIGN_CENTRE,
                      "%d", cat[2].mice2num);
        al_draw_textf(font, al_map_rgb(0, 0, 0), 1023, 260,
                      ALLEGRO_ALIGN_CENTRE, "%d", cat[2].mice3num);
        al_draw_textf(font, al_map_rgb(0, 0, 0), 1173, 260,
                      ALLEGRO_ALIGN_CENTRE, "%d", cat3points);
        al_draw_textf(font, al_map_rgb(0, 0, 0), 923, 310, ALLEGRO_ALIGN_CENTRE,
                      "%d", cat[3].mice1num);
        al_draw_textf(font, al_map_rgb(0, 0, 0), 973, 310, ALLEGRO_ALIGN_CENTRE,
                      "%d", cat[3].mice2num);
        al_draw_textf(font, al_map_rgb(0, 0, 0), 1023, 310,
                      ALLEGRO_ALIGN_CENTRE, "%d", cat[3].mice3num);
        al_draw_textf(font, al_map_rgb(0, 0, 0), 1173, 310,
                      ALLEGRO_ALIGN_CENTRE, "%d", cat4points);
        al_draw_text(font, al_map_rgb(0, 0, 0), 1000, 400, ALLEGRO_ALIGN_CENTRE,
                     "number of the Round:");
        al_draw_textf(font, al_map_rgb(0, 0, 0), 1130, 400,
                      ALLEGRO_ALIGN_CENTRE, "%d", gameRound);
        al_draw_line(800, 100, 1200, 100, al_map_rgb(0, 0, 0), 3);
        al_draw_line(800, 150, 1200, 150, al_map_rgb(0, 0, 0), 3);
        al_draw_line(800, 200, 1200, 200, al_map_rgb(0, 0, 0), 3);
        al_draw_line(800, 250, 1200, 250, al_map_rgb(0, 0, 0), 3);
        al_draw_line(800, 300, 1200, 300, al_map_rgb(0, 0, 0), 3);
        al_draw_line(850, 100, 850, 350, al_map_rgb(0, 0, 0), 3);
        al_draw_line(900, 100, 900, 350, al_map_rgb(0, 0, 0), 3);
        al_draw_line(950, 100, 950, 350, al_map_rgb(0, 0, 0), 3);
        al_draw_line(1000, 100, 1000, 350, al_map_rgb(0, 0, 0), 3);
        al_draw_line(1050, 100, 1050, 350, al_map_rgb(0, 0, 0), 3);
        al_draw_line(1100, 100, 1100, 350, al_map_rgb(0, 0, 0), 3);
        al_draw_line(1150, 100, 1150, 350, al_map_rgb(0, 0, 0), 3);
        if (cat[0].freeze)
          al_draw_bitmap(cat1Image, 775, 130, 0);
        else
          al_draw_bitmap(ice_cat1Image, 775, 130, 0);

        if (cat[1].freeze)
          al_draw_bitmap(cat2Image, 775, 180, 0);
        else
          al_draw_bitmap(ice_cat2Image, 775, 180, 0);
        if (cat[2].freeze)
          al_draw_bitmap(cat3Image, 775, 230, 0);
        else
          al_draw_bitmap(ice_cat3Image, 775, 230, 0);
        if (cat[3].freeze)
          al_draw_bitmap(cat4Image, 775, 280, 0);
        else
          al_draw_bitmap(ice_cat4Image, 775, 280, 0);
        al_draw_bitmap(mouse1Image, 900, 100, 0);
        al_draw_bitmap(mouse2Image, 950, 100, 0);
        al_draw_bitmap(mouse3Image, 1000, 100, 0);
        al_draw_bitmap(chocolateImage, 1040, 100, 0);
        al_draw_bitmap(fishImage, 1080, 90, 0);
        if (t_c1_cpy == 1) {
          al_draw_bitmap(t1Image, 850, 145, 0);
        } else if (t_c1_cpy == 2) {
          al_draw_bitmap(t2Image, 850, 145, 0);
        } else if (t_c1_cpy == 3) {
          al_draw_bitmap(t3Image, 850, 145, 0);
        } else if (t_c1_cpy == 4) {
          al_draw_bitmap(t4Image, 850, 145, 0);
        } else if (t_c1_cpy == 5) {
          al_draw_bitmap(t5Image, 850, 145, 0);
        } else {
          al_draw_bitmap(t6Image, 850, 145, 0);
        }
        if (t_c2_cpy == 1) {
          al_draw_bitmap(t1Image, 850, 195, 0);
        } else if (t_c2_cpy == 2) {
          al_draw_bitmap(t2Image, 850, 195, 0);
        } else if (t_c2_cpy == 3) {
          al_draw_bitmap(t3Image, 850, 195, 0);
        } else if (t_c2_cpy == 4) {
          al_draw_bitmap(t4Image, 850, 195, 0);
        } else if (t_c2_cpy == 5) {
          al_draw_bitmap(t5Image, 850, 195, 0);
        } else {
          al_draw_bitmap(t6Image, 850, 195, 0);
        }
        if (t_c3_cpy == 1) {
          al_draw_bitmap(t1Image, 850, 245, 0);
        } else if (t_c3_cpy == 2) {
          al_draw_bitmap(t2Image, 850, 245, 0);
        } else if (t_c3_cpy == 3) {
          al_draw_bitmap(t3Image, 850, 245, 0);
        } else if (t_c3_cpy == 4) {
          al_draw_bitmap(t4Image, 850, 245, 0);
        } else if (t_c3_cpy == 5) {
          al_draw_bitmap(t5Image, 850, 245, 0);
        } else {
          al_draw_bitmap(t6Image, 850, 245, 0);
        }
        if (t_c4_cpy == 1) {
          al_draw_bitmap(t1Image, 850, 295, 0);
        } else if (t_c4_cpy == 2) {
          al_draw_bitmap(t2Image, 850, 295, 0);
        } else if (t_c4_cpy == 3) {
          al_draw_bitmap(t3Image, 850, 295, 0);
        } else if (t_c4_cpy == 4) {
          al_draw_bitmap(t4Image, 850, 295, 0);
        } else if (t_c4_cpy == 5) {
          al_draw_bitmap(t5Image, 850, 295, 0);
        } else {
          al_draw_bitmap(t6Image, 850, 295, 0);
        }
        if (turn == 0)
          al_draw_filled_circle(775, 170, 10, al_map_rgb(0, 255, 0));
        if (turn == 1)
          al_draw_filled_circle(775, 220, 10, al_map_rgb(0, 255, 0));
        if (turn == 2)
          al_draw_filled_circle(775, 270, 10, al_map_rgb(0, 255, 0));
        if (turn == 3)
          al_draw_filled_circle(775, 320, 10, al_map_rgb(0, 255, 0));
        al_flip_display();
      }
    }
  }
  al_clear_to_color(al_map_rgb(255, 255, 255));
  if (cat1points > cat2points && cat1points > cat3points &&
      cat1points > cat4points) {
    al_draw_bitmap(cat1Image, 575, 275, 0);
    al_draw_text(font, al_map_rgb(0, 0, 0), 625, 375, ALLEGRO_ALIGN_CENTRE,
                 "winner!");
  };
  if (cat2points > cat1points && cat2points > cat3points &&
      cat2points > cat4points) {
    al_draw_bitmap(cat2Image, 575, 275, 0);
    al_draw_text(font, al_map_rgb(0, 0, 0), 625, 375, ALLEGRO_ALIGN_CENTRE,
                 "winner!");
  };
  if (cat3points > cat1points && cat3points > cat2points &&
      cat3points > cat4points) {
    al_draw_bitmap(cat3Image, 575, 275, 0);
    al_draw_text(font, al_map_rgb(0, 0, 0), 625, 375, ALLEGRO_ALIGN_CENTRE,
                 "winner!");
  };
  if (cat4points > cat1points && cat4points > cat2points &&
      cat4points > cat3points) {
    al_draw_bitmap(cat4Image, 575, 275, 0);
    al_draw_text(font, al_map_rgb(0, 0, 0), 625, 375, ALLEGRO_ALIGN_CENTRE,
                 "winner!");
  };
  al_flip_display();
  al_rest(3);
  al_destroy_bitmap(houseImage);
  al_destroy_bitmap(mouse1Image);
  al_destroy_bitmap(mouse2Image);
  al_destroy_bitmap(mouse3Image);
  al_destroy_bitmap(dog1Image);
  al_destroy_bitmap(dog2Image);
  al_destroy_bitmap(dog3Image);
  al_destroy_bitmap(dog4Image);
  al_destroy_bitmap(cat1Image);
  al_destroy_bitmap(cat2Image);
  al_destroy_bitmap(cat3Image);
  al_destroy_bitmap(cat4Image);
  al_destroy_display(display);
  al_destroy_event_queue(queue);
  al_destroy_font(font);

  return 0;
}
