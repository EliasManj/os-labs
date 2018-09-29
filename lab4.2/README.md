### The Dining Philosophers Problem

Philosophers alternate between thinking and eating.
To simulate both activities, have the thread sleep for a random period between
one and three seconds. When a philosopher wishes to eat, she invokes the
function

`pickup_forks(int philosopher_number)`

where `philosopher_number` identifies the number of the philosopher wishing
to eat. When a philosopher finishes eating, she invokes

`return_forks(int philosopher_number)`
