# Round_Robin_algorithm
simulation of round robin algorithm

      -- The following information has been collected from the web -- 

  Round-robin (RR):
  is one of the algorithms employed by process and network schedulers in computing. As the
  term is generally used, time slices are assigned to each process in equal portions and in
  circular order, handling all processes without priority (also known as cyclic executive).
  
  Round-robin scheduling is simple, easy to implement . round-robin scheduling can also be
  applied to other scheduling problems, such as data packet scheduling in computer networks.
  It is an Operating System concept.
  
  The name of the algorithm comes from the round-robin principle known from other fields,
  where each person takes an equal share of something in turn.
  
  Each process gets a small unit of CPU time (time quantum q), usually 10-100 milliseconds. After
  this time has elapsed, the process is preempted and added to the end of the ready queue.
  
    •  If there are n processes in the ready queue and the time quantum is q, then each process
    gets 1/n of the CPU time in chunks of at most q time units at once. No process waits more
    than (n-1)q time units.
    •  Timer interrupts every quantum to schedule next process
    •  Performance
    •  q large  FIFO
    •  q small  q must be large with respect to context switch,
       otherwise overhead is too high
