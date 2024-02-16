#ifndef GENERO_H
#define GENERO_H
#include <string>
enum class Genero {
    POP,
    ROCK,
    RAP,
    DANCE,
    REGGAE,
    ELECTRONICA,
    RANCHERA
};
QString enumToString(Genero genre);



class GeneroMusical
{
public:
    GeneroMusical(); // Constructor
    GeneroMusical(Genero genre); // Constructor with parameter
    Genero getGenero() const; // Getter function
    void setGenero(Genero genre); // Setter function

private:
    Genero m_genre; // Member variable to store the genre
};

#endif // GENERO_H

