#define REG(x) (*((volatile CYG_BYTE *)(x)))
#define REG_READ(x, bit) ((REG(x) & (1 << (bit))) != 0)
#define REG_WRITE(x, bit, state) REG(x) = state ? (REG(x) | (1 << (bit))) : (REG(x) & ~(1 << (bit)))
