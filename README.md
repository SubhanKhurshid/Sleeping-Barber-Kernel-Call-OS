# Project Report Operating System 
## Project Title
### Sleeping Barber System Call
## Group Members
### Subhan Khurshid  - 21k-3096
### Ruhama Umer Khan - 21k-3097

## Overview
The Sleeping Barber Problem is a classic synchronization problem in Operating Systems, which deals with managing resources in a multi-process environment. The problem involves a barber shop that has one barber and a limited number of chairs for customers to wait in line. The barber alternates between sleeping in the back room and cutting hair in the barber chair, while customers arrive and take a seat in one of the chairs if they are available. If there are no available chairs, they leave and come back later.

## Objective
The objective of this project is to implement the Sleeping Barber Problem using system calls in an operating system. Through this project, we aim to gain a practical understanding of synchronization mechanisms and system calls in operating systems. Additionally, we will learn about the challenges involved in developing concurrent programs and how to overcome them

## Implementation 
We have used ubuntu 16.04.7 for the implementation of this project.

## Prerequisites
• sudo apt-get install gcc
• sudo apt-get install libncurses5-dev
• sudo apt-get install bison
• sudo apt-get install flex
• sudo apt install make
• sudo apt-get install libssl-dev
• sudo apt-get install libelf-dev
• sudo add-apt-repository "deb http://archive.ubuntu.com/ubuntu $(lsb_release -sc) main
universe"
• sudo apt-get update
• sudo apt-get upgrade

## Steps
### 1. Acquiring the Kernel
To begin, we need to obtain a kernel from kernel.org. There are two ways to do this: either through the "wget" command or manually by selecting the "tarball" option and downloading it.

### 2. Extracting The Kernel
Similarly, to extract the downloaded kernel, navigate to the directory where it is saved and use the command "tar -xvf filename" or extract it by right-clicking on the file and selecting the "extract to" option.

### 3. Creating a New Directory named hello1
Navigate to the directory where the kernel was extracted, and then enter into the kernel's folder. Now, create a new directory by either using the terminal and executing the command "mkdir folder name" or by right-clicking and selecting the "New Folder" option.

### 4. Adding a Sleeping Barber C code for the system call
Now, go to the folder which we created just now and open the terminal there and create a
new C code file by typing “gedit code.c” and paste the following code there:

### 5. Creating a Make File for the C code
To create a Makefile for our new folder, we need to follow a few steps. Firstly, we need to open the terminal and navigate to our new folder by using the 'cd' command. Once we are in the new folder, we can create a new file called 'Makefile' using the command "touch Makefile". Then, we need to open this file using a text editor such as nano or gedit by typing "nano Makefile" or "gedit Makefile" respectively.

In the Makefile, we need to specify the object file that needs to be compiled. We do this by using the "obj-y" flag, followed by the name of our object file, which in this case is "hello1.o". The final line in the Makefile should look like this:

obj-y := code.o

Once we have entered this information into the Makefile, we can save and exit the file. This Makefile will ensure that our C code is always compiled whenever the kernel is compiled.

<img width="343" alt="makeFile" src="https://github.com/SubhanKhurshid/ProjectOs/assets/105592966/11159af5-5f12-4825-a02c-69900efd37b3">



### 6. Adding the new code into the system table file 
Since we are creating a 64-bit system call according to our system we have to add the
system call entry into the syscall_64.tbl file which keeps the name of all the system calls in
our system. If our system was a 32-bit system, we would have to add our system call into
syscall_32.tbl (We can check the type of our system by typing “uname -m” in a terminal).
This tbl file is located inside the kernel folder in /arch/x86/entry/syscalls/syscall_64.tbl. We
can go into this directory by using cd and then edit the file by typing “gedit syscall_64.tbl”


<img width="352" alt="table" src="https://github.com/SubhanKhurshid/ProjectOs/assets/105592966/616c33c2-fdda-4251-a4e1-d942a3b83da3">


### 7. Adding The Prototype Of New System Call
Now we have to add the prototype of our system call in the system’s header file which is
located in the kernel folder then “/include/linux/syscalls.h”. We have to add the prototype
of our system call function in this file.

<img width="243" alt="include" src="https://github.com/SubhanKhurshid/ProjectOs/assets/105592966/6fc9c747-1054-419c-a4b6-9a6957656cbd">



### 8. Adding Code Folder in kernel's MakeFile
Now, we have to add our roll number in the extraversion of the kernel’s make file and we
have to add the new module that we created into our kernel’s make file. For this, we open
the Makefile of the kernel and search for “core-y” and go to it’s second instance which is
under “KBUILD_EXTMOD” and add our new module which is “hello1” at the end of it. At the
end, our make file will look something like this


<img width="389" alt="make2" src="https://github.com/SubhanKhurshid/ProjectOs/assets/105592966/adbacf42-61b9-4fca-b452-90be21c30fda">


### 8. Config File Creation
Now we have to create a config file for our kernel. The order of the steps before this can
change but the order of this step and the steps coming right after it can’t change. We can
either create a Menuconfig or simply copy the oldconfig. I will be copying the oldconfig and
using that config for my new kernel. First of all, we search for the config that we currently
have by typing “ls /boot | grep config” and the we copy the config that is shown to us by
typing “cp /boot/config-4.15.0-112-generic *our linux kernel directory*”. Then we create the
old config by typing “yes "" | make oldconfig -j2”, by doing so, the system will automatically
create the new config for us and select the default option for everything. 


<img width="299" alt="config1" src="https://github.com/SubhanKhurshid/ProjectOs/assets/105592966/d77ae803-ce93-4469-9301-6e03ee69df9a">


 ### 9. Cleaning and Compiling The Kernel
 We have to clean all of our existing object and executable file because compiler sometimes
link or compile files incorrectly and to avoid this, we delete all of our old object and
executable files by typing “make clean -j2” (It is better to switch to super user mode by
typing “sudo su” before running the commands after this) and when this all is done, we type
“make -j2” to start building our kernel (-j2 allocates the multiple cores that our system have
for compiling. If we don’t do this, the system will only use a single core for compiling the 
kernel which is rather slow. Adding -j2 will increase the speed of our compiling by almost 2
times. Note that 2 is the number of Cores that I have in my Laptop. You can check your
number of cores by typing the command “lscpu” and enter the number accordingly)
Now we have to wait until our Kernel image is built and ready. If we see “Kernel image is
ready” when the command is done executing, that means that our kernel image is ready to
be installed


<img width="274" alt="make1" src="https://github.com/SubhanKhurshid/ProjectOs/assets/105592966/460995c6-7c48-4f1b-9b2d-c718e86f8ddd">
<img width="363" alt="make2" src="https://github.com/SubhanKhurshid/ProjectOs/assets/105592966/6c882d26-f955-4e5f-bb27-d57bb1f4e7b8">


### 10. Installing modules
Now we have to install the kernel that we built by typing “make modules_install install”
which will install the kernel and update our grub as well. When this all is done and the
terminal says “done”, then we can restart our laptop either manually or by typing
“shutdown -r now” and hold the “Shift” key while it is restarting to open up the grub menu
and switch to the new kernel which we just installed.

### 11. Check if the system is working properly
After logging into the newly compiled kernel, we check the system call by making a C code
named “userspace.c” and putting the following code in it:
#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
int main()
{
 long int i = syscall(335);
 printf("System call sys_SleepingBarber returned %ld\n", i);
 return 0;
}
Now we compile the code by typing “gcc userspace.c” and executing it by typing “./a.out”. If
it returns 0, this means that our code has compiled successfully

<img width="146" alt="project1" src="https://github.com/SubhanKhurshid/ProjectOs/assets/105592966/cb052153-6d64-4097-b683-c9c43c52ad0b">


### SCREENSHOT OF THE OUTPUT:


<img width="209" alt="project2" src="https://github.com/SubhanKhurshid/ProjectOs/assets/105592966/ed5710f6-df7a-4ef9-92be-f278525e2edd">






