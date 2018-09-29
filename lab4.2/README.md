### The Dining Philosophers Problem

Philosophers alternate between thinking and eating.
To simulate both activities, have the thread sleep for a random period between
one and three seconds. When a philosopher wishes to eat, she invokes the
function

`pickup forks(int philosopher number)`

where `philosopher number` identifies the number of the philosopher wishing
to eat. When a philosopher finishes eating, she invokes

`return forks(int philosopher number)`
