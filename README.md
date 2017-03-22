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

  

# Compilation and Usage 


 To download > open terminal :
 
    cd ~/Desktop
    git clone https://github.com/momaiaz/Round_Robin_algorithm.git

 Compilers recommended :
   - Linux: g++4.8

   - Not tested on windwos but supposed to work
   
   
 compilation steps : 
  
    cd Round_Robin_algorithm/
    g++ -std=c++11 -o RoundRobin.out RoundRobin.cpp
 
 now we have a file called "RoundRobin.out" which is the executive program .
 run program using this pattern
 
     ./RoundRobin.out <input.text> <output.text>
   
- <input.text>     file contain process information   
- <output.text>      file target which is store output ... It will appear on the screen as well
      
input file format:
      
      <processName>$<arival_time>$<burst_time>
      
  Example : 

      p1$0$27
      p2$1$7
      p3$2$10
      p5$5$20
      p4$300$6
 
run ?

    ======================
    Process name: cal
    Process arrival time: 0
    Process burst time: 27
    ======================
    ======================
    Process name: office
    Process arrival time: 2
    Process burst time: 7
    ======================
    ======================
    Process name: media
    Process arrival time: 60
    Process burst time: 10
    ======================

    Enter quantum time : 3

    |0==[cal]==3||3==[office]==6||6==[cal]==9||9==[office]==12||12==[cal]==15|
    |15==[office]==16||16==[cal]==19||19==[cal]==22||22==[cal]==25||25==[cal]==28|
    |28==[cal]==31||31==[cal]==34||34==[idle]==60||60==[media]==63||63==[media]==66|
    |66==[media]==69||69==[media]==70|

    Average Turn Time = 19.3333
    Average WaitingTime = 4.66667
