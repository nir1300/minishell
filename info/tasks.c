nina: execution, builtins, expansion

1. expansion
    handle variable expansion
    handle $?
    potential errors: 

2. execution
    execute commands
    handle redirections and fds
    builtins: should run in parent process
    potential errors: command not found, permission denied, file not found,... 

to-do:
fix pipex -> should only wait for last child to finish
fix pipex -> do not create all pipes at once -> can limit number of available fds with "ulimit -n 10"
sleep 10 | sleep 2 should take 2 seconds -> takes 10 right now
handle >> in append mode
handle heredoc (<<)
builtins in parent process (echo -n, cd, pwd, export, unset, env, exit)
save environmental variables somewhere even if path is destroyed

to-do 11/2:
heredoc
>> in append mode
