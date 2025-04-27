cmake_minimum_required(VERSION 3.16)
project(Yukon_Solitaire C)

set(CMAKE_C_STANDARD 11)

add_executable(yukon
        main.c
        card.c
        deck.c
        game.c
)
