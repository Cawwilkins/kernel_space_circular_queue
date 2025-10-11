## Student Information
- Name: Christian Wilkins
- Email: cwilkin2@umbc.edu
- Student ID: VA96371
- Class Section: 03-LEC (1317)

## Project Description
This project is an implementation of a kernel-space circular queue. It implements 4 syscalls: init,
free, dequeue, and enqueue to expose the queue to the user-space. It is a newly compiled kernel with
the calls now acessible. 

## How to Configure, Compile, and Install the Custom Kernel
1. Make new folder to place files (mkdir /usr/src/project2) 
2. Run git clone git@github.com:UMBC-CMSC421/project2-fa25-Cawwilkins.git
3. Set Extraversion in Makefile at root of repository
4. If havent already, run make mrproper and make xconfig
5. Run curl https://userpages.cs.umbc.edu/lsebald1/cmsc421-fa2022/dotconfig > ./.config, to speed up process
6. Run make bindeb-pkg -j$(nproc)
7. Go up one folder
8. Run Sudo dpkg -i {highestNumberCustomDebFile}.deb
9. Restart machine and select kernel version with earlier set Extraversion
10. Kernel is now installed!

## How to Compile and Run the Proof-of-Concept Userspace Program
1. If havent already, run make mrproper and make xconfig
2. Run curl https://userpages.cs.umbc.edu/lsebald1/cmsc421-fa2022/dotconfig > ./.config, to speed up process
3. Run make bindeb-pkg -j$(nproc)
4. Go up one folder
5. Run Sudo dpkg -i {highestNumberCustomDebFile}.deb
6. Restart machine and select kernel version with earlier set Extraversion
7. Navigate to root of repository, open code tests, and run make build_poc
8. Run make run to run the proof of concept

## How to Compile and Run the Testing Suite Userspace Program
1. If havent already, run make mrproper and make xconfig
2. Run curl https://userpages.cs.umbc.edu/lsebald1/cmsc421-fa2022/dotconfig > ./.config, to speed up process
3. Run make bindeb-pkg -j$(nproc)
4. Go up one folder
5. Run Sudo dpkg -i {highestNumberCustomDebFile}.deb
6. Restart machine and select kernel version with earlier set Extraversion
7. Navigate to root of repository, open code tests, and run make build_test
8. Run make run_t to run test suite

## Known Project Issues
1. None known

## LLM/AI Prompts Used
1. Does valgrind work on kernel space stuff? : I was getting a lot of errors trying to use valgrind
2. Please give a yes or no, is it possible to fail to allocate memory space without running out of memory space: I was trying to determine if it was possible to actually test ENOMEM or if it was a function that required running out of memory space

## Sources Used
1. https://docs.google.com/document/d/1dOhc2yvjjMMYqlr0C8pn4-uoVtVkl8C9z4rWkLYBnH0/edit?tab=t.0
2. https://docs.google.com/document/d/1eglPOdldJ3fYfZK5inA-YM2oR-mtGVco/edit#heading=h.9wcrycb9i6ic
3. https://www.geeksforgeeks.org/cpp/how-to-use-errno-in-cpp/
4. https://docs.google.com/document/d/1qxkPMTcp0S3EkQVdCQk_y_mLGqGsd8H(/edit?rtpof=true#heading=h.2d2yafn80qhg
5. https://www.geeksforgeeks.org/dsa/queue-data-structure/
6. https://www.geeksforgeeks.org/c/print-an-integer-value-in-c/
