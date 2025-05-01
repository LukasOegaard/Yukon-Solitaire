Yukon Solitaire - Projektbeskrivelse

Programmet implementerer en tekstbaseret version af Yukon Solitaire i C.

 - Kommandoer:
LD <filnavn>     - Load et kortdæk fra fil
SW               - Vis deck
SR               - Random shuffle
SI <split>       - Interleave shuffle
SD <filnavn>     - Gem deck til fil
P                - Deal kort ud i 7 kolonner
C3:7H->C5        - Flyt kort fra kolonne 3 til 5
C2:AH->F1        - Flyt kort til foundation
Q                - Afslut spil
QQ               - Luk programmet

Eksempel:
LD cards.txt
SR
P
C6:9D->C5
C4:AH->F1
Q
QQ

Udviklet i CLion / CMake på Windows.
