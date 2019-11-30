#ifndef NSH_H
 #define NSH_H

#include <iostream>
#include <vector>
#include <sstream>
#include <limits.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define CD      1
#define HELP    2
#define PAUSE   3
#define ENVIRON 4


class Process
{
    private:
        pid_t                        pid;
        int                       jobnum;
        std::vector<std::string> command;
        bool                        pipe;

    public:
        Process();
        Process(pid_t, int, std::vector<std::string>, bool);
        pid_t get_pid();
        int get_job_num();
        std::vector<std::string> get_command();
        bool get_pipe();
        void set_values(pid_t, int, std::vector<std::string>);
        void set_pipe(bool);
        void set_pid(pid_t);
        void set_job_num(int);
        void set_command(std::vector<std::string>);
        void print();
};



std::vector<Process *> parse_input(std::string input, bool& background);
void start_process(Process * n, std::vector<std::string> command, int jobnum, int& status);
int kill_process(Process * p);
void execute_process(Process * p);

#endif