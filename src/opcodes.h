const int OP_HALT = 0x0F;
const int OP_NOOP = 0xEA;


// ..._IMM => Immediate
// ..._ZPG => Zero Page
// ..._ZPX => Zero Page, X
// ..._ABS => Absolute
// ..._ABX => Absolute,  X
// ..._ABY => Absolute,  Y
// ..._ATX => Accumulator to X
// ..._ATY => Accumulator to Y
// ..._XTA => X to accumulator
// ..._YTA => Y to accumulator
// ..._STX => Stack pointer to X
// ..._XTS => X to stack pointer
// ..._STK => (to/from) Stack

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


// ------- Transfers -------
const int OP_TRANS_ATX = 0xAA;
const int OP_TRANS_ATY = 0xA8;
const int OP_TRANS_XTA = 0x8A;
const int OP_TRANS_YTA = 0x98;
const int OP_TRANS_STX = 0xBA;
const int OP_TRANS_XTS = 0x9A;

// ---- Stack Operations ----
const int OP_PUSHA_STK = 0x48;
const int OP_PUSHP_STK = 0x08;
const int OP_PULLA_STK = 0x68;
const int OP_PULLP_STK = 0x28;

// -------- Logical --------
const int OP_AND_IMM = 0x29;
const int OP_AND_ZPG = 0x25;
const int OP_AND_ZPX = 0x35;
const int OP_AND_ABS = 0x2D;
const int OP_AND_ABX = 0x3D;
const int OP_AND_ABY = 0x39;

const int OP_XOR_IMM = 0x49;
const int OP_XOR_ZPG = 0x45;
const int OP_XOR_ZPX = 0x55;
const int OP_XOR_ABS = 0x4D;
const int OP_XOR_ABX = 0x5D;
const int OP_XOR_ABY = 0x59;

const int OP_ORA_IMM = 0x09;
const int OP_ORA_ZPG = 0x05;
const int OP_ORA_ZPX = 0x15;
const int OP_ORA_ABS = 0x0D;
const int OP_ORA_ABX = 0x1D;
const int OP_ORA_ABY = 0x19;


const int OP_TST_ZPG = 0x24;
const int OP_TST_ABS = 0x2C;
