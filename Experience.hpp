#ifndef EXPERIENCE_H
#define EXPERIENCE_H

/*
ADDING 
STATE
ACTION
REWARD
NEXT STATE

-------------
HOW CAN I USE HASHMAP FOR DOING THING.
WAIT. I CAN USE HASHMAP FOR STORING AND RETERIVING THE `Experience` RIGHT?

***FIGURE THIS OUT!!!
*/

struct Experience {
    int id;          // Unique identifier for the experience
    float tdError;   // Temporal Difference error

    // additional fields such as state, action, reward, next state might get added in next version.
    // we will look into that later on.
};

#endif 
