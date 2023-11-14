#include <stdio.h>

#include <termswipe.h>

int main() {
    while (1) {
        enum TERMSWIPE out = termswipe();
        printf("%d %c %c %c %c\n", out,
            out & TERMSWIPE_L ? 'L' : '-',
            out & TERMSWIPE_R ? 'R' : '-',
            out & TERMSWIPE_U ? 'U' : '-',
            out & TERMSWIPE_D ? 'D' : '-'
        );
    }
}