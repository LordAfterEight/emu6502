const int OP_HALT = 0x0F;
const int OP_NOOP = 0xEA;


// ..._IMM => Immediate
// ..._ZPG => Zero Page
// ..._ZPX => Zero Page, X
// ..._ABS => Absolute
// ..._ABX => Absolute,  X
// ..._ABY => Absolute,  Y

// ------- A register -------
const int OP_LOADA_IMM = 0xA9;
const int OP_LOADA_ZPG = 0xA5;
const int OP_LOADA_ZPX = 0xB5;
const int OP_LOADA_ABS = 0xAD;
const int OP_LOADA_ABX = 0xBD;
const int OP_LOADA_ABY = 0xB9;

const int OP_STORA_ZPG = 0x85;
const int OP_STORA_ZPX = 0x95;
const int OP_STORA_ABS = 0x8D;
const int OP_STORA_ABX = 0x9D;
const int OP_STORA_ABY = 0x99;


// ------- X register -------
const int OP_LOADX_IMM = 0xA2;
const int OP_LOADX_ZPG = 0xA6;
const int OP_LOADX_ZPX = 0xB6;
const int OP_LOADX_ABS = 0xAE;
const int OP_LOADX_ABY = 0xBE;

const int OP_STORX_ZPG = 0x86;
const int OP_STORX_ZPY = 0x96;
const int OP_STORX_ABS = 0x8E;

// ------- Y register -------
const int OP_LOADY_IMM = 0xA0;
const int OP_LOADY_ZPG = 0xA4;
const int OP_LOADY_ZPX = 0xB4;
const int OP_LOADY_ABS = 0xAC;
const int OP_LOADY_ABX = 0xBC;

const int OP_STORY_ZPG = 0x84;
const int OP_STORY_ZPX = 0x94;
const int OP_STORY_ABS = 0x8C;