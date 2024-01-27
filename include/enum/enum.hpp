/*
** EPITECH PROJECT, 2024
** GlobalGameJam-2024
** File description:
** enum
*/

#pragma once

typedef enum {
    FAT_PIGEON,
    SMALL_PIGEON,
    THIN_PIGEON,
    MUSCULAR_PIGEON
} PigeonType;

typedef enum {
    PLAYER1,
    PLAYER2
} PlayerType;

typedef enum {
    MENU,
    GAME,
    END
} SceneType;

typedef enum {
    VOLCANO,
    JUNGLE,
    SNOW,
    SKY
} MapType;

typedef enum {
    NOJUMP,
    FIRSTJUMP,
    CANDJUMP,
    DOUBLEJUMP,
    NONE
} JumpType;


typedef enum {
    IDLER,
    IDLEL,
    WALKR,
    WALKL,
    SPECIALR,
    SPECIALL,
    ATTACKR,
    ATTACKL,
    MAXANIMP,
} PlayerAnimation;
