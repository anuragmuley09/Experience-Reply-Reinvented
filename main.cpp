#include "BST.hpp"
#include "Logger.hpp"
#include "Experience.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

// Lightweight busy wait function to simulate delay without high CPU usage
// cause for some reason my g++ isnt upto date.
// thus for simualiting "thread" functionality im using this "busywait" function
// mannn i need to update my g++!
void lightBusyWait(int ms) {
    // Lower iteration count per ms to reduce CPU burn
    const int iterationsPerMs = 10000;  // Adjust as needed
    for (int m = 0; m < ms; ++m) {
        for (volatile int i = 0; i < iterationsPerMs; ++i) {
            // Small delay per ms
        }
    }
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    BST replayBuffer;

    // Simulate insertion of experiences into the replay buffer.
    for (int i = 0; i < 10; ++i) {
        // Simulate a TD error between 0 and 1.
        float tdError = static_cast<float>(std::rand()) / RAND_MAX;
        Experience exp = { i, tdError };
        replayBuffer.insert(exp);

        // Log current highest-priority experience after each insertion.
        const Experience* highPriority = replayBuffer.getHighestPriority();
        if (highPriority) {
            Logger::log("Current highest TD error experience: id " +
                        std::to_string(highPriority->id) +
                        " with TD error " + std::to_string(highPriority->tdError));
        }

        // Use lightweight busy wait for approx 300ms
        lightBusyWait(300);
    }

    // Visualize the entire BST state.
    replayBuffer.inOrderTraversal();
    replayBuffer.printHashMap();      
    replayBuffer.printQueue();

    // Example update (simulate learning update that changes the TD error)
    replayBuffer.update(5, 0.95f);

    // Final visualization after update.
    replayBuffer.inOrderTraversal();
    // replayBuffer.printHashMap();      
    // replayBuffer.printQueue();


    return 0;
}
