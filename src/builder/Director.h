#ifndef DIRECTOR_H
#define DIRECTOR_H

class Computer;

class Director {
public:
    Computer* buildGamingPC();
    Computer* buildWorkstation();
    Computer* buildServer();
};

#endif