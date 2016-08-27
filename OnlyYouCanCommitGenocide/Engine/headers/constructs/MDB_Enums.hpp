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

//Space of 0x73XX is for different animation situations and actions
#define MDB_E_STATIC          0x7301
#define MDB_E_FLY_LEFT        0x7302
#define MDB_E_FLY_RIGHT       0x7303
#define MDB_E_FLY_UP          0x7304
#define MDB_E_FLY_DOWN        0x7305
#define MDB_E_FLY_UP_RIGHT    0x7306
#define MDB_E_FLY_UP_LEFT     0x7307
#define MDB_E_FLY_DOWN_RIGHT  0x7308
#define MDB_E_FLY_DOWN_LEFT   0x7309
#define MDB_E_SHOT_CHARGE     0x730A
#define MDB_E_SHOT_FIRED      0x730B
#define MDB_E_ROLL_RIGHT      0x730C
#define MDB_E_ROLL_LEFT       0x730D

//Space of 0x74XX is for different file types
#define MDB_E_FILE_IMAGE     0x7401
#define MDB_E_FILE_ANIMATION 0x7402
#define MDB_E_FILE_ACTOR     0x7403

//Space of 0x75XX is for key presses
#define MDB_E_MOUSE_1   0x7501
#define MDB_E_MOUSE_2   0x7502
#define MDB_E_KEY_SPACE 0x7503
#define MDB_E_KEY_W     0x7504
#define MDB_E_KEY_A     0x7505
#define MDB_E_KEY_S     0x7506
#define MDB_E_KEY_D     0x7507
#define MDB_E_KEY_UP    0x7508
#define MDB_E_KEY_LEFT  0x7509
#define MDB_E_KEY_DOWN  0x750A
#define MDB_E_KEY_RIGHT 0x750B
#define MDB_E_KEY_ESC   0x750C
#define MDB_E_KEY_Q     0x750D
#define MDB_E_KEY_E     0x750E

//Space of 0x76XX is for button states (which may be overkill, but meh)
#define MDB_E_BUTTON_PRESSED  0x7601
#define MDB_E_BUTTON_HELD     0x7602
#define MDB_E_BUTTON_RELEASED 0x7603

#endif