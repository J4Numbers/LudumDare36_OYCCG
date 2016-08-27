#ifndef MDB_ENUMS_H
#define MDB_ENUMS_H

//Space of 0x71XX is for different room types

#define MDB_E_ROOM  0x7101
#define MDB_E_LEVEL 0x7102

//Space of 0x72XX is for different enemy types
#define MDB_E_PLAYER   0x7201
#define MDB_E_BASIC    0x7202
#define MDB_E_MINIBOSS 0x7203
#define MDB_E_BOSS     0x7204

//Space of 0x73XX is for different animation situations
#define MDB_E_STATIC          0x7301
#define MDB_E_FLY_LEFT        0x7302
#define MDB_E_FLY_RIGHT       0x7303
#define MDB_E_FLY_UP          0x7304
#define MDB_E_FLY_DOWN        0x7305
#define MDB_E_FLY_UP_RIGHT    0x7306
#define MDB_E_FLY_UP_LEFT     0x7307
#define MDB_E_FLY_DOWN_RIGHT  0x7308
#define MDB_E_FLY_DOWN_LEFT   0x7309
#define MDB_E_FLY_CHARGE_SHOT 0x730A
#define MDB_E_FLY_SHOT_FIRED  0x730B

#endif