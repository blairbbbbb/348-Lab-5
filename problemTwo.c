#include <stdio.h>

void findCombinations(int score) {
    printf("Possible combinations of scoring plays for score %d:\n", score);

    //Scoring plays
    int td = 6; //Touchdown
    int td1 = 7; //Touchdown + 1-point conversion
    int td2 = 8; //Touchdown + 2-point conversion
    int fg = 3; //Field goal
    int safety = 2; //Safety

    //Try every combination of scoring play
    for (int a = 0; a * td2 <= score; a++) {
        for (int b = 0; b * td1 + a * td2 <= score; b++) {
            for (int c = 0; c * td + b * td1 + a * td2 <= score; c++) {
                for (int d = 0; d * fg + c * td + b * td1 + a * td2 <= score; d++) {
                    for (int e = 0; e * safety + d * fg + c * td + b * td1 + a * td2 <= score; e++) {
                        if (e * safety + d * fg + c * td + b * td1 + a * td2 == score) {
                            printf("%d TD + 2pt, %d TD + 1pt, %d TD, %d FG, %d Safety\n",
                                   a, b, c, d, e);
                        }
                    }
                }
            }
        }
    }
}

int main() {
    int score;
    printf("Enter 0 or 1 to STOP\n");

    while (1) {
        printf("Enter the NFL score: ");
        scanf("%d", &score);
        if (score == 0 || score == 1) break;

        findCombinations(score);
    }
    return 0;
}
