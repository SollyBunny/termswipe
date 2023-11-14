#include <termswipe.h>

#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


enum TERMSWIPE termswipe() {
    static enum TERMSWIPE out;
    out = TERMSWIPE_NONE;
    // Termios init
        static struct termios old;
        static struct termios new;
        tcgetattr(STDIN_FILENO, &old);
        tcgetattr(STDIN_FILENO, &new);
        new.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &new);
        printf("\x1b[?1003h\x1b[?1015h\x1b[?1006h");
        fflush(stdout);
    // Read input
        static char buf[16];
        static char *bufp;
        static int size;
        static int x1, y1, x2, y2;
        x1 = -1;
        while (1) {
            memset(buf, 0, sizeof(buf));
            bufp = buf;
            size = read(STDIN_FILENO, buf, sizeof(buf) / sizeof(buf[0]));
            if (size == 0) goto l_fail;
            if (*bufp++ != '\x1b') goto l_fail;
            if (*bufp++ != '[') goto l_fail;
            if (*bufp++ != '<') goto l_fail;
            static unsigned int m, x, y;
            static char p;
            sscanf(bufp, "%u;%u;%u%c", &m, &x, &y, &p);
            if (m == 0) {
                if (p == 'm') {
                    x2 = x;
                    y2 = y;
                    break;
                } else {
                    x1 = x;
                    y1 = y;
                }
            }
        }
        if (abs(x1 - x2) > 3)
            out |= x1 > x2 ? TERMSWIPE_L : TERMSWIPE_R;
        if (abs(y1 - y2) > 3)
            out |= y1 > y2 ? TERMSWIPE_U : TERMSWIPE_D;
        goto l_end;
    l_fail: {
        fputs(buf, stdin);
        goto l_end;
    }
    l_end: {
        printf("\x1b[?1003l\x1b[?1015l\x1b[?1006l");
        fflush(stdout);
        tcsetattr(STDIN_FILENO, TCSANOW, &old);
        return out;
    }
}