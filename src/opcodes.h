#define OP_HALT 0x0F
#define OP_NOOP 0xEA


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
#define OP_LOADA_IMM 0xA9
#define OP_LOADA_ZPG 0xA5
#define OP_LOADA_ZPX 0xB5
#define OP_LOADA_ABS 0xAD
#define OP_LOADA_ABX 0xBD
#define OP_LOADA_ABY 0xB9

#define OP_STORA_ZPG 0x85
#define OP_STORA_ZPX 0x95
#define OP_STORA_ABS 0x8D
#define OP_STORA_ABX 0x9D
#define OP_STORA_ABY 0x99


// ------- X register -------
#define OP_LOADX_IMM 0xA2
#define OP_LOADX_ZPG 0xA6
#define OP_LOADX_ZPY 0xB6
#define OP_LOADX_ABS 0xAE
#define OP_LOADX_ABY 0xBE

#define OP_STORX_ZPG 0x86
#define OP_STORX_ZPY 0x96
#define OP_STORX_ABS 0x8E

// ------- Y register -------
#define OP_LOADY_IMM 0xA0
#define OP_LOADY_ZPG 0xA4
#define OP_LOADY_ZPX 0xB4
#define OP_LOADY_ABS 0xAC
#define OP_LOADY_ABX 0xBC

#define OP_STORY_ZPG 0x84
#define OP_STORY_ZPX 0x94
#define OP_STORY_ABS 0x8C


// ------- Transfers -------
#define OP_TRANS_ATX 0xAA
#define OP_TRANS_ATY 0xA8
#define OP_TRANS_XTA 0x8A
#define OP_TRANS_YTA 0x98
#define OP_TRANS_STX 0xBA
#define OP_TRANS_XTS 0x9A

// ---- Stack Operations ----
#define OP_PUSHA_STK 0x48
#define OP_PUSHP_STK 0x08
#define OP_PULLA_STK 0x68
#define OP_PULLP_STK 0x28

// -------- Logical --------
#define OP_AND_IMM 0x29
#define OP_AND_ZPG 0x25
#define OP_AND_ZPX 0x35
#define OP_AND_ABS 0x2D
#define OP_AND_ABX 0x3D
#define OP_AND_ABY 0x39

#define OP_XOR_IMM 0x49
#define OP_XOR_ZPG 0x45
#define OP_XOR_ZPX 0x55
#define OP_XOR_ABS 0x4D
#define OP_XOR_ABX 0x5D
#define OP_XOR_ABY 0x59

#define OP_ORA_IMM 0x09
#define OP_ORA_ZPG 0x05
#define OP_ORA_ZPX 0x15
#define OP_ORA_ABS 0x0D
#define OP_ORA_ABX 0x1D
#define OP_ORA_ABY 0x19

#define OP_TST_ZPG 0x24
#define OP_TST_ABS 0x2C
