#include "nsh.h"

using namespace std;

string dir;
vector<Process *> running;
vector<Process *> finished;
int runningJobs = 0;
int jobCount    = 1;
string home_dir;
string input;

/*---------- Process Constructors ----------*/
Process::Process(pid_t p, int job, vector<string> c, bool pi)
{
    pid = p;
    jobnum = job;
    command = c;
    pipe = pi;
}

Process::Process() { }

/*---------- Process Getter/Setter Commands ----------*/
pid_t Process::get_pid()
{
    return pid;
}

int Process::get_job_num()
{
    return jobnum;
}

vector<string> Process::get_command()
{
    return command;
}

bool Process::get_pipe()
{
    return pipe;
}

void Process::set_values(pid_t p, int job, vector<string> c)
{
    pid = p;
    jobnum = job;
    command = c;
}

void Process::set_pid(pid_t p)
{
    pid = p;
}

void Process::set_job_num(int job)
{
    jobnum = job;
}

void Process::set_command(vector<string> c)
{
    command = c;
}

void Process::set_pipe(bool p)
{
    pipe = p;
}

void Process::print()
{
    cout << "pid: " << get_pid() << endl;
    vector<string> c = get_command();
    cout << "command: ";
    for (auto it = command.begin(); it < command.end(); ++it)
    {
        if (it == command.begin()) cout << "[|" << *it << "|]"; 
        else cout << "[" << *it << "]";
    }
    cout << endl;
    cout << "job num: " << get_job_num() << endl;
    if (get_pipe()) cout << "pipe : true" << endl;
    else cout << "pipe : false" << endl;
}
/*---------- End Process Class Commands ----------*/


/** start_process -- Starts a process and executes the fork call
 * 
 * @param: n      -- a pointer to the process to start
 * @param: jobnum -- the job number of this process
 * @param: status -- a reference variable to the parent process
 * 
 * @returns: none
 * */
void start_process(Process * n, int jobnum, int& status)
{
    vector<string> command = n->get_command();
    pid_t id;

    if (!command.at(0).compare("clr"))
    {
        vector<string> clear;
        clear.push_back("clear");
        command = clear;
    }
    else if (!command.at(0).compare("exit") || !command.at(0).compare("quit"))
    {
        exit(0);
    }
    else if (!command.at(0).compare("cd"))
    {
        status = CD;
        int cd;
        if (command.size() != 2)
        {
            cd = chdir(home_dir.c_str());
            if (cd < 0)
            {
                cout << "Error: Error moving to home directory: " << home_dir << endl;
                exit(1);
            }
        }
        else 
        {
            cd = chdir(command[1].c_str());
            if (cd < 0)
            {
                cout << "Error: No such file or directory." << endl;
            }
        }
        return;
    }
    else if (!command.at(0).compare("help"))
    {
        // Needs to be done with piping. Just exec the bash command "help | more"
    }
    else if (!command.at(0).compare("pause"))
    {
        string in;
        getline(cin, in);
        status = PAUSE;
        return;
    }
    else if (!command.at(0).compare("environ"))
    {
        // print list of environment variables?
        status = ENVIRON;
        return;
    }
    else if (!command.at(0).compare("ll"))
    {
        vector<string> c;
        c.push_back("ls");
        c.push_back("-al");
        command = c;
    }
    id = fork();
    if (id < 0)
    {
        cout << "Error: could not create child process." << endl;
        exit(1);
    }
    n->set_values(id, jobnum, command);
}

/** kill_process -- Helper method to kill a process and delete it's memory.
 * 
 * @param: p -- pointer to the process to kill and delete
 * 
 * @returns: int indicating the status of killed process
 * */
int kill_process(Process * p)
{
    if (kill(p->get_pid(), SIGKILL))
    {
        // The process has been killed, free the memory and return 0
        delete(p);
        return 0;
    }
    // Error killing process
    else return 1;
}

/** parse_input -- Parses the input and breaks it down into a vector of strings
 * 
 * @param: input      -- input string to be parsed
 * @param: background -- reference boolean, indicates if this should is a background call
 * 
 * @returns: vector of empty process pointers with filled in commands from input
 * */
vector<Process *> parse_input(string input, bool& background)
{
    vector<Process *> out;
    vector<string> command;
    
    if (input.at(input.size()-1) == '&')
    {
        background = true;
        input.pop_back();
    }
    string token = "";
    for (size_t i = 0; i < input.size(); i++)
    {
        if (input.at(i) != ' ')
        {
            if (input.at(i) == ';')
            {
                if (!token.empty())
                {
                    command.push_back(token);
                    token = "";

                    Process * p = new Process(0, 0, command, false);
                    command.clear();
                    out.push_back(p);
                }
            }
            else if(input.at(i) == '|')
            {
                if (!token.empty())
                {
                    command.push_back(token);
                    token = "";
                }
                Process * p = new Process(0, 0, command, true);
                command.clear();
                out.push_back(p);
            }
            else token.push_back(input.at(i));
        }
        else
        {
            // we have a new token. Check that it isn't empty (double space)
            if (!token.empty())
            {
                command.push_back(token);
                token = "";
            }
        }
    }
    if (!token.empty()) command.push_back(token);
    // Create the last command (first if no ';')
    Process * p = new Process(0, 0, command, false);
    out.push_back(p);
    command.clear();

    return out;
}

/** execute_process -- Helper method that calls exec() on the Process command.
 * 
 * @param: p -- pointer to Process to execute
 * 
 * @returns: none
 * */
void execute_process(Process * p)
{
    vector<char *> command;
    for(size_t i = 0; i < p->get_command().size(); i++)
    {
        command.push_back((char*) p->get_command()[i].c_str());
    }
    command.push_back(NULL);

    char ** args = &command[0];
    execvp(args[0], args);
    cerr << "process executed successfully." << endl;
}

void run_pipe(Process * p, int inFd, int outFd)
{
    pid_t pid = fork();
    if (pid < 0)
    {
        cerr << "Error creating fork. Exiting." << endl;
        exit(1);
    }
    p->set_pid(pid);
    // sub child
    if (pid == 0)
    {
        if (inFd != 0)
        {
            dup2(inFd, 0);
            close(inFd);
        }
        execute_process(p);
    }
    // main child
    else
    {
        waitpid(pid, 0, 0);
    }
}

void handle_pipe(Process * c, vector<Process *> p)
{
    int fd[2];
    pipe(fd);
    int out = 1;

    if (fd[1] != 1)
    {
        dup2(fd[1], 1);
        close(fd[1]);
    }

    execute_process(c);
    for (size_t i = 0; i < p.size(); i++)
    {
        run_pipe(p[i], fd[0], out);
    }
    close(fd[1]);
    close(fd[0]);
}

/** kill_shell -- Clean-Up command. Kills all old processes, and deletes process memory space.
 * 
 * @param: none
 * 
 * @returns: none
 * */
void kill_shell()
{
    for (size_t i = 0; i < running.size(); i++)
    {
        if (kill_process(running[i]))
        {
            delete(running[i]);
        }
    }
    running.clear();

    for (size_t i = 0; i < finished.size(); i++)
    {
        if (kill_process(finished[i]))
        {
            delete(finished[i]);
        }
    }
    finished.clear();
}


/**
 * Note: To run a new process, we want to call exec(), this allows us to run other c code from this program.
 *       So say we want to run neofetch, we would call exec(neofetch, args). Fork just creates a new child
 *       process, where exec actually runs the code that the user specified.
 * 
 * General Idea:
 *      while (1)
 *      {
 *          display prompt on screen
 *          read command from terminal with params
 *          if (fork() != 0) parent
 *              wait (NULL)  wait for child
 *          else execve(command, params, 0) execute the command
 *      }
 */


int main(int argc, char *argv[])
{
    // Trigger for getting home directory
    int trigger = 1;

    pid_t parent_id = getpid();

    // Outer loop
    while (true)
    {
        char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            dir = cwd;
            if (trigger)
            {
                home_dir = dir;
                trigger = 0;
            }
        }
        else 
        {
            cout << "Error reading directory." << endl;
            exit(1);
        }

        cout << "nsh-:" << dir << endl << "-$ ";
        getline(cin, input);
        bool background = false;
        vector<string> command;
        vector<Process *> processes;

        if (input.empty()) goto fin;

        processes = parse_input(input, background);
        
        // Loop through all processes picked up from the input
        for (size_t i = 0; i < processes.size(); i++)
        {
            int status = 0; // running normally
            Process * child = processes[i];
            vector<Process *> pipes;

            start_process(child, jobCount++, status);

            // Parent
            if (getpid() == parent_id)
            {
                if (status) goto fin;
                running.push_back(child);

                //cout << "Child process created with pid: " << child->get_pid() << endl;
                if (!background)
                {
                    // wait for child to finish
                    waitpid(child->get_pid(), 0, 0);
                    running.pop_back();
                    finished.push_back(child);
                }
                else cout << "Process started with id: " << child->get_pid() << endl;
                //cout << "\nChild process finished." << endl;
            }

            // Current Child
            if (child->get_pid() == 0)
            {
                //cout << "Child Process running....\n" << endl;
                if (child->get_pipe())
                {
                    handle_pipe(child, pipes);
                }
                else execute_process(child);
                
                // close this process
                exit(0);
            }
        }

        // exit point for skipping processing and fork
        fin:;
    }

    // Cleanup
    kill_shell();

    return 0;
}