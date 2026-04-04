*This project has been created as part of the 42 curriculum by lalkhati, malsabah.*

# Description
### **Minishell** is a miniature version of bash, meant to immitate the original as closely as possible. The following features are included:-
1. Pipes
2. Redirections ['>', '<', '>>', '<<']
3. Environment variables [$HOME, $USER, $CUSTOM, etc]
4. Singals: SIGINT [CTRL^C], SIGQUIT [CTRL^\\] (does nothing),  & EOF: [CTRL D] 
5. Exit satus symbol: $? & tilde expression: ~
6. Builtins: 
    - **cd**
    - **pwd**
    - **exit**
    - **export**
    - **echo** with option -n
    - **unset**
    - **env**

# Instructions
### run the following:
``` bash
make
./minishell
```

# Resources

### [GNU Bash Manual](https://www.gnu.org/software/bash/manual/bash.html)

### [Minishell: Building a mini-bash by zlaarous](https://medium.com/@zouhairlrs/minishell-building-a-mini-bash-a-42-project-5dc20d671fbb)

### [Minishell: Building a mini-bash by MannBell](https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218)

### [Project: 42-minishell by multitudes & ProjektPhoenix ](https://multitudes.github.io/42-minishell/)

### [man7.org by Michael Kerrisk](https://www.man7.org/linux/man-pages/index.html)

### [Bash Redirection Explained With Examples by revWhiteShadow](https://itsfoss.gitlab.io/post/bash-redirection-explained-with-examples/)

### [What happens when you type a command in the terminal?](https://www.youtube.com/watch?v=EEvY9pptM5Q)

### [**LINUX.ORG** BASH 03 – Command-line Processing by Jarret B](https://www.linux.org/threads/bash-03-%E2%80%93-command-line-processing.38676/)

### AI

**We used AI in the following ways:**

- **Roadmap planning**
Exploring possible roadmaps to follow and what phases it includes in order to have a fairly structured end product.

- **Bash behavior calrification:** 
Asking for explanation for unexpected behavior by bash and why certain features exist (e.g. cd //).

- **Getting feedback for implementation logic**
Asking if my code encompasses all possible cases and behaviors of the original.

- **Possible Edge-cases for testing**
Identifying tricky cases for testing correctness.

- **Help debugging**
Help with spotting tricky logical errors and exploring possible explanation for unexpected behavior.
