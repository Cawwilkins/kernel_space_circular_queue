## INFO
This project was from one of my classes that is now being repurposed for my portfolio. 

## Project Description
This project is an implementation of a kernel-space circular queue. It implements 4 syscalls: init,
free, dequeue, and enqueue to expose the queue to the user-space. It is a newly compiled kernel with
the calls now acessible. 

## How to Configure, Compile, and Install the Custom Kernel
1. Make new folder to place files (mkdir /usr/src/project2) 
2. Run git clone git@github.com:Cawwilkins/kernel_space_circular_queue.git
3. Set Extraversion in Makefile at root of repository
4. If havent already, run make mrproper and make xconfig
5. Run make bindeb-pkg -j$(nproc)
6. Go up one folder
7. Run Sudo dpkg -i {highestNumberCustomDebFile}.deb
8. Restart machine and select kernel version with earlier set Extraversion
9. Kernel is now installed!

## How to Compile and Run the Proof-of-Concept Userspace Program
1. If havent already, run make mrproper and make xconfig
2. Run make bindeb-pkg -j$(nproc)
3. Go up one folder
4. Run Sudo dpkg -i {highestNumberCustomDebFile}.deb
5. Restart machine and select kernel version with earlier set Extraversion
6. Navigate to root of repository, open code tests, and run make build_poc
7. Run make run to run the proof of concept

## How to Compile and Run the Testing Suite Userspace Program
1. If havent already, run make mrproper and make xconfig
2. Run make bindeb-pkg -j$(nproc)
3. Go up one folder
4. Run Sudo dpkg -i {highestNumberCustomDebFile}.deb
5. Restart machine and select kernel version with earlier set Extraversion
6. Navigate to root of repository, open code tests, and run make build_test
7. Run make run_t to run test suite

## Known Project Issues
1. None known

## LLM/AI Prompts Used
1. Does valgrind work on kernel space stuff? : I was getting a lot of errors trying to use valgrind
2. Please give a yes or no, is it possible to fail to allocate memory space without running out of memory space: I was trying to determine if it was possible to actually test ENOMEM or if it was a function that required running out of memory space

## Sources Used
1. https://www.geeksforgeeks.org/cpp/how-to-use-errno-in-cpp/
2. https://www.geeksforgeeks.org/dsa/queue-data-structure/
3. https://www.geeksforgeeks.org/c/print-an-integer-value-in-c/
