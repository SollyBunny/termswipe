enum TERMSWIPE_ACTION {
    TERMSWIPE_NONE = 0,
    TERMSWIPE_U = 1 << 0,
    TERMSWIPE_D = 1 << 1,
    TERMSWIPE_L = 1 << 2,
    TERMSWIPE_R = 1 << 3,
    TERMSWIPE_UL = TERMSWIPE_U | TERMSWIPE_L,
    TERMSWIPE_UR = TERMSWIPE_U | TERMSWIPE_R,
    TERMSWIPE_DL = TERMSWIPE_D | TERMSWIPE_L,
    TERMSWIPE_DR = TERMSWIPE_D | TERMSWIPE_R,
};

#define TERMSWIPE_GET_ACTION(n) ((enum TERMSWIPE_ACTION)(n & (1 << 8)))
#define TERMSWIPE_GET_X(n) ((unsigned char)((n & (0xFF << 8)) >> 8))
#define TERMSWIPE_GET_Y(n) ((unsigned char)((n & (0xFF << 16)) >> 16))

int termswipe_print(int n);
int termswipe();