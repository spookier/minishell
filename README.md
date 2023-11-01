# minishell
#### minishell is a minimalist shell implementation in C
This project aims to create a simple UNIX shell from scratch to deepen the understanding of system calls, processes, and signals among other system level programming concepts

The creation of minishell was a journey filled with challenges, learning, and growth...  
The project demanded a deep dive into the underpinnings of UNIX systems and an understanding of how shells operate at a fundamental level  

Due to the level of complexity of this project, this project was coded along with [@sleepychloe](https://github.com/sleepychloe)

## Features
- Basic shell functionality: executing commands, navigating directories
- Built-in commands: echo, cd, pwd, export, unset, env, exit
- Command history and line editing capabilities
- Signal handling for CTRL+C, CTRL+D and CTRL+\

## Installation
Clone the repository and compile the project using `make`:
```bash
git clone https://github.com/spookier/minishell.git
cd minishell
make
```
This will create an executable named minishell

## Usage
Launch the shell by executing the minishell binary:

```bash
./minishell
```
Now you can start entering commands. To exit the shell, use the exit command or press CTRL+D

![image](https://github.com/spookier/minishell/assets/77325667/aea12041-d081-49d6-9750-72792e6cb4c1)
