The level file will be read as shown below.
the first item is the type of event, followed by the timer
and how many enemies at that specific time. the next lines
show the type of the enemy and the position on the screen.

There are two types of event:
    TIMED_EVENT which sends the enemies at a specific time
    CLEAR_EVENT which sends the enemies when all the enemies
that are currently on the screen get killed. (Note that when
this type of event is found, 'seconds' is not read)

The last line tells the name of the file of the next level to 
be executed. If this last line is excluded (e.g. if no next
level is specified), then this will be the final level.



TIMED_EVENT 30 2
    DummyShip 40
    DummyShip 45

CLEAR_EVENT 3
    ZigZagShip 10
    DummyShip 15
    ZigZagShip 20

CLEAR_EVENT 1
    SpawnerShip 100

level2.lvl
