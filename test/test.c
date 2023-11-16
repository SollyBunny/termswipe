#include <stdio.h>

#include <termswipe.h>

int main() {
    while (1) {
        int out = termswipe();
        termswipe_print(out);
    }
}