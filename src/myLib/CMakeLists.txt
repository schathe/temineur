# Ajout de la bibliothèque myLib
add_library(myLib
    Game.cpp
    Tile.cpp
    Map.cpp
)

# Inclure les headers
target_include_directories(myLib PUBLIC ../myLibHeaders)
