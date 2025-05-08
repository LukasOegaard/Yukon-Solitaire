cmake_minimum_required(VERSION 3.16)
project(Yukon_Solitaire C)

set(CMAKE_C_STANDARD 11)

add_executable(yukon
        card.c
        deck.c
        game.c
        main.c
)
