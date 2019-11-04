* Processes: 
    * Organisms:
        * Operating Thread
            * Waits on Environments food lock, then get's a food 
        * Hunger Thread
            * Waits a random period of time, then consumes a food or kills the organism
    * Environment:
        * Does nothing?

* Structures:
    * Environment:
        * Keeps track of everything
        * Makes food (only makes one at a time)
    * Food:
        * Just a unique token
    * Organism:
        * Acquires food, occasionally consumes it or dies if it cannot
        * Keeps track of information for the threads piloting an Organism
            * Operating Thread
            * Hunger Thread
        * A flag for whether the Organism has died


* Locks: 
    * Log lock
        * Owned by the Environment
        * Acquire the lock to write to the log
    * Food lock
        * Owned by the Environment
        * Acquire the lock to get some food
    * Orgmap lock
        * Owned by the Environment
        * Acquire when adding/removing organisms to environment
    * Organism lock
        * Owned by the organism
        * Each Organism has its own lock to be used while reading/writing the organisms state
        * Organism lock **must** be released before waiting on global locks (this is necessary so that the hunger thread can kill an Organism while it waits for food)
        * Upon acquiring the Organism lock, one must check if the Organism is still alive before doing anything else

* When the Organism dies, remove it from the Environment, but don't destroy it until all threads have finished.
